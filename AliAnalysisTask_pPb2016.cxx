#include "AliAnalysisTask_pPb2016.h"

using namespace std;


AliAnalysisTask_pPb2016::AliAnalysisTask_pPb2016(const char* name)
    :AliAnalysisTaskSE(name),
    fEventHandler(0),
    fEsdEvent(0),
    fEsdPid(),
    fBBParametersLightParticles(),
    fBBParametersNuclei(),
    fESDtrackCuts(0),
    fESDtrackCutsSharp(0),
    matching(0),
    fTPCHist(0),
    fTPCHist2(0),
    results(new TTree("results", "Tree")),
    NewEventMarker(0),
    PassedSharpCuts(0),
    TPCsignalN(0),
    TPCsignal(0),
    InnerParamP(0),
    P(0),
    Pt(0),
    SignedPt(0),
    Eta(0),
    Phi(0),
    beta(0),
    TRDvalid(0),
    MatchingResult(0),
    gtuPt(0),
    gtuPID(0),
    mask(0),
    trkl0(0),
    trkl1(0),
    trkl2(0),
    trkl3(0),
    trkl4(0),
    trkl5(0),
    Sector(0),
    Stack(0),
    kINT7(0),
    HNU(0),
    HQU(0),
    HSE(0),
    HJT(0),
    fTRDgeometry(0),
    fPIDResponse(0),
    fHistEvStats(0),
    CINT7_T_NOPF_CENT(0),
    CINT7_B_NOPF_CENT(0),
    CINT7HNU_T_NOPF_CENT(0),
    CINT7HQU_T_NOPF_CENT(0),
    CINT7HSE_T_NOPF_CENT(0),
    CINT7HJT_T_NOPF_CENT(0),
    CINT7HNU_B_NOPF_CENT(0),
    CINT7HQU_B_NOPF_CENT(0),
    CINT7HSE_B_NOPF_CENT(0),
    CINT7HJT_B_NOPF_CENT(0),
    CINT7_T_NOPF_CENTNOPMD(0),
    CINT7HNU_T_NOPF_CENTNOPMD(0),
    CINT7HQU_T_NOPF_CENTNOPMD(0),
    CINT7HSE_T_NOPF_CENTNOPMD(0),
    CINT7HJT_T_NOPF_CENTNOPMD(0),
    CINT7_T_SPD2_CENT(0),
    CINT7_B_SPD2_CENT(0),
    CINT7HNU_T_SPD2_CENT(0),
    CINT7HQU_T_SPD2_CENT(0),
    CINT7HSE_T_SPD2_CENT(0),
    CINT7HJT_T_SPD2_CENT(0),
    CINT7HNU_B_SPD2_CENT(0),
    CINT7HQU_B_SPD2_CENT(0),
    CINT7HSE_B_SPD2_CENT(0),
    CINT7HJT_B_SPD2_CENT(0)  {
        DefineOutput (1, TTree::Class());
    }


AliAnalysisTask_pPb2016::~AliAnalysisTask_pPb2016() {

}


void AliAnalysisTask_pPb2016::UserCreateOutputObjects() {

    fBBParametersLightParticles[0] = 1.45802;
    fBBParametersLightParticles[1] = 27.4992;
    fBBParametersLightParticles[2] = 4.00313e-15;
    fBBParametersLightParticles[3] = 2.48485;
    fBBParametersLightParticles[4] = 8.31768;

    fBBParametersNuclei[0] = 1.69155;
    fBBParametersNuclei[1] = 27.4992;
    fBBParametersNuclei[2] = 4.00313e-15;
    fBBParametersNuclei[3] = 2.48485;
    fBBParametersNuclei[4] = 8.31768;

    fTRDgeometry = new AliTRDgeometry();
    matching = new AliTRDonlineTrackMatching();

    results->Branch("NewEventMarker", &NewEventMarker, "NewEventMarker/O");
    results->Branch("PassedSharpCuts", &PassedSharpCuts, "PassedSharpCuts/O");
    results->Branch("kINT7", &kINT7, "kINT7/O");
    results->Branch("HNU", &HNU, "HNU/O");
    results->Branch("HNU", &HNU, "HNU/O");
    results->Branch("HQU", &HQU, "HQU/O");
    results->Branch("HSE", &HSE, "HSE/O");
    results->Branch("HJT", &HJT, "HJT/O");
    results->Branch("GetTPCsignalN", &TPCsignalN, "GetTPCsignalN/D");
    results->Branch("GetTPCsignal", &TPCsignal, "GetTPCsignal/D");
    results->Branch("InnerParamP", &InnerParamP, "InnerParamP/D");
    results->Branch("P", &P, "P/D");
    results->Branch("SignedPt", &SignedPt, "SignedPt/D");
    results->Branch("Eta", &Eta, "Eta/D");
    results->Branch("Phi", &Phi, "Phi/D");
    results->Branch("beta", &beta, "beta/D");
    results->Branch("TRDvalid", &TRDvalid, "TRDvalid/O");
    results->Branch("MatchingResult", &MatchingResult, "MatchingResult/D");
    results->Branch("gtuPt", &gtuPt, "gtuPt/D");
    results->Branch("gtuPID", &gtuPID, "gtuPID/I");
    results->Branch("mask", &mask, "mask/I");
    results->Branch("trkl0", &trkl0, "trkl0/b");
    results->Branch("trkl1", &trkl1, "trkl1/b");
    results->Branch("trkl2", &trkl2, "trkl2/b");
    results->Branch("trkl3", &trkl3, "trkl3/b");
    results->Branch("trkl4", &trkl4, "trkl4/b");
    results->Branch("trkl5", &trkl5, "trkl5/b");
    results->Branch("GetSector", &Sector, "GetSector/I");
    results->Branch("GetStack", &Stack, "GetStack/I");

    results->Branch("CINT7_T_NOPF_CENT", &CINT7_T_NOPF_CENT, "CINT7_T_NOPF_CENT/O");
    results->Branch("CINT7_B_NOPF_CENT", &CINT7_B_NOPF_CENT, "CINT7_B_NOPF_CENT/O");
    results->Branch("CINT7HJT_T_NOPF_CENT", &CINT7HJT_T_NOPF_CENT, "CINT7HJT_T_NOPF_CENT/O");
    results->Branch("CINT7HQU_T_NOPF_CENT", &CINT7HQU_T_NOPF_CENT, "CINT7HQU_T_NOPF_CENT/O");
    results->Branch("CINT7HNU_T_NOPF_CENT", &CINT7HNU_T_NOPF_CENT, "CINT7HNU_T_NOPF_CENT/O");
    results->Branch("CINT7HSE_T_NOPF_CENT", &CINT7HSE_T_NOPF_CENT, "CINT7HSE_T_NOPF_CENT/O");
    results->Branch("CINT7HJT_B_NOPF_CENT", &CINT7HJT_B_NOPF_CENT, "CINT7HJT_B_NOPF_CENT/O");
    results->Branch("CINT7HQU_B_NOPF_CENT", &CINT7HQU_B_NOPF_CENT, "CINT7HQU_B_NOPF_CENT/O");
    results->Branch("CINT7HNU_B_NOPF_CENT", &CINT7HNU_B_NOPF_CENT, "CINT7HNU_B_NOPF_CENT/O");
    results->Branch("CINT7HSE_B_NOPF_CENT", &CINT7HSE_B_NOPF_CENT, "CINT7HSE_B_NOPF_CENT/O");

    results->Branch("CINT7_T_NOPF_CENTNOPMD", &CINT7_T_NOPF_CENTNOPMD, "CINT7_T_NOPF_CENTNOPMD/O");
    results->Branch("CINT7HJT_T_NOPF_CENTNOPMD", &CINT7HJT_T_NOPF_CENTNOPMD, "CINT7HJT_T_NOPF_CENTNOPMD/O");
    results->Branch("CINT7HQU_T_NOPF_CENTNOPMD", &CINT7HQU_T_NOPF_CENTNOPMD, "CINT7HQU_T_NOPF_CENTNOPMD/O");
    results->Branch("CINT7HNU_T_NOPF_CENTNOPMD", &CINT7HNU_T_NOPF_CENTNOPMD, "CINT7HNU_T_NOPF_CENTNOPMD/O");
    results->Branch("CINT7HSE_T_NOPF_CENTNOPMD", &CINT7HSE_T_NOPF_CENTNOPMD, "CINT7HSE_T_NOPF_CENTNOPMD/O");

    results->Branch("CINT7_T_SPD2_CENT", &CINT7_T_SPD2_CENT, "CINT7_T_SPD2_CENT/O");
    results->Branch("CINT7_B_SPD2_CENT", &CINT7_B_SPD2_CENT, "CINT7_B_SPD2_CENT/O");
    results->Branch("CINT7HJT_T_SPD2_CENT", &CINT7HJT_T_SPD2_CENT, "CINT7HJT_T-SPD2_CENT/O");
    results->Branch("CINT7HQU_T_SPD2_CENT", &CINT7HQU_T_SPD2_CENT, "CINT7HQU_T_SPD2_CENT/O");
    results->Branch("CINT7HNU_T_SPD2_CENT", &CINT7HNU_T_SPD2_CENT, "CINT7HNU_T_SPD2_CENT/O");
    results->Branch("CINT7HSE_T_SPD2_CENT", &CINT7HSE_T_SPD2_CENT, "CINT7HSE_T_SPD2_CENT/O");
    results->Branch("CINT7HJT_B_SPD2_CENT", &CINT7HJT_B_SPD2_CENT, "CINT7HJT_B_SPD2_CENT/O");
    results->Branch("CINT7HQU_B_SPD2_CENT", &CINT7HQU_B_SPD2_CENT, "CINT7HQU_B_SPD2_CENT/O");
    results->Branch("CINT7HNU_B_SPD2_CENT", &CINT7HNU_B_SPD2_CENT, "CINT7HNU_B_SPD2_CENT/O");
    results->Branch("CINT7HSE_B_SPD2_CENT", &CINT7HSE_B_SPD2_CENT, "CINT7HSE_B_SPD2_CENT/O");

    PostData(1, results);

    // Cuts Nicole LHC11h:
    fESDtrackCuts = new AliESDtrackCuts("AliESDtrackCuts", "AliESDtrackCuts");
    fESDtrackCuts->SetAcceptKinkDaughters(kFALSE);
    fESDtrackCuts->SetMinNClustersTPC(70);
    fESDtrackCuts->SetMaxChi2PerClusterTPC(6);
    fESDtrackCuts->SetMaxDCAToVertexXY(3);
    fESDtrackCuts->SetMaxDCAToVertexZ(2);
    fESDtrackCuts->SetRequireTPCRefit(kTRUE);
    fESDtrackCuts->SetMinNClustersITS(1);
    fESDtrackCuts->SetEtaRange(-1.0, 1.0);

    // Cuts for final paper:
    fESDtrackCutsSharp = new AliESDtrackCuts("AliESDtrackCuts", "AliESDtrackCuts");
    fESDtrackCutsSharp->SetAcceptKinkDaughters(kFALSE);
    fESDtrackCutsSharp->SetMinNClustersTPC(80);
    fESDtrackCutsSharp->SetMaxChi2PerClusterTPC(5);
    fESDtrackCutsSharp->SetMaxDCAToVertexXY(0.1);
    fESDtrackCutsSharp->SetMaxDCAToVertexZ(0.5);
    fESDtrackCutsSharp->SetRequireTPCRefit(kTRUE);
    fESDtrackCutsSharp->SetMinNClustersITS(2);
    fESDtrackCutsSharp->SetEtaRange(-0.8, 0.8);

    fESDtrackCutsSharp->SetRequireITSRefit(kTRUE);
    fESDtrackCutsSharp->SetMaxChi2PerClusterITS(10); // TO BE INVESTIGATED !!!!!!!!!!!!!!

}


void AliAnalysisTask_pPb2016::UserExec(Option_t *) {

    // get Event-Handler for the trigger information
    fEventHandler = dynamic_cast<AliInputEventHandler*>(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
    if(!fEventHandler) {
        AliError("Could not get InputHandler");
        //return -1;
        return;
    }

    fEsdEvent = dynamic_cast<AliESDEvent*>(InputEvent());
    if(!fEsdEvent) {
        std::cout << "AliAnalysisTask_pPb2016: Could not load fEsdEvent, skip Event." << std::endl;
        return;
    }

    NewEventMarker=kTRUE;

    TString classes = fEsdEvent->GetFiredTriggerClasses();

    HNU=kFALSE;
    HQU=kFALSE;
    HSE=kFALSE;
    HJT=kFALSE;
    kINT7=kFALSE;

    CINT7_T_NOPF_CENT=kFALSE;
    CINT7_B_NOPF_CENT=kFALSE;
    CINT7HJT_T_NOPF_CENT=kFALSE;
    CINT7HQU_T_NOPF_CENT=kFALSE;
    CINT7HNU_T_NOPF_CENT=kFALSE;
    CINT7HSE_T_NOPF_CENT=kFALSE;
    CINT7HJT_B_NOPF_CENT=kFALSE;
    CINT7HQU_B_NOPF_CENT=kFALSE;
    CINT7HNU_B_NOPF_CENT=kFALSE;
    CINT7HSE_B_NOPF_CENT=kFALSE;

    CINT7_T_NOPF_CENTNOPMD=kFALSE;
    CINT7HJT_T_NOPF_CENTNOPMD=kFALSE;
    CINT7HQU_T_NOPF_CENTNOPMD=kFALSE;
    CINT7HNU_T_NOPF_CENTNOPMD=kFALSE;
    CINT7HSE_T_NOPF_CENTNOPMD=kFALSE;

    CINT7_T_SPD2_CENT=kFALSE;
    CINT7_B_SPD2_CENT=kFALSE;
    CINT7HJT_T_SPD2_CENT=kFALSE;
    CINT7HQU_T_SPD2_CENT=kFALSE;
    CINT7HNU_T_SPD2_CENT=kFALSE;
    CINT7HSE_T_SPD2_CENT=kFALSE;
    CINT7HJT_B_SPD2_CENT=kFALSE;
    CINT7HQU_B_SPD2_CENT=kFALSE;
    CINT7HNU_B_SPD2_CENT=kFALSE;
    CINT7HSE_B_SPD2_CENT=kFALSE;

    if((fEventHandler->IsEventSelected() & AliVEvent::kINT7)) {
        kINT7=kTRUE;
        // cout << "-----------------------------------------------------------------------------------------INT7 found!"<<endl;
    }
    else {
        // cout << "no INT7 found!"<<endl;
    }

    if(classes.Contains("HNU")) HNU=kTRUE;
    if(classes.Contains("HQU")) HQU=kTRUE;
    if(classes.Contains("HSE")) HSE=kTRUE;
    if(classes.Contains("HJT")) HJT=kTRUE;

    if(classes.Contains("CINT7-T-NOPF-CENT")) CINT7_T_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7-B-NOPF-CENT")) CINT7_B_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7HJT-T-NOPF-CENT")) CINT7HJT_T_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7HQU-T-NOPF-CENT")) CINT7HQU_T_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7HNU-T-NOPF-CENT")) CINT7HNU_T_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7HSE-T-NOPF-CENT")) CINT7HSE_T_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7HJT-B-NOPF-CENT")) CINT7HJT_B_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7HQU-B-NOPF-CENT")) CINT7HQU_B_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7HNU-B-NOPF-CENT")) CINT7HNU_B_NOPF_CENT=kTRUE;
    if(classes.Contains("CINT7HSE-B-NOPF-CENT")) CINT7HSE_B_NOPF_CENT=kTRUE;

    if(classes.Contains("CINT7-T-NOPF-CENTNOPMD")) CINT7_T_NOPF_CENTNOPMD=kTRUE;
    if(classes.Contains("CINT7HJT-T-NOPF-CENTNOPMD")) CINT7HJT_T_NOPF_CENTNOPMD=kTRUE;
    if(classes.Contains("CINT7HQU-T-NOPF-CENTNOPMD")) CINT7HQU_T_NOPF_CENTNOPMD=kTRUE;
    if(classes.Contains("CINT7HNU-T-NOPF-CENTNOPMD")) CINT7HNU_T_NOPF_CENTNOPMD=kTRUE;
    if(classes.Contains("CINT7HSE-T-NOPF-CENTNOPMD")) CINT7HSE_T_NOPF_CENTNOPMD=kTRUE;

    if(classes.Contains("CINT7-T-SPD2-CENT")) CINT7_T_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7-B-SPD2-CENT")) CINT7_B_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7HJT-T-SPD2-CENT")) CINT7HJT_T_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7HQU-T-SPD2-CENT")) CINT7HQU_T_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7HNU-T-SPD2-CENT")) CINT7HNU_T_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7HSE-T-SPD2-CENT")) CINT7HSE_T_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7HJT-B-SPD2-CENT")) CINT7HJT_B_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7HQU-B-SPD2-CENT")) CINT7HQU_B_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7HNU-B-SPD2-CENT")) CINT7HNU_B_SPD2_CENT=kTRUE;
    if(classes.Contains("CINT7HSE-B-SPD2-CENT")) CINT7HSE_B_SPD2_CENT=kTRUE;

    TPCsignalN=0;
    TPCsignal=0;
    InnerParamP=0;
    SignedPt=0;
    Eta=0;
    Phi=0;
    beta=0;
    TRDvalid=0;
    MatchingResult=0;
    gtuPt=0;
    gtuPID=0;
    mask=0;
    trkl0=0;
    trkl1=0;
    trkl2=0;
    trkl3=0;
    trkl4=0;
    trkl5=0;
    Sector=0;
    Stack=0;

    results->Fill();

    NewEventMarker=kFALSE;


    //========================================================================//
    //                             main track loop                            //
    //========================================================================//
    for(Int_t i = 0; i < fEsdEvent->GetNumberOfTracks(); i++) {

        AliESDtrack* currentEsdTrack = fEsdEvent->GetTrack(i);

        if(!currentEsdTrack) {
            std::cout << "AliAnalysisTask_pPb2016: Esd Track not available. Continue." << std::endl;
            continue;
            }

        if(!currentEsdTrack->GetInnerParam()) {
            // cout << "InnerParam not available"<<endl;
            continue;
        }

        if(!fESDtrackCuts->AcceptTrack(currentEsdTrack)) continue;

        if(fESDtrackCutsSharp->AcceptTrack(currentEsdTrack)) PassedSharpCuts=kTRUE;
        else PassedSharpCuts=kFALSE;

        TPCsignalN = currentEsdTrack->GetTPCsignalN();
        TPCsignal = currentEsdTrack->GetTPCsignal();
        InnerParamP = currentEsdTrack->GetInnerParam()->P();

        // if((InnerParamP > 3) and (TPCsignal < 95)) continue;

        if(TPCsignal < AliExternalTrackParam::BetheBlochAleph(InnerParamP/0.93827, fBBParametersLightParticles[0], fBBParametersLightParticles[1], fBBParametersLightParticles[2], fBBParametersLightParticles[3], fBBParametersLightParticles[4])) continue;

        // if(TPCsignal>expSignalTriton) continue;
        // if(!fPIDResponse->CheckPIDStatus(AliPIDResponse::kTPC, currentEsdTrack)) continue;
        // if(fPIDResponse->NumberOfSigmasTPC(currentEsdTrack, AliPID::kElectron) >= 1) continue;

        P = currentEsdTrack->GetP(); // total momentum of the incoming particle
        Pt = currentEsdTrack->Pt();

        Eta = currentEsdTrack->Eta();
        Phi = currentEsdTrack->Phi();

        SignedPt = currentEsdTrack->GetSignedPt();
        beta = EstimateBeta(currentEsdTrack);

        AliESDTrdTrack* bestGtuTrack = 0x0;

        MatchingResult = FindBestMatch(&bestGtuTrack, currentEsdTrack);

        if((MatchingResult > 0) && (bestGtuTrack)) {
            // cout << "TRD track found! -------------------------------------------------------------------------"<<endl;
            TRDvalid = kTRUE;
            gtuPt = bestGtuTrack->Pt();
            gtuPID = bestGtuTrack->GetPID();
            mask = bestGtuTrack->GetLayerMask();

            /*
            if(mask & (1<<0)) {
                trkl0 = bestGtuTrack->GetTracklet(0)->GetPID();
            }
            else trkl0 = 0;

            if(mask & (1<<1)) {
                trkl1 = bestGtuTrack->GetTracklet(1)->GetPID();
            }
            else trkl1 = 0;

            if(mask & (1<<2)) {
                trkl2 = bestGtuTrack->GetTracklet(2)->GetPID();
            }
            else trkl2 = 0;

            if(mask & (1<<3)) {
                trkl3 = bestGtuTrack->GetTracklet(3)->GetPID();
            }
            else trkl3 = 0;

            if(mask & (1<<4)) {
                trkl4 = bestGtuTrack->GetTracklet(4)->GetPID();
            }
            else trkl4 = 0;

            if(mask & (1<<5)) {
                trkl5 = bestGtuTrack->GetTracklet(5)->GetPID();
            }
            else trkl5 = 0;
            */
            // --Bug in code-- for the moment do not fill tracklet fields

            trkl0 = 0;
            trkl1 = 0;
            trkl2 = 0;
            trkl3 = 0;
            trkl4 = 0;
            trkl5 = 0;

            Sector = bestGtuTrack->GetSector();
            Stack = bestGtuTrack->GetStack();
        }
        else {
            TRDvalid = kFALSE;
            gtuPt = 0;
            gtuPID = 0;
            mask = 0;
            trkl0 = 0;
            trkl1 = 0;
            trkl2 = 0;
            trkl3 = 0;
            trkl4 = 0;
            trkl5 = 0;
            Sector = 0;
            Stack = 0;
        }

        results->Fill();

    } //===================== end main track loop ============================//


    PostData(1, results);

}


void AliAnalysisTask_pPb2016::Terminate(Option_t*) {
    /*
    for(Int_t i = 0; i <= 999; i++){

        // Electron_dedx->SetBinContent(i+1, fPIDResponse->GetTPCResponse().GetExpectedSignal(10/1000.*i + 5/1000., AliPID::kElectron));

        // Pion_dedx->SetBinContent(i+1, fPIDResponse->GetTPCResponse().GetExpectedSignal(10/1000.*i + 5/1000., AliPID::kPion));

        // Kaon_dedx->SetBinContent(i+1, fPIDResponse->GetTPCResponse().GetExpectedSignal(10/1000.*i + 5/1000., AliPID::kKaon));

        Proton_dedx->SetBinContent(i+1, AliExternalTrackParam::BetheBlochAleph((10/1000.*i + 5/1000.)/0.93827, fBBParametersLightParticles[0], fBBParametersLightParticles[1], fBBParametersLightParticles[2], fBBParametersLightParticles[3], fBBParametersLightParticles[4]));

        Deuteron_dedx->SetBinContent(i+1, AliExternalTrackParam::BetheBlochAleph((10/1000.*i + 5/1000.)/1.875612, fBBParametersLightParticles[0], fBBParametersLightParticles[1], fBBParametersLightParticles[2], fBBParametersLightParticles[3], fBBParametersLightParticles[4]));

        Triton_dedx->SetBinContent(i+1, AliExternalTrackParam::BetheBlochAleph((10/1000.*i + 5/1000.)/2.808921, fBBParametersLightParticles[0], fBBParametersLightParticles[1], fBBParametersLightParticles[2], fBBParametersLightParticles[3], fBBParametersLightParticles[4]));

        He3_dedx->SetBinContent(i+1, 4*AliExternalTrackParam::BetheBlochAleph(2*(10/1000.*i + 5/1000.)/2.80941, fBBParametersNuclei[0], fBBParametersNuclei[1], fBBParametersNuclei[2], fBBParametersNuclei[3], fBBParametersNuclei[4]));

        Alpha_dedx->SetBinContent(i+1, 4*AliExternalTrackParam::BetheBlochAleph(2*(10/1000.*i + 5/1000.)/3.728401, fBBParametersNuclei[0], fBBParametersNuclei[1], fBBParametersNuclei[2], fBBParametersNuclei[3], fBBParametersNuclei[4]));

    }

    HistTPCSignal->Draw("");
    Proton_dedx->Draw("same");
    Deuteron_dedx->Draw("same");
    Triton_dedx->Draw("same");
    He3_dedx->Draw("same");
    Alpha_dedx->Draw("same");
    */
}


Double_t AliAnalysisTask_pPb2016::FindBestMatch(AliESDTrdTrack** bestGtuTrack, AliESDtrack* esdTrack) {

    if(!esdTrack) {
        std::cout << "AliAnalysisTask_pPb2016::FindBestMatch: esd_track is NullPointer!" << std::endl;
        return 0;
    }

    if(fEsdEvent->GetNumberOfTrdTracks() == 0) {
        // std::cout<<"AliAnalysisTask_pPb2016::FindBestMatch: No GTU tracks to match!"<<std::endl;
        return 0;
    }

    Double_t esdPt = esdTrack->GetSignedPt();
    Double_t mag = fEsdEvent->GetMagneticField();
    Double_t currentMatch = 0;
    Double_t bestMatch = 0;

    for(Int_t i = 0; i < fEsdEvent->GetNumberOfTrdTracks(); i++) {

        AliESDTrdTrack* gtuTrack= fEsdEvent->GetTrdTrack ( i );

        // if(!(gtuTrack->GetLabel() == -5)) continue;
        // cout << gtuTrack->GetLabel() << endl;

        Double_t gtuPt = gtuTrack->Pt();

        if(mag > 0.) gtuPt = gtuPt * (-1.0);

        Double_t ydist;
        Double_t zdist;

        // if(!fTRDgeometry->GetClusterMatrix(fTRDgeometry->GetDetector(0, gtuTrack->GetStack(), gtuTrack->GetSector()))) continue;
        if(matching->EstimateTrackDistance(esdTrack, gtuTrack, mag, &ydist, &zdist) == 0)

        currentMatch = matching->RateTrackMatch(ydist, zdist, esdPt, gtuPt);

        if(currentMatch > bestMatch) {
            bestMatch = currentMatch;
            *bestGtuTrack = gtuTrack;
        }

    }

    return bestMatch;

}


Double_t AliAnalysisTask_pPb2016::EstimateBeta(AliESDtrack* track) {

    UInt_t status = track->GetStatus();
    Bool_t hasTOFout = status & AliESDtrack::kTOFout;
    Bool_t hasTOFtime = status & AliESDtrack::kTIME;
    Bool_t hasTOF = kFALSE;

    if(hasTOFout && hasTOFtime) hasTOF = kTRUE;

    Float_t length = 0.;
    length = track->GetIntegratedLength();
    if(length < 350.) hasTOF = kFALSE;

    // Float_t time0 = 0;
    // if(fESDpid)

    // else {
    //     std::cout<<"fESDpid not available"<<std::endl;
    //     return -3;
    // }

    // if(time0 == 0)
    // return -4;

    Float_t time = -1;

    if(hasTOF == kTRUE) {
        time = track->GetTOFsignal() ;

        if(time > 0) return length / (2.99792457999999984e-02 * time);
        else return -1;
    }
    else {
        return -2;
    }
}
