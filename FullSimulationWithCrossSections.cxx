void FullSimulationWithCrossSections()
{
    

    //
    // Gamma beam energy
    //
    Double_t E_beam = 9;
    ifstream file;
    file.open("Gluex_Gamma_Beam.txt");
    TH1F* GammaBeamHist= new TH1F("","", 54, 3.12-0.16/2, 11.76+.16/2);
    Double_t EnergyIterator1, EnergyIterator2;
    int counter = 0;
    for(int i=0;i<54;i++){
        GammaBeamHist->SetBinContent(i+1,0);
    }

    while(! file.eof()){
            file >> EnergyIterator1;
            file >> EnergyIterator2;
            GammaBeamHist->Fill(EnergyIterator1, EnergyIterator2);
    }
    
    
    
    
    
    
    
    
    for(int i=1;i<=54;i++){GammaBeamHist->SetBinError(i,0);}
    GammaBeamHist->Rebin(2);
    
    
    
    //
    //Parametrisation of the gamma+n -> p pi- cross section
    //
//    TF1* F_CrossSection = new TF1("F_CrossSection","(3.81583e+04)/(x**7)",1,15);// gamma+p->pi+ + n  | Hayan + SLAC
    //    TF1* F_CrossSection = new TF1("F_CrossSection","(1.30380e+04)/(x**5.763)",1,15);// gamma+n->pi- + p  | Hayan
    //    TF1* F_CrossSection = new TF1("F_CrossSection","(1.60048e+04)/(x**5.95421)",1,15);// gamma+n->pi- + p  | Hayan - only high s
        TF1* F_CrossSection = new TF1("F_CrossSection","(6.67314e+04)/(x**7)",1,15);// gamma+n->pi- + p  | Hayan - only high s
    
    
    
    
    //
    // Tree to hold (gamma,p pi p) 'SRC' events and extra kinematical variables.
    // Each Event has  forward scatter proton, a pion, and a recoil neutron.
    // The reconstructed initial momentum of the proton knockout of the nucleus is lables as "missing momentum"
    //
    TFile* f = new TFile("FullMC_Gluex_9GeV_test1.root","recreate");
    TTree* T = new TTree("T","T");
    
    Double_t theta_recoil, phi_recoil, Recoil_P;
    Double_t theta_miss, phi_miss, Missing_P;
    Double_t theta_P2, phi_P2, P2;
    Double_t theta_P1, phi_P1, P1;
    Double_t P_1[3], P_2[3];
    Double_t t,u,s;
    Double_t theta_cm;
    Double_t weight;
    Double_t Effective_E;
    Double_t Original_E;
    Double_t gamma_cm;
    Double_t Nucleon_cm;
    
    T->Branch("weight",&weight,"weight/D");                     // Event weight based on cross-section
    T->Branch("theta_cm",&theta_cm,"theta_cm/D");
    T->Branch("Effective_E",&Effective_E,"Effective_E/D");
    T->Branch("Original_E",&Original_E,"Original_E/D");
    
    T->Branch("gamma_cm",&gamma_cm,"gamma_cm/D");               // gamma   energy in the gamma-neutron c.m. frame
    T->Branch("Nucleon_cm",&Nucleon_cm,"Nucleon_cm/D");         // Neutron energy in the gamma-neutron c.m. frame
    
    T->Branch("theta_recoil",&theta_recoil,"theta_recoil/D");   // recoil proton in-plane angle
    T->Branch("phi_recoil",&phi_recoil,"phi_recoil/D");         // recoil proton out-of-plane angle
    T->Branch("P_recoil",&Recoil_P,"P_recoil/D");               // recoil proton momentum vector magnitude
    
    T->Branch("theta_miss",&theta_miss,"theta_miss/D");         // Initial neutron in-plane angle
    T->Branch("phi_miss",&phi_miss,"phi_miss/D");               // Initial neutron out-of-plane angle
    T->Branch("P_miss",&Missing_P,"P_miss/D");                  // Initial neutron momentum vector magnitude
    
    T->Branch("theta_P1",&theta_P1,"theta_P1/D");               // Leading proton in-plane angle
    T->Branch("phi_P1",&phi_P1,"phi_P1/D");                     // Leading proton out-of-plane angle
    T->Branch("P1",&P1,"P1/D");                                 // Leading proton momentum vector magnitude
    
    T->Branch("theta_P2",&theta_P2,"theta_P2/D");               // Leading pion in-plane angle
    T->Branch("phi_P2",&phi_P2,"phi_P2/D");                     // Leading pion out-of-plane angle
    T->Branch("P2",&P2,"P2/D");                                 // Leading pion momentum vector magnitude
    
    
    // Final 3-momentum vector for the scattered protons in the lab
    T->Branch("P_1",&P_1,"P_1[3]/D");
    T->Branch("P_2",&P_2,"P_2[3]/D");
    
    T->Branch("t",&t,"t/D");
    T->Branch("u",&u,"u/D");
    T->Branch("s",&s,"s/D");
    
    
    
    
    
    //
    // Parametrization of the momentum distribution for nucleons in a nucleus (including SRC nucleons)
    //
    TF1* SRCtail = new TF1("SRCtail","1/(x**4)",0.25,0.7);
    TF1* n_k     = new TF1("","((x<0.25)?0.8*3/((0.25)**3):0.5*0.2*2.533333/(1./(0.25)-1./5)/(x**4))       ",0,1);
    TF1* n_k_k2  = new TF1("","((x<0.25)?0.8*3/((0.25)**3):0.5*0.2*2.533333/(1./(0.25)-1./5)/(x**4))*(x**2)",0,1);
    
    
    
    
    
    //
    // Parameters to be used for kinematical variables calculation
    //
    Double_t x=0, y=0, z=0;
    Double_t Pcm_x=0, Pcm_y=0, Pcm_z=0;
    Double_t Recoil_x=0, Recoil_y=0, Recoil_z=0;
    Double_t Missing_x=0, Missing_y=0, Missing_z=0;
    Double_t cross_section;
    
    
    
    
    //
    // Events Generation:
    // 1. Raffle a nucleon in the nucleus.
    // 2. If it has high-momentum raffle a correlated partner
    // 3. Boost to the nucleon rest frame
    //
    const int N = 500;
    for(int i=0; i<N; i++){
        
        if(i%(N/100)==0) cout << i/(N/100)<<"%" << endl;
        
        //do{
            E_beam = GammaBeamHist->GetRandom();
	    //}while(E_beam < 7.5);
        Original_E = E_beam;
        
        //
        // Raffle 3-momentum vector for 1st nucleon in the pair.
        //
        Missing_P = n_k_k2->GetRandom();                             // raffle vector magnitude
        gRandom->Sphere(Missing_x,Missing_y,Missing_z, Missing_P);   // smear vector direction
        theta_miss = TMath::ACos(Missing_z/Missing_P)*180/3.14;      // Calculate theta [degrees]
        phi_miss = TMath::ATan2(Missing_y,Missing_x)*180/3.14;       // Calculate phi   [degrees]
        
        //
        // If the nucleon has momentum > kF, create a recoil nucleon
        //
        if(Missing_P > 0.25){
            
            // Raffle SRC-pair C.M. momentum.
            Pcm_x = gRandom->Gaus(0,0.14);
            Pcm_y = gRandom->Gaus(0,0.14);
            Pcm_z = gRandom->Gaus(0,0.14);
            
            // Calculate 3-momentum vector for the 2nd nucleon in the pair.
            Recoil_x = Pcm_x - Missing_x;
            Recoil_y = Pcm_y - Missing_y;
            Recoil_z = Pcm_z - Missing_z;
            Recoil_P = TMath::Sqrt(pow(Recoil_x,2)+pow(Recoil_y,2)+pow(Recoil_z,2));
            theta_recoil = TMath::ACos(Recoil_z/Recoil_P)*180/3.14;
            phi_recoil = TMath::ATan2(Recoil_y,Recoil_x)*180/3.14;
            
        }else{
            Recoil_x = 0;
            Recoil_y = 0;
            Recoil_z = 0;
            Recoil_P = 0;
            theta_recoil = 0;
            phi_recoil = 0;
        }
        
        
        
        //
        // Keep the 4-momentum vector of the beam and nucleon in the lab frame.
        //
        TLorentzVector v1org( TVector3(0,0,E_beam),                               E_beam                   ); // Gamma Beam
        TLorentzVector v2org( TVector3(Missing_x,Missing_y,Missing_z), sqrt(pow(0.938,2)+pow(Missing_P,2)) ); // Missing Momentum ('initial' nucleon in the nucleus)
        
        
        
        // Keep 'lab' 4-momentum for the gamma and nucleon before scattering and boosts.
        TLorentzVector v_beam = v1org;  // Beam Proton
        TLorentzVector v_miss = v2org;  // Missing Momentum ('initial' nucleon in the nucleus)

        
        //
        // Boost to the nucleon rest frame
        // Extracting the 'effective beam momentum' and cross-section.
        // Boost back to the lab
        //
        
        // boost to the SRC nucleon rest frame.
        TLorentzVector m1 = v_miss; //v_miss for for Lorentz Boost
        v_beam.Boost(-m1.BoostVector());
        v_miss.Boost(-m1.BoostVector());
        
        // calculate the 'effective' cross section
        Effective_E = sqrt( pow(v_beam.X(),2)+pow(v_beam.Y(),2)+pow(v_beam.Z(),2) );   // Chech that momentum = energy in the 4-momentum of the gamma after the boost.
        cross_section = F_CrossSection->Eval( Effective_E );

        // boost back to the lab
        v_miss.Boost(m1.BoostVector());
        v_beam.Boost(m1.BoostVector());


        
        //
        // Iterate over c.m. scattering angles.
        //
        for(int k=50;k<=130;k++){
            
             //scattering angle in the c.m.
            theta_cm = k;//20.5+k;
            
            
            // 'initial coditions' - lab frame beam and nucleon.
            v_beam = v1org;
            v_miss = v2org;
            
            
            
            //
            // Calculate scattering in the beam+nucleon c.m. frame
            //
            
            // boost to the c.m. frame. of the beam + SRC nucleon
            TLorentzVector m = (v_beam + v_miss); //C.M. for Lorentz Boost
            v_beam.Boost(-m.BoostVector());
            v_miss.Boost(-m.BoostVector());
            
            // Rotate the vectors in the c.m. to go along the z-axis.
            TVector3 tmp1, tmp2, tmp3, tmp4;
            tmp1.SetXYZ(v_beam.X(),v_beam.Y(),v_beam.Z());
            tmp2.SetXYZ(v_miss.X(),v_miss.Y(),v_miss.Z());

            // save momentum in the c.m. frame
            gamma_cm   = tmp1.Mag();
            Nucleon_cm = tmp2.Mag();
            
            
            Double_t rot_phi     = tmp1.Phi();
            Double_t rot_theta   = tmp1.Theta();
            
            tmp1.RotateZ(-rot_phi);
            tmp1.RotateY(-rot_theta);
            tmp2.RotateZ(-rot_phi);
            tmp2.RotateY(-rot_theta);
            
            /* //test that the boost worked well.
             cout <<"1\t"<< tmp2.Mag() <<"  \t"<< tmp1.Mag() <<"  \t"<< tmp1.Angle(tmp2) << endl;    // verify that after the boost v1 = -v2.
             cout <<"2\t"<< tmp1.z() <<"  \t"<< tmp1.Mag() <<"  \t"<< tmp1.Angle(tmp2) << endl;      // verify that after the boost v1_z = |v1|.
             cout <<"3\t"<< tmp2.z() <<"  \t"<< tmp2.Mag() <<"  \t"<< tmp2.Angle(tmp1) << endl<<endl;// verify that after the boost v2_z = |v2|.
             */
            
            // Define the scattering angle in the c.m.
            Double_t theta_ll=theta_cm*3.14/180;
            Double_t phi_ll = gRandom->Uniform(0,2*3.14);
            
            // Calculate outgoing protons in the scattering reaction
            tmp3.SetXYZ( tmp1.z()*cos(phi_ll)*sin(theta_ll),  tmp1.z()*sin(phi_ll)*sin(theta_ll), tmp1.z()*cos(theta_ll));
            tmp4.SetXYZ(-tmp1.z()*cos(phi_ll)*sin(theta_ll), -tmp1.z()*sin(phi_ll)*sin(theta_ll),-tmp1.z()*cos(theta_ll));
            
            /* //Another validation
             cout <<theta_cm<<endl;
             cout <<"1\t"<< tmp3.Mag() <<"\t"<< tmp4.Mag() <<"\t"<< tmp4.Angle(tmp3)*180/3.14 << endl;    // verify that after the boost v1 = -v2.
             cout <<"2\t"<< tmp3.Mag() <<"\t"<< tmp1.Mag() <<"\t"<< tmp1.Angle(tmp3)*180/3.14 << endl;    // verify that after the boost v1 = -v2.
             cout <<"3\t"<< tmp4.Mag() <<"\t"<< tmp1.Mag() <<"\t"<< tmp1.Angle(tmp4)*180/3.14 << endl;    // verify that after the boost v1 = -v2.
             cout <<"3\t"<< tmp4.Mag() <<"\t"<< tmp2.Mag() <<"\t"<< tmp2.Angle(tmp4)*180/3.14 << endl;    // verify that after the boost v1 = -v2.
             */
            
            // Rotate all back from the z axis in the c.m. frame.
            tmp1.RotateY(rot_theta);
            tmp1.RotateZ(rot_phi);
            tmp2.RotateY(rot_theta);
            tmp2.RotateZ(rot_phi);
            tmp3.RotateY(rot_theta);
            tmp3.RotateZ(rot_phi);
            tmp4.RotateY(rot_theta);
            tmp4.RotateZ(rot_phi);
            
            /*
             //Verify all angles and momenta
             cout <<theta_cm<<endl;
             cout << tmp1.Angle(tmp2)*180/3.14 <<"\t"<< tmp1.Angle(tmp3)*180/3.14 <<"\t"<< tmp1.Angle(tmp4)*180/3.14 <<"\t"<< tmp3.Angle(tmp4)*180/3.14 <<"\t"<< v_beam.E() <<"\t"<< v_miss.E() << endl<<endl;
             */
            
            // Boost back to the lab
            TLorentzVector v3( TVector3(tmp3.x(),tmp3.y(),tmp3.z()), sqrt( pow(tmp3.Mag(),2) + pow(0.140,2) ) );
            TLorentzVector v4( TVector3(tmp4.x(),tmp4.y(),tmp4.z()), sqrt( pow(tmp4.Mag(),2) + pow(0.938,2) ) );
            v3.Boost(m.BoostVector());
            v4.Boost(m.BoostVector());
//            v3.Boost(m1.BoostVector());
//            v4.Boost(m1.BoostVector());
            
            
            
            tmp3.SetXYZ(v3.X(),v3.Y(),v3.Z());
            tmp4.SetXYZ(v4.X(),v4.Y(),v4.Z());
            
            //Verify that all the boost bring back the original vectors in the lab
            //        cout<<v1.X()-v1org.X()<<"\t"<<v1.Y()-v1org.Y()<<"\t"<<v1.Z()-v1org.Z()<<"\t"<<v2.X()-v2org.X()<<"\t"<<v2.Y()-v2org.Y()<<"\t"<<v2.Z()-v2org.Z()<<"\t\t"<<v2.E()-v2org.E()<<"\t\t"<<v1.E()-v1org.E()<< endl;
            
            
            //
            // Keep all kinematical variables
            //
            P_1[0] = tmp3.x();
            P_1[1] = tmp3.y();
            P_1[2] = tmp3.z();
            P_2[0] = tmp4.x();
            P_2[1] = tmp4.y();
            P_2[2] = tmp4.z();
            P1 = tmp3.Mag();
            P2 = tmp4.Mag();
            theta_P1 = TMath::ACos(tmp3.z()/tmp3.Mag())*180/3.14;
            theta_P2 = TMath::ACos(tmp4.z()/tmp4.Mag())*180/3.14;
            phi_P1 = TMath::ATan2(tmp3.y(),tmp3.x())*180./3.14;
            phi_P2 = TMath::ATan2(tmp4.y(),tmp4.x())*180./3.14;
            
            
            t = pow((E_beam-sqrt(pow(P1,2)+pow(0.140,2))),2) - (pow(-P_1[0],2)+pow(-P_1[1],2)+pow((E_beam-P_1[2]),2));
            u = pow((E_beam-sqrt(pow(P2,2)+pow(0.938,2))),2) - (pow(-P_2[0],2)+pow(-P_2[1],2)+pow((E_beam-P_2[2]),2));
            s = pow((sqrt(pow(P1,2)+pow(0.140,2))+sqrt(pow(P2,2)+pow(0.938,2))),2) - (pow((P_1[0]+P_2[0]),2)+pow((P_1[1]+P_2[1]),2)+pow((P_1[2]+P_2[2]),2)); // (E1+E2)^2 - (|p1+p2|)^2
            
            // Define the event weight based on the cross-section
            //                       nb/Sr                       nb->b    b->cm2                                 Sr                                       Beam     Target    transp. d.eff     30 days                       theta_cm dependence of the cross-seection
            weight = (cross_section*(gamma_cm*gamma_cm)/3.14) * (1e-9) * (1e-24) * (2*3.14*(cos((theta_cm-0.5)*3.14/180)-cos((theta_cm+0.5)*3.14/180))) * (5e7) *  (6e23)  *  0.5   * 0.75 *  3600*24*30 * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4) /(N);
            
            if(abs(t)>3 && abs(u)>3){ // only consider 'hard' scattering events.
                T->Fill();
            }
            
        }
        
        
    }
    
    T->Write();
    f->Write();
    f->Close();
    
}





/*
 //Hayan paper

 
 Double_t z[100] = {0};
 TF1* F = new TF1("F","[1]/x**[2]",1,15);
 

 // gamma+n->pi- + p
 Double_t k[7] = {1.106, 1.659, 1.815, 2.481, 3.321, 4.158, 5.536};
 Double_t X[7] = {5.72e3, 2.39e3, 1.58e3, 2.43e2, 1.16e1, 4.05, 0.56};
 Double_t Xe[7] = {0.47e3, 0.20e3, 0.14e3, 0.20e2,  0.10e1, 0.33,  0.05};
 
 TGraphErrors* G = new TGraphErrors(7, k,X,z,Xe);
 G->Fit("F");
 
 
 // gamma+p->pi+ + n  (Hayan + SLAC)
 Double_t k [10] = {1.106 , 1.659 , 1.815 , 2.481 , 3.321, 4.158, 5.536,   4,    5,    7.5  };
 Double_t X [10] = {1.16e4, 1.36e3, 1.06e3, 1.87e2, 8.07 , 2.34 , 0.33 ,   2.84, 0.69, 0.045};
 Double_t Xe[10] = {0.10e4, 0.12e3, 0.09e3, 0.16e2, 0.66 , 0.20 , 0.04 ,   0.30, 0.11, 0.019};
 
 TGraphErrors* G = new TGraphErrors(7, k,X,z,Xe);
 G->Fit("F");
 

 
 
 
 
 
 */


















