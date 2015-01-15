
void Display(){

  //hCosPointing_MC->SetFillStyle(3325);
  //hCosPointing_MC->SetFillColor(2);


  TFile*finputMC=new TFile("results/output_isData0_genmatched0.root");
  TFile*finputMC_GenM=new TFile("results/output_isData0_genmatched1.root");
  TFile*finputData=new TFile("results/output_isData1_genmatched0.root");

  TH1F*hPt_MC=(TH1F*)finputMC->Get("hPt");
  TH1F*hDecaySign_MC=(TH1F*)finputMC->Get("hDecaySign");
  TH1F*hCosPointing_MC=(TH1F*)finputMC->Get("hCosPointing");
  TH1F*hVertexProb_MC=(TH1F*)finputMC->Get("hVertexProb");
  TH1F*hMassD_MC=(TH1F*)finputMC->Get("hMassD");

  TH1F*hPt_MC_GenM=(TH1F*)finputMC_GenM->Get("hPt");
  TH1F*hDecaySign_MC_GenM=(TH1F*)finputMC_GenM->Get("hDecaySign");
  TH1F*hCosPointing_MC_GenM=(TH1F*)finputMC_GenM->Get("hCosPointing");
  TH1F*hVertexProb_MC_GenM=(TH1F*)finputMC_GenM->Get("hVertexProb");
  TH1F*hMassD_MC_GenM=(TH1F*)finputMC_GenM->Get("hMassD");


  TH1F*hPt_Data=(TH1F*)finputData->Get("hPt");
  TH1F*hDecaySign_Data=(TH1F*)finputData->Get("hDecaySign");
  TH1F*hCosPointing_Data=(TH1F*)finputData->Get("hCosPointing");
  TH1F*hVertexProb_Data=(TH1F*)finputData->Get("hVertexProb");
  TH1F*hMassD_Data=(TH1F*)finputData->Get("hMassD");

  
  hPt_MC->Sumw2();
  hDecaySign_MC->Sumw2();
  hCosPointing_MC->Sumw2();
  hVertexProb_MC->Sumw2();
  hMassD_MC->Sumw2();
  
  hPt_MC_GenM->Sumw2();
  hDecaySign_MC_GenM->Sumw2();
  hCosPointing_MC_GenM->Sumw2();
  hVertexProb_MC_GenM->Sumw2();
  hMassD_MC_GenM->Sumw2();
  
  hPt_Data->Sumw2();
  hDecaySign_Data->Sumw2();
  hCosPointing_Data->Sumw2();
  hVertexProb_Data->Sumw2();
  hMassD_Data->Sumw2();

  
  int normMC=hPt_MC->GetEntries();
  int normMC_GenM=hPt_MC_GenM->GetEntries();
  int normData=hPt_Data->GetEntries();
  
  cout<<"number of MC entries"<<normMC<<endl;
  

  hPt_MC->Scale(1./normMC); 
  hDecaySign_MC->Scale(1./normMC); 
  hCosPointing_MC->Scale(1./normMC); 
  hVertexProb_MC->Scale(1./normMC); 

  hPt_MC_GenM->Scale(1./normMC_GenM); 
  hDecaySign_MC_GenM->Scale(1./normMC_GenM); 
  hCosPointing_MC_GenM->Scale(1./normMC_GenM); 
  hVertexProb_MC_GenM->Scale(1./normMC_GenM); 
  
  hPt_Data->Scale(1./normData); 
  hDecaySign_Data->Scale(1./normData); 
  hCosPointing_Data->Scale(1./normData); 
  hVertexProb_Data->Scale(1./normData); 

  TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
  leg->AddEntry(hDecaySign_Data,"D^{+} data","f");
  leg->AddEntry(hDecaySign_MC,  "D^{+} MC","f");
  leg->AddEntry(hDecaySign_MC_GenM,  "D^{+} MC gen matched","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  
    
  TCanvas*canvas=new TCanvas("canvas","canvas",1400,500);
  canvas->SetLogy();
  canvas->Divide(3,1);
    
  canvas->cd(1);
  canvas_1->SetLogy();
  hDecaySign_MC->SetMinimum(1e-5);
  hDecaySign_MC->SetMaximum(10);
  hDecaySign_MC->SetMarkerStyle(0);
  hDecaySign_MC->SetLineColor(2);
  hDecaySign_MC->SetLineWidth(1);
  hDecaySign_MC->SetYTitle("Entries");
  hDecaySign_MC->SetXTitle("normalized decay length");
  hDecaySign_MC->Draw("hist e");
  hDecaySign_Data->SetMarkerStyle(0);
  hDecaySign_Data->SetLineColor(1);
  hDecaySign_Data->SetLineWidth(1);
  hDecaySign_Data->Draw("same hist e");
  hDecaySign_MC_GenM->SetMarkerStyle(0);
  hDecaySign_MC_GenM->SetLineColor(4);
  hDecaySign_MC_GenM->SetLineWidth(1);
  hDecaySign_MC_GenM->Draw("same hist e");

  leg->Draw();

  
  canvas->cd(2);
  canvas_2->SetLogy();
  
  hCosPointing_MC->SetMinimum(1e-6);
  hCosPointing_MC->SetMaximum(100);
  hCosPointing_MC->SetMarkerStyle(0);
  hCosPointing_MC->SetLineColor(2);
  hCosPointing_MC->SetLineWidth(1);
  hCosPointing_MC->SetYTitle("Entries");
  hCosPointing_MC->SetXTitle("Cosine pointing angle");
  hCosPointing_MC->Draw("hist e");
  hCosPointing_Data->SetMarkerStyle(0);
  hCosPointing_Data->SetLineColor(1);
  hCosPointing_Data->SetLineWidth(1);
  hCosPointing_Data->Draw("same hist e");
  hCosPointing_MC_GenM->SetMarkerStyle(0);
  hCosPointing_MC_GenM->SetLineColor(4);
  hCosPointing_MC_GenM->SetLineWidth(1);
  hCosPointing_MC_GenM->Draw("same hist e");

  leg->Draw();
  
  
  canvas->cd(3);
  
  hVertexProb_MC->SetMinimum(0);
  hVertexProb_MC->SetMaximum(0.12);
  hVertexProb_MC->SetMarkerStyle(0);
  hVertexProb_MC->SetLineColor(2);
  hVertexProb_MC->SetLineWidth(1);
  hVertexProb_MC->SetYTitle("Entries");
  hVertexProb_MC->SetXTitle("vertex probability");
  hVertexProb_MC->Draw("hist e");
  hVertexProb_Data->SetMarkerStyle(0);
  hVertexProb_Data->SetLineColor(1);
  hVertexProb_Data->SetLineWidth(1);
  hVertexProb_Data->Draw("same hist e");
  hVertexProb_MC_GenM->SetMarkerStyle(0);
  hVertexProb_MC_GenM->SetLineColor(4);
  hVertexProb_MC_GenM->SetLineWidth(1);
  hVertexProb_MC_GenM->Draw("same hist e");

  leg->Draw();

 
  canvas->SaveAs("Plots/canvas.pdf");


}

