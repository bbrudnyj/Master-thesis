#include "AliAnalysisTaskSE.h"
#include "TList.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include "TObjArray.h"
#include "math.h"
#include "AliESDEvent.h"
#include "AliMCEvent.h"
#include "AliESDHeader.h"
#include "AliESDtrack.h"
#include "AliESDTrdTrack.h"
#include "AliESDtrackCuts.h"
#include "AliESDpid.h"
#include "AliESDInputHandler.h"
#include "AliAnalysisManager.h"
#include "AliTRDtrackGTU.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TTree.h"
#include "AliPIDResponse.h"
#include "AliPIDCombined.h"
#include "AliTPCPIDResponse.h"
#include "AliTRDonlineTrackMatching.h"
#include "AliVTrack.h"
#include "AliTRDgtuSim.h"
#include "AliTRDgtuParam.h"
#include "AliExternalTrackParam.h"
#include "AliTRDgeometry.h"
#include "AliTRDpadPlane.h"


class TList;
class TH1F;
class TH2F;
class TH3F;
class TH1I;
class THnSparse;
class TObjArray;
class AliESDEvent;
class AliESDHeader;
class AliESDtrack;
class AliESDTrdTrack;
class AliExternalTrackParam;
class AliESDtrackCuts;
class AliESDpid;
class AliTRDgeometry;
class TTree;

class AliAnalysisTask_pPb2016: public AliAnalysisTaskSE {
    public:
        AliAnalysisTask_pPb2016(const char* name = "LHC16rs");
        ~AliAnalysisTask_pPb2016();

        virtual void UserCreateOutputObjects();
        virtual void UserExec(Option_t *option);
        virtual void Terminate(Option_t *);
        Double_t FindBestMatch(AliESDTrdTrack** bestGtuTrack, AliESDtrack* esdTrack);
        Double_t EstimateBeta(AliESDtrack* track);

    private:
        AliESDEvent* fEsdEvent;
        AliESDpid* fEsdPid;

        Double_t fBBParametersLightParticles[5];             //! Bethe Bloch paramters for light paritcles
        Double_t fBBParametersNuclei[5];                     //! Bethe Bloch paramters for nuclei
        AliInputEventHandler* fEventHandler;
        AliESDtrackCuts* fESDtrackCuts;
        AliESDtrackCuts* fESDtrackCutsSharp;
        AliTRDonlineTrackMatching* matching;

        AliPIDResponse *fPIDResponse;

        AliTRDgeometry *fTRDgeometry;
        TH2F* fTPCHist;
        TH2F* fTPCHist2;
        TH1F* fHistEvStats;
        TTree* results;
        Bool_t NewEventMarker;
        Bool_t PassedSharpCuts;
        Double_t TPCsignalN;
        Double_t TPCsignal;
        Double_t InnerParamP;
        Double_t P;
        Double_t Pt;
        Double_t SignedPt;
        Double_t Eta,Phi;
        Double_t beta;
        Bool_t TRDvalid;
        Double_t MatchingResult;
        Double_t gtuPt; // vorher Int_t
        Int_t gtuPID; // vorher UChar_t
        UChar_t trkl0;
        UChar_t trkl1;
        UChar_t trkl2;
        UChar_t trkl3;
        UChar_t trkl4;
        UChar_t trkl5;
        Int_t mask;

        Int_t Sector,Stack;
        Bool_t kINT7;
        Bool_t HNU;
        Bool_t HQU;
        Bool_t HSE;
        Bool_t HJT;

        Bool_t CINT7_T_NOPF_CENT;
        Bool_t CINT7_B_NOPF_CENT;
        Bool_t CINT7HNU_T_NOPF_CENT;
        Bool_t CINT7HQU_T_NOPF_CENT;
        Bool_t CINT7HSE_T_NOPF_CENT;
        Bool_t CINT7HJT_T_NOPF_CENT;
        Bool_t CINT7HNU_B_NOPF_CENT;
        Bool_t CINT7HQU_B_NOPF_CENT;
        Bool_t CINT7HSE_B_NOPF_CENT;
        Bool_t CINT7HJT_B_NOPF_CENT;

        Bool_t CINT7_T_NOPF_CENTNOPMD;
        Bool_t CINT7HNU_T_NOPF_CENTNOPMD;
        Bool_t CINT7HQU_T_NOPF_CENTNOPMD;
        Bool_t CINT7HSE_T_NOPF_CENTNOPMD;
        Bool_t CINT7HJT_T_NOPF_CENTNOPMD;

        Bool_t CINT7_T_SPD2_CENT;
        Bool_t CINT7_B_SPD2_CENT;
        Bool_t CINT7HNU_T_SPD2_CENT;
        Bool_t CINT7HQU_T_SPD2_CENT;
        Bool_t CINT7HSE_T_SPD2_CENT;
        Bool_t CINT7HJT_T_SPD2_CENT;
        Bool_t CINT7HNU_B_SPD2_CENT;
        Bool_t CINT7HQU_B_SPD2_CENT;
        Bool_t CINT7HSE_B_SPD2_CENT;
        Bool_t CINT7HJT_B_SPD2_CENT;

        ClassDef(AliAnalysisTask_pPb2016, 1);
};
