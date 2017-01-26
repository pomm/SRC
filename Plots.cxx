{
    
    
    gStyle->SetOptStat(0);
//    TTree* T = ((TTree*)(TFile::Open("FullMC_Gluex_9GeV_StandingProton.root")->Get("T")));
    TTree* T = ((TTree*)(TFile::Open("FullMC_Gluex_9GeV_test1.root")->Get("T")));
    
    
    
    // Mean Field. Theta c.m. = 90
    TH2F* theta_P_p_MF_90 = new TH2F("theta_P_p_MF_90","",24,0,12 , 70,5,75);
    TH2F* theta_P_pi_MF_90 = new TH2F("theta_P_pi_MF_90","",24,0,12 , 70,5,75);
    TH2F* theta_Ppi_MF_90 = new TH2F("theta_Ppi_MF_90","",70,5,75 , 70,5,75);
    TH1F* phi_MF_90 = new TH1F("phi_MF_90","",40,160,200);
    TCanvas C1;
    C1.Divide(2,2);
    C1.cd(1);
    T->Draw("theta_P1:P1>>theta_P_p_MF_90"      , "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1&&TMath::Abs(theta_cm-90)<10)","col2z");
    C1.cd(2);
    T->Draw("theta_P2:P2>>theta_P_pi_MF_90"      , "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1&&TMath::Abs(theta_cm-90)<10)","col2z");
    C1.cd(3);
    T->Draw("theta_P2:theta_P1>>theta_Ppi_MF_90", "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1&&TMath::Abs(theta_cm-90)<10)","col2z");
    C1.cd(4);
    T->Draw("TMath::Abs(phi_P1-phi_P2)>>phi_MF_90","weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1&&TMath::Abs(theta_cm-90)<10)","h");
    
    theta_P_p_MF_90->SetXTitle("|P_{p}| [GeV/c]");
    theta_P_p_MF_90->SetYTitle("#theta_{p} [degrees]");
    theta_P_pi_MF_90->SetXTitle("|P_{#pi}| [GeV/c]");
    theta_P_pi_MF_90->SetYTitle("#theta_{#pi} [degrees]");
    theta_Ppi_MF_90->SetXTitle("#theta_{p} [degrees]");
    theta_Ppi_MF_90->SetYTitle("#theta_{#pi} [degrees]");
    phi_MF_90->SetXTitle("#Delta#phi [degrees]");

    
    
    // Mean Field. Theta c.m. = All
    TH2F* theta_P_p_MF_All = new TH2F("theta_P_p_MF_All","",24,0,12 , 70,5,75);
    theta_P_p_MF_All->SetXTitle("|P_{p}| [GeV/c]");
    theta_P_p_MF_All->SetYTitle("#theta_{p} [degrees]");
    TH2F* theta_P_pi_MF_All = new TH2F("theta_P_pi_MF_All","",24,0,12 , 70,5,75);
    theta_P_pi_MF_All->SetXTitle("|P_{#pi}| [GeV/c]");
    theta_P_pi_MF_All->SetYTitle("#theta_{#pi} [degrees]");
    TH2F* theta_Ppi_MF_All = new TH2F("theta_Ppi_MF_All","",70,5,75 , 70,5,75);
    theta_Ppi_MF_All->SetXTitle("#theta_{p} [degrees]");
    theta_Ppi_MF_All->SetYTitle("#theta_{#pi} [degrees]");
    TH1F* phi_MF_All = new TH1F("phi_MF_All","",40,160,200);
    phi_MF_All->SetXTitle("#Delta#phi [degrees]");
    TCanvas C2;
    C2.Divide(2,2);
    C2.cd(1);
    T->Draw("theta_P1:P1>>theta_P_p_MF_All"      , "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1)","col2z");
    C2.cd(2);
    T->Draw("theta_P2:P2>>theta_P_pi_MF_All"      , "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1)","col2z");
    C2.cd(3);
    T->Draw("theta_P2:theta_P1>>theta_Ppi_MF_All", "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1)","col2z");
    C2.cd(4);
    T->Draw("TMath::Abs(phi_P1-phi_P2)>>phi_MF_All","weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1)","h");

    
    // SRC. Theta c.m. = 90
    TH2F* theta_P_p_SRC_90 = new TH2F("theta_P_p_SRC_90","",24,0,12 , 70,5,75);
    theta_P_p_SRC_90->SetXTitle("|P_{p}| [GeV/c]");
    theta_P_p_SRC_90->SetYTitle("#theta_{p} [degrees]");
    TH2F* theta_P_pi_SRC_90 = new TH2F("theta_P_pi_SRC_90","",24,0,12 , 70,5,75);
    theta_P_pi_SRC_90->SetXTitle("|P_{#pi}| [GeV/c]");
    theta_P_pi_SRC_90->SetYTitle("#theta_{#pi} [degrees]");
    TH2F* theta_Ppi_SRC_90 = new TH2F("theta_Ppi_SRC_90","",70,5,75 , 70,5,75);
    theta_Ppi_SRC_90->SetXTitle("#theta_{p} [degrees]");
    theta_Ppi_SRC_90->SetYTitle("#theta_{#pi} [degrees]");
    TH1F* phi_SRC_90 = new TH1F("phi_SRC_90","",40,160,200);
    phi_SRC_90->SetXTitle("#Delta#phi [degrees]");
    TCanvas C3;
    C3.Divide(2,2);
    C3.cd(1);
    T->Draw("theta_P1:P1>>theta_P_p_SRC_90",            "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8","col2z");
    C3.cd(2);
    T->Draw("theta_P2:P2>>theta_P_pi_SRC_90",           "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8","col2z");
    C3.cd(3);
    T->Draw("theta_P2:theta_P1>>theta_Ppi_SRC_90",      "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8","col2z");
    C3.cd(4);
    T->Draw("TMath::Abs(phi_P1-phi_P2)>>phi_SRC_90"  ,  "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8","h");
    
    
    // SRC. Theta c.m. = All
    TH2F* theta_P_p_SRC_All = new TH2F("theta_P_p_SRC_All","",24,0,12 , 70,5,75);
    theta_P_p_SRC_All->SetXTitle("|P_{p}| [GeV/c]");
    theta_P_p_SRC_All->SetYTitle("#theta_{p} [degrees]");
    TH2F* theta_P_pi_SRC_All = new TH2F("theta_P_pi_SRC_All","",24,0,12 , 70,5,75);
    theta_P_pi_SRC_All->SetXTitle("|P_{#pi}| [GeV/c]");
    theta_P_pi_SRC_All->SetYTitle("#theta_{#pi} [degrees]");
    TH2F* theta_Ppi_SRC_All = new TH2F("theta_Ppi_SRC_All","",70,5,75 , 70,5,75);
    theta_Ppi_SRC_All->SetXTitle("#theta_{p} [degrees]");
    theta_Ppi_SRC_All->SetYTitle("#theta_{#pi} [degrees]");
    TH1F* phi_SRC_All = new TH1F("phi_SRC_All","",40,160,200);
    phi_SRC_All->SetXTitle("#Delta#phi [degrees]");
    TCanvas C4;
    C4.Divide(2,2);
    C4.cd(1);
    T->Draw("theta_P1:P1>>theta_P_p_SRC_All"                ,         "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3)*0.5*0.8","col2z");
    C4.cd(2);
    T->Draw("theta_P2:P2>>theta_P_pi_SRC_All"                ,        "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3)*0.5*0.8","col2z");
    C4.cd(3);
    T->Draw("theta_P2:theta_P1>>theta_Ppi_SRC_All"          ,         "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3)*0.5*0.8","col2z");
    C4.cd(4);
    T->Draw("TMath::Abs(phi_P1-phi_P2)>>phi_SRC_All"  ,               "weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3)*0.5*0.8","h");



    
    
    // divide by 5 for 5 nuclear targets 'sharing' the beam time

    
    TCanvas TmpC;
    T->Draw("1","weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1)/5.","h");
    T->Draw("1","weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1&&TMath::Abs(theta_cm-90)<10)/5.","h same");

    TCanvas TmpC2;
    T->Draw("1"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3                            )*0.5*0.8/5.","h");
    T->Draw("1"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8/5.","h same");

    TCanvas TmpC1;
    T->Draw("theta_recoil>>(18,0,180)"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<1600&&P_recoil>0.3                            )*0.5*0.8/5.","h");
    T->Draw("theta_recoil"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<1600&&P_recoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8/5.","h same");
    
    TCanvas TmpC3;
    T->Draw("-t>>aa(17,3,20)"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1                            )/5.","hist");
    T->Draw("-t"               ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil<0.1&&TMath::Abs(theta_cm-90)<10)/5.","hist same");
    
    TCanvas TmpC4;
    T->Draw("-t>>bb(17,3,20)"  ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3                            )*0.5*0.8/5.","hist");
    T->Draw("-t"               ,"weight*(TMath::Abs(t)>3&&TMath::Abs(u)>3&&P_recoil>0.1&&theta_recoil<160&&P_recoil>0.3&&TMath::Abs(theta_cm-90)<10)*0.5*0.8/5.","hist same");

    
    
    
    
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
    
    /*
    
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
    
    cout<<"MF, 90, N events = "<<phi_MF_90->Integral()<<endl;
    cout<<"MF, All, N events = "<<phi_MF_All->Integral()<<endl;
    cout<<"SRC, 90, N events = "<<phi_SRC_90->Integral()<<endl;
    cout<<"SRC, All, N events = "<<phi_SRC_All->Integral()<<endl;

    cout<<"MF, 90, N events = "<<theta_P_p_MF_90->Integral()<<endl;
    cout<<"MF, All, N events = "<<theta_P_p_MF_All->Integral()<<endl;
    cout<<"SRC, 90, N events = "<<theta_P_p_SRC_90->Integral()<<endl;
    cout<<"SRC, All, N events = "<<theta_P_p_SRC_All->Integral()<<endl;
}













