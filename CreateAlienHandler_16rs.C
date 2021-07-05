#ifndef __CINT__
#include "AliAnalysisAlien.h"
#endif

AliAnalysisGrid* CreateAlienHandler_16rs() {

    AliAnalysisAlien *plugin = new AliAnalysisAlien();
    plugin->SetOverwriteMode();

    // Set the run mode (can be "full", "test", "offline", "submit" or "terminate")
    // plugin->SetRunMode("offline");                                               // modification needed
    plugin->SetRunMode("submit");                                                 // modification needed

    // Set versions of used packages
    plugin->SetAPIVersion("V1.1x");

    //plugin->SetAliROOTVersion ("v5-08-14-1");
    // plugin->SetAliPhysicsVersion("vAN-20180921-1");
    // plugin->SetAliPhysicsVersion("vAN-20210111-1");
    plugin->SetAliPhysicsVersion("vAN-20210206-1");

    // Declare input data to be processed.
    // Method 1: Create automatically XML collections using alien 'find' command.
    // Define production directory LFN
    plugin->SetGridDataDir("/alice/data/2016/LHC16r");                         // modification needed

    // Set data search pattern
    // Data pattern for reconstructed datarrra
    plugin->SetDataPattern("/pass2_CENT_woSDD/*/AliESDs.root");                      // modification needed
    plugin->SetRunPrefix("000"); // real data

    // ...then add run numbers to be considered

    //========================================================================//
    //                              run list                                  //// modification needed
    //========================================================================//
    // LHC16r
    // plugin->AddRunNumber(266318);  // n      pass1_CENT_woSDD & pass1_FAST
    // plugin->AddRunNumber(266317);  // n      pass1_CENT_woSDD & pass1_FAST
    // plugin->AddRunNumber(266316);  // n      pass1_CENT_woSDD & pass1_FAST
    // plugin->AddRunNumber(266305);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266300);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266208);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266197);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266196);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266193);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266190);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266189);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266187);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266117);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266086);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266085);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266084);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266083);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266081);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266076);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266074);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266034);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265795);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265789);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265788);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265754);  // n only pass1_CENT_woSDD
    plugin->AddRunNumber(265746);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(265744);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(265742);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265741);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265714);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265713);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265709);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265705);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265701);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265700);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265698);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265697);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(265607);  // n only pass1_CENT_woSDD
    // plugin->AddRunNumber(265596);  // n only pass1_CENT_woSDD
    // plugin->AddRunNumber(265594);  // n only pass1_CENT_woSDD


    // LHC16s
    // plugin->AddRunNumber(267110);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(267081);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(267077);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(267072);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(267070);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(267030);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266998);  // n      pass1_CENT_woSDD & pass1_FAST
    // plugin->AddRunNumber(266997);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266994);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266993);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266944);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266886);  // n only pass1_CENT_woSDD
    // plugin->AddRunNumber(266885);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266883);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266882);  // y only pass1_CENT_woSDD
    // plugin->AddRunNumber(266881);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266549);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266543);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266492);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266487);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266441);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266439);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266438);  // y2 only pass1_CENT_woSDD
    // plugin->AddRunNumber(266437);  // y only pass1_CENT_woSDD


    // Define alien work directory where all files will be copied. Relative to alien $HOME.
    plugin->SetGridWorkingDir("LHC16r_pass2_CENT_woSDD_265746");                                        //modification needed

    // Declare alien output directory. Relative to working directory.
    plugin->SetGridOutputDir("output");

    // Declare the analysis source files names separated by blancs. To be compiled runtime
    // using ACLiC on the worker nodes.
    plugin->SetAnalysisSource("AliAnalysisTask_pPb2016.cxx");                   //modification needed

    // Declare all libraries (other than the default ones for the framework. These will be
    // loaded by the generated analysis macro. Add all extra files (task .cxx/.h) here.
    plugin->SetAdditionalLibs("AliAnalysisTask_pPb2016.h AliAnalysisTask_pPb2016.cxx"); //modification needed

    plugin->SetDefaultOutputs();

    // Optionally set a name for the generated analysis macro (default MyAnalysis.C)
    plugin->SetAnalysisMacro("MyAnalysis.C");

    // Optionally modify the executable name (default analysis.sh)
    plugin->SetExecutable("analysis.sh");

    // Optionally set time to live (default 30000 sec)
    // plugin->SetTTL(30000);

    // Number of ESD files chained for each subjob

    // plugin->SetSplitMaxInputFileNumber(50);

    // Optionally modify the name of the generated JDL (default analysis.jdl)
    plugin->SetJDLName("analysis.jdl");

    plugin->SetCheckCopy(kFALSE);

    // Optionally modify job price (default 1)
    plugin->SetPrice(1);

    return plugin;

}
