#include "sigma.C"
void t(){

  TCanvas* c = new TCanvas("c","c",0,0,800,500);
  //  c->Divide(1,2);
  SetRootPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetLabelSize(0.05,"X");
  gStyle->SetLabelSize(0.05,"Y");
  gStyle->SetLabelSize(0.05,"Z");
  gStyle->SetTitleSize(0.05,"X");
  gStyle->SetTitleSize(0.05,"Y");
  gStyle->SetTitleSize(0.05,"Z");

  ifstream file;
  //  file.open("Gluex_Gamma_Beam.txt");                                                                                                                                         
  //const Int_t lines = 55;                                                                                                                                                       
  file.open("collimated_cor1.txt");
  const Int_t lines =46;
  TH1F* GammaBeamHist= new TH1F("","", lines, 2.8, 12.);
  Double_t EnergyIterator1, EnergyIterator2;
  double counts = 0.;
  double ener = 0.;

  for(int i=0; i<lines; i++){
    file >> ener >> counts;
    //          cout<<"i: "<<i<<", ener = "<<ener<<", counts = "<<counts<<endl;                                                                                                   
    GammaBeamHist->SetBinContent(i+1, counts);
  }
  //for(int i=1;i<=54;i++){GammaBeamHist->SetBinError(i,0);}                                                                                                                    
  /*
  c->cd(1);
  GammaBeamHist->GetXaxis()->SetTitleSize(0.06);
  GammaBeamHist->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  GammaBeamHist->GetYaxis()->SetTitleSize(0.06);
  GammaBeamHist->GetYaxis()->SetTitle("#gamma / s");
  GammaBeamHist->Draw();
  */

  TH2F* tt = new TH2F("tt","tt",lines,2.8,12.,17,47.5,132.5);
  double E_beam = 0.;
  double s = 0.;
  double k_i, k_f;
  double Nev = 0.;
  double t = 0.;
  double theta_cm = 0.;
  double Pm = 0.6;// Pm = 0.2 for CT , Pm = 0.6 for SRC 
  TLorentzVector v_miss(0.,0.,Pm,sqrt(0.940*0.940+Pm*Pm));
  //  cout<<"v_miss: "<<endl; print(v_miss);
  TVector3 m1 = v_miss.BoostVector();
  //cout<<"boost vector: "<<m1.X()<<", "<<m1.Y()<<", "<<m1.Z()<<endl;
  TLorentzVector v_beam;
  for(Int_t i=0; i<lines; i++){
    E_beam = 2.9+0.2*i;
    s = 2*E_beam*0.940 + 0.940*0.940;
    k_i = sqrt(0.5*E_beam*0.940);
    k_f = sqrt((s - pow(0.940-0.140,2))*(s - pow(0.940+0.140,2))/4./s);
    v_beam.SetPxPyPzE(0.,0.,E_beam,E_beam);

    // nucleon rest frame:
    TLorentzVector v_beam_nrf = v_beam;
    TLorentzVector v_miss_nrf = v_miss;
    v_beam_nrf.Boost(-m1);
    v_miss_nrf.Boost(-m1);
    cout<<"E_beam = "<<E_beam<<endl;
    cout<<"N at rest v_beam: "<<endl; print(v_beam_nrf);
    cout<<"N at rest v_miss: "<<endl; print(v_miss_nrf);

    // nucleon + beam c.m. frame:
    TLorentzVector v_beam_cm = v_beam;
    TLorentzVector v_miss_cm = v_miss;
    cout<<"v_beam: "<<endl; print(v_beam_cm);
    cout<<"v_miss: "<<endl; print(v_miss_cm); 
    TLorentzVector m = (v_beam + v_miss); //C.M. for Lorentz Boost                                                                                              
    v_beam_cm.Boost(-m.BoostVector());
    v_miss_cm.Boost(-m.BoostVector());
    cout<<"v_beam_cm: "<<endl; print(v_beam_cm);
    cout<<"v_miss_cm: "<<endl; print(v_miss_cm);
   
    // rotate v_beam_cm and v_miss_cm so that they go along z axis - don't need as we have only z-components
    TVector3 v_beam_cm_oz, v_miss_cm_oz;
    v_beam_cm_oz.SetXYZ(v_beam_cm.X(),v_beam_cm.Y(),v_beam_cm.Z());
    v_miss_cm_oz.SetXYZ(v_miss_cm.X(),v_miss_cm.Y(),v_miss_cm.Z());

    for(Int_t j=0; j<17; j++){
      theta_cm = (50.+j*5);
      
      // Define the scattering angle in the c.m.                                                                                                                           
      TVector3 p1f, p2f;
      Double_t theta_ll=theta_cm*3.14/180;
      
      // Calculate outgoing protons in the scattering reaction                                                                                                            
      p1f.SetXYZ( v_beam_cm_oz.z()*sin(theta_ll),  0., v_beam_cm_oz.z()*cos(theta_ll));
      p2f.SetXYZ(-v_beam_cm_oz.z()*sin(theta_ll),  0.,-v_beam_cm_oz.z()*cos(theta_ll));

      // Boost back to the lab                                                                                                                                                     
      TLorentzVector v3( TVector3(p1f.x(),p1f.y(),p1f.z()), sqrt( pow(p1f.Mag(),2) + pow(0.140,2) ) );
      TLorentzVector v4( TVector3(p2f.x(),p2f.y(),p2f.z()), sqrt( pow(p2f.Mag(),2) + pow(0.938,2) ) );
      v3.Boost(m.BoostVector());
      v4.Boost(m.BoostVector());
      cout<<"theta = "<<theta_cm<<endl;
      cout<<"tmp3: "<<v3.X()<<", "<<v3.Y()<<", "<<v3.Z()<<endl;
      cout<<"tmp4: "<<v4.X()<<", "<<v4.Y()<<", "<<v4.Z()<<endl;
      t = pow((E_beam-sqrt(pow(v3.Vect().Mag(),2)+pow(0.140,2))),2) - (pow(-v3.X(),2)+pow(-v3.Y(),2)+pow((E_beam-v3.Z()),2));
      cout<<"t = "<<t<<endl;
      if(fabs(t) > 3. && fabs(t) < 10.){
	tt->SetBinContent(i+1, j+1, t);
      }else{tt->SetBinContent(i+1, j+1, -100000.);}
      }
  }
  tt->SetTitle("");
  tt->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  tt->GetYaxis()->SetTitle("#theta_{cm} [degrees]");
  tt->SetMinimum(-10.);
  tt->SetMaximum(-2.);
  tt->Draw("col2z");
}

void print(TLorentzVector a){
  cout<<a.Px()<<", "<<a.Py()<<", "<<a.Pz()<<", "<<a.E()<<endl;
}
