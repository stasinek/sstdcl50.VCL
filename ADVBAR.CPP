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


//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "ADVBAR.H"
#include "FRAMEPAN.H"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TAdvancedBar *)
{
new TAdvancedBar(NULL);
}
//---------------------------------------------------------------------------

namespace Advbar
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TAdvancedBar)};
        RegisterComponents("User", classes, 0);
    }
}
//---------------------------------------------------------------------------

__fastcall TAdvancedBar::TAdvancedBar(TComponent* Owner)
    : TGraphicControl(Owner), FTextAlignment(taCenter), FTextSuffix("%"),
    FInnerRect(), FBackRect(), FForeRect(),
    FMin(0), FMax(100),FPos(0),FBarForeColor(clHighlight),FBarBackColor(clBtnFace),FTextBackColor(clHighlight),FTextForeColor(clHighlightText),
	FShowText(false), FOrientation(pbHorizontal),Block(false),FBorderSize(absSingle),FBorderKind(abkLowered)
{
        FBitmap = new Graphics::TBitmap;
         Height = 20;
FBitmap->Height = 20;
          Width = 100;
 FBitmap->Width = 100;
   ControlStyle = ControlStyle << csOpaque << csNoStdEvents;
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::CalculatePixelWidth()
{
if (FOrientation == pbHorizontal) FPixelWidth = int(int(FInnerRect.Right-FInnerRect.Left) * int(FPercent)) / 100;
else FPixelWidth = int(int(FInnerRect.Bottom-FInnerRect.Top) * int(FPercent)) / 100;
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::CalculatePercentDone()
{
double SDif = FMax-FMin;
if (SDif == 0) FPercent = 100;
else FPercent = double(100 * double(FPos-FMin))/double(SDif);
CalculatePixelWidth();
}
//---------------------------------------------------------------------------

#define COPY_RECT(x,y) x.left = y.Left; x.top = y.Top; x.right = y.Right; x.bottom = y.Bottom;

void __fastcall TAdvancedBar::Paint(void)
{
RECT crect;
COPY_RECT(crect,ClientRect)

if (crect.right!=FBitmap->Width || crect.bottom!=FBitmap->Height)
   {
	this->ForceRepaint();
	return;
   }
else
   {
	::GetClipBox(this->Canvas->Handle,&crect);
	::BitBlt(this->Canvas->Handle,
			 crect.left,crect.top,crect.right-crect.left,crect.bottom-crect.top,
			 FBitmap->Canvas->Handle,
			 crect.left,crect.top,
			 SRCCOPY);
   }
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::ForceRepaint(void)
{
while (Block==true) Application->ProcessMessages();
Block = true;
//---------------------------------------------------
RECT crect;
COPY_RECT(crect,ClientRect)
FBitmap->Width = crect.right; FBitmap->Height = crect.bottom;
CalculatePercentDone();
TRamka::PaintBorder(FBitmap->Canvas->Handle,&FInnerRect,&crect,FBorderKind,FBorderSize);
//---------------------------------------------------
if (FOrientation==pbHorizontal)
	{
	FForeRect.Right = FInnerRect.Left + FPixelWidth;
	FForeRect.Top = FInnerRect.Top;
	}
else
	{
	FForeRect.Top = FInnerRect.Bottom - FPixelWidth;
	FForeRect.Right = FInnerRect.Right;
	}
FForeRect.Bottom = FInnerRect.Bottom;
FForeRect.Left = FInnerRect.Left;

if (FOrientation==pbHorizontal)
	{
	FBackRect.Left = FInnerRect.Left + FPixelWidth;
	FBackRect.Bottom = FInnerRect.Bottom;
	}
else
	{
	FBackRect.Bottom = FInnerRect.Bottom - FPixelWidth;
	FBackRect.Left = FInnerRect.Left;
	}
FBackRect.Right = FInnerRect.Right;
FBackRect.Top = FInnerRect.Top;
//---------------------------------------------------
PaintBar(); PaintText();
//---------------------------------------------------
::BitBlt(this->Canvas->Handle,
		 0,0,crect.right,crect.bottom,
		 FBitmap->Canvas->Handle,
		 0,0,
		 SRCCOPY);
Block = false;
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::PaintBar(void)
{
FBitmap->Canvas->Brush->Style = bsSolid;
FBitmap->Canvas->Brush->Color = FBarForeColor;
FBitmap->Canvas->FillRect(FForeRect);
FBitmap->Canvas->Brush->Color = FBarBackColor;
FBitmap->Canvas->FillRect(FBackRect);
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::PaintText(void)
{
if (FShowText==false)
    return;
static AnsiString SText;
if (FTextSuffix.Pos("%")==0) SText = IntToStr((int)FPos-FMin) + FTextSuffix;
else SText = IntToStr((int)FPercent) + FTextSuffix;
FBitmap->Canvas->Font->Assign(Font);
int iw = FInnerRect.Right-FInnerRect.Left, ih = FInnerRect.Bottom-FInnerRect.Top;
int  TextWidth = FBitmap->Canvas->TextWidth(SText);
int TextX;
if (FTextAlignment==taCenter || FOrientation==pbVertical)  TextX = (iw  - TextWidth)/2;
else if (FTextAlignment==taLeftJustify)  TextX = FInnerRect.Left+FBitmap->Canvas->TextWidth("0");
    else if (FTextAlignment==taRightJustify)  TextX = FInnerRect.Right-FBitmap->Canvas->TextWidth("0")-TextWidth;
        else return;
int TextHeight = FBitmap->Canvas->TextHeight(SText);
int TextY = (ih - TextHeight)/2;

int t2w = 2*TextWidth, t2h = 2*TextHeight;
if (t2w>iw || t2h>ih) return;

FBitmap->Canvas->Brush->Style = bsClear;

RECT tempForeRect = FForeRect;
FBitmap->Canvas->Font->Color = FTextForeColor;
ExtTextOut(FBitmap->Canvas->Handle,TextX, TextY, ETO_CLIPPED,
           &tempForeRect, SText.c_str(), SText.Length(),NULL);
FBitmap->Canvas->Font->Color = FTextBackColor;
RECT tempBackRect = FBackRect;
ExtTextOut(FBitmap->Canvas->Handle, TextX, TextY, ETO_CLIPPED,
           &tempBackRect, SText.c_str(), SText.Length(),NULL);
}
//---------------------------------------------------------------------------

#define SETVALUE(oldvalue,newvalue) \
if (oldvalue==newvalue)\
    return;\
oldvalue = newvalue;

#include <limits.h>
#define SETMINMAXVALUE(oldvalue,minvalue,maxvalue,newvalue) \
if (newvalue==oldvalue)\
    return;\
if (newvalue > maxvalue)\
    return;\
if (newvalue < minvalue)\
    return;\
oldvalue = newvalue;

void __fastcall TAdvancedBar::SetTextSuffix(AnsiString ATextSuffixValue)
{
SETVALUE(FTextSuffix,ATextSuffixValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetTextAlignment(TAlignment ATextAlignmentValue)
{
SETVALUE(FTextAlignment,ATextAlignmentValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetShowText(bool AShowTextValue)
{
SETVALUE(FShowText,AShowTextValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetOrientation(TProgressBarOrientation AOrientationValue)
{
SETVALUE(FOrientation,AOrientationValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetBarBackColor(TColor ABarBackColorValue)
{
SETVALUE(FBarBackColor,ABarBackColorValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetTextForeColor(TColor ATextForeColorValue)
{
SETVALUE(FTextForeColor,ATextForeColorValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetBarForeColor(TColor ABarForeColorValue)
{
SETVALUE(FBarForeColor,ABarForeColorValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetTextBackColor(TColor ATextBackColorValue)
{
SETVALUE(FTextBackColor,ATextBackColorValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetBorderKind(TBorderKind ABorderKindValue)
{
SETVALUE(FBorderKind,ABorderKindValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetBorderSize(TBorderSize ABorderSizeValue)
{
SETVALUE(FBorderSize,ABorderSizeValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetMin(int AMinValue)
{
SETMINMAXVALUE(FMin,INT_MIN,FMax,AMinValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetPosition(int APosValue)
{
SETMINMAXVALUE(FPos,FMin,FMax,APosValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall TAdvancedBar::SetMax(int AMaxValue)
{
SETMINMAXVALUE(FMax,FMin,INT_MAX,AMaxValue);
ForceRepaint();
}
//---------------------------------------------------------------------------

__fastcall TAdvancedBar::~TAdvancedBar(void)
{
delete FBitmap;
}
//---------------------------------------------------------------------------
