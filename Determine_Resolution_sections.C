/* ============================================================================================ *\
|                                                                                                |
|     Macro to plot the deviation of measured deuteron, triton, He3 and alphas from expected     |
|       Bethe-Bloch curves in various rigidity bins to determine the resolution for nsigma       |
|                                                                                                |
| Author: Benjamin Dönigus on 20.02.17                                                           |
| Edited by Ömür Erkiner (2019), Benjamin Brudnyj (2020-21)                                      |
\* ============================================================================================ */

#include "TChain.h"
#include <Riostream.h>
#include <iostream>
#include <fstream>
#include <string>
#include "TList.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "THnSparse.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLegend.h"
#include "TFile.h"
#include "TLine.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TBranch.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
//#include "time.h"

/////////////////////////////////////////////////////////////////
// adjust year_Bethe_Bloch_param in variable year_used_BB_params:
//
//

// string period_data = "LHC16r";
// string period_data = "LHC16s";
string period_data = "LHC16rs";

// string year_data = "2016"; Int_t year_used_BB_params = 2018; //for 2016 pass1 data use 2018 BB_params
string year_data = "2016"; Int_t year_used_BB_params = 2016; //for 2016 pass2 data use 2016 BB_params


// gegen betha gamma normal
// aleph parametisierung
Double_t BetheBlochAleph(Double_t bg=0,Double_t kp1=0,Double_t kp2=0,Double_t kp3=0,Double_t kp4=0,Double_t kp5=0) {
    Double_t beta = bg/TMath::Sqrt(1.+ bg*bg);
    Double_t aa = TMath::Power(beta,kp4);
    Double_t bb = TMath::Power(1./bg,kp5);
    bb=TMath::Log(kp3+bb);
    return (kp2-aa-bb)*kp1/aa;
}

// TF1 eindimensionale funktion
TF1* Bethe(Double_t year_Bethe_Bloch_param=year_used_BB_params, Double_t type=0, string name="alpha", Double_t mass=3, Double_t charge=1, Int_t helium3=0){
    Double_t xMin = 0;
    Double_t xMax = 0;
    Double_t fBBParametersLightParticles[5];  // creating array
    Double_t fBBParametersNuclei[5];
    Double_t fBBParametersDeuteron[5];
    if(year_Bethe_Bloch_param == 2018 && type == 0){
        // same parameters used for data in pPb in 2016 pass1
        // He3
        fBBParametersNuclei[0] = 1.81085;//2.87221;//2.14694;//1.68163;//1.67894;//1.71664;
        fBBParametersNuclei[1] = 29.4656;//17.2012;//25.1543;//27.3706;//27.3365;//27.8963;
        fBBParametersNuclei[2] = 0.0458225;//-0.838261;//-0.251458;//4.00473e-15;//-3.31415e-09;//4.05413e-15;
        fBBParametersNuclei[3] = 2.08689;//2.02935;//2.01704;//2.48269;//2.64864;//2.52443;
        fBBParametersNuclei[4] = 2.28772;//0.156238;//0.340005;//7.00204;//10.7479;//9.12963;
        // Triton
        fBBParametersLightParticles[0] = 0.427978;//0.756826;//0.587186;//0.426467;
        fBBParametersLightParticles[1] = 105.46;//56.4042;//73.3374;//99.5886;
        fBBParametersLightParticles[2] = -7.08642e-07;//-0.000914894;//-9.74737e-05;//-0.00207203;
        fBBParametersLightParticles[3] = 2.23332;//2.29644;//2.22824;//2.3559;
        fBBParametersLightParticles[4] = 18.8231;//11.0431;//10.4254;//23.5914;
        // Deuteron
        fBBParametersDeuteron[0]   = 2.84798;
        fBBParametersDeuteron[1]   = 12.9233;
        fBBParametersDeuteron[2]   = 1.61851e-05;
        fBBParametersDeuteron[3]   = 2.59961;
        fBBParametersDeuteron[4]   = 4.02119;
    }

    if(year_Bethe_Bloch_param == 2017 && type == 0){
        // He3
        fBBParametersNuclei[0]  = 3.20025;//1.92549;
        fBBParametersNuclei[1]  = 16.4971;//30.9412;
        fBBParametersNuclei[2]  = -0.0116571;//0.077449;
        fBBParametersNuclei[3]  = 2.3152;//1.93073;
        fBBParametersNuclei[4]  = 3.11135;//-3.05628;
        // Triton
        fBBParametersLightParticles[0]   = 0.420434;//0.380305;
        fBBParametersLightParticles[1]   = 106.102;//116.679;
        fBBParametersLightParticles[2]   = -3.15587e-07;//-8.0075e-09;
        fBBParametersLightParticles[3]   = 2.32499;//2.30688;
        fBBParametersLightParticles[4]   = 21.3439;//21.7968;
        // Deuteron
        fBBParametersDeuteron[0]   = 0.85219;
        fBBParametersDeuteron[1]   = 50.6727;
        fBBParametersDeuteron[2]   = 127.676;
        fBBParametersDeuteron[3]   = 2.3279;
        fBBParametersDeuteron[4]   = 9.06887;
    }

    if(year_Bethe_Bloch_param == 2016 && type == 0){
        // parameters used for data in pPb in 2016 pass2 (pass1 use 2018)
        // He3
        fBBParametersNuclei[0] = 0.715489;
        fBBParametersNuclei[1] = 59.5463;
        fBBParametersNuclei[2] = 4.44487e-12;
        fBBParametersNuclei[3] = 2.69874;
        fBBParametersNuclei[4] = 24.063;
        // Triton
        fBBParametersLightParticles[0] = 0.223948;
        fBBParametersLightParticles[1] = 180.564;
        fBBParametersLightParticles[2] = -3.03884e-10;
        fBBParametersLightParticles[3] = 2.30095;
        fBBParametersLightParticles[4] = 34.2269;
        // Deuteron
        fBBParametersDeuteron[0]   = 2.84798;
        fBBParametersDeuteron[1]   = 12.9233;
        fBBParametersDeuteron[2]   = 1.61851e-05;
        fBBParametersDeuteron[3]   = 2.59961;
        fBBParametersDeuteron[4]   = 4.02119;
    }

    if(charge>0){
        xMin = 0.1;             // positiv charged particles
        xMax = 100;
    }
    else{
        xMin = -100;            // negativ charged particles
        xMax = -0.1;
    }

    TF1 *f = new TF1(name.c_str(),"[5]*[5]*BetheBlochAleph([5]*x/([6]),[0],[1],[2],[3],[4])",xMin,xMax);
    f->SetLineColor(2);

    //data
    if(helium3 == 0)f->SetParameters(fBBParametersLightParticles[0],fBBParametersLightParticles[1],fBBParametersLightParticles[2],fBBParametersLightParticles[3],fBBParametersLightParticles[4],charge,mass);

    if(helium3 == 1)f->SetParameters(fBBParametersNuclei[0],fBBParametersNuclei[1],fBBParametersNuclei[2],fBBParametersNuclei[3],fBBParametersNuclei[4],charge,mass);

    if(helium3 == 2)f->SetParameters(fBBParametersDeuteron[0],fBBParametersDeuteron[1],fBBParametersDeuteron[2],fBBParametersDeuteron[3],fBBParametersDeuteron[4],charge,mass);
    return f;
}


Double_t BetheTheory(Double_t ptot=0, Int_t year_Bethe_Bloch_param=year_used_BB_params, Int_t type=0, Double_t mass=4, Int_t partSpezi=3, Int_t charge=1){
    Double_t fBBParameters[5];
    // partSpez = Teilchenspezies 0: tritons, 1: z=2-particles, 2:deuterons
    // Type = Data from MonteCarlo
    // ptot = Rigidity (p/z) am Eintrittspunkt der TPC

    if(year_Bethe_Bloch_param == 2018){
        if(type == 0 && partSpezi == 1){  // same parameters used for data in pPb in 2016 pass1
            fBBParameters[0]  = 1.81085;//2.87221;//2.14694;//1.69155;
            fBBParameters[1]  = 29.4656;//17.2012;//25.1543;//27.4992;
            fBBParameters[2]  = 0.0458225;//-0.838261;//-0.251458;//4.00313e-15;
            fBBParameters[3]  = 2.08689;//2.02935;//2.01704;//2.48485;
            fBBParameters[4]  = 2.28772;//0.156238;//0.340005;//8.31768;
        }
        if(type == 0 && partSpezi == 0){
            fBBParameters[0]   = 0.427978;//0.756826;//0.587186;//0.426467;
            fBBParameters[1]   = 105.46;//56.4042;//73.3374;//99.5886;
            fBBParameters[2]   = -7.08642e-07;//-0.000914894;//-9.74737e-05;//-0.00207203;
            fBBParameters[3]   = 2.23332;//2.29644;//2.22824;//2.3559;
            fBBParameters[4]   = 18.8231;//11.0431;//10.4254;//23.5914;
        }
        if(type == 0 && partSpezi == 2){
            fBBParameters[0]   = 2.84798;
            fBBParameters[1]   = 12.9233;
            fBBParameters[2]   = 1.61851e-05;
            fBBParameters[3]   = 2.59961;
            fBBParameters[4]   = 4.02119;
        }
    }

    if(year_Bethe_Bloch_param == 2017){
        if(type == 0 && partSpezi == 1){
            fBBParameters[0]  = 3.20025;//1.92549;
            fBBParameters[1]  = 16.4971;//30.9412;
            fBBParameters[2]  = -0.0116571;//0.077449;
            fBBParameters[3]  = 2.3152;//1.93073;
            fBBParameters[4]  = 3.11135;//-3.05628;
        }
        if(type == 0 && partSpezi == 0){
            fBBParameters[0]   = 0.420434;//0.380305;
            fBBParameters[1]   = 106.102;//116.679;
            fBBParameters[2]   = -3.15587e-07;//-8.0075e-09;
            fBBParameters[3]   = 2.32499;//2.30688;
            fBBParameters[4]   = 21.3439;//21.7968;
        }
        if(type == 0 && partSpezi == 2){
            fBBParameters[0]   = 0.85219;
            fBBParameters[1]   = 50.6727;
            fBBParameters[2]   = 127.676;
            fBBParameters[3]   = 2.3279;
            fBBParameters[4]   = 9.06887;
        }
    }

    if(year_Bethe_Bloch_param == 2016){
        if(type == 0 && partSpezi == 1){  // parameters used for data in pPb in 2016 pass2 (pass1 use 2018)
            fBBParameters[0] = 0.715489;
            fBBParameters[1] = 59.5463;
            fBBParameters[2] = 4.44487e-12;
      	    fBBParameters[3] = 2.69874;
      	    fBBParameters[4] = 24.063;
        }
        if(type == 0 && partSpezi == 0){
            fBBParameters[0] = 0.223948;
            fBBParameters[1] = 180.564;
            fBBParameters[2] = -3.03884e-10;
            fBBParameters[3] = 2.30095;
            fBBParameters[4] = 34.2269;
        }
        if(type == 0 && partSpezi == 2){
            fBBParameters[0]   = 2.84798;
            fBBParameters[1]   = 12.9233;
            fBBParameters[2]   = 1.61851e-05;
            fBBParameters[3]   = 2.59961;
            fBBParameters[4]   = 4.02119;
        }
    }

    Double_t x = charge*charge*BetheBlochAleph(charge*ptot/(mass),fBBParameters[0],fBBParameters[1],fBBParameters[2],fBBParameters[3],fBBParameters[4]);
    return x;
}


Double_t BetaTheory(Double_t x, Double_t ptot, Double_t tof_mass){
    x = 1/TMath::Sqrt(1+(tof_mass/(ptot*2))*tof_mass/(ptot*2));
    return x;
}


//==============================================================================================//
//                                                                                              //
//                                       main function                                          //
//                                                                                              //
//==============================================================================================//
void Determine_Resolution_sections(Int_t sel = 4, Int_t year_Bethe_Bloch_param = year_used_BB_params, Int_t type = 0){
    // sel=4 -> alphas

    time_t starttime = time(NULL);
    gStyle->SetOptStat(0);
    if (period_data == "LHC16rs") cout << "period: LHC16r+s\n" << endl;
    else cout << Form("period: %s\n", period_data.c_str()) << endl;

    // TFileCollection fc("dum","",Form("~/alidock/alice/%s/LHC16rs/lists/Liste_%s_woHSE.txt", year_data.c_str(), period_data.c_str()));
    // TFileCollection fc("dum","",Form("~/alidock/alice/%s/LHC16rs/lists/Liste_%s_try2.txt", year_data.c_str(), period_data.c_str()));
    // TFileCollection fc("dum","",Form("~/alidock/alice/%s/LHC16rs/lists/Liste_%s_NOPMD.txt", year_data.c_str(), period_data.c_str())); // 2016, pass1
    TFileCollection fc("dum","",Form("~/alidock/alice/%s/LHC16rs/lists/Liste_%s_NOPMD_pass2.txt", year_data.c_str(), period_data.c_str()));

    TChain tre("results");
    tre.AddFileInfoList(fc.GetList());

    // Create a tree reader (of type Int_t) on the branch "fEventSize"
    TTreeReader myReader(&tre);

    TTreeReaderValue<Bool_t> myEvent(myReader, "NewEventMarker");
    // TTreeReaderValue<Int_t> trdPt(myReader, "gtuPt");
    // TTreeReaderValue<Double_t> trdPt(myReader, "gtuPt");
    // TTreeReaderValue<Bool_t> myHNU(myReader, "HNU");
    // TTreeReaderValue<Bool_t> myHQU(myReader, "HQU");
    // TTreeReaderValue<Bool_t> myHSE(myReader, "HSE");
    // TTreeReaderValue<Bool_t> myHJT(myReader, "HJT");
    // TTreeReaderValue<Bool_t> myMB(myReader, "kINT7");
    // TTreeReaderValue<Bool_t> myMB(myReader, "CINT7_T_NOPF_CENT");
    // TTreeReaderValue<Bool_t> myHNU(myReader, "CINT7HNU_T_NOPF_CENT");
    // TTreeReaderValue<Bool_t> myHQU(myReader, "CINT7HQU_T_NOPF_CENT");
    // TTreeReaderValue<Bool_t> myHSE(myReader, "CINT7HSE_T_NOPF_CENT");
    // TTreeReaderValue<Bool_t> myHJT(myReader, "CINT7HJT_T_NOPF_CENT");
    TTreeReaderValue<Bool_t> myMB(myReader, "CINT7_T_NOPF_CENTNOPMD");
    TTreeReaderValue<Bool_t> myHNU(myReader, "CINT7HNU_T_NOPF_CENTNOPMD");
    TTreeReaderValue<Bool_t> myHQU(myReader, "CINT7HQU_T_NOPF_CENTNOPMD");
    TTreeReaderValue<Bool_t> myHSE(myReader, "CINT7HSE_T_NOPF_CENTNOPMD");
    TTreeReaderValue<Bool_t> myHJT(myReader, "CINT7HJT_T_NOPF_CENTNOPMD");
    TTreeReaderValue<Bool_t> myTRDstatus(myReader, "TRDvalid");
    TTreeReaderValue<Bool_t> myPassedSharpCuts(myReader, "PassedSharpCuts");
    TTreeReaderValue<Double_t> myTPCsignal(myReader, "GetTPCsignal");
    TTreeReaderValue<Double_t> myTPCsignalN(myReader, "GetTPCsignalN");
    TTreeReaderValue<Double_t> myRigidity(myReader, "InnerParamP");
    TTreeReaderValue<Double_t> myP(myReader, "P");
    // TTreeReaderValue<UChar_t> mygtuPID(myReader, "gtuPID");
    TTreeReaderValue<Int_t> mygtuPID(myReader, "gtuPID");
    TTreeReaderValue<Double_t> mySignedPt(myReader, "SignedPt");
    TTreeReaderValue<Double_t> myBeta(myReader, "beta");
    TTreeReaderValue<Double_t> myEta(myReader, "Eta");
    TTreeReaderValue<Double_t> myPhi(myReader, "Phi");

    // P = positiv, N= negativ
    TF1 *fPionP = Bethe(year_Bethe_Bloch_param, type, "fPionP", 0.140, 1, 0);
    TF1 *fPionN = Bethe(year_Bethe_Bloch_param, type, "fPionN", 0.140, -1, 0);

    TF1 *fKaonP = Bethe(year_Bethe_Bloch_param, type, "fKaonP", 0.493, 1, 0);
    TF1 *fKaonN = Bethe(year_Bethe_Bloch_param, type, "fKaonN", 0.493, -1, 0);

    TF1 *fProtonP = Bethe(year_Bethe_Bloch_param, type, "fProtonP", 0.93827, 1, 0);
    TF1 *fProtonN = Bethe(year_Bethe_Bloch_param, type, "fProtonN", 0.93827, -1, 0);

    TF1 *fDeuteronP = Bethe(year_Bethe_Bloch_param, type, "fDeuteronP", 1.875612, 1, 2);
    TF1 *fDeuteronN = Bethe(year_Bethe_Bloch_param, type, "fDeuteronN", 1.875612, -1, 2);

    TF1 *fTritonP = Bethe(year_Bethe_Bloch_param, type, "fTritonP", 2.808921, 1, 0);
    TF1 *fTritonN = Bethe(year_Bethe_Bloch_param, type, "fTritonN", 2.808921, -1, 0);

    TF1 *fHelium3P = Bethe(year_Bethe_Bloch_param, type, "fHelium3P", 2.829856, 2, 1);
    TF1 *fHelium3N = Bethe(year_Bethe_Bloch_param, type, "fHelium3N", 2.829856, -2, 1);

    TF1 *fHelium4P = Bethe(year_Bethe_Bloch_param, type, "fHelium4P", 3.728401, 2, 1);
    TF1 *fHelium4N = Bethe(year_Bethe_Bloch_param, type, "fHelium4N", 3.728401, -2, 1);

    TH1F *fHistDeDxResolution_3He = new TH1F("fHistDeDxResolution_3He", "DeDxResolution_3He", 200, -1.0, 1.0);
    TH1F *fHistDeDxResolution_alpha = new TH1F("fHistDeDxResolution_alpha", "DeDxResolution_alpha", 200, -1.0, 1.0);
    TH1F *fHistDeDxResolution_tritonen = new TH1F("fHistDeDxResolution_triton", "DeDxResolution_triton", 200, -1.0, 1.0);
    TH1F *fHistDeDxResolution_deuteronen = new TH1F("fHistDeDxResolution_deuteron", "DeDxResolution_deuteron", 200, -1.0, 1.0);
    TH2F *fHistDeDx = new TH2F("fHistDeDx", "DeDx", 500, 0.1, 5.0, 500, 0, 4000); // 500 als bins?


    Double_t deuteronen_rigidity_bins[17] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.};
    //Double_t deuteronen_rigidity_bins[15] = {0.9, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3., 3.5, 4., 5.};
    string resolution_particle_d = "fHistDeDxResolution_deuteronen";

    Double_t tritonen_rigidity_bins[18] = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.05, 1.1, 1.15, 1.2, 1.3, 1.4, 1.5};
    string resolution_particle_t = "fHistDeDxResolution_tritonen";

    Double_t He3_rigidity_bins[7] = {0.7, 0.8, 0.9, 1., 1.2, 1.8, 5.};
    // Double_t He3_rigidity_bins[14] = {0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.1, 1.2, 1.4, 1.6, 1.8, 2.2, 5.};
    string resolution_particle_He3 = "fHistDeDxResolution_He3";

    Double_t alpha_rigidity_bins[5] = {0.3, 0.8, 1.3, 2.3, 5.};
    // Double_t alpha_rigidity_bins[12] = {0.3, 0.5, 0.8, 1.1, 1.4, 1.7, 2.0, 2.3, 2.6, 3., 4., 5.};
    string resolution_particle_alpha = "fHistDeDxResolution_alpha";


    Int_t deuteron_nohists = sizeof(deuteronen_rigidity_bins)/sizeof(deuteronen_rigidity_bins[0]) - 1;
    Int_t triton_nohists = sizeof(tritonen_rigidity_bins)/sizeof(tritonen_rigidity_bins[0]) - 1;
    Int_t He3_nohists = sizeof(He3_rigidity_bins)/sizeof(He3_rigidity_bins[0]) - 1;
    Int_t alpha_nohists = sizeof(alpha_rigidity_bins)/sizeof(alpha_rigidity_bins[0]) - 1;

    TH1F** histResolutionSections_d = new TH1F*[deuteron_nohists];
    TH1F** histResolutionSections_t = new TH1F*[triton_nohists];
    TH1F** histResolutionSections_He3 = new TH1F*[He3_nohists];
    TH1F** histResolutionSections_alpha = new TH1F*[alpha_nohists];


    for(Int_t i=0; i<deuteron_nohists;i++){
        string intervall_rigidity_d = Form("%s_%s", to_string(deuteronen_rigidity_bins[i]).c_str(), to_string(deuteronen_rigidity_bins[i+1]).c_str());
        string resolution_deuteron = Form("%s_%s", resolution_particle_d.c_str(), intervall_rigidity_d.c_str());
        //TH1F *resolution_deuteron.c_str() = new TH1F(resolution_deuteron.c_str(), resolution_deuteron.c_str(), 200, -1.0, 1.0);
        histResolutionSections_d[i] = new TH1F(resolution_deuteron.c_str(), resolution_deuteron.c_str(), 200, -1.0, 1.0);
    }

    for(Int_t i=0; i<triton_nohists;i++){
        string intervall_rigidity_t = Form("%s_%s", to_string(tritonen_rigidity_bins[i]).c_str(), to_string(tritonen_rigidity_bins[i+1]).c_str());
        string resolution_triton = Form("%s_%s", resolution_particle_t.c_str(), intervall_rigidity_t.c_str());
        histResolutionSections_t[i] = new TH1F(resolution_triton.c_str(), resolution_triton.c_str(), 200, -1.0, 1.0);
    }

    for(Int_t i=0; i<He3_nohists;i++){
        string intervall_rigidity_He3 = Form("%s_%s", to_string(He3_rigidity_bins[i]).c_str(), to_string(He3_rigidity_bins[i+1]).c_str());
        string resolution_He3 = Form("%s_%s", resolution_particle_He3.c_str(), intervall_rigidity_He3.c_str());
        histResolutionSections_He3[i] = new TH1F(resolution_He3.c_str(), resolution_He3.c_str(), 200, -1.0, 1.0);
    }

    for(Int_t i=0; i<alpha_nohists;i++){
        string intervall_rigidity_alpha = Form("%s_%s", to_string(alpha_rigidity_bins[i]).c_str(), to_string(alpha_rigidity_bins[i+1]).c_str());
        string resolution_alpha = Form("%s_%s", resolution_particle_alpha.c_str(), intervall_rigidity_alpha.c_str());
        histResolutionSections_alpha[i] = new TH1F(resolution_alpha.c_str(), resolution_alpha.c_str(), 200, -1.0, 1.0);
    }

    // Different Triggers
    Int_t fCountsEvents=0;
    Int_t fCountsHNU=0;
    Int_t fCountsHQU=0;
    Int_t fCountsHSE=0;
    Int_t fCountsHJT=0;
    Int_t fCountsMB=0;

    TF1 *fdEdxTest = new TF1("fdEdxTest", "[5]*[5]*BetheBlochAleph([5]*x/([6]),[0],[1],[2],[3],[4])", 0.1, 5.);
    Double_t bblight[7];

    fDeuteronP->GetParameters(bblight);
    cout << "Deuteron Parameter: " << bblight[0] << ", " << bblight[1] << ", " << bblight[2] << ", " << bblight[3] << ", " << bblight[4] << endl;
    fTritonP->GetParameters(bblight);
    cout << "Triton Parameter: " << bblight[0] << ", " << bblight[1] << ", " << bblight[2] << ", " << bblight[3] << ", " << bblight[4] << endl;
    fHelium3P->GetParameters(bblight);
    cout << "Helium3 Parameter: " << bblight[0] << ", " << bblight[1] << ", " << bblight[2] << ", " << bblight[3] << ", " << bblight[4] << endl;


    //==========================================================================================//
    //                                                                                          //
    //                   Loop over all entries of the TTree or TChain                           //
    //                                                                                          //
    //==========================================================================================//
    while (myReader.Next()) {
        if (*myHNU==kTRUE || *myHQU==kTRUE || *myHSE==kTRUE || *myHJT==kTRUE || *myMB==kTRUE){
            if ((*myHNU==kTRUE && *myHQU==kTRUE) || (*myHNU==kTRUE && *myHSE==kTRUE) || (*myHNU==kTRUE && *myHJT==kTRUE) || (*myHQU==kTRUE && *myHJT==kTRUE) || (*myHSE==kTRUE && *myHJT==kTRUE)) continue;
            if ((*myHNU==kTRUE && *myMB==kTRUE) || (*myHQU==kTRUE && *myMB==kTRUE) || (*myHSE==kTRUE && *myMB==kTRUE) || (*myHJT==kTRUE && *myMB==kTRUE)) continue;

            // Get the data from the current TTree entry by getting
            // the value from the connected reader (eventSize):
            if (*myHNU==kTRUE) fCountsHNU++;
            if (*myHQU==kTRUE) fCountsHQU++;
            if (*myHSE==kTRUE && !(*myHQU==kTRUE)) fCountsHSE++;
            if (*myHJT==kTRUE) fCountsHJT++;
            if (*myEvent==1) fCountsEvents++;
            if (*myMB==kTRUE) fCountsMB++;
            //if (*mySignedPt>0) continue; // seperation of particles and antiparticles

            //if (*myTPCsignalN<120) continue;
            if (*myRigidity > 0){
                Double_t betaT=*myBeta;
                Double_t betaT2=betaT*betaT;

                Double_t expTrackD=BetheBlochAleph(*myRigidity/(1.875612),bblight[0],bblight[1],bblight[2],bblight[3],bblight[4]);
                Double_t expTrack3He=BetheBlochAleph(*myRigidity/(2.829856),bblight[0],bblight[1],bblight[2],bblight[3],bblight[4]);

                Double_t mass = *myRigidity/sqrt(1/TMath::Sqrt(1 - betaT*betaT)*1/TMath::Sqrt(1 - betaT*betaT)-1);

                Double_t xBetheAlpha = BetheTheory(*myRigidity, year_Bethe_Bloch_param, type, 3.728401, 1, 2);
                Double_t xBetheHelium3 = BetheTheory(*myRigidity, year_Bethe_Bloch_param, type, 2.829856, 1, 2);
                Double_t xBetheDeuteron = BetheTheory(*myRigidity, year_Bethe_Bloch_param, type, 1.875612, 2, 1);
                Double_t xBetheTriton = BetheTheory(*myRigidity, year_Bethe_Bloch_param, type, 2.808921, 0, 1);

                Double_t nSigma_dEdx_Alpha = (*myTPCsignal - xBetheAlpha)/xBetheAlpha;
                Double_t nSigma_dEdx_Helium3 = (*myTPCsignal - xBetheHelium3)/xBetheHelium3;
                Double_t nSigma_dEdx_Triton = (*myTPCsignal - xBetheTriton)/xBetheTriton;
                Double_t nSigma_dEdx_Deuteron = (*myTPCsignal - xBetheDeuteron)/xBetheDeuteron;

        	      //cout << "nSigma_dEdx_Alpha: " << nSigma_dEdx_Alpha << endl;
              	//cout << "nSigma_dEdx_Helium3: " << nSigma_dEdx_Helium3 << endl;
        	      //cout << "nSigma_dEdx_Triton: " << nSigma_dEdx_Triton << endl;
        	      //cout << "nSigma_dEdx_Deuteron: " << nSigma_dEdx_Deuteron << endl;

                fHistDeDx->Fill(*myRigidity,*myTPCsignal);

    	          Double_t n = 0.4;
    	          // Resolution is 4 percent from fit of 3He
    	          //
                if (abs(nSigma_dEdx_Deuteron)<n){
            	      for(Int_t j=0; j<deuteron_nohists;j++){
            	          if(*myRigidity > deuteronen_rigidity_bins[j] && *myRigidity<deuteronen_rigidity_bins[j+1]){
            	              histResolutionSections_d[j]->Fill(nSigma_dEdx_Deuteron);
            	          }
            	      }
            	  }

                if (abs(nSigma_dEdx_Triton)<n){
            	      for(Int_t j=0; j<triton_nohists;j++){
            	          if(*myRigidity > tritonen_rigidity_bins[j] && *myRigidity<tritonen_rigidity_bins[j+1]){
            		            histResolutionSections_t[j]->Fill(nSigma_dEdx_Triton);
            	          }
            	      }
            	  }

              	if (abs(nSigma_dEdx_Helium3)<n){
              	    for(Int_t j=0; j<He3_nohists;j++){
              	        if(*myRigidity > He3_rigidity_bins[j] && *myRigidity<He3_rigidity_bins[j+1]){
              	            histResolutionSections_He3[j]->Fill(nSigma_dEdx_Helium3);
              	        }
              	    }
              	}

            	  if (abs(nSigma_dEdx_Alpha)<n){
            	      for(Int_t j=0; j<alpha_nohists;j++){
            	          if(*myRigidity > alpha_rigidity_bins[j] && *myRigidity<alpha_rigidity_bins[j+1]){
            		             histResolutionSections_alpha[j]->Fill(nSigma_dEdx_Alpha);
            	          }
            	      }
            	  }

            	  //if (abs(nSigma_dEdx_Alpha)<0.12){

            	  //fHistTOFmass->Fill(pow(mass,2));
            	  //if (*myHNU==kTRUE) fHistTOFmassHNU->Fill(mass*mass);
            	  //if (*myHQU==kTRUE) fHistTOFmassHQU->Fill(mass*mass);
            	  //if (*myHSE==kTRUE && !(*myHQU==kTRUE)) fHistTOFmassHSE->Fill(mass*mass);
            	  //if (*myHJT==kTRUE) fHistTOFmassHJT->Fill(mass*mass);

            	  //fHistDeDxAfterSel_alpha->Fill(*myRigidity,*myTPCsignal);
            	  //fHist_mass_pT_sel_alpha->Fill(*mySignedPt,mass*mass);

            	  if(*myRigidity<n) fHistDeDxResolution_alpha->Fill(nSigma_dEdx_Alpha);
            }
        }
    }

    //==========================================================================================//
    //                                                                                          //
    //                                    Results/Outputs                                       //
    //                                    Plots/Canvases                                        //
    //                                                                                          //
    //==========================================================================================//
    cout << "Number of Events: " << fCountsEvents << endl;
    cout << "HNU Trigger insgesamt gefeuert: " << fCountsHNU << endl;
    cout << "HQU Trigger insgesamt gefeuert: " <<fCountsHQU << endl;
    cout << "HSE Trigger insgesamt gefeuert: " <<fCountsHSE << endl;
    cout << "HJT Trigger insgesamt gefeuert: " <<fCountsHJT << endl;
    cout << "MB Counts: " << fCountsMB << endl;

    cout << "Expected (m/z)^2 Deuteron : " << 1.875612*1.875612 << endl;
    cout << "Expected (m/z)^2 Triton : " << 2.829856*2.829856 << endl;
    cout << "Expected (m/z)^2 Helium3 : " << 2.829856*2.829856/4 << endl;
    cout << "Expected (m/z)^2 Alpha : " << 3.728401*3.728401/4 << '\n' << endl;


    TCanvas *canv_resolution_deuteronen = new TCanvas("resolution_deuteron","resolution_deuteron",800,800);
    fHistDeDxResolution_deuteronen->Draw();

    TCanvas *canv_resolution_alpha = new TCanvas("resolution_alpha","resolution_alpha",800,800);
    fHistDeDxResolution_alpha->Draw();

    TCanvas** CanvResolutionSections_d = new TCanvas*[deuteron_nohists];
    TCanvas** CanvResolutionSections_t = new TCanvas*[triton_nohists];
    TCanvas** CanvResolutionSections_He3 = new TCanvas*[He3_nohists];
    TCanvas** CanvResolutionSections_alpha = new TCanvas*[alpha_nohists];

    for(Int_t k=0; k<deuteron_nohists;k++){
        string canv_intervall_rigidity_d = Form("%s_%s", to_string(deuteronen_rigidity_bins[k]).c_str(), to_string(deuteronen_rigidity_bins[k+1]).c_str());
        string canv_resolution_deuteron = Form("resolution_d_%s", canv_intervall_rigidity_d.c_str());
        //TH1F *resolution_deuteron.c_str() = new TH1F(resolution_deuteron.c_str(), resolution_deuteron.c_str(), 200, -1.0, 1.0);
        CanvResolutionSections_d[k] = new TCanvas(canv_resolution_deuteron.c_str(), canv_resolution_deuteron.c_str(), 800, 800);
        histResolutionSections_d[k]->Draw();
    }

    for(Int_t k=0; k<triton_nohists;k++){
        string canv_intervall_rigidity_t = Form("%s_%s", to_string(tritonen_rigidity_bins[k]).c_str(), to_string(tritonen_rigidity_bins[k+1]).c_str());
        string canv_resolution_tritonen = Form("resolution_t_%s", canv_intervall_rigidity_t.c_str());
        CanvResolutionSections_t[k] = new TCanvas(canv_resolution_tritonen.c_str(), canv_resolution_tritonen.c_str(), 800, 800);
        histResolutionSections_t[k]->Draw();
    }

    for(Int_t k=0; k<He3_nohists;k++){
        string canv_intervall_rigidity_He3 = Form("%s_%s", to_string(He3_rigidity_bins[k]).c_str(), to_string(He3_rigidity_bins[k+1]).c_str());
        string canv_resolution_He3 = Form("resolution_He3_%s", canv_intervall_rigidity_He3.c_str());
        CanvResolutionSections_He3[k] = new TCanvas(canv_resolution_He3.c_str(), canv_resolution_He3.c_str(), 800, 800);
        histResolutionSections_He3[k]->Draw();
    }

    for(Int_t k=0; k<alpha_nohists;k++){
        string canv_intervall_rigidity_alpha = Form("%s_%s", to_string(alpha_rigidity_bins[k]).c_str(), to_string(alpha_rigidity_bins[k+1]).c_str());
        string canv_resolution_alpha = Form("resolution_alpha_%s", canv_intervall_rigidity_alpha.c_str());
        CanvResolutionSections_alpha[k] = new TCanvas(canv_resolution_alpha.c_str(), canv_resolution_alpha.c_str(), 800, 800);
        histResolutionSections_alpha[k]->Draw();
    }


    TCanvas *canv_resolution_tritonen = new TCanvas("resolution_triton", "resolution_triton", 800, 800);
    fHistDeDxResolution_tritonen->Draw();

    TCanvas *canv_resolution_3He = new TCanvas("resolution_3He", "resolution_3He", 800, 800);
    fHistDeDxResolution_3He->Draw();


    TCanvas *horst = new TCanvas("dEdx","dEdx",800,800);
    fHistDeDx->Draw("colz");
    fDeuteronP->Draw("same");
    fDeuteronN->Draw("same");
    fTritonP->Draw("same");
    fTritonN->Draw("same");
    fHelium3P->Draw("same");
    fHelium3N->Draw("same");
    fHelium4P->Draw("same");
    fHelium4N->Draw("same");
    horst->SetLogz();


    //==========================================================================================//
    //                                                                                          //
    //                                         Saving-part                                      //
    //                                                                                          //
    //==========================================================================================//
    /*
    canv_resolution_alpha->SaveAs("resolution_alpha_2018_trd_MB.root");
    canv_resolution_deuteronen->SaveAs("resolution_deuteron_2018_trd_mb.root");
    canv_resolution_tritonen->SaveAs("resolution_triton_2018_trd_mb.root");
    canv_resolution_3He->SaveAs("resolution_3He_2018_trd_mb.root");
    */

    for(Int_t l=0; l<deuteron_nohists;l++){
        string file_name = Form("resolution_d_%s_%s_%s.root", year_data.c_str(), to_string(deuteronen_rigidity_bins[l]).c_str(), to_string(deuteronen_rigidity_bins[l+1]).c_str());
        CanvResolutionSections_d[l]->SaveAs(Form("plots_%s/%s", period_data.c_str(), file_name.c_str()));
    }

    for(Int_t l=0; l<triton_nohists;l++){
        string file_name = Form("resolution_t_%s_%s_%s.root", year_data.c_str(), to_string(tritonen_rigidity_bins[l]).c_str(), to_string(tritonen_rigidity_bins[l+1]).c_str());
        CanvResolutionSections_t[l]->SaveAs(Form("plots_%s/%s", period_data.c_str(), file_name.c_str()));
    }

    for(Int_t l=0; l<He3_nohists;l++){
        string file_name = Form("resolution_He3_%s_%s_%s.root", year_data.c_str(), to_string(He3_rigidity_bins[l]).c_str(), to_string(He3_rigidity_bins[l+1]).c_str());
        CanvResolutionSections_He3[l]->SaveAs(Form("plots_%s/%s", period_data.c_str(), file_name.c_str()));
    }

    for(Int_t l=0; l<alpha_nohists;l++){
        string file_name = Form("resolution_alpha_%s_%s_%s.root", year_data.c_str(), to_string(alpha_rigidity_bins[l]).c_str(), to_string(alpha_rigidity_bins[l+1]).c_str());
        CanvResolutionSections_alpha[l]->SaveAs(Form("plots_%s/%s", period_data.c_str(), file_name.c_str()));
    }


    time_t endtime = time(NULL);
    cout << "Zeit " << (Double_t)(endtime-starttime)/60. << " Minuten" << endl;
}
