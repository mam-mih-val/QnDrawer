#include "TStyle.h"

void SetStyle()
{
    gStyle->SetTitleSize(0.05,"T");
    gStyle->SetTitleSize(0.05,"X");
    gStyle->SetTitleSize(0.05,"Y");
    gStyle->SetTitleSize(0.035,"Z");
    gStyle->SetTitleOffset(1.0,"Y");
    gStyle->SetTitleOffset(1.0,"X");
    gStyle->SetFrameLineWidth(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetPadColor(0);
    gStyle->SetLabelSize(0.05,"X");
    gStyle->SetLabelSize(0.04,"Y");
    gStyle->SetLabelSize(0.03,"Z");
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadBottomMargin(0.2);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadRightMargin(0.15);
    gStyle->SetMarkerSize(1.5);
    gStyle->SetErrorX(0);
    gStyle->SetOptStat(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetTitleFillColor(0);
    gStyle->SetTitleBorderSize(0);
    gStyle->SetHistLineWidth(3);
    gStyle->SetLineWidth(3);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetLegendBorderSize(0);
    gStyle->SetPadBorderMode(1);
    gStyle->SetEndErrorSize(5);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetMarkerSize(2);
    gStyle->SetLineWidth(4);
    gStyle->SetNdivisions(505, "Y");
    gStyle->SetStripDecimals();

            cout
        << "User's style have been set" << endl;
}