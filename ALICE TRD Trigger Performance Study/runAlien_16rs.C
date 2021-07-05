#ifndef __CINT__
#include "AliAnalysisTask_pPb2016.h"
#include "AliCDBManager.h"
#include "AliGeomManager.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisDataContainer.h"
#include "TChain.h"
#include "AliESDInputHandler.h"
#include "AliMCEventHandler.h"
#endif


void runAlien_16rs() {

    gSystem->Load("libTree.so");
    gSystem->Load("libGeom.so");
    gSystem->Load("libVMC.so");
    gSystem->Load("libSTEERBase.so");
    gSystem->Load("libESD.so");
    gSystem->Load("libAOD.so");

    // load analysis framework
    gSystem->Load("libANALYSIS");
    gSystem->Load("libANALYSISalice");



    // for includes use either global setting in $HOME/.rootrc
    // ACLiC.IncludePaths: -I$(ALICE_ROOT)/include
    // or in each macro
    gSystem->AddIncludePath("-I$ALICE_ROOT/include");

    gROOT->LoadMacro("AliAnalysisTask_pPb2016.cxx++");
    gROOT->LoadMacro("CreateAlienHandler_16rs.C");

    AliAnalysisGrid *alienHandler = CreateAlienHandler_16rs();
    if(!alienHandler) return;

    // alienHandler->SetMergeViaJDL(1);
    // alienHandler->SetMaxMergeStages(2);


    // Create the analysis manager
    AliAnalysisManager *mgr = new AliAnalysisManager("testAnalysis");
    if(!mgr) cout << "Analyis Manger is missing!"
        gROOT->LoadMacro("AliAnalysisTask_pPb2016.cxx++");
        // gROOT->LoadMacro("AliAnalysisTaskEfficiencyMC.cxx++");
    mgr->SetGridHandler(alienHandler);

    // AliAnalysisTaskEfficiencyMC* TaskEfficiencyMC = new AliAnalysisTaskEfficiencyMC("TaskEfficiencyMC");

    //mgr->AddTask(TaskEfficiencyMC);



    //Input Handlers
    AliESDInputHandler* esdH = new AliESDInputHandler();
    mgr->SetInputEventHandler(esdH);
    // AliMCEventHandler* mcHandler = new AliMCEventHandler();
    // mgr->SetMCtruthEventHandler(mcHandler);

    gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");

    /*
    AliAnalysisTask *AddTaskPIDResponse(Bool_t isMC=kFALSE, Bool_t autoMCesd=kTRUE,
                                        Bool_t tuneOnData=kTRUE, TString recoPass="2",
                                        Bool_t cachePID=kFALSE, TString detResponse="",
                                        Bool_t useTPCEtaCorrection = kTRUE, /*Please use default value! Otherwise splines can be off*/
                                    /*  Bool_t useTPCMultiplicityCorrection = kTRUE, /*Please use default value! Otherwise splines can be off*/
                                    /*  Int_t recoDataPass = -1)
    */

    AddTaskPIDResponse(kFALSE, kTRUE, kFALSE, "1");



    // PhysicsSelection
    gROOT->LoadMacro("$ALICE_PHYSICS/OADB/macros/AddTaskPhysicsSelection.C");
    AliPhysicsSelectionTask* phySelectionTask = AddTaskPhysicsSelection(kFALSE);

    AliAnalysisTask_pPb2016* Task_pPb2016 = new AliAnalysisTask_pPb2016("Task_pPb2016");
    mgr->AddTask(Task_pPb2016);
    // Task_pPb2016->SelectCollisionCandidates(AliVEvent::kMB || AliVEvent::kCentral || AliVEvent::kSemiCentral);



    // Create containers for input/output
    AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();

    AliAnalysisDataContainer *coutput_pPb2016 = mgr->CreateContainer("pPb2016",TTree::Class(), AliAnalysisManager::kOutputContainer, "pPb2016.root");
    // AliAnalysisDataContainer *coutputEfficiencyMC = mgr->CreateContainer("EfficiencyMC", TList::Class(), AliAnalysisManager::kOutputContainer, "EfficiencyMC.root");

    // Connect input/output
    mgr->ConnectInput(Task_pPb2016, 0, cinput);

    mgr->ConnectOutput(Task_pPb2016, 1, coutput_pPb2016);



    // Enable debug printouts
    mgr->SetDebugLevel(2);

    if(!mgr->InitAnalysis()) return;
    mgr->PrintStatus();
    mgr->StartAnalysis("grid");

}
