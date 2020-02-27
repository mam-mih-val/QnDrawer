//
// Created by mikhail on 2/23/20.
//
void projection(){
  auto file = new TFile( "/home/mikhail/QnDrawer/Cent10_PID14_vn_clean_systematic_ver1218.root" );
  TH2D* histo;
  file->GetObject("PtY_v2EPcent1020_v2_p_ref", histo);
  auto projection = histo->ProjectionY("projection_y", 6, 6);
  projection->SaveAs("points.cxx");
}