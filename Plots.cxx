#include "rate.C"
void Plots(){
    
  SetRootPalette(1);
    gStyle->SetOptStat(0);
    gStyle->SetLabelSize(0.05,"X");
    gStyle->SetLabelSize(0.05,"Y");
    gStyle->SetLabelSize(0.05,"Z");
    gStyle->SetTitleSize(0.05,"X");
    gStyle->SetTitleSize(0.05,"Y");
    gStyle->SetTitleSize(0.05,"Z");

    TTree* T = ((TTree*)(TFile::Open("gn_pimp_N10000.root")->Get("T")));
    
    // Mean Field. Theta c.m. = 90
    TH2F* theta_P_p_MF_90 = new TH2F("theta_P_p_MF_90","; |P_{#pi}| [GeV/c]; #theta_{#pi} [degrees]",24,0,12 , 14,5,75);
    TH2F* theta_P_pi_MF_90 = new TH2F("theta_P_pi_MF_90","; |P_{p}| [GeV/c]; #theta_{p} [degrees]",24,0,12 , 14,5,75);
    TH2F* theta_Ppi_MF_90 = new TH2F("theta_Ppi_MF_90","; #theta_{p} [GeV/c]; #theta_{#pi} [degrees]",14,5,75 , 14,5,75);
    TH1F* phi_MF_90 = new TH1F("phi_MF_90","; #phi_{#pi} - #phi_{p} [degrees]",40,160,200);
    TCanvas* C1 = new TCanvas("C1","C1",800,800);
    C1->Divide(2,2);
    C1->cd(1);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P3:absP3>>theta_P_p_MF_90"      , "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1&&TMath::Abs(theta_cm-90)<10)","col2z");
    C1->cd(2);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P4:absP4>>theta_P_pi_MF_90"      , "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1&&TMath::Abs(theta_cm-90)<10)","col2z");
    C1->cd(3);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P4:theta_P3>>theta_Ppi_MF_90", "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1&&TMath::Abs(theta_cm-90)<10)","col2z");
    C1->cd(4);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("TMath::Abs(phi_P3-phi_P4)>>phi_MF_90","weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1&&TMath::Abs(theta_cm-90)<10)","h");
    
    /*    theta_P_p_MF_90->SetXTitle("|P_{p}| [GeV/c]");
    theta_P_p_MF_90->SetYTitle("#theta_{p} [degrees]");
    theta_P_pi_MF_90->SetXTitle("|P_{#pi}| [GeV/c]");
    theta_P_pi_MF_90->SetYTitle("#theta_{#pi} [degrees]");
    theta_Ppi_MF_90->SetXTitle("#theta_{p} [degrees]");
    theta_Ppi_MF_90->SetYTitle("#theta_{#pi} [degrees]");
    phi_MF_90->SetXTitle("#Delta#phi [degrees]");
    */
     
    
    // Mean Field. Theta c.m. = All
    TH2F* theta_P_p_MF_All = new TH2F("theta_P_p_MF_All","; |P_{p}| [GeV/c]; #theta_{p} [degrees]",24,0,12 , 14,5,75);
    TH2F* theta_P_pi_MF_All = new TH2F("theta_P_pi_MF_All","; |P_{#pi}| [GeV/c]; #theta_{#pi} [degrees]",24,0,12 , 14,5,75);
    TH2F* theta_Ppi_MF_All = new TH2F("theta_Ppi_MF_All","; #theta_{p} [degrees]; #theta_{#pi} [degrees]",14,5,75 , 14,5,75);
    TH1F* phi_MF_All = new TH1F("phi_MF_All","; #Delta#phi [degrees]",40,160,200);
    TCanvas* C2 = new TCanvas("C2","C2",800,800);
    C2->Divide(2,2);
    C2->cd(1);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P4:absP4>>theta_P_pi_MF_All"      , "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1)","colz");
    C2->cd(2);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P3:absP3>>theta_P_p_MF_All"      , "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1)","colz");
    C2->cd(3);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P4:theta_P3>>theta_Ppi_MF_All", "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1)","colz");
    C2->cd(4);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("TMath::Abs(phi_P4-phi_P3)>>phi_MF_All","weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1)","h");
    
    // SRC. Theta c.m. = 90
    TH2F* theta_P_p_SRC_90 = new TH2F("theta_P_p_SRC_90","; |P_{p}| [GeV/c]; #theta_{p} [degrees]",24,0,12 , 14,5,75);
    TH2F* theta_P_pi_SRC_90 = new TH2F("theta_P_pi_SRC_90","; |P_{#pi}| [GeV/c]; #theta_{#pi} [degrees]",24,0,12 , 14,5,75);
    TH2F* theta_Ppi_SRC_90 = new TH2F("theta_Ppi_SRC_90","; #theta_{p} [degrees]; #theta_{#pi} [degrees]",14,5,75 , 14,5,75);
    TH1F* phi_SRC_90 = new TH1F("phi_SRC_90","; #Delta#phi [degrees]",40,160,200);
    TCanvas* C3 = new TCanvas("C3","C3",800,800);
    C3->Divide(2,2);
    C3->cd(1);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P4:absP4>>theta_P_p_SRC_90","weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8","col2z");
    C3->cd(2);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P3:absP3>>theta_P_pi_SRC_90",           "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8","col2z");
    C3->cd(3);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P4:theta_P3>>theta_Ppi_SRC_90",      "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8","col2z");
    C3->cd(4);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("TMath::Abs(phi_P4-phi_P3)>>phi_SRC_90"  ,  "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8","h");
    
    
    // SRC. Theta c.m. = All
    TH2F* theta_P_p_SRC_All = new TH2F("theta_P_p_SRC_All","; |P_{p}| [GeV/c]; #theta_{p} [degrees]",24,0,12 , 14,5,75);
    TH2F* theta_P_pi_SRC_All = new TH2F("theta_P_pi_SRC_All","; |P_{#pi}| [GeV/c]; #theta_{#pi} [degrees]",24,0,12 , 14,5,75);
    TH2F* theta_Ppi_SRC_All = new TH2F("theta_Ppi_SRC_All","; #theta_{p} [degrees]; #theta_{#pi} [degrees]",14,5,75 , 14,5,75);
    TH1F* phi_SRC_All = new TH1F("phi_SRC_All","; #Delta#phi [degrees]",40,160,200);
    TCanvas* C4 = new TCanvas("C4","C4",800,800);
    C4->Divide(2,2);
    C4->cd(1);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P4:absP4>>theta_P_pi_SRC_All","weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3)*0.5*0.8","colz");
    C4->cd(2);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P3:absP3>>theta_P_p_SRC_All","weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3)*0.5*0.8","colz");
    C4->cd(3);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("theta_P4:theta_P3>>theta_Ppi_SRC_All", "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3)*0.5*0.8","colz");
    C4->cd(4);
    gPad->SetGridx();
    gPad->SetGridy();
    T->Draw("TMath::Abs(phi_P4-phi_P3)>>phi_SRC_All", "weight_kk*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3)*0.5*0.8","h");


    // TCanvas* C5 = new TCanvas("C5","C5",800,800);
    cout<<"MF, 90, N events = "<<phi_MF_90->Integral(1,40)<<endl;
    cout<<"MF, All, N events = "<<phi_MF_All->Integral(1,40)<<endl;
    cout<<"SRC, 90, N events = "<<phi_SRC_90->Integral(1,40)<<endl;
    cout<<"SRC, All, N events = "<<phi_SRC_All->Integral(1,40)<<endl;

    /*
    
    // divide by 5 for 5 nuclear targets 'sharing' the beam time

    
    TCanvas TmpC;
    T->Draw("1","weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1)/5.","h");
    T->Draw("1","weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1&&TMath::Abs(theta_cm-90)<10)/5.","h same");

    TCanvas TmpC2;
    T->Draw("1"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3                            )*0.5*0.8/5.","h");
    T->Draw("1"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8/5.","h same");

    TCanvas TmpC1;
    T->Draw("theta_recoil>>(18,0,180)"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<1600&&Precoil>0.3                            )*0.5*0.8/5.","h");
    T->Draw("theta_recoil"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<1600&&Precoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8/5.","h same");
    
    TCanvas TmpC3;
    T->Draw("-t>>aa(17,3,20)"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1                            )/5.","hist");
    T->Draw("-t"               ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil<0.1&&TMath::Abs(theta_cm-90)<10)/5.","hist same");
    
    TCanvas TmpC4;
    T->Draw("-t>>bb(17,3,20)"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3                            )*0.5*0.8/5.","hist");
    T->Draw("-t"               ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&Precoil>0.1&&theta_recoil<160&&Precoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8/5.","hist same");

    
    
    
    
    theta_P_p_MF_90->GetXaxis()->SetTitleSize(0.06);
    theta_P_p_MF_90->GetYaxis()->SetTitleSize(0.06);
    theta_P_pi_MF_90->GetXaxis()->SetTitleSize(0.06);
    theta_P_pi_MF_90->GetYaxis()->SetTitleSize(0.06);
    theta_Ppi_MF_90->GetXaxis()->SetTitleSize(0.06);
    theta_Ppi_MF_90->GetYaxis()->SetTitleSize(0.06);
    phi_MF_90->GetXaxis()->SetTitleSize(0.06);
    
    theta_P_p_MF_90->GetXaxis()->SetTitleOffset(0.8);
    theta_P_p_MF_90->GetYaxis()->SetTitleOffset(0.8);
    theta_P_pi_MF_90->GetXaxis()->SetTitleOffset(0.8);
    theta_P_pi_MF_90->GetYaxis()->SetTitleOffset(0.8);
    theta_Ppi_MF_90->GetXaxis()->SetTitleOffset(0.8);
    theta_Ppi_MF_90->GetYaxis()->SetTitleOffset(0.8);
    phi_MF_90->GetXaxis()->SetTitleOffset(0.8);
    
    theta_P_p_MF_90->GetXaxis()->SetLabelSize(0.06);
    theta_P_p_MF_90->GetYaxis()->SetLabelSize(0.06);
    theta_P_pi_MF_90->GetXaxis()->SetLabelSize(0.06);
    theta_P_pi_MF_90->GetYaxis()->SetLabelSize(0.06);
    theta_Ppi_MF_90->GetXaxis()->SetLabelSize(0.06);
    theta_Ppi_MF_90->GetYaxis()->SetLabelSize(0.06);
    phi_MF_90->GetXaxis()->SetLabelSize(0.06);
    
    
    
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
    
    
    
    theta_P_p_SRC_90->GetXaxis()->SetTitleSize(0.06);
    theta_P_p_SRC_90->GetYaxis()->SetTitleSize(0.06);
    theta_P_pi_SRC_90->GetXaxis()->SetTitleSize(0.06);
    theta_P_pi_SRC_90->GetYaxis()->SetTitleSize(0.06);
    theta_Ppi_SRC_90->GetXaxis()->SetTitleSize(0.06);
    theta_Ppi_SRC_90->GetYaxis()->SetTitleSize(0.06);
    phi_SRC_90->GetXaxis()->SetTitleSize(0.06);
    
    theta_P_p_SRC_90->GetXaxis()->SetTitleOffset(0.8);
    theta_P_p_SRC_90->GetYaxis()->SetTitleOffset(0.8);
    theta_P_pi_SRC_90->GetXaxis()->SetTitleOffset(0.8);
    theta_P_pi_SRC_90->GetYaxis()->SetTitleOffset(0.8);
    theta_Ppi_SRC_90->GetXaxis()->SetTitleOffset(0.8);
    theta_Ppi_SRC_90->GetYaxis()->SetTitleOffset(0.8);
    phi_SRC_90->GetXaxis()->SetTitleOffset(0.8);
    
    theta_P_p_SRC_90->GetXaxis()->SetLabelSize(0.06);
    theta_P_p_SRC_90->GetYaxis()->SetLabelSize(0.06);
    theta_P_pi_SRC_90->GetXaxis()->SetLabelSize(0.06);
    theta_P_pi_SRC_90->GetYaxis()->SetLabelSize(0.06);
    theta_Ppi_SRC_90->GetXaxis()->SetLabelSize(0.06);
    theta_Ppi_SRC_90->GetYaxis()->SetLabelSize(0.06);
    phi_SRC_90->GetXaxis()->SetLabelSize(0.06);
    
    
    
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
    
    */
    
    
}













