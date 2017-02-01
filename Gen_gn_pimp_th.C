#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "TMath.h"
#include "TString.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include "TRandom2.h"

void Gen_gn_pimp_th(int N = 100000, int A = 2, bool printOutput = false){
  // A - nucleus, which contains the target nucleon

  // Half of the step in theta
  double tsh = 1./2.;// degrees
  int Nthpo = (130. - 50.)/(2.*tsh);

  TString out;
  out.Form("gn_pimp_N%d_col5a.root",N);

  // Gamma spectrum
  double E_beam = 9;
  std::ifstream file("collimated5_Ee12.txt");
  //  std::ifstream file("collimated_cor3.txt");  
  std::string line;
  const int lines =46;
  TH1F* GammaBeamHist= new TH1F("","", lines, 2.8, 12.);
  int i = 0;

  while(getline(file, line)) {
    if (!line.length() || line[0] == '#')
      continue;
    i++;
    std::istringstream iss(line);
    double x = 0., y = 0.;
    iss>>x>>y;
    std::cout<<"point: "<<x<<" "<<y<<" ; i = "<<i<<std::endl;
    GammaBeamHist->SetBinContent(i, y);
  }

  //for(int i=1;i<=54;i++){GammaBeamHist->SetBinError(i,0);}                                                                                                                           
  GammaBeamHist->GetXaxis()->SetTitleSize(0.06);                                                                                                                                       
  GammaBeamHist->GetXaxis()->SetTitle("E_{#gamma} [GeV]");                                                                                                                             
  GammaBeamHist->GetYaxis()->SetTitleSize(0.06);                                                                                                                                       
  GammaBeamHist->GetYaxis()->SetTitle("#gamma / s");                                                                                                                                   
  GammaBeamHist->Draw();

  //                                                                                                                                                                                 
  // Tree to hold (gamma,p pi p) 'SRC' events and extra kinematical variables.                                                                                                       
  // Each Event has  forward scatter proton, a pion, and a recoil neutron.                                                                                                           
  // The reconstructed initial momentum of the proton knockout of the nucleus is lables as "missing momentum"                                                                        
  //                                                                                                                                                                                 
  TFile* f = new TFile(out,"recreate");
  TTree* T = new TTree("T","T");

  double theta_recoil, phi_recoil, Precoil;
  double theta_miss, phi_miss, Pmiss;
  double theta_P3, phi_P3, absP3;
  double theta_P4, phi_P4, absP4;
  TVector3 P3, P4;
  double t,u,s;
  double theta_cm;
  double weight;
  double weight_kk;
  double Effective_E;
  double Original_E;
  double gamma_cm;
  double Nucleon_cm;
  double cross_section;

  double k_i;
  double k_f;

  T->Branch("weight",&weight,"weight/D");                     // Event weight based on cross-section                                                                                 
  T->Branch("weight_kk",&weight_kk,"weight_kk/D");
  T->Branch("theta_cm",&theta_cm,"theta_cm/D");
  T->Branch("Effective_E",&Effective_E,"Effective_E/D");     // E_beam in the standing nucleon frame
  T->Branch("Original_E",&Original_E,"Original_E/D");        // E_beam in the lab frame

  T->Branch("gamma_cm",&gamma_cm,"gamma_cm/D");              // gamma energy in the gamma-neutron c.m. frame                                                                       
  T->Branch("Nucleon_cm",&Nucleon_cm,"Nucleon_cm/D");         // Neutron energy in the gamma-neutron c.m. frame                                                                      

  T->Branch("k_i",&k_i,"k_i/D");
  T->Branch("k_f",&k_f,"k_f/D");
  T->Branch("cross_section",&cross_section,"cross_section/D");

  T->Branch("theta_recoil",&theta_recoil,"theta_recoil/D");   // recoil proton in-plane angle                                                                                        
  T->Branch("phi_recoil",&phi_recoil,"phi_recoil/D");         // recoil proton out-of-plane angle                                                                                    
  T->Branch("Precoil",&Precoil,"Precoil/D");               // recoil proton momentum vector magnitude                                                                             

  T->Branch("theta_miss",&theta_miss,"theta_miss/D");         // Initial neutron in-plane angle                                                                                      
  T->Branch("phi_miss",&phi_miss,"phi_miss/D");               // Initial neutron out-of-plane angle                                                                                  
  T->Branch("P_miss",&Pmiss,"Pmiss/D");                  // Initial neutron momentum vector magnitude                                                                           

  T->Branch("theta_P3",&theta_P3,"theta_P3/D");               // Leading proton in-plane angle                                                                                       
  T->Branch("phi_P3",&phi_P3,"phi_P3/D");                     // Leading proton out-of-plane angle                                                                                   
  T->Branch("absP3",&absP3,"absP3/D");                                 // Leading proton momentum vector magnitude                                                                            

  T->Branch("theta_P4",&theta_P4,"theta_P4/D");               // Leading pion in-plane angle                                                                                         
  T->Branch("phi_P4",&phi_P4,"phi_P4/D");                     // Leading pion out-of-plane angle                                                                                     
  T->Branch("absP4",&absP4,"absP4/D");                                 // Leading pion momentum vector magnitude                                                                              

  // Final 3-momentum vector for the scattered protons in the lab                                                                                                                    
  T->Branch("P3","TVector3",&P3);
  T->Branch("P4","TVector3",&P4);

  T->Branch("t",&t,"t/D");
  T->Branch("u",&u,"u/D");
  T->Branch("s",&s,"s/D");

  T->Branch("N",&N,"N/D");

  //Parametrisation of the gamma+n -> p pi- cross section                                                                                                                            
  // TF1* F_CrossSection = new TF1("F_CrossSection","(3.81583e+04)/(x**7)",1,15);// gamma+p->pi+ + n  | Hayan + SLAC                                                                 
  //    TF1* F_CrossSection = new TF1("F_CrossSection","(1.30380e+04)/(x**5.763)",1,15);// gamma+n->pi- + p  | Hayan                                                                 
  //    TF1* F_CrossSection = new TF1("F_CrossSection","(1.60048e+04)/(x**5.95421)",1,15);// gamma+n->pi- + p  | Hayan - only high s                                                 
  TF1* F_CrossSection = new TF1("F_CrossSection","(6.67314e+04)/(x**7)",1,15);// gamma+n->pi- + p  | Hayan - only high s                                                         

  // Parametrization of the momentum distribution for nucleons in a nucleus (including SRC nucleons)
  TF1* SRCtail = new TF1("SRCtail","1/(x**4)",0.25,0.7);
  TF1* n_k     = new TF1("","((x<0.25)?0.8*3/((0.25)**3):0.5*0.2*2.533333/(1./(0.25)-1./5)/(x**4))       ",0,1);
  TF1* n_k_k2  = new TF1("","((x<0.25)?0.8*3/((0.25)**3):0.5*0.2*2.533333/(1./(0.25)-1./5)/(x**4))*(x**2)",0,1);

  /* //SOME HISTOGRAMS:                                                                                                                                                                 
  TH1F* hga = new TH1F("hga","",100,0.,10.);
  TH1F* hkk = new TH1F("hkk","",100,0.,10.);
  TH1F* hEd = new TH1F("hEd","",100,0.,100.);
  */
  double PmissX, PmissY, PmissZ;
  TVector3 Prec3, Pcm3;
  double con, Sr, Beam, cs_theta_cm;

  // Event generation:
  // 1. Raffle a nucleon in the nucleus
  // 2. If it has high momentum, raffle a correlated partner = recoil
  for (int i=0; i<N; i++){

    if(i%(N/100)==0) cout << i/(N/100)<<"%" << endl; 

    E_beam = GammaBeamHist->GetRandom();
    //    cout<<"bin number is "<<GammaBeamHist->FindBin(E_beam)<<endl;
    Original_E = E_beam;

    Pmiss = n_k_k2->GetRandom();
    gRandom->Sphere(PmissX, PmissY, PmissZ, Pmiss);
    /*    PmissX = 0.;
    PmissY = 0.;
    PmissZ = 0.2;*/
    theta_miss = TMath::ACos(PmissZ/Pmiss)*180/3.14;      // Calculate theta [degrees]                                                                                      
    phi_miss = TMath::ATan2(PmissY,PmissX)*180/3.14;       // Calculate phi   [degrees]

    //create recoil
    if(Pmiss > 0.25){
      // Raffle SRC-pair C.M. momentum. from gauss with sigma of 0.14 GeV
      Pcm3.SetXYZ(gRandom->Gaus(0,0.14),gRandom->Gaus(0,0.14),gRandom->Gaus(0,0.14));
      // Calculate 3-momentum vector for the 2nd nucleon in the pair.
      Prec3.SetXYZ(Pcm3.X()-PmissX, Pcm3.Y()-PmissY, Pcm3.Z()-PmissZ);
    }else{
      Prec3.SetXYZ(0.,0.,0.);
    }
    Precoil = Prec3.Mag();
    theta_recoil = Prec3.Theta()/TMath::Pi()*180.;
    phi_recoil = Prec3.Phi()/TMath::Pi()*180.;

    // Factor:
    // scattering off free moving proton:
    double s_init = pow((E_beam + sqrt(Pmiss*Pmiss + 0.940*0.940)),2) - pow(PmissX,2) - pow(PmissY,2) - pow(PmissZ+E_beam,2);//2*E_beam*0.940 + 0.940*0.940;
    // k_i, k_f relative c.m. momentum in the initial and final states:
    k_i = (s_init - 0.940*0.940)/2./sqrt(s_init);//sqrt(0.5*E_beam*0.940);
    k_f = sqrt((s_init - pow((0.938-0.140),2))*(s_init - pow((0.938+0.140),2))/4./s_init);
    // scattering off proton inside nucleus:
    /*Double_t s_new;
    if(Pmiss < 0.25){
      s_init = pow((E_beam + 0.940 - 0.015 - Pmiss*Pmiss/2./0.940/(A-1)),2) - pow(PmissX,2) - pow(PmissY,2) - pow(PmissZ+E_beam,2);
    }else{
      s_init = pow((E_beam + sqrt(pow(2*0.940,2) + pow(Pcm3.Mag(),2)) - sqrt(pow(Prec3.Mag(),2) + 0.940*0.940)),2) - pow(PmissX,2) - pow(PmissY,2) - pow(PmissZ+E_beam,2);
    }
    cout<<"raffled recoil : "<<Prec3.Mag()<<endl;
    cout<<"calculated recoil : "<<Pmiss.Mag()<<endl;*/
    //    hkk->Fill(k_i*k_f);
    //    cout<<"Sinit = "<<s_init<<endl;  
    //    Double_t s_init1 = 2*E_beam*0.940 + 0.940*0.940;  
    //cout<<"Sinit1 = "<<s_init1<<endl;

    // 4-momentum of the beam and nucleon in the lab:
    TLorentzVector Vbeam_lab(TVector3(0.,0.,E_beam),         E_beam                            );
    TLorentzVector Vmiss_lab(TVector3(PmissX,PmissY,PmissZ), sqrt(pow(0.940,2) + pow(Pmiss,2)) );
    
    // beam and nucleon in the nucleon rest frame to calculate the cross-section:
    TVector3 m1 = Vmiss_lab.BoostVector();
    TLorentzVector Vbeam_nrf = Vbeam_lab;
    TLorentzVector Vmiss_nrf = Vmiss_lab;
    Vbeam_nrf.Boost(-m1);
    Vmiss_nrf.Boost(-m1);
    Effective_E = Vbeam_nrf.Vect().Mag();
    cross_section = F_CrossSection->Eval(Effective_E);
    //cout<<"Effective_E = "<<Effective_E<<", cs = "<<cross_section<<endl;
    //cout<<"nucl rest :"<<Vbeam_nrf.X()<<", "<<Vbeam_nrf.Y()<<", "<<Vbeam_nrf.Z()<<endl;

    // boost to the c.m. system of the nucleon + beam:
    TVector3 m = (Vmiss_lab + Vbeam_lab).BoostVector();
    TLorentzVector Vbeam_cm = Vbeam_lab;
    TLorentzVector Vmiss_cm = Vmiss_lab;
    Vbeam_cm.Boost(-m);
    Vmiss_cm.Boost(-m);
    gamma_cm = Vbeam_cm.Vect().Mag();
    //cout<<"gamma_cm = "<<gamma_cm<<endl;
    Nucleon_cm = Vmiss_cm.Vect().Mag();
    
    // loop over theta_cm scattering angles:
    //for(int k=50; k<=130; k++){
      for(int k=0; k<=Nthpo; k++){

      theta_cm = 50.+k*tsh*2.;
	//      theta_cm = k;
      //      cout<<"theta = "<<theta_cm<<endl;

      // rotate vectors so that the collision is along z axis:
      double rot_phi = Vbeam_cm.Vect().Phi();
      double rot_theta = Vbeam_cm.Vect().Theta();
      TVector3 Vbeam_cm_oz3 = Vbeam_cm.Vect();
      TVector3 Vmiss_cm_oz3 = Vmiss_cm.Vect();
      Vbeam_cm_oz3.RotateZ(-rot_phi);
      Vbeam_cm_oz3.RotateY(-rot_theta);
      Vmiss_cm_oz3.RotateZ(-rot_phi);
      Vmiss_cm_oz3.RotateY(-rot_theta);

      //cout<<"rot_phi = "<<rot_phi<<", rot_theta = "<<rot_theta<<endl;
      //cout<<"beam_cm: "<<Vbeam_cm_oz3.z()<<", mag = "<<Vbeam_cm_oz3.Mag()<<endl;
      //cout<<"miss_cm: "<<Vmiss_cm_oz3.z()<<", mag = "<<Vmiss_cm_oz3.Mag()<<", angle with beam = "<<Vbeam_cm_oz3.Angle(Vmiss_cm_oz3)/3.1415*180.<<endl;
      
      // scattering angle - theta_cm
      double theta_ll = theta_cm*TMath::Pi()/180.;
      double phi_ll = gRandom->Uniform(0,2*TMath::Pi());
      
      // outgoing particles:
      TVector3 Vpart3_cm_oz3( Vbeam_cm_oz3.Z()*cos(phi_ll)*sin(theta_ll),  Vbeam_cm_oz3.Z()*sin(phi_ll)*sin(theta_ll),  Vbeam_cm_oz3.Z()*cos(theta_ll));
      TVector3 Vpart4_cm_oz3(-Vbeam_cm_oz3.Z()*cos(phi_ll)*sin(theta_ll), -Vbeam_cm_oz3.Z()*sin(phi_ll)*sin(theta_ll), -Vbeam_cm_oz3.Z()*cos(theta_ll));
      
      // rotate back:
      TVector3 Vpart3_cm3 = Vpart3_cm_oz3;
      TVector3 Vpart4_cm3 = Vpart4_cm_oz3;
      Vpart3_cm3.RotateY(rot_theta);
      Vpart3_cm3.RotateZ(rot_phi);
      Vpart4_cm3.RotateY(rot_theta);
      Vpart4_cm3.RotateZ(rot_phi);
      
      // boost outgoing particles to the lab system:
      TLorentzVector Vpart3_lab(Vpart3_cm3, sqrt( pow(Vpart3_cm3.Mag(),2) + pow(0.140,2) ) );
      TLorentzVector Vpart4_lab(Vpart4_cm3, sqrt( pow(Vpart4_cm3.Mag(),2) + pow(0.938,2) ) );
      Vpart3_lab.Boost(m);
      Vpart4_lab.Boost(m);

      //cout<<"tmp3: "<<Vpart3_lab.X()<<", "<<Vpart3_lab.Y()<<" "<<Vpart3_lab.Z()<<endl;
      //cout<<"tmp4: "<<Vpart4_lab.X()<<", "<<Vpart4_lab.Y()<<" "<<Vpart4_lab.Z()<<endl;

      // save stuff to the tree:
      P3 = Vpart3_lab.Vect();
      P4 = Vpart4_lab.Vect();
      absP3 = Vpart3_lab.Vect().Mag();
      absP4 = Vpart4_lab.Vect().Mag();
      theta_P3 = P3.Theta()/TMath::Pi()*180.;
      theta_P4 = P4.Theta()/TMath::Pi()*180.;
      phi_P3 = P3.Phi()/TMath::Pi()*180.;
      phi_P4 = P4.Phi()/TMath::Pi()*180.;
      //      cout<<"phiP3 = "<<phi_P3<<", phi_P4 - "<<phi_P4<<endl;      

      t = pow((E_beam-sqrt(pow(absP3,2)+pow(0.140,2))),2) - (pow(-P3.X(),2)+pow(-P3.Y(),2)+pow((E_beam-P3.Z()),2));
      u = pow((E_beam-sqrt(pow(absP4,2)+pow(0.938,2))),2) - (pow(-P4.X(),2)+pow(-P4.Y(),2)+pow((E_beam-P4.Z()),2));
      s = pow((sqrt(pow(absP3,2)+pow(0.140,2))+sqrt(pow(absP4,2)+pow(0.938,2))),2) - (pow((P3.X()+P4.X()),2)+pow((P3.Y()+P4.Y()),2)+pow((P3.Z()+P4.Z()),2)); // (E1+E2)^2 - (|p1+p2|)^2
  
      //cout<<"t = "<<t<<", s = "<<s<<", u = "<<u<<endl;

      // define components for the weight:
      //    Target   transp.eff det.eff.   30 days   nb->b   b->cm2
      con = 6.3e23 * 0.5       * 0.75  * 3600*24*30 * 1e-9 * 1e-24;     // target 1
      //con = 1.27e24 * 0.5     * 0.75  * 3600*24*30 * 1e-9 * 1e-24; // target 2
      Sr = (2*3.14*(cos((theta_cm-tsh)*3.14/180)-cos((theta_cm+tsh)*3.14/180))) ; // theta_cm +- half of the step
      Beam = GammaBeamHist->GetBinContent(GammaBeamHist->FindBin(E_beam));
      cs_theta_cm = pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4);

      // Define the event weight based on the cross-section                                                                                                                      
      //                       nb/Sr                       nb->b    b->cm2                                 Sr                                       Beam     Target    transp. d.eff     30 days                       theta_cm dependence of the cross-seection                                                                                                       
      //weight = (cross_section*(gamma_cm*gamma_cm)/3.14) * (1e-9) * (1e-24) * (2*3.14*(cos((theta_cm-0.5)*3.14/180)-cos((theta_cm+0.5)*3.14/180))) * (5e7) *  (6e23)  *  0.5   *  0.75 *  3600*24*30 * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4) /(N);

      weight = con * (cross_section*(gamma_cm*gamma_cm)/3.14) * Sr * Beam *  cs_theta_cm / N;
      weight_kk = con * (cross_section*(k_i*k_f)/3.14) * Sr * Beam * cs_theta_cm / N;

      //cout<<"w = "<<weight<<", w_kk = "<<weight_kk<<endl;

      if(abs(t)>2 && abs(u)>2){ // only consider 'hard' scattering events.                                                                                                       
	T->Fill();
      }
    } // loop over theta_cm
    //hga->Fill(gamma_cm*gamma_cm);

  }// loop over N
  T->Write();
  //hkk->Write();
  //hga->Write();
  f->Write();
  f->Close();
}
