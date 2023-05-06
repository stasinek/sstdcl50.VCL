/* --------------------------------------------------------------------------
 *
 * SSTSOFT User Components Library for VCL programing
 * Copyright (C) 2004-2018, Stanislaw Stasiak, All Rights Reserved
 *
 * This library is a freeware; it may be used and distributed according to
 * the terms of The MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the file.
 * Author mentioned in this motice, aviable in credits of software You made using it.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * --------------------------------------------------------------------------*/
#ifndef __tsoft_bargraph_HDR__
#define __tsoft_bargraph_HDR__
//---------------------------------------------------------------------------
#include "FRAMEPAN.H"
//---------------------------------------------------------------------------

enum TGridKind    { gkSolid,gkJustOneDot,gkDot,gkDash };
enum TGridVisible { gvNone,gvBoth,gvVertical,gvHorizontal };
enum TBarKind     { bkBar,bkLine };
//---------------------------------------------------------------------------

typedef struct __Items
{
	 __Items();
struct __Item { TColor Color; int Value; } *Item;
void __fastcall Set(int AIndex, TColor AColor, int AValue);
int  __fastcall Add(TColor AColor, int AValue);
int  __fastcall Ins(int AIndex, TColor AColor, int AValue);
int  __fastcall Del(int AIndex);
void __fastcall Clr();
int  __fastcall GetCount();
int  __fastcall SetCount(int ACount);
	 ~__Items();
int Count;
} *LPTBarDataStruct, TBarDataStruct;
//---------------------------------------------------------------------------

class PACKAGE TBarGraph : public TGraphicControl
{
private:
  RECT RRect;
  TRect FCanvasRect;
  Graphics::TBitmap *FBitmap;

  void __fastcall ForceRepaint(void);
  TBorderKind FBorderKind;
  void __fastcall SetBorderKind(TBorderKind Value);
  TBorderSize FBorderSize;
  void __fastcall SetBorderSize(TBorderSize Value);
  TColor FColor;
  void __fastcall SetColor(TColor Value);

  void __fastcall SetBarKind(TBarKind ABarKindValue);
  TBarKind FBarKind;
  void __fastcall SetBarLineSize(int ABarLineSizeValue);
  int FBarLineSize;
  int FBarHigherValue;
  void __fastcall SetBarDataCount(int ABarCount);
  int FBarDataCount;
  void __fastcall SetBarData(int index, TColor AColorValue, int AValueValue);
  int  __fastcall GetBarData(int index, TColor AColorValue);
  TBarDataStruct *FBarData;
  void __fastcall SetBarAutoScale(bool ABarAutoScaleValue);
  bool FBarAutoScale;
  void __fastcall SetBarScale(int ABarScaleValue);
  int FBarScale;
  void __fastcall PaintBar();

  void __fastcall SetGridVisible(TGridVisible AGridVisibleValue);
  TGridVisible FGridVisible;
  void __fastcall SetGridColor(TColor AGridColorValue);
  TColor FGridColor;
  void __fastcall SetGridKindVertical(TGridKind AGridKindValue);
  TGridKind FGridKindVertical;
  void __fastcall SetGridStepVertical(int AGridStepVerticalValue);
  int FGridStepVertical;
  void __fastcall PaintGridVertical();
  void __fastcall SetGridKindHorizontal(TGridKind AGridKindValue);
  TGridKind FGridKindHorizontal;
  void __fastcall SetGridStepHorizontal(int AGridStepHorizontalValue);
  int FGridStepHorizontal;
  void __fastcall PaintGridHorizontal();
public:
  virtual void __fastcall Paint(void);
       __fastcall TBarGraph(TComponent* Owner);
  __property int Items[int index][TColor ColorValue] = {read =GetBarData,write=SetBarData};
  __property int Count = {read=FBarDataCount, write=SetBarDataCount,default=0};
  void __fastcall Shift(void);
  void __fastcall Add(TColor AColorValue, int AValueValue);
  __property Canvas;
       __fastcall ~TBarGraph(void);
__published:
  __property Align;
  __property TBorderKind BorderKind = {read=FBorderKind, write=SetBorderKind,default=abkLowered};
  __property TBorderSize BorderSize = {read=FBorderSize, write=SetBorderSize,default=absSingle};
  __property TColor Color = {read=FColor,write=SetColor,default=clGreen};

  __property TColor GridColor = {read=FGridColor, write=SetGridColor,default=clBlack};
  __property TGridVisible GridVisible = {read=FGridVisible, write=SetGridVisible,default=gvBoth};
  __property TGridKind GridKindVertical = {read=FGridKindVertical, write=SetGridKindVertical,default=gkSolid};
  __property int GridStepVertical = {read=FGridStepVertical, write=SetGridStepVertical,default=10};
  __property TGridKind GridKindHorizontal = {read=FGridKindHorizontal, write=SetGridKindHorizontal,default=gkSolid};
  __property int GridStepHorizontal = {read=FGridStepHorizontal, write=SetGridStepHorizontal,default=10};

  __property TBarKind BarKind = {read=FBarKind, write=SetBarKind,default=bkBar};
  __property int BarLineSize = {read=FBarLineSize, write=SetBarLineSize,default=1};
  __property bool BarAutoScale = {read=FBarAutoScale, write=SetBarAutoScale,default=false};
  __property int BarScale = {read=FBarScale, write=SetBarScale,default=100};
  __property Visible;
};

//---------------------------------------------------------------------------
#endif
