#include "rate.C"
void Plots_new(){

  SetRootPalette(1);
    gStyle->SetOptStat(0);
    gStyle->SetLabelSize(0.05,"X");
    gStyle->SetLabelSize(0.05,"Y");
    gStyle->SetLabelSize(0.05,"Z");
    gStyle->SetTitleSize(0.05,"X");
    gStyle->SetTitleSize(0.05,"Y");
    gStyle->SetTitleSize(0.05,"Z");

    //    TTree* T = ((TTree*)(TFile::Open("gn_pimp_N10000_ng_tm1.root")->Get("T")));
    TTree* T = ((TTree*)(TFile::Open("gn_pimp_N100000_up.root")->Get("T")));

  //nubmer of targets:
  TString nt;
  nt.Form("/5.");
  TString unit;
  unit.Form("1");

  TString w;
  w.Form("*weight_kk*0.75");// _kk   detection efficiency

  TString wst, wst_f;
  wst.Form("TMath::Abs(t)>2&&TMath::Abs(u)>2");
  wst_f = wst;
  wst_f.Prepend("(");
  wst_f.Append(")");
  wst_f.Append(w);
  cout<<"wst"<<endl;
  cout<<wst_f.Data()<<endl;
  //  cout<<"(TMath::Abs(t)>2&&TMath::Abs(u)>2)*weight_kk"<<endl;

  TString wSRC90, wSRC, wMF90, wMF;
  TString wSRC90coh, wSRCcoh, wMF90coh, wMFcoh;
  TString rec, rec1, tcm90, fac, coh;
  rec.Form("(Pmiss<0.25&&");//Precoil<0.25&&");
  rec.Append(wst);
  wMF.Append(rec);
  wMFcoh.Append(wMF);
  wMF.Append(")");
  wMF.Append(w);
  fac.Form("*0.8"); // No CT!!!
  cout<<"wMF"<<endl;
  cout<<  wMF.Data()<<endl;

  coh.Form("&&Original_E>=8.4&&Original_E<=9.1)"); // 7.8
  wMFcoh.Append(coh);
  wMFcoh.Append(w);
  cout<<"wMFcoh"<<endl;
  cout<<  wMFcoh.Data()<<endl;

  //  cout<<"weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&theta_recoil<160&&Precoil>0.3)*0.5*0.8"<<endl;
  rec1.Form("(theta_recoil<160&&Pmiss>0.3");// Precoil > 0.3
  wSRC.Append(rec1);
  wSRC.Append("&&");
  wSRC.Append(wst);
  wSRCcoh.Append(wSRC);
  wSRC.Append(")");
  wSRC.Append(w);
  wSRC.Append(fac);
  cout<<"wSRC"<<endl;
  cout<<  wSRC.Data()<<endl;

  wSRCcoh.Append(coh);
  wSRCcoh.Append(w);
  wSRCcoh.Append(fac);
  cout<<"wSRCcoh"<<endl;
  cout<<  wSRCcoh.Data()<<endl;

  //Draw beam photons:
  TH1F* GammaBeamHist= new TH1F("GammaBeamHist","E_{beam} [GeV]; [#gamma/s]", 46, 2.8, 12.); // nbins = 46
  TCanvas* cb = new TCanvas("cb","beam",800,800);
  T->Draw("Original_E>>GammaBeamHist");

  // Draw s:
  TH1F* s1 = new TH1F("s1","; s [GeV^{2}]",120, -5.,55.);
  TH1F* s2 = new TH1F("s2","; s [GeV^{2}]",120, -5.,55.);
  TH1F* s3 = new TH1F("s3","; s [GeV^{2}]",120, -5.,55.);
  s1->SetLineColor(8);
  s2->SetLineColor(4);
  s3->SetLineColor(6);
  s1->SetLineWidth(3);
  s2->SetLineWidth(3);
  s3->SetLineWidth(3);
  TCanvas* Cs = new TCanvas("Cs","s",800,800);
  T->Draw("s>>s1", unit,"h");
  T->Draw("s_init>>s2", unit,"same");
  //  T->Draw("s_misak>>s3", unit,"same");

  TLegend* legs = new TLegend(0.5,0.5,0.75,0.75);
  legs->SetTextSize(0.04);
  legs->SetFillColor(0);
  legs->SetLineColor(0);
  legs->AddEntry(s1, "s for final state","l");
  legs->AddEntry(s2, "s for scattering on a SRC nucleon", "l");
  legs->AddEntry(s3, "s from Misak","l");
  legs->Draw();

    // Mean Field. Theta c.m. = All
    TH2F* theta_P_p_MF_All = new TH2F("theta_P_p_MF_All","; |P_{p}| [GeV/c]; #theta_{p} [#circ]",24,0,12 , 14,5,75);
    TH2F* theta_P_pi_MF_All = new TH2F("theta_P_pi_MF_All","; |P_{#pi}| [GeV/c]; #theta_{#pi} [#circ]",24,0,12 , 14,5,75);
    TH2F* theta_Ppi_MF_All = new TH2F("theta_Ppi_MF_All","; #theta_{p} [degrees]; #theta_{#pi} [#circ]",14,5,75 , 14,5,75);
    TH1F* phi_MF_All = new TH1F("phi_MF_All","; #Delta#phi [degrees]",40,160,200);
    TCanvas* C2 = new TCanvas("C2","MF, all",800,800);
    C2->Divide(2,2);
    C2->cd(1);
    T->Draw("theta_P4:absP4>>theta_P_pi_MF_All"      , wMFcoh,"col2z");
    C2->cd(2);
    T->Draw("theta_P3:absP3>>theta_P_p_MF_All"      , wMFcoh,"col2z");
    C2->cd(3);
    T->Draw("theta_P4:theta_P3>>theta_Ppi_MF_All", wMFcoh,"col2z");
    C2->cd(4);
    T->Draw("TMath::Abs(phi_P4-phi_P3)>>phi_MF_All",wMFcoh,"h");

    // SRC. Theta c.m. = All
    TH2F* theta_P_p_SRC_All = new TH2F("theta_P_p_SRC_All","; |P_{p}| [GeV/c]; #theta_{p} [#circ]",24,0,12 , 14,5,75);
    TH2F* theta_P_pi_SRC_All = new TH2F("theta_P_pi_SRC_All","; |P_{#pi}| [GeV/c]; #theta_{#pi} [#circ]",24,0,12 , 14,5,75);
    TH2F* theta_Ppi_SRC_All = new TH2F("theta_Ppi_SRC_All","; #theta_{p} [degrees]; #theta_{#pi} [#circ]",14,5,75 , 14,5,75);
    TH1F* phi_SRC_All = new TH1F("phi_SRC_All","; #Delta#phi [degrees]",40,160,200);
    TCanvas* C4 = new TCanvas("C4","SRC, All",800,800);
    C4->Divide(2,2);
    C4->cd(1);
    T->Draw("theta_P4:absP4>>theta_P_pi_SRC_All",wSRCcoh,"colz");
    C4->cd(2);
    T->Draw("theta_P3:absP3>>theta_P_p_SRC_All",wSRCcoh,"colz");
    C4->cd(3);
    T->Draw("theta_P4:theta_P3>>theta_Ppi_SRC_All", wSRCcoh,"colz");
    C4->cd(4);
    T->Draw("TMath::Abs(phi_P4-phi_P3)>>phi_SRC_All", wSRCcoh,"h");

    // Print the number of events!!!!

       cout<<"MF, All, N events = "<<theta_P_p_MF_All->Integral()<<endl;
     cout<<"SRC, All, N events = "<<theta_P_p_SRC_All->Integral()<<endl;
     
    TH1F* Ebeam_MF_All = new TH1F("Ebeam_MF_All","; E_{beam} [GeV]", 46, 2.8, 12);    
    TH1F* Ebeam_SRC_All = new TH1F("Ebeam_SRC_All","; E_{beam} [GeV]", 46, 2.8, 12);
    TCanvas* Cbe = new TCanvas("Cbe","Cbe",800,800);
    gPad->SetLogy();
    T->Draw("Original_E>>Ebeam_MF_All",wMF,"h");
    Ebeam_MF_All->SetLineColor(8);
    Ebeam_MF_All->SetLineWidth(3);
    gROOT->ForceStyle();
    T->Draw("Original_E>>Ebeam_SRC_All",wSRC,"same");
    Ebeam_SRC_All->SetLineColor(2);
    Ebeam_SRC_All->SetLineWidth(3);
    gROOT->ForceStyle();

    TLegend* leg = new TLegend(0.5,0.5,0.75,0.75);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.04);
    leg->AddEntry(Ebeam_MF_All,"MF, #theta_{cm}=(50,130)#circ","l");
    leg->AddEntry(Ebeam_SRC_All,"SRC, #theta_{cm}=(50,130)#circ","l");
    leg->Draw("same");

    //E_beam vs t
    gStyle->SetPalette(56);
    TH2F* Et_MF_All = new TH2F("Et_MF_All","MF, #theta_{cm} in (50,130)#circ; E_{beam} [GeV]; |t| [GeV^{2}]",46, 2.8,12, 17,3.,20.);
    TH2F* Et_SRC_All = new TH2F("Et_SRC_All","SRC, #theta_{cm} in (50,130)#circ; E_{beam} [GeV]; |t| [GeV^{2}]",46, 2.8,12, 17,3.,20.);
    TCanvas* C6 = new TCanvas("C6","Et",500,500);
    C6->Divide(2,1);
    C6->cd(1);
    T->Draw("TMath::Abs(t):Original_E>>Et_MF_All",wMF,"col2z");
    C6->cd(2);
    T->Draw("TMath::Abs(t):Original_E>>Et_SRC_All",wSRC,"col2z");
     
    // divide by 5 for 5 nuclear targets 'sharing' the beam time

    /*
    TCanvas TmpC;
    T->Draw("1","weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1)/5.","h");
    T->Draw("1","weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1&&TMath::Abs(theta_cm-90)<10)/5.","h same");

    TCanvas TmpC2;
    T->Draw("1"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3                            )*0.5*0.8/5.","h");
    T->Draw("1"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8/5.","h same");
    */

    TCanvas* TmpC1 = new TCanvas("TmpC1","theta_recoil",500,500);
    TH1F* hth_rec = new TH1F("hth_rec","; #theta_{recoil} [#circ]; counts",18,0,180);
    TmpC1->cd();
    T->Draw("theta_recoil>>hth_rec"  ,wSRC,"h");
    T->Draw("theta_recoil"  ,wSRC90,"h same");
    
    TCanvas* TmpC3 = new TCanvas("TmpC3","t for all theta range",800,600);
    TH1F* ht = new TH1F("ht","; |t| [GeV^{2}]; counts",18,2.,20.);
    ht->SetTitle("");
    ht->SetLineColor(8);
    //    ht->GetYaxis()->SetRangeUser(0.1,500.);
    TH1F* ht2 = new TH1F("ht2","; |t| [GeV^{2}]; counts",18,2.,20.);
    TmpC3->cd();
    gPad->SetLogy();
    T->Draw("TMath::Abs(t)>>ht"  ,wMF,"h");
    T->Draw("TMath::Abs(t)>>ht2"      ,wSRC,"same");
    
    TLegend* leg = new TLegend(0.5,0.5,0.75,0.75);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.04);
    leg->AddEntry(ht,"MF, #theta_{cm} in (50, 130)#circ","l");
    leg->AddEntry(ht2, "SRC, #theta_{cm} in (50, 130)#circ","l");
    leg->Draw("same");

    //sanity checks:
    TCanvas* sany = new TCanvas("sany","sanity checks",900,300);
    sany->Divide(3,2);
    sany->cd(1);
    T->Draw("Precoil:theta_recoil"  ,wst,"col2z");
    sany->cd(2);
    T->Draw("P_miss:theta_miss"  ,wst,"col2z");
    sany->cd(3);
    T->Draw("Precoil:P_miss"  ,wst,"col2z");
    sany->cd(4);
    T->Draw("theta_cm:t",wst,"col2z");
    sany->cd(5);
    T->Draw("P_miss",wst,"hist");
    sany->cd(6);
    T->Draw("P_miss");
    
    theta_P_p_MF_All->GetXaxis()->SetTitleSize(0.06);
    theta_P_p_MF_All->GetYaxis()->SetTitleSize(0.06);
    theta_P_pi_MF_All->GetXaxis()->SetTitleSize(0.06);
    theta_P_pi_MF_All->GetYaxis()->SetTitleSize(0.06);
    theta_Ppi_MF_All->GetXaxis()->SetTitleSize(0.06);
    theta_Ppi_MF_All->GetYaxis()->SetTitleSize(0.06);
    phi_MF_All->GetXaxis()->SetTitleSize(0.06);
    
    theta_P_p_MF_All->GetXaxis()->SetTitleOffset(0.8);
    theta_P_p_MF_All->GetYaxis()->SetTitleOffset(0.8);
    theta_P_pi_MF_All->GetXaxis()->SetTitleOffset(0.8);
    theta_P_pi_MF_All->GetYaxis()->SetTitleOffset(0.8);
    theta_Ppi_MF_All->GetXaxis()->SetTitleOffset(0.8);
    theta_Ppi_MF_All->GetYaxis()->SetTitleOffset(0.8);
    phi_MF_All->GetXaxis()->SetTitleOffset(0.8);
    
    theta_P_p_MF_All->GetXaxis()->SetLabelSize(0.06);
    theta_P_p_MF_All->GetYaxis()->SetLabelSize(0.06);
    theta_P_pi_MF_All->GetXaxis()->SetLabelSize(0.06);
    theta_P_pi_MF_All->GetYaxis()->SetLabelSize(0.06);
    theta_Ppi_MF_All->GetXaxis()->SetLabelSize(0.06);
    theta_Ppi_MF_All->GetYaxis()->SetLabelSize(0.06);
    phi_MF_All->GetXaxis()->SetLabelSize(0.06);
    

    theta_P_p_SRC_All->GetXaxis()->SetTitleSize(0.06);
    theta_P_p_SRC_All->GetYaxis()->SetTitleSize(0.06);
    theta_P_pi_SRC_All->GetXaxis()->SetTitleSize(0.06);
    theta_P_pi_SRC_All->GetYaxis()->SetTitleSize(0.06);
    theta_Ppi_SRC_All->GetXaxis()->SetTitleSize(0.06);
    theta_Ppi_SRC_All->GetYaxis()->SetTitleSize(0.06);
    phi_SRC_All->GetXaxis()->SetTitleSize(0.06);
    
    theta_P_p_SRC_All->GetXaxis()->SetTitleOffset(0.8);
    theta_P_p_SRC_All->GetYaxis()->SetTitleOffset(0.8);
    theta_P_pi_SRC_All->GetXaxis()->SetTitleOffset(0.8);
    theta_P_pi_SRC_All->GetYaxis()->SetTitleOffset(0.8);
    theta_Ppi_SRC_All->GetXaxis()->SetTitleOffset(0.8);
    theta_Ppi_SRC_All->GetYaxis()->SetTitleOffset(0.8);
    phi_SRC_All->GetXaxis()->SetTitleOffset(0.8);
    
    theta_P_p_SRC_All->GetXaxis()->SetLabelSize(0.06);
    theta_P_p_SRC_All->GetYaxis()->SetLabelSize(0.06);
    theta_P_pi_SRC_All->GetXaxis()->SetLabelSize(0.06);
    theta_P_pi_SRC_All->GetYaxis()->SetLabelSize(0.06);
    theta_Ppi_SRC_All->GetXaxis()->SetLabelSize(0.06);
    theta_Ppi_SRC_All->GetYaxis()->SetLabelSize(0.06);
    phi_SRC_All->GetXaxis()->SetLabelSize(0.06);   
 
}













