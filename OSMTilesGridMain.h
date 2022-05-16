// ---------------------------------------------------------------------------

#ifndef OSMTilesGridMainH
#define OSMTilesGridMainH

// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>

#include <ObjList.h>

// ---------------------------------------------------------------------------
class TLatLon : public TObject {
public:
	double lat;
	double lon;
};

typedef TObjList<TLatLon>TLatLonList;

// ---------------------------------------------------------------------------
class TMain : public TForm {
__published:
	TGroupBox *gbLeftTop;
	TLabeledEdit *eLeftTopLat;
	TLabeledEdit *eLeftTopLon;
	TGroupBox *gbRightBottom;
	TLabeledEdit *eRightBottomLat;
	TLabeledEdit *eRightBottomLon;
	TGroupBox *gbZoom;
	TEdit *eZoom;
	TMemo *mOutput;
	TButton *btnCalc;
	TButton *btnSave;
	TSaveDialog *SaveDialog;
	TButton *btnClose;

	void __fastcall btnCalcClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnSaveClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

private:
	int xTileLeftTop;
	int yTileLeftTop;

	int xTileRightBottom;
	int yTileRightBottom;

	TLatLonList * LatLonList;

public:
	__fastcall TMain(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif
