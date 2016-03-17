{
//=========Macro generated from canvas: D0_RAFONLL_Npart/D0_RAFONLL_Npart
//=========  (Wed Jan 13 16:12:23 2016) by ROOT version5.34/10
   TCanvas *D0_RAFONLL_Npart = new TCanvas("D0_RAFONLL_Npart", "D0_RAFONLL_Npart",764,132,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   D0_RAFONLL_Npart->Range(-63.05031,-0.2147239,441.3522,1.503067);
   D0_RAFONLL_Npart->SetFillColor(0);
   D0_RAFONLL_Npart->SetBorderMode(0);
   D0_RAFONLL_Npart->SetBorderSize(0);
   D0_RAFONLL_Npart->SetTickx(1);
   D0_RAFONLL_Npart->SetTicky(1);
   D0_RAFONLL_Npart->SetLeftMargin(0.125);
   D0_RAFONLL_Npart->SetRightMargin(0.08);
   D0_RAFONLL_Npart->SetTopMargin(0.06);
   D0_RAFONLL_Npart->SetBottomMargin(0.125);
   D0_RAFONLL_Npart->SetFrameBorderMode(0);
   D0_RAFONLL_Npart->SetFrameBorderMode(0);
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph0");
   grae->SetTitle("Graph");
   grae->SetFillColor(13);
   grae->SetLineColor(13);
   grae->SetPoint(0,22.06,0.687388);
   grae->SetPointError(0,5,5,0.1759721,0.1759721);
   grae->SetPoint(1,86.23,0.5920716);
   grae->SetPointError(1,5,5,0.1356099,0.1356099);
   grae->SetPoint(2,130.06,0.4306733);
   grae->SetPointError(2,5,5,0.106022,0.106022);
   grae->SetPoint(3,187.35,0.4000138);
   grae->SetPointError(3,5,5,0.1036707,0.1036707);
   grae->SetPoint(4,261.49,0.2923325);
   grae->SetPointError(4,5,5,0.08210243,0.08210243);
   grae->SetPoint(5,355.45,0.2300415);
   grae->SetPointError(5,5,5,0.06953689,0.06953689);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,0,401);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(1.4);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);
   Graph_Graph1->GetXaxis()->SetTitle("N_{part}");
   Graph_Graph1->GetXaxis()->CenterTitle(true);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}} , R_{AA}");
   Graph_Graph1->GetYaxis()->CenterTitle(true);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph1);
   
   grae->Draw("a2");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph1");
   grae->SetTitle("Graph");
   grae->SetFillStyle(0);
   grae->SetPoint(0,22.06,0.687388);
   grae->SetPointError(0,5,5,0.1662957,0.1666203);
   grae->SetPoint(1,86.23,0.5920716);
   grae->SetPointError(1,5,5,0.1432364,0.1435159);
   grae->SetPoint(2,130.06,0.4306733);
   grae->SetPointError(2,5,5,0.1041902,0.1043936);
   grae->SetPoint(3,187.35,0.4000138);
   grae->SetPointError(3,5,5,0.09677296,0.09696184);
   grae->SetPoint(4,261.49,0.2923325);
   grae->SetPointError(4,5,5,0.07072226,0.0708603);
   grae->SetPoint(5,355.45,0.2300415);
   grae->SetPointError(5,5,5,0.05565257,0.05576119);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Graph",100,0,394.789);
   Graph_Graph2->SetMinimum(0.106427);
   Graph_Graph2->SetMaximum(0.9219702);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph2);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph2");
   grae->SetTitle("Graph");
   grae->SetFillColor(13);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,22.06,0.687388);
   grae->SetPointError(0,5,5,0.05725673,0.05725673);
   grae->SetPoint(1,86.23,0.5920716);
   grae->SetPointError(1,5,5,0.05216637,0.05216637);
   grae->SetPoint(2,130.06,0.4306733);
   grae->SetPointError(2,5,5,0.03445954,0.03445954);
   grae->SetPoint(3,187.35,0.4000138);
   grae->SetPointError(3,5,5,0.02786751,0.02786751);
   grae->SetPoint(4,261.49,0.2923325);
   grae->SetPointError(4,5,5,0.02073636,0.02073636);
   grae->SetPoint(5,355.45,0.2300415);
   grae->SetPointError(5,5,5,0.0164228,0.0164228);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","Graph",100,0,394.789);
   Graph_Graph3->SetMinimum(0.1605161);
   Graph_Graph3->SetMaximum(0.7977473);
   Graph_Graph3->SetDirectory(0);
   Graph_Graph3->SetStats(0);
   Graph_Graph3->GetXaxis()->SetLabelFont(42);
   Graph_Graph3->GetXaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetLabelFont(42);
   Graph_Graph3->GetYaxis()->SetTitleFont(42);
   Graph_Graph3->GetZaxis()->SetLabelFont(42);
   Graph_Graph3->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3);
   
   grae->Draw("p");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph3");
   grae->SetTitle("Graph");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#33cc33");
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#33cc33");
   grae->SetLineColor(ci);
   grae->SetPoint(0,22.06,0.79);
   grae->SetPointError(0,5,5,0.107029,0.107029);
   grae->SetPoint(1,86.23,0.75);
   grae->SetPointError(1,5,5,0.1046721,0.1046721);
   grae->SetPoint(2,130.06,0.59);
   grae->SetPointError(2,5,5,0.08012247,0.08012247);
   grae->SetPoint(3,187.35,0.54);
   grae->SetPointError(3,5,5,0.07721373,0.07721373);
   grae->SetPoint(4,261.49,0.49);
   grae->SetPointError(4,5,5,0.06666941,0.06666941);
   grae->SetPoint(5,355.45,0.4);
   grae->SetPointError(5,5,5,0.0538145,0.0538145);
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","Graph",100,0,394.789);
   Graph_Graph4->SetMinimum(0.2911012);
   Graph_Graph4->SetMaximum(0.9521134);
   Graph_Graph4->SetDirectory(0);
   Graph_Graph4->SetStats(0);
   Graph_Graph4->GetXaxis()->SetLabelFont(42);
   Graph_Graph4->GetXaxis()->SetTitleFont(42);
   Graph_Graph4->GetYaxis()->SetLabelFont(42);
   Graph_Graph4->GetYaxis()->SetTitleFont(42);
   Graph_Graph4->GetZaxis()->SetLabelFont(42);
   Graph_Graph4->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph4);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph4");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#33cc33");
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#006600");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#006600");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(22);
   grae->SetPoint(0,22.06,0.79);
   grae->SetPointError(0,5,5,0.11,0.11);
   grae->SetPoint(1,86.23,0.75);
   grae->SetPointError(1,5,5,0.09,0.09);
   grae->SetPoint(2,130.06,0.59);
   grae->SetPointError(2,5,5,0.06,0.06);
   grae->SetPoint(3,187.35,0.54);
   grae->SetPointError(3,5,5,0.05,0.05);
   grae->SetPoint(4,261.49,0.49);
   grae->SetPointError(4,5,5,0.04,0.04);
   grae->SetPoint(5,355.45,0.4);
   grae->SetPointError(5,5,5,0.03,0.03);
   
   TH1F *Graph_Graph5 = new TH1F("Graph_Graph5","Graph",100,0,394.789);
   Graph_Graph5->SetMinimum(0.317);
   Graph_Graph5->SetMaximum(0.953);
   Graph_Graph5->SetDirectory(0);
   Graph_Graph5->SetStats(0);
   Graph_Graph5->GetXaxis()->SetLabelFont(42);
   Graph_Graph5->GetXaxis()->SetTitleFont(42);
   Graph_Graph5->GetYaxis()->SetLabelFont(42);
   Graph_Graph5->GetYaxis()->SetTitleFont(42);
   Graph_Graph5->GetZaxis()->SetLabelFont(42);
   Graph_Graph5->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph5);
   
   grae->Draw("p");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph5");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#3333ff");
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#3333ff");
   grae->SetLineColor(ci);
   grae->SetPoint(0,381,0.1519);
   grae->SetPointError(0,5,5,0.01544347,0.01544347);
   grae->SetPoint(1,329,0.1791);
   grae->SetPointError(1,5,5,0.01954947,0.01954947);
   grae->SetPoint(2,224,0.2358);
   grae->SetPointError(2,5,5,0.02603719,0.02603719);
   grae->SetPoint(3,108,0.3613);
   grae->SetPointError(3,5,5,0.04207744,0.04207744);
   grae->SetPoint(4,42,0.5412);
   grae->SetPointError(4,5,5,0.0860446,0.0860446);
   grae->SetPoint(5,11.4,0.6418);
   grae->SetPointError(5,5,5,0.1278951,0.1278951);
   
   TH1F *Graph_Graph6 = new TH1F("Graph_Graph6","Graph",100,0,423.96);
   Graph_Graph6->SetMinimum(0.07313268);
   Graph_Graph6->SetMaximum(0.8330189);
   Graph_Graph6->SetDirectory(0);
   Graph_Graph6->SetStats(0);
   Graph_Graph6->GetXaxis()->SetLabelFont(42);
   Graph_Graph6->GetXaxis()->SetTitleFont(42);
   Graph_Graph6->GetYaxis()->SetLabelFont(42);
   Graph_Graph6->GetYaxis()->SetTitleFont(42);
   Graph_Graph6->GetZaxis()->SetLabelFont(42);
   Graph_Graph6->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph6);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("Graph6");
   grae->SetTitle("Graph");
   grae->SetFillColor(16);

   ci = TColor::GetColor("#000099");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,381,0.1519);
   grae->SetPointError(0,5,5,0.002,0.002);
   grae->SetPoint(1,329,0.1791);
   grae->SetPointError(1,5,5,0.0024,0.0024);
   grae->SetPoint(2,224,0.2358);
   grae->SetPointError(2,5,5,0.0024,0.0024);
   grae->SetPoint(3,108,0.3613);
   grae->SetPointError(3,5,5,0.0041,0.0041);
   grae->SetPoint(4,42,0.5412);
   grae->SetPointError(4,5,5,0.0081,0.0081);
   grae->SetPoint(5,11.4,0.6418);
   grae->SetPointError(5,5,5,0.0181,0.0181);
   
   TH1F *Graph_Graph7 = new TH1F("Graph_Graph7","Graph",100,0,423.96);
   Graph_Graph7->SetMinimum(0.0989);
   Graph_Graph7->SetMaximum(0.7109);
   Graph_Graph7->SetDirectory(0);
   Graph_Graph7->SetStats(0);
   Graph_Graph7->GetXaxis()->SetLabelFont(42);
   Graph_Graph7->GetXaxis()->SetTitleFont(42);
   Graph_Graph7->GetYaxis()->SetLabelFont(42);
   Graph_Graph7->GetYaxis()->SetTitleFont(42);
   Graph_Graph7->GetZaxis()->SetLabelFont(42);
   Graph_Graph7->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph7);
   
   grae->Draw("p");
   
   TF1 *fun = new TF1("fun","1.0",0,500);
   fun->SetFillColor(19);
   fun->SetFillStyle(0);
   fun->SetLineWidth(0);
   fun->SetLineStyle(3);
   fun->GetXaxis()->SetLabelFont(42);
   fun->GetXaxis()->SetTitleFont(42);
   fun->GetYaxis()->SetLabelFont(42);
   fun->GetYaxis()->SetTitleFont(42);
   fun->Draw("same");
   
   TH1F *Graph = new TH1F("Graph","Graph",100,0,401);
   Graph->SetMinimum(0);
   Graph->SetMaximum(1.4);
   Graph->SetDirectory(0);
   Graph->SetStats(0);
   Graph->GetXaxis()->SetTitle("N_{part}");
   Graph->GetXaxis()->CenterTitle(true);
   Graph->GetXaxis()->SetLabelFont(42);
   Graph->GetXaxis()->SetTitleSize(0.05);
   Graph->GetXaxis()->SetTitleFont(42);
   Graph->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}} , R_{AA}");
   Graph->GetYaxis()->CenterTitle(true);
   Graph->GetYaxis()->SetLabelFont(42);
   Graph->GetYaxis()->SetTitleSize(0.05);
   Graph->GetYaxis()->SetTitleFont(42);
   Graph->GetZaxis()->SetLabelFont(42);
   Graph->GetZaxis()->SetTitleFont(42);
   Graph->Draw("sameaxis");
   
   TLegend *leg = new TLegend(0.5,0.76,0.8,0.91,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph6","Charged_{} particle_{} R_{AA}","PL");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","#scale[0.7]{7.2 < p_{T} < 9.6 GeV/c, |#eta| < 1.0}","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","#scale[0.7]{CMS, EPJC 72 (2012) 1945}","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph5","Total Syst.","F");

   ci = TColor::GetColor("#3333ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#3333ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.16,0.71,0.45,0.91,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("Graph2","Prompt D^{0} R*_{#kern[-0.3]{AA}}","PL");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","#scale[0.7]{8.0 < p_{T} < 16.0 GeV/c, |y| < 1.0}","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph0","Syst._{} PbPb data+","f");
   entry->SetFillColor(13);
   entry->SetFillStyle(1001);
   entry->SetLineColor(13);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","T_{AA}+N_{MB}+BR","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","Err. pp reference","f");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.5,0.57,0.8,0.69,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("Graph4","Non-prompt_{} J/#psi_{} R_{AA}","PL");

   ci = TColor::GetColor("#006600");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#006600");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","#scale[0.7]{6.5 < p_{T} < 30.0 GeV/c, |y| < 1.2}","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph3","Total Syst.","F");

   ci = TColor::GetColor("#33cc33");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#33cc33");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLatex *   tex = new TLatex(0.125,0.97,"#scale[1.25]{CMS}");
tex->SetNDC();
   tex->SetTextAlign(12);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.24,0.97,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(12);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.57,0.97,"PbPb #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();
   tex->SetTextAlign(12);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TH1F *Graph = new TH1F("Graph","Graph",100,0,401);
   Graph->SetMinimum(0);
   Graph->SetMaximum(1.4);
   Graph->SetDirectory(0);
   Graph->SetStats(0);
   Graph->GetXaxis()->SetTitle("N_{part}");
   Graph->GetXaxis()->CenterTitle(true);
   Graph->GetXaxis()->SetLabelFont(42);
   Graph->GetXaxis()->SetTitleSize(0.05);
   Graph->GetXaxis()->SetTitleFont(42);
   Graph->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}} , R_{AA}");
   Graph->GetYaxis()->CenterTitle(true);
   Graph->GetYaxis()->SetLabelFont(42);
   Graph->GetYaxis()->SetTitleSize(0.05);
   Graph->GetYaxis()->SetTitleFont(42);
   Graph->GetZaxis()->SetLabelFont(42);
   Graph->GetZaxis()->SetTitleFont(42);
   Graph->Draw("sameaxis");
   D0_RAFONLL_Npart->Modified();
   D0_RAFONLL_Npart->cd();
   D0_RAFONLL_Npart->SetSelected(D0_RAFONLL_Npart);
}
