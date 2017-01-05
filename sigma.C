#include "rate.C"
#include "t.C"
void sigma(){

  TCanvas* c = new TCanvas("c","c",0,0,1500,800);
    c->Divide(3,2);
  gStyle->SetLabelSize(0.05,"X");
  gStyle->SetLabelSize(0.05,"Y");
  gStyle->SetLabelSize(0.05,"Z");
  gStyle->SetTitleSize(0.05,"X");
  gStyle->SetTitleSize(0.05,"Y");
  gStyle->SetTitleSize(0.05,"Z");

  //                                                                                                                                                                              
  // Gamma beam energy                                                                                                                                                            
  //                                                                                                                                                                                 

  Double_t E_beam = 9;
  ifstream file;
  //  file.open("Gluex_Gamma_Beam.txt");     
  //const Int_t lines = 55;                                                                                                                       
  file.open("collimated_cor1.txt");
  const Int_t lines =46;
  TH1F* GammaBeamHist= new TH1F("","", lines, 2.8, 12.);
  Double_t EnergyIterator1, EnergyIterator2;
  double counts = 0.;
  double ener = 0.;
  for(int i=0;i<lines;i++){
    GammaBeamHist->SetBinContent(i+1,0);
  }

  for(int i=0; i<lines; i++){
    file >> ener >> counts;
    //          cout<<"i: "<<i<<", ener = "<<ener<<", counts = "<<counts<<endl;                                                                                  
    // for(int j=0; j<counts; j++){
    //  GammaBeamHist->Fill(ener);
    //}
    GammaBeamHist->SetBinContent(i+1, counts);
  }
  //for(int i=1;i<=54;i++){GammaBeamHist->SetBinError(i,0);}                                                                                                  

  c->cd(1);
  //  GammaBeamHist->Scale(1.66*1e9/GammaBeamHist->Integral(1,lines));
  GammaBeamHist->GetXaxis()->SetTitleSize(0.06);
  GammaBeamHist->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  GammaBeamHist->GetYaxis()->SetTitleSize(0.06);
  GammaBeamHist->GetYaxis()->SetTitle("#gamma / s");
  GammaBeamHist->Draw();
    
  TF1* n_k_k2  = new TF1("","((x<0.25)?0.8*3/((0.25)**3):0.5*0.2*2.533333/(1./(0.25)-1./5)/(x**4))*(x**2)",0,1);
  c->cd(2);
  n_k_k2->SetTitle("momentum distribution of a nucleon in nucleus");
  n_k_k2->GetXaxis()->SetTitle("[GeV/c]");
  n_k_k2->Draw();
 
  TF1* F_CrossSection1 = new TF1("F_CrossSection","(3.81583e+04)/(x**7)",1,15);// gamma+p->pi+ + n  | Hayan + SLAC                                                   
  TF1* F_CrossSection2 = new TF1("F_CrossSection","(1.30380e+04)/(x**5.763)",1,15);// gamma+n->pi- + p  | Hayan                                               
  TF1* F_CrossSection3 = new TF1("F_CrossSection","(1.60048e+04)/(x**5.95421)",1,15);// gamma+n->pi- + p  | Hayan - only high s 
  TF1* F_CrossSection = new TF1("F_CrossSection","(6.67314e+04)/(x**7)",1,15);// gamma+n->pi- + p  | Hayan - only high s   
  c->cd(3);
  F_CrossSection->GetXaxis()->SetTitle("s [GeV]");
  F_CrossSection->GetYaxis()->SetTitle("d#sigma/dt [nb]");
  F_CrossSection->SetTitle("cross section");
  F_CrossSection->Draw();
  F_CrossSection1->SetLineColor(4);
  F_CrossSection1->Draw("same");
  F_CrossSection2->SetLineColor(8);
  F_CrossSection2->Draw("same");
  F_CrossSection3->SetLineColor(6);
  F_CrossSection3->Draw("same");

  TLegend* leg = new TLegend(0.5,0.5,0.75,0.75);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.05);
  leg->AddEntry(F_CrossSection,"6.67e4/x^{7}","l");
  leg->AddEntry(F_CrossSection1,"3.8e4/x^{7}","l");
  leg->AddEntry(F_CrossSection2,"1.3e4/x^{5.8}","l");
  leg->AddEntry(F_CrossSection3,"1.6e4/x^{6}","l");
  leg->Draw("same");

  //SOME HISTOGRAMS:                                            
  TH1F* hkk = new TH1F("hkk","",lines,2.8,12.);
  
  // Factor:
  double s_init = 0.;
  double E_beam = 0.;
  double k_i, k_f;                                                                                                                                                  
  double theta_cm = 0.;
  for(Int_t i=0; i<lines; i++){
    E_beam = 2.9+i*0.2;
    s_init = 2*E_beam*0.940 + 0.940*0.940;
    k_i = sqrt(0.5*E_beam*0.940);
    k_f = sqrt((s_init - pow(0.940-0.140,2))*(s_init - pow(0.940+0.140,2))/4./s_init);
    hkk->SetBinContent(i+1,k_i*k_f);
  }
  c->cd(4);
  hkk->SetTitle("d#sigma/dt * k_{i}k_{f}/2#pi  = d#sigma/d#Omega");
  hkk->GetYaxis()->SetTitle("k_{i}k_{f} [(GeV/c)^{2}]");
  hkk->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  hkk->Draw();

  TH1F* hth = new TH1F("hth","hth",17,47.5,132.5);
  TH1F* hth1 = new TH1F("hth1","hth1",17,47.5,132.5);
  Double_t theta_cm = 0.;
  for(Int_t j=0; j<17; j++){
    theta_cm = 50.+j*5;
    hth->SetBinContent(j+1, (2*3.14*(cos((theta_cm-2.5)*3.14/180)-cos((theta_cm+2.5)*3.14/180))));
    hth1->SetBinContent(j+1, pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4));
  }
  c->cd(5);
  hth->SetTitle("2#pi(cos((#theta_{cm}-0.5)#pi/180)-cos((#theta_{cm}+0.5)#pi/180))");
  hth->GetXaxis()->SetTitle("#theta_{cm} [degrees]");  
  hth->Draw();
  c->cd(6);
  hth1->SetTitle("(1-cos#theta_{cm})^{-5} * (1+cos#theta_{cm})^{4}");
  hth1->GetXaxis()->SetTitle("#theta_{cm} [degrees]");
  hth1->Draw();

  gStyle->SetOptStat(0);
  SetRootPalette(1);

  TH2F* hh2 = new TH2F("hh2","hh2",lines,2.8,12.,17,47.5,132.5);
  TH2F* hh3 = new TH2F("hh3","hh3",lines,2.8,12.,17,47.5,132.5);
  TH2F* tt = new TH2F("tt","tt",lines,2.8,12.,17,47.5,132.5);
  TH2F* uu = new TH2F("uu","uu",lines,2.8,12.,17,47.5,132.5);
  TH2F* t2 = new TH2F("t2","t2",lines,2.8,12.,17,47.5,132.5);
  TH2F* t3 = new TH2F("t3","t3",lines,2.8,12.,17,47.5,132.5);
  TH1F* ev1 = new TH1F("ev1","ev1",17,47.5,132.5);
  TH1F* ev2 = new TH1F("ev2","ev2",17,47.5,132.5);
  TH1F* ev3 = new TH1F("ev3","ev3",17,47.5,132.5);
  TH1F* ev4 = new TH1F("ev4","ev4",17,47.5,132.5);

  double Nev = 0.;
  double t = 0.;
  double u = 0.;
  double s = 0.;
  double Pm = 0.0;
  TLorentzVector v_miss(0.,0.,Pm,sqrt(0.940*0.940+Pm*Pm)); // Pm = 0.2 for CT
  TVector3 m1 = v_miss.BoostVector();
  TLorentzVector v_beam;
  for(Int_t i = 0; i<1/*lines*/; i++){
    E_beam = 2.9+0.2*i;
    s_init = 2*E_beam*0.940 + 0.940*0.940;
    k_i = sqrt(0.5*E_beam*0.940);
    k_f = sqrt((s_init - pow(0.940-0.140,2))*(s_init - pow(0.940+0.140,2))/4./s_init);
    cout<<"E_beam = "<<E_beam<<", bin = "<<i+1<<", gamma rate - "<<GammaBeamHist->GetBinContent(i+1)<<", cs = "<<F_CrossSection->Eval(2*E_beam*0.940 + 0.940*0.940)<<endl;
    v_beam.SetPxPyPzE(0.,0.,E_beam,E_beam);
    cout<<"s_init = "<<s_init<<endl;

    // nucleon rest frame
    TLorentzVector v_beam_nrf = v_beam;
    TLorentzVector v_miss_nrf = v_miss;
    v_beam_nrf.Boost(-m1);
    v_miss_nrf.Boost(-m1);
    Effective_E = sqrt( pow(v_beam_nrf.X(),2)+pow(v_beam_nrf.Y(),2)+pow(v_beam_nrf.Z(),2) );
    //    cout<<"Effective e = "<<v_beam_nrf.Vect().Mag()<<" = "<<v_beam.E()<<endl;

    //cm frame:
    TLorentzVector m = (v_beam + v_miss); //C.M. for Lorentz Boost
    cout<<"v_beam in lab: "<<endl; print(v_beam);
    cout<<"v_miss in lab: "<<endl; print(v_miss);
    TLorentzVector v_beam_cm = v_beam;
    TLorentzVector v_miss_cm = v_miss;                                                                                                                       
    v_beam_cm.Boost(-m.BoostVector());
    v_miss_cm.Boost(-m.BoostVector());
    cout<<"v_beam cm :"<<endl; print(v_beam_cm);
    cout<<"v_miss cm :"<<endl; print(v_miss_cm);
    TVector3 tmp1, tmp2;
    tmp1=v_beam_cm.Vect();
    tmp2=v_miss_cm.Vect();

    for(Int_t j=0; j<17; j++){
      theta_cm = (50.+j*5.);
      // Define the scattering angle in the c.m.                                                                                                                                          
      TVector3 tmp3, tmp4;
      Double_t theta_ll=theta_cm*3.14/180;

      // Calculate outgoing protons in the scattering reaction                                                                                                                             
      tmp3.SetXYZ( tmp1.z()*sin(theta_ll),  0., tmp1.z()*cos(theta_ll));
      tmp4.SetXYZ(-tmp1.z()*sin(theta_ll),  0.,-tmp1.z()*cos(theta_ll));

      // Boost back to the lab                                                                                                                                                           
      TLorentzVector v3( TVector3(tmp3.x(),tmp3.y(),tmp3.z()), sqrt( pow(tmp3.Mag(),2) + pow(0.140,2) ) );
      TLorentzVector v4( TVector3(tmp4.x(),tmp4.y(),tmp4.z()), sqrt( pow(tmp4.Mag(),2) + pow(0.938,2) ) );
      v3.Boost(m.BoostVector());
      v4.Boost(m.BoostVector());
      cout<<"theta = "<<theta_cm<<endl;
      cout<<"tmp3: "<<v3.X()<<", "<<v3.Y()<<", "<<v3.Z()<<endl;
      cout<<"tmp4: "<<v4.X()<<", "<<v4.Y()<<", "<<v4.Z()<<endl;
      //      t = pow((E_beam-sqrt(pow(P1,2)+pow(0.140,2))),2) - (pow(-P_1[0],2)+pow(-P_1[1],2)+pow((E_beam-P_1[2]),2));// from test
      t = pow((E_beam-sqrt(pow(v3.Vect().Mag(),2)+pow(0.140,2))),2) - (pow(-v3.X(),2)+pow(-v3.Y(),2)+pow((E_beam-v3.Z()),2));
      u = pow((E_beam-sqrt(pow(v4.Vect().Mag(),2)+pow(0.938,2))),2) - (pow(-v4.X(),2)+pow(-v4.Y(),2)+pow((E_beam-v4.Z()),2));

      cout<<"t = "<<t<<", u = "<<u<<", s = "<<s<<endl;
      tt->SetBinContent(i+1, j+1, t);
      uu->SetBinContent(i+1, j+1, u);
      if(fabs(t) > 2.){
	t2->SetBinContent(i+1, j+1, t);
      }else{t2->SetBinContent(i+1,j+1, -100000000.);}
      if(fabs(t) > 3.){
        t3->SetBinContent(i+1, j+1, t);
      }else{t3->SetBinContent(i+1,j+1, -100000000.);}
      //                                         nb/Sr (s)                                             nb->b     b->cm2                                      Sr                                  Beam       Target    efficiencies   30 days           theta_cm dependency of the cross section
      if(fabs(t) > 2.){
	hh2->SetBinContent(i+1, j+1, F_CrossSection->Eval(Effective_E)* (k_i*k_f)/3.14 * (1e-9) * (1e-24) * (2*3.14*(cos((theta_cm-2.5)*3.14/180)-cos((theta_cm+2.5)*3.14/180)))* GammaBeamHist->GetBinContent(i+1) * (6.3e23) * 0.5 * 0.75* 3600*24*30  * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4));
      } else{hh2->SetBinContent(i+1, j+1, 0.000001);}
      if(fabs(t) > 3.){
	hh3->SetBinContent(i+1, j+1, F_CrossSection->Eval(Effective_E)* (k_i*k_f)/3.14 * (1e-9) * (1e-24) * (2*3.14*(cos((theta_cm-2.5)*3.14/180)-cos((theta_cm+2.5)*3.14/180)))*GammaBeamHist->GetBinContent(i+1) * (6.3e23) * 0.5 * 0.75* 3600*24*30  * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4));
      } else{hh3->SetBinContent(i+1, j+1, 0.000001);}
      //some particular cases:
      if(E_beam < 5. && fabs(t) > 3.){
	ev1->SetBinContent(j+1, ev1->GetBinContent(j+1) + F_CrossSection->Eval(Effective_E)* (k_i*k_f)/3.14 * (1e-9) * (1e-24) * (2*3.14*(cos((theta_cm-2.5)*3.14/180)-cos((theta_cm+2.5)*3.14/180)))* GammaBeamHist->GetBinContent(i+1) * (6.3e23) * 0.5 * 0.75* 3600*24*30  * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4));
      }
      if(E_beam >= 5. && E_beam < 7.5 && fabs(t) > 3.){
	ev2->SetBinContent(j+1, ev2->GetBinContent(j+1) + F_CrossSection->Eval(Effective_E)* (k_i*k_f)/3.14 * (1e-9) * (1e-24) * (2*3.14*(cos((theta_cm-2.5)*3.14/180)-cos((theta_cm+2.5)*3.14/180)))* GammaBeamHist->GetBinContent(i+1) * (6.3e23) * 0.5 * 0.75* 3600*24*30  * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4));
      }
      if(E_beam >= 7.5 && E_beam < 9. && fabs(t) > 3.){
	ev3->SetBinContent(j+1, ev3->GetBinContent(j+1) + F_CrossSection->Eval(Effective_E)* (k_i*k_f)/3.14 * (1e-9) * (1e-24) * (2*3.14*(cos((theta_cm-2.5)*3.14/180)-cos((theta_cm+2.5)*3.14/180)))* GammaBeamHist->GetBinContent(i+1) * (6.3e23) * 0.5 * 0.75* 3600*24*30  * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4));
      }
      if(E_beam > 9. && fabs(t) > 3.){
	ev4->SetBinContent(j+1, ev4->GetBinContent(j+1) + F_CrossSection->Eval(Effective_E)* (k_i*k_f)/3.14 * (1e-9) * (1e-24) * (2*3.14*(cos((theta_cm-2.5)*3.14/180)-cos((theta_cm+2.5)*3.14/180)))* GammaBeamHist->GetBinContent(i+1) * (6.3e23) * 0.5 * 0.75* 3600*24*30  * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4));
      }
    }
  }
  TCanvas* c1 = new TCanvas("c1","c1",1000,500);
  c1->Divide(2,1);
  hh2->SetMinimum(0.01);
  c1->cd(1);
  gPad->SetLogz();  
  hh2->SetTitle("Number of events in 30 days for |t| > 2");
  hh2->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  hh2->GetYaxis()->SetTitleOffset(1.12);
  hh2->GetYaxis()->SetTitle("#theta_{cm} [degrees]");
  hh2->SetMinimum(0.0001);
  hh2->Draw("col2z");
  c1->cd(2);
  hh3->SetMinimum(0.01);
  gPad->SetLogz();
  hh3->SetTitle("Number of events in 30 days for |t| > 3");
  hh3->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  hh3->GetYaxis()->SetTitleOffset(1.12);
  hh3->GetYaxis()->SetTitle("#theta_{cm} [degrees]");
  hh3->SetMinimum(0.0001);
  hh3->Draw("col2z");
  /*
  (F_CrossSection*(gamma_cm*gamma_cm)/3.14)  *   (2*3.14*(cos((theta_cm-0.5)*3.14/180)-cos((theta_cm+0.5)*3.14/180))) * pow((1-cos(theta_cm*3.14/180)),-5) * pow((1+cos(theta_cm*3.14/180)),-4)
  */

  TCanvas* c3 = new TCanvas("c3","c3",1800,500);
  c3->Divide(3,1);
  c3->cd(1);
  tt->SetTitle("t");
  tt->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  tt->GetYaxis()->SetTitle("#theta_{cm} [degrees]");
  //tt->SetMinimum(0.0001);
  tt->Draw("col2z");
  c3->cd(2);
  t2->SetTitle("|t| > 2.");
  t2->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  t2->GetYaxis()->SetTitle("#theta_{cm} [degrees]");
  t2->SetMinimum(-20.);
  t2->Draw("col2z");
  c3->cd(3);
  t3->SetTitle("|t| > 3.");
  t3->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  t3->GetYaxis()->SetTitle("#theta_{cm} [degrees]");
  t3->SetMinimum(-20.);
  t3->Draw("col2z");

  TCanvas* c4 = new TCanvas("c4","c4",500,500);
  uu->SetTitle("u");
  uu->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  uu->GetYaxis()->SetTitle("#theta_{cm} [degrees]");
  //tt->SetMinimum(0.0001);                                                                                                                                                      
  uu->Draw("col2z");


  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  c2->cd();
  ev1->SetLineWidth(2);
  ev1->GetYaxis()->SetRangeUser(0.1,1e7);
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  ev1->SetLineColor(6);
  ev1->SetTitle("");
  ev1->GetYaxis()->SetTitle("Number of events");
  ev1->GetXaxis()->SetTitle("#theta_{cm} [degrees]");
  ev1->Draw();
  ev2->SetLineWidth(2);
  ev2->SetLineColor(4);
  ev2->Draw("same");
  ev3->SetLineWidth(2);
  ev3->SetLineColor(8);
  ev3->Draw("same");
  ev4->SetLineWidth(2);
  ev4->SetLineColor(32);
  ev4->Draw("same");

  TString intev1, intev2, intev3, intev4;
  intev1.Form("E_{#gamma} (3-5] GeV, %.0f ev", ev1->Integral(1,20));
  intev2.Form("E_{#gamma} (5-7.5] GeV, %.0f ev", ev2->Integral(1,20));
  intev3.Form("E_{#gamma} (7.5-9] GeV, %.0f ev", ev3->Integral(1,20));
  intev4.Form("E_{#gamma} (9-12], %.0f ev", ev4->Integral(1,20));

  TLegend* leg1 = new TLegend(0.5,0.5,0.75,0.75);
  leg1->SetLineColor(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(ev1, intev1.Data(),"l");//~85 k","l");
  leg1->AddEntry(ev2, intev2.Data(),"l");//~6.3 k","l");
  leg1->AddEntry(ev3, intev3.Data(),"l");//~3.3 k","l");
  leg1->AddEntry(ev4, intev4.Data(),"l");//~1.2 k","l");
  leg1->Draw("same");
}
