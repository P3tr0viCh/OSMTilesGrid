// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.Math.hpp>

#include <UtilsStr.h>
#include <UtilsMisc.h>

#include "OSMTilesGridMain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMain *Main;

// ---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender) {
	FormatSettings.DecimalSeparator = '.';

	eLeftTopLat->Text = "51.479031";
	eLeftTopLon->Text = "57.7027701";

	eRightBottomLat->Text = "51.0474379";
	eRightBottomLon->Text = "58.8571928";

	LatLonList = new TLatLonList();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender) {
	LatLonList->Free();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
long double sec(long double x) {
	return 1 / cos(x);
}

// ---------------------------------------------------------------------------
int long2tilex(double lon, int z) {
	return (int)(floor((lon + 180.0) / 360.0 * (1 << z)));
}

// ---------------------------------------------------------------------------
int lat2tiley(double lat, int z) {
	double latrad = lat * M_PI / 180.0;
	return (int)(floor((1.0 - ArcSinh(tan(latrad)) / M_PI) / 2.0 * (1 << z)));
}

// ---------------------------------------------------------------------------
double tilex2long(int x, int z) {
	return x / (double)(1 << z) * 360.0 - 180;
}

// ---------------------------------------------------------------------------
double tiley2lat(int y, int z) {
	double n = M_PI - 2.0 * M_PI * y / (double)(1 << z);
	return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnCalcClick(TObject *Sender) {
	int z;

	mOutput->Lines->Clear();

	LatLonList->Clear();

	ShowWaitCursor();

	btnCalc->Enabled = false;

	TLatLon * LatLon;

	try {
		try {
			z = StrToInt(eZoom->Text);

			xTileLeftTop = long2tilex(StrToFloat(eLeftTopLon->Text), z);
			yTileLeftTop = lat2tiley(StrToFloat(eLeftTopLat->Text), z);

			xTileRightBottom = long2tilex(StrToFloat(eRightBottomLon->Text), z);
			yTileRightBottom = lat2tiley(StrToFloat(eRightBottomLat->Text), z);

			// mOutput->Lines->Add(IntToStr(xTileLeftTop) + ":" +
			// IntToStr(yTileLeftTop));
			// mOutput->Lines->Add(IntToStr(xTileRightBottom) + ":" +
			// IntToStr(yTileRightBottom));

			for (int x = xTileLeftTop; x < xTileRightBottom + 2; x++) {
				for (int y = yTileLeftTop; y < yTileRightBottom + 2; y++) {
					// Result->Add(IntToStr(x) + ":" + IntToStr(y));
					LatLon = new TLatLon();

					LatLon->lat = tiley2lat(y, z);
					LatLon->lon = tilex2long(x, z);

					LatLonList->Add(LatLon);
				}
			}

			mOutput->Lines->BeginUpdate();
			for (int i = 0; i < LatLonList->Count; i++) {
				mOutput->Lines->Add(FloatToStr(LatLonList->Items[i]->lat) +
					", " + FloatToStr(LatLonList->Items[i]->lon));
			}
			mOutput->Lines->EndUpdate();
		}
		catch (Exception &E) {
			mOutput->Lines->Clear();

			LatLonList->Clear();

			MsgBoxErr("error: " + E.Message);
		}
	}
	__finally {
		btnCalc->Enabled = true;

		RestoreCursor();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnSaveClick(TObject *Sender) {
	if (LatLonList->Count == 0) {
		MsgBoxErr("error: empty coords");
		return;
	}

	TStringList * OSMFile = new TStringList();

	ShowWaitCursor();

	btnSave->Enabled = false;

	try {
		TLatLon * LatLon;

		OSMFile->Add("<?xml version='1.0' encoding='UTF-8'?>");
		OSMFile->Add("<osm version='0.6' generator='OSMTilesGrid'>");

		for (int i = 0; i < LatLonList->Count; i++) {
			OSMFile->Add("<node id='-" + IntToStr(i + 1) +
				"' action='modify' visible='true' lat='" +
				FloatToStr(LatLonList->Items[i]->lat) + "' lon='" +
				FloatToStr(LatLonList->Items[i]->lon) + "' />");
		}

		OSMFile->Add("<way id='-" + IntToStr(LatLonList->Count + 1) +
			"' action='modify' visible='true'>");

		int ref = 1;

		bool inc = true;

		int y = 1;

		int yCount = yTileRightBottom - yTileLeftTop + 2;

		for (int i = 0; i < LatLonList->Count; i++) {
			OSMFile->Add("<nd ref='-" + IntToStr(ref) + "' />");

			if (y == yCount) {
				y = 1;
				ref = ref + yCount;
				inc = !inc;
			}
			else {
				y++;

				if (inc) {
					ref++;
				}
				else {
					ref--;
				}
			}
		}

		ref = 1;

		inc = true;

		int x = 1;

		int xCount = xTileRightBottom - xTileLeftTop + 2;

		for (int i = 0; i < LatLonList->Count; i++) {
			OSMFile->Add("<nd ref='-" + IntToStr(ref) + "' />");

			if (inc) {
				if (x > xCount - 1) {
					ref++;
					x = 1;
					inc = false;
				}
				else {
					ref = ref + yCount;
					x++;
				}
			}
			else {
				if (x > xCount - 1) {
					ref++;
					x = 1;
					inc = true;
				}
				else {
					ref = ref - yCount;
					x++;
				}
			}
		}

		OSMFile->Add("</way>");

		OSMFile->Add("</osm>");

		if (SaveDialog->Execute()) {
			OSMFile->SaveToFile(SaveDialog->FileName);
		}
	}
	__finally {
		OSMFile->Free();

		btnSave->Enabled = true;

		RestoreCursor();
	}
}
// ---------------------------------------------------------------------------
