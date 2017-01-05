void SetRootPalette(Int_t pal = 0){

  // pal =  1: rainbow\n"
  // pal =  2: reverse-rainbow\n"
  // pal =  3: amber\n"
  // pal =  4: reverse-amber\n"
  // pal =  5: blue/white\n"
  // pal =  6: white/blue\n"
  // pal =  7: red temperature\n"
  // pal =  8: reverse-red temperature\n"
  // pal =  9: green/white\n"
  // pal = 10: white/green\n"
  // pal = 11: orange/blue\n"
  // pal = 12: blue/orange\n"
  // pal = 13: white/black\n"
  // pal = 14: black/white\n"

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  gStyle->SetNumberContours(NCont);

  if (pal < 1 && pal> 14) return;
  else pal--;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[14][NRGBs]   = {{ 0.00, 0.00, 0.87, 1.00, 0.51 },
			       { 0.51, 1.00, 0.87, 0.00, 0.00 },
			       { 0.17, 0.39, 0.62, 0.79, 1.00 },
			       { 1.00, 0.79, 0.62, 0.39, 0.17 },
			       { 0.00, 0.00, 0.00, 0.38, 1.00 },
			       { 1.00, 0.38, 0.00, 0.00, 0.00 },
			       { 0.00, 0.50, 0.89, 0.95, 1.00 },
			       { 1.00, 0.95, 0.89, 0.50, 0.00 },
			       { 0.00, 0.00, 0.38, 0.75, 1.00 },
			       { 0.00, 0.34, 0.61, 0.84, 1.00 },
			       { 0.75, 1.00, 0.24, 0.00, 0.00 },
			       { 0.00, 0.00, 0.24, 1.00, 0.75 },
			       { 0.00, 0.34, 0.61, 0.84, 1.00 },
			       { 1.00, 0.84, 0.61, 0.34, 0.00 }
  };
  Double_t green[14][NRGBs] = {{ 0.00, 0.81, 1.00, 0.20, 0.00 },    
			       { 0.00, 0.20, 1.00, 0.81, 0.00 },
			       { 0.01, 0.02, 0.39, 0.68, 1.00 },
			       { 1.00, 0.68, 0.39, 0.02, 0.01 },
			       { 0.00, 0.00, 0.38, 0.76, 1.00 },
			       { 1.00, 0.76, 0.38, 0.00, 0.00 },
			       { 0.00, 0.00, 0.27, 0.71, 1.00 },
			       { 1.00, 0.71, 0.27, 0.00, 0.00 },
			       { 0.00, 0.35, 0.62, 0.85, 1.00 },
			       { 1.00, 0.75, 0.38, 0.00, 0.00 },
			       { 0.24, 1.00, 0.75, 0.18, 0.00 },
			       { 0.00, 0.18, 0.75, 1.00, 0.24 },
			       { 0.00, 0.34, 0.61, 0.84, 1.00 },
			       { 1.00, 0.84, 0.61, 0.34, 0.00 }
  };
  Double_t blue[14][NRGBs]  = {{ 0.51, 1.00, 0.12, 0.00, 0.00 },
			       { 0.00, 0.00, 0.12, 1.00, 0.51 },
			       { 0.00, 0.09, 0.18, 0.09, 0.00 },
			       { 0.00, 0.09, 0.18, 0.09, 0.00 },
			       { 0.00, 0.47, 0.83, 1.00, 1.00 },
			       { 1.00, 1.00, 0.83, 0.47, 0.00 },
			       { 0.00, 0.00, 0.00, 0.40, 1.00 },
			       { 1.00, 0.40, 0.00, 0.00, 0.00 },
			       { 0.00, 0.00, 0.00, 0.47, 1.00 },
			       { 1.00, 0.47, 0.00, 0.00, 0.00 },
			       { 0.00, 0.62, 1.00, 0.68, 0.12 },
			       { 0.12, 0.68, 1.00, 0.62, 0.00 },
			       { 0.00, 0.34, 0.61, 0.84, 1.00 },
			       { 1.00, 0.84, 0.61, 0.34, 0.00 }
  };

  TColor::CreateGradientColorTable(NRGBs, stops, red[pal], green[pal], blue[pal], NCont); 
}

void rate(double coincrate = 0.25, double Emax = 12.){

  TF1 * coinc = new TF1("coinc","2.38*log(12./x)",3,12);
  /*
  TVectorD e(91);
  TVectorD Rtar(91);
  for(Int_t i=0; i<91; i++){
    e[i] = 3.+i*0.1;
    Rtar[i]=calc(e[i]);
    }*/

  TH2F* hco = new TH2F("hco","hco",int((Emax-3.)/0.1),3.,Emax,int((Emax-3.)/0.1),3.,Emax);
  TH2F* hta = new TH2F("hta","hta",int((Emax-3.)/0.1),3.,Emax,int((Emax-3.)/0.1),3.,Emax);
  for(int i=0; i<int((Emax-3.)/0.1);i++){
    for(int j=i; j<int((Emax-3.)/0.1); j++){
      hco->SetBinContent(i+1, j+1, 100.*2.38*log((3.+j*0.1)/(3.+i*0.1)));
      hta->SetBinContent(i+1, j+1, calc1(3.+i*0.1, 3.+j*0.1));
    }
  }

  /*
  TGraph* gRtar = new TGraph(e,Rtar);
  gRtar->SetLineWidth(2);
  gRtar->SetLineColor(kGreen+2);
  gRtar->SetTitle("");
  gRtar->GetXaxis()->SetTitle("min E_{#gamma} [GeV]");
  gRtar->GetXaxis()->SetRangeUser(3.,Emax);
  gRtar->GetYaxis()->SetTitle("rate on target");
  */
  TCanvas* c = new TCanvas("c","c",0.,0.,500.,800.);
  c->Divide(1,2);
  c->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  coinc->SetTitle("");
  coinc->GetXaxis()->SetTitle("min E_{#gamma} [GeV]");
  coinc->GetXaxis()->SetRangeUser(3.,Emax);
  coinc->SetLineColor(kBlue);
  coinc->GetYaxis()->SetTitle("coincidenta rate");
  coinc->Draw("");
  c->cd(2);
  //gRtar->Draw("al");

  gStyle->SetOptStat(0);
  SetRootPalette(1);
  TCanvas* c1 = new TCanvas("c1","c1",0.,0.,500.,1000.);
  c1->Divide(1,2);
  c1->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  hco->SetTitle("coincidental rate in %");
  hco->GetXaxis()->SetTitle("min E_{#gamma}");
  hco->GetYaxis()->SetTitle("max E_{#gamma}");
  hco->Draw("col2z");
  c1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogz();
  hta->SetTitle("rate on target [#gamma/s]");
  hta->GetXaxis()->SetTitle("min E_{#gamma}");
  hta->GetYaxis()->SetTitle("max E_{#gamma}");
  hta->Draw("col2z");

  // using constant coinc rate                                                                                                                  
  TF1* fEmax = new TF1("fEmax","x*exp([0]/2.38)",3.,Emax);
  fEmax->SetParameter(0,coincrate);

  TH1F* hTra = new TH1F("hTra","hTra",int((Emax-3.)/0.1),3.,Emax);
  TH2F* hTra2 = new TH2F("hTra","hTra",int((Emax-3.)/0.1),3.,Emax,int((Emax-3.)/0.1),3.,Emax);
  for(int i=0; i<int((Emax-3.)/0.1);i++){
    cout<<3.+0.1*i<<" = Emin, Emax = "<<1.1*(3.+0.1*i)<<", rate = "<<calc1(3.+0.1*i, 1.1*(3.+0.1*i))<<endl;
    hTra->SetBinContent(i+1, calc1(3+0.1*i,1.1*(3.+0.1*i)));
    for(int j=i; j<int((Emax-3.)/0.1); j++){ 
      if(1.1*(3.+0.1*i) >= (3.+j*0.1)){
	hTra2->SetBinContent(i+1, j+1, calc1(3.+i*0.1, 3.+j*0.1));
      }
    }
  }

  TCanvas* c1 = new TCanvas("c2","c2",0.,0.,1000.,500.);
  c1->Divide(2,1);
  c1->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  /*  fEmax->SetTitle("");
  fEmax->GetXaxis()->SetTitle("min E_{#gamma} [GeV]");
  fEmax->GetXaxis()->SetRangeUser(3.,Emax);
  fEmax->SetLineColor(kMagenta);
  fEmax->GetYaxis()->SetTitle("max E_{#gamma} [GeV]");
  fEmax->Draw();*/
  hTra2->SetTitle("rate on target [#gamma/s]");
  hTra2->GetXaxis()->SetTitle("min E_{#gamma} [GeV]");
  hTra2->GetYaxis()->SetTitle("max E_{#gamma} [GeV]");
  hTra2->Draw("col2z");
  c1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  hTra->SetTitle("");
  hTra->GetXaxis()->SetTitle("min E_{#gamma} [GeV]");
  hTra->GetYaxis()->SetTitle("target rate assuming coinc. rate of 25%");
  hTra->GetYaxis()->SetRangeUser(0.,46*1e6);
  hTra->Draw();
  TLegend* pt = new TLegend(0.5,0.5,0.75,0.75);
  pt->AddEntry(hTra2, "E_{max} = E_{min} #upoint 1.1","l");
  pt->SetFillColor(0);
  pt->SetLineColor(0);
  pt->SetTextSize(0.04);
  pt->Draw("same");
}

double calc(double Emin = 3.){
  double Ninit = log(Emax/Emin)*1.19*1e9;
  double ln1 = 0.;
  double ln2 = log(9./7.5);
  double ln3= log(Emax/9.);
  double fr1, fr2, fr3;

  if(Emin <= 7.5){
    fr1 = log(7.5/Emin)/log(Emax/Emin);
    fr2 = ln2/log(Emax/Emin);
    fr3 = ln3/log(Emax/Emin);
  }else if(Emin > 7.5 && Emin < 9. && Emax > 9.){
    fr1 = 0.;
    fr2 = log(9./Emin)/log(Emax/Emin);
    fr3 = ln3/log(Emax/Emin);
  }else if(Emin > 9.){
    fr1 = 0.;
    fr2 = 0.;
    fr3 = 1.;
  }
  //  cout<<"+++++ calc output +++++"<<endl;
  //cout<<"Emin = "<<Emin<<", fr1 = "<<fr1<<", fr2 = "<<fr2<<", fr3 = "<<fr3<<", sum = "<<fr1+fr2+fr3<<endl;
  return Ninit*(fr1*0.223 + fr2*0.376 + fr3*0.286);
}

double calc1(double Emin = 3., double Emax = 12.){
  double Ninit = log(Emax/Emin)*1.19*1e9;
  double ln1 = 0.;
  double ln2 = log(9./7.5);
  double ln3= 0.;
  double ln0 = log(Emax/Emin);
  double fr1, fr2, fr3;

  if(Emin <= 7.5){
    if(Emax <= 7.5){
      fr1 = 1.;
      fr2 = 0.;
      fr3 = 0.;
    }else if(Emax > 7.5 <= 9.){
      fr1 = log(7.5/Emin)/ln0;
      fr2 = log(Emax/7.5)/ln0;
      fr3 = 0.;
    }else if(Emax > 9.){
      fr1 = log(7.5/Emin)/ln0;
      fr2 = ln2/ln0;
      fr3 = log(Emax/9.)/ln0;
    }
  }else if(Emin > 7.5 && Emin <= 9.){
    fr1 = 0.;
    if(Emax >= 7.5 && Emax <= 9.){
      fr2 = 1.;
      fr3 = 0.;
    }else if(Emax > 9.){
      fr2 = log(9./Emin)/ln0;
      fr3 = log(Emax/9.)/ln0;
    }
  }else if(Emin > 9.){
    fr1 = 0.;
    fr2 = 0.;
    fr3 = 1.;
  }
  //    cout<<"+++++ calc output +++++"<<endl;                                                                                                      
  // cout<<"Emin = "<<Emin<<" Emax = "<<Emax<<", fr1 = "<<fr1<<", fr2 = "<<fr2<<", fr3 = "<<fr3<<", sum = "<<fr1+fr2+fr3<<endl;                                      
  return Ninit*(fr1*0.223 + fr2*0.376 + fr3*0.286);
}
