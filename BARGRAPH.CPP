/* --------------------------------------------------------------------------
 *
 * SSTSOFT User Components Library for VCL programing
 * Copyright (C) 2000-2020, Stanislaw Stasiak, All Rights Reserved
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
#include <vcl.h>
#pragma hdrstop
#include "BARGRAPH.H"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TBarGraph *)
{
    new TBarGraph(NULL);
}
//---------------------------------------------------------------------------

namespace Bargraph
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TBarGraph)};
        RegisterComponents("User", classes, 0);
    }
}
//---------------------------------------------------------------------------

__fastcall TBarGraph::TBarGraph(TComponent* Owner)
    : TGraphicControl(Owner)
{
FBarLineSize = 1;
FColor = clBlack;
FGridColor = clGreen;
FBarScale = 100;
FBarAutoScale = false;
FBarHigherValue = 1;
FBarDataCount = 0;
FBarKind = bkBar;
FBarData = new TBarDataStruct();

FBorderKind = abkLowered;
FBorderSize = absSingle;
FBitmap = new Graphics::TBitmap;
FCanvasRect = ClientRect;
Height = 102;
FBitmap->Height = 0;
FGridStepVertical = 10;
Width = 102;
FBitmap->Width = 0;
FGridVisible = gvBoth;
FGridStepHorizontal = 10;
FGridKindVertical = gkSolid;
FGridKindHorizontal = gkSolid;
ControlStyle = ControlStyle << csFramed << csOpaque;
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::Paint(void)
{
RECT crect;
#define COPY_RECT(x,y) x.left = y.Left; x.top = y.Top; x.right = y.Right; x.bottom = y.Bottom;
COPY_RECT(crect,ClientRect)
if (crect.right!=FBitmap->Width || crect.bottom!=FBitmap->Height)
   {
	this->ForceRepaint();
	return;
   }
else
   {::GetClipBox(this->Canvas->Handle,&crect);
	::BitBlt(this->Canvas->Handle,
			 0,0,crect.right,crect.bottom,
			 FBitmap->Canvas->Handle,
			 0,0,
			 SRCCOPY);
   }
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::ForceRepaint(void)
{
RECT crect;
COPY_RECT(crect,ClientRect)
FBitmap->Width = crect.right; FBitmap->Height = crect.bottom;
FCanvasRect = ClientRect;

if (FBorderSize==absSingle)
   {FCanvasRect.Left=1;
	FCanvasRect.Right=crect.right-1;
	FCanvasRect.Top=1;
	FCanvasRect.Bottom=crect.bottom-1;
   }
if (FBorderSize==absDouble)
   {FCanvasRect.Left=2;
	FCanvasRect.Right=crect.right-2;
	FCanvasRect.Top=2;
	FCanvasRect.Bottom=crect.bottom-2;
   }

FBitmap->Canvas->Brush->Color = Color;
FBitmap->Canvas->FillRect(FCanvasRect);
PaintGridHorizontal();
PaintGridVertical();
PaintBar();

TRamka::PaintBorder(FBitmap->Canvas->Handle,&RRect,&crect,FBorderKind,FBorderSize);

::BitBlt(this->Canvas->Handle,
		 0,0,crect.right,crect.bottom,
		 FBitmap->Canvas->Handle,
		 0,0,
		 SRCCOPY);
}
//---------------------------------------------------------------------------
#define SETVALUE(oldvalue,newvalue) \
if (oldvalue==newvalue)\
	return;\
oldvalue = newvalue;

#define SETMINMAXVALUE(oldvalue,minvalue,maxvalue,newvalue) \
if (newvalue ==oldvalue)\
	return;\
if (newvalue > maxvalue)\
	return;\
if (newvalue < minvalue)\
	return;\
oldvalue = newvalue;

void __fastcall TBarGraph::SetGridVisible(TGridVisible AGridVisibleValue)
{
SETVALUE(FGridVisible,AGridVisibleValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetBorderKind(TBorderKind ABorderKindValue)
{
SETVALUE(FBorderKind,ABorderKindValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetBorderSize(TBorderSize ABorderSizeValue)
{
SETVALUE(FBorderSize,ABorderSizeValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetColor(TColor AColorValue)
{
SETVALUE(FColor,AColorValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetGridColor(TColor AGridColorValue)
{
SETVALUE(FGridColor,AGridColorValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetGridStepVertical(int AGridStepVerticalValue)
{
SETVALUE(FGridStepVertical,AGridStepVerticalValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetGridStepHorizontal(int AGridStepHorizontalValue)
{
SETMINMAXVALUE(FGridStepHorizontal,1,MaxInt,AGridStepHorizontalValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetGridKindHorizontal(TGridKind AGridKindValue)
{
SETVALUE(FGridKindHorizontal,AGridKindValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetGridKindVertical(TGridKind AGridKindValue)
{
SETVALUE(FGridKindVertical,AGridKindValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::PaintGridHorizontal()
{
if ((GridVisible!=gvBoth && GridVisible!=gvHorizontal) || Count==0)
    return;

double EGridStepVertical;
double EGridStepHorizontal;
double X,Y;

    EGridStepHorizontal = (GridStepHorizontal*(FCanvasRect.Bottom - FCanvasRect.Top + 2)) / FBarHigherValue;
if (EGridStepHorizontal < 2)
    EGridStepHorizontal = 2;
if (BarKind==bkLine && Count > 1)
   {EGridStepVertical  = (GridStepVertical*(FCanvasRect.Right - FCanvasRect.Left + 2)) / (Count-1);
   }
else
   {EGridStepVertical  = (GridStepVertical*(FCanvasRect.Right - FCanvasRect.Left + 2)) /  Count;
   }
if (EGridStepVertical  < 2)
    EGridStepVertical  = 2;

if (GridKindHorizontal==gkJustOneDot)
   {
    FBitmap->Canvas->Pen->Color = GridColor;

    for (Y = FCanvasRect.Bottom - EGridStepHorizontal; Y > FCanvasRect.Top; Y-=EGridStepHorizontal)
        {
     for (X = FCanvasRect.Left + EGridStepVertical; X > FCanvasRect.Left;  X-=EGridStepVertical)
          FBitmap->Canvas->Pixels[X][Y] = GridColor;
     for (X = FCanvasRect.Left + EGridStepVertical; X < FCanvasRect.Right; X+=EGridStepVertical)
          FBitmap->Canvas->Pixels[X][Y] = GridColor;
        }
   }
else
if (GridKindHorizontal==gkDot)
   {
    FBitmap->Canvas->Pen->Color = GridColor;

    for (Y = FCanvasRect.Bottom - EGridStepHorizontal; Y > FCanvasRect.Top; Y-=EGridStepHorizontal)
    for (X = FCanvasRect.Left; X < FCanvasRect.Right; X+=3)
        {
         FBitmap->Canvas->Pixels[X][Y] = GridColor;
        }
   }
else
   {
    switch (GridKindHorizontal)
        {
         case gkDash:
		 FBitmap->Canvas->Pen->Style = psDot;
		 break;
		 case gkSolid:
		 FBitmap->Canvas->Pen->Style = psSolid;
		 break;
		 default:
		 FBitmap->Canvas->Pen->Style = psSolid;
         break;
		}
    FBitmap->Canvas->Pen->Color = GridColor;
    for (Y = FCanvasRect.Bottom - EGridStepHorizontal; Y > FCanvasRect.Top; Y-=EGridStepHorizontal)
        {
         FBitmap->Canvas->MoveTo(FCanvasRect.Left,Y);
         FBitmap->Canvas->LineTo(FCanvasRect.Right,Y);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::PaintGridVertical()
{
if ((GridVisible!=gvBoth && GridVisible!=gvVertical) || Count==0)
    return;

double EGridStepVertical;
double EGridStepHorizontal;
double X,Y;

    EGridStepHorizontal = (GridStepHorizontal*(FCanvasRect.Bottom - FCanvasRect.Top + 2)) / FBarHigherValue;
if (EGridStepHorizontal < 2)
    EGridStepHorizontal = 2;
if (BarKind==bkLine && Count > 1)
   {EGridStepVertical  = (GridStepVertical*(FCanvasRect.Right - FCanvasRect.Left + 2)) / (Count-1);
   }
else
   {EGridStepVertical  = (GridStepVertical*(FCanvasRect.Right - FCanvasRect.Left + 2)) /  Count;
   }
if (EGridStepVertical  < 2)
    EGridStepVertical  = 2;

if (GridKindVertical==gkJustOneDot)
   {
    FBitmap->Canvas->Pen->Color = GridColor;
    for (Y = FCanvasRect.Bottom - EGridStepHorizontal; Y > FCanvasRect.Top;Y-=EGridStepHorizontal)
        {
     for (X = FCanvasRect.Left + EGridStepVertical; X > FCanvasRect.Left;  X-=EGridStepVertical)
          FBitmap->Canvas->Pixels[X][Y] = GridColor;
     for (X = FCanvasRect.Left + EGridStepVertical; X < FCanvasRect.Right; X+=EGridStepVertical)
          FBitmap->Canvas->Pixels[X][Y] = GridColor;
        }
   }
else
if (GridKindVertical==gkDot)
   {
    FBitmap->Canvas->Pen->Color = GridColor;
    for (X = FCanvasRect.Left + EGridStepVertical; X < FCanvasRect.Right; X+=EGridStepVertical)
    for (Y = FCanvasRect.Top; Y < FCanvasRect.Bottom; Y+=3)
        {
         FBitmap->Canvas->Pixels[X][Y] = GridColor;
        }
   }
else
   {
	switch (GridKindVertical)
        {
		 case gkJustOneDot:
		 case gkDash:
		 FBitmap->Canvas->Pen->Style = psDot;
		 break;
		 case gkSolid:
         default:
		 FBitmap->Canvas->Pen->Style = psSolid;
		 break;
		}
	FBitmap->Canvas->Pen->Color = GridColor;

	for (X = FCanvasRect.Left + EGridStepVertical; X < FCanvasRect.Right; X+=EGridStepVertical)
		{
         FBitmap->Canvas->MoveTo(X,FCanvasRect.Top);
         FBitmap->Canvas->LineTo(X,FCanvasRect.Bottom);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::PaintBar()
{
if (Count==0)
    return;

double EBarWidth;
double EBarHeight;
double X;
int i, p;
if (BarKind==bkLine)
   {
    FBitmap->Canvas->Pen->Style = psSolid;
    FBitmap->Canvas->Pen->Width = BarLineSize;

    if (Count<=1) EBarWidth = FCanvasRect.Right - FCanvasRect.Left;
    else
        EBarWidth = double(FCanvasRect.Right - FCanvasRect.Left) / (Count-1);
    if (EBarWidth < 1)
        EBarWidth = 1;
       EBarHeight = double(FCanvasRect.Bottom - FCanvasRect.Top) / FBarHigherValue;
    if (EBarWidth ==0)
        EBarWidth = 1;

    for (X = FCanvasRect.Left, i = 0; i < Count && X < FCanvasRect.Right; i++, X+=EBarWidth)
    for (p = 0; p < FBarData[i].Count; p++)
        {
         FBitmap->Canvas->Pen->Color = FBarData[i].Item[p].Color;
         FBitmap->Canvas->MoveTo(X, FCanvasRect.Top + int((FBarHigherValue-FBarData[i].Item[p].Value)*EBarHeight));
         FBitmap->Canvas->LineTo(X + EBarWidth, FCanvasRect.Top + int((FBarHigherValue-FBarData[i+1].Item[p].Value)*EBarHeight));
        }
     if (X < FCanvasRect.Right)
    for (p = 0; p < FBarData[Count-1].Count; p++)
        {
         FBitmap->Canvas->Pen->Color = FBarData[Count-1].Item[p].Color;
         FBitmap->Canvas->LineTo(FCanvasRect.Right, FCanvasRect.Top + int((FBarHigherValue-FBarData[Count-1].Item[p].Value)*EBarHeight));
        }
    FBitmap->Canvas->Pen->Width = 1;
   }
else
if (BarKind==bkBar)
   {
    FBitmap->Canvas->Brush->Style = bsSolid;

    if (Count <= 1) EBarWidth = FCanvasRect.Right - FCanvasRect.Left;
    else
     EBarWidth = double(FCanvasRect.Right - FCanvasRect.Left) /  Count;
    if (EBarWidth < 1)
        EBarWidth = 1;
    EBarHeight = double(FCanvasRect.Bottom - FCanvasRect.Top+1) / FBarHigherValue;
    if (EBarWidth ==0)
        EBarWidth = 1;

    for (X = FCanvasRect.Left, i = 0; i < Count && X < FCanvasRect.Right; i++, X+=EBarWidth)
    for (p = 0; p < FBarData[i].Count; p++)
        {
         FBitmap->Canvas->Brush->Color = FBarData[i].Item[p].Color;
         FBitmap->Canvas->FillRect(Rect(X, FCanvasRect.Top + int((FBarHigherValue-FBarData[i].Item[p].Value)*EBarHeight), X + EBarWidth, FCanvasRect.Bottom));
        }
     if (X-=EBarWidth < FCanvasRect.Right)
    for (p = 0; p < FBarData[Count-1].Count; p++)
        {
         FBitmap->Canvas->Brush->Color = FBarData[Count-1].Item[p].Color;
         FBitmap->Canvas->FillRect(Rect(X, FCanvasRect.Top + int((FBarHigherValue-FBarData[Count-1].Item[p].Value)*EBarHeight), FCanvasRect.Right, FCanvasRect.Bottom));
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetBarLineSize(int ABarLineSizeValue)
{
SETVALUE(FBarLineSize,ABarLineSizeValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetBarKind(TBarKind ABarKindValue)
{
SETVALUE(FBarKind,ABarKindValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetBarAutoScale(bool ABarAutoScaleValue)
{
SETVALUE(FBarAutoScale,ABarAutoScaleValue);

if (FBarAutoScale==true)
   {FBarHigherValue = 1;
    for (int i = 0; i < Count; i++ )
    for (int p = 0; p < FBarData[i].Count; p++)
        {
         if (FBarHigherValue < FBarData[i].Item[p].Value)
             FBarHigherValue = FBarData[i].Item[p].Value;
        }
   }
else
   {FBarHigherValue = FBarScale;
   }
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetBarScale(int ABarScaleValue)
{
SETMINMAXVALUE(FBarScale,0,MaxInt,ABarScaleValue);
if (BarAutoScale==false)
    FBarHigherValue = FBarScale;
ForceRepaint();
}
//---------------------------------------------------------------------------

int __fastcall TBarGraph::GetBarData(int AIndex, TColor ABarDataColorValue)
{
for (int p = 0 ; p < FBarData[AIndex].Count; p++)
    {
     if (FBarData[AIndex].Item[p].Color==ABarDataColorValue)
         return FBarData[AIndex].Item[p].Value;
    }
return -1;
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetBarData(int AIndex, TColor AColorValue, int AValueValue)
{
if (AValueValue > BarScale || AValueValue < 0)
    return;

int isBarColorExists = false, p;

for (p = 0 ; p < FBarData[AIndex].Count; p++)
    {
     if (FBarData[AIndex].Item[p].Color==AColorValue)
        {isBarColorExists = true;
         break;
        }
    }
 if (isBarColorExists==false)
    {if (++FBarData[AIndex].Count>=16)
        {p = 0;
         FBarData[AIndex].Count = 1;
        }
     FBarData[AIndex].Item[p].Color = AColorValue;
     FBarData[AIndex].Item[p].Value = AValueValue;
    }
else FBarData[AIndex].Item[p].Value =AValueValue;

 if (BarAutoScale==false) FBarHigherValue = BarScale;
 else
    {
     if (FBarHigherValue<=AValueValue) FBarHigherValue = AValueValue;
     else
     {FBarHigherValue = 1;
      for (int i = 0; i < Count; i++ )
      for (int p = 0; p < FBarData[i].Count; p++)
          {
           if (FBarHigherValue < FBarData[i].Item[p].Value)
               FBarHigherValue = FBarData[i].Item[p].Value;
          }
    }
  }
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::Shift(void)
{
for (int i = 0; i+1 <=FBarData->Count; i++)
    {
     FBarData[i] = FBarData[i+1];
    }
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::SetBarDataCount(int ACount)
{
FBarData->SetCount(ACount);
FBarDataCount = ACount;
}
//---------------------------------------------------------------------------

__fastcall TBarGraph::~TBarGraph(void)
{
delete FBitmap;
delete FBarData;
}
//---------------------------------------------------------------------------

void __fastcall TBarGraph::Add(TColor AColorValue, int AValueValue)
{
FBarData->Add(AColorValue,AValueValue);
}
//---------------------------------------------------------------------------
// ITEMS
//---------------------------------------------------------------------------

__fastcall __Items::__Items()
{
Item = (__Item*)LocalAlloc(LMEM_MOVEABLE,sizeof(__Item)*(8));
Item[0].Color = clRed;
Item[0].Value = 0;
Count = 0;
}
//---------------------------------------------------------------------------

__fastcall __Items::~__Items()
{
LocalFree((void*)Item);
}
//---------------------------------------------------------------------------

int __fastcall __Items::SetCount(int ACount)
{
if (ACount==Count) return Count;
if (ACount >Count)
   {
    Item = (__Item*)LocalReAlloc((void*)Item,sizeof(__Item)*(ACount+1),LMEM_MOVEABLE);
    for (int i = Count; i < ACount; i++)
        {Item[i].Color = clRed;
         Item[i].Value = 0;
        }
   }
if (ACount <Count)
   {
    Item = (__Item*)LocalReAlloc((void*)Item,sizeof(__Item)*(ACount+1),LMEM_MOVEABLE);
    Item[ACount-1].Color = clRed;
    Item[ACount-1].Value = 0;
   }
return Count = ACount;
//ForceRepaint();
}
//---------------------------------------------------------------------------

int __fastcall __Items::Add(TColor AColorValue, int AValueValue)
{
this->Set(Count,AColorValue,AValueValue);
return Count;
}
//---------------------------------------------------------------------------

void __fastcall __Items::Clr()
{
this->SetCount(0);
//ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall __Items::Set(int AIndex, TColor AColor, int AValue)
{
if (AIndex <=Count) this->SetCount(AIndex);
    Item[AIndex].Color = AColor;
    Item[AIndex].Value = AValue;
//ForceRepaint();
}
//---------------------------------------------------------------------------

int __fastcall __Items::Ins(int AIndex, TColor AColor, int AValue)
{
if (AIndex>=Count) this->SetCount(AIndex+1);
else this->SetCount(Count+1);
for (int i = Count-1; i > AIndex; i--)
    {
     Item[i] = Item[i-1];
    }
Item[AIndex].Color = AColor;
Item[AIndex].Value = AValue;
return Count;
//ForceRepaint();
}
//---------------------------------------------------------------------------

int __fastcall __Items::Del(int AIndex)
{
if (AIndex>=Count)
     return Count;
for (int i = AIndex; i < Count; i++)
    {
     Item[i] = Item[i+1];
    }
this->SetCount(Count-1);
return Count;
//ForceRepaint();
}
//---------------------------------------------------------------------------

