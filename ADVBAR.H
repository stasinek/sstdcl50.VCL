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
#ifndef __tsoft_advbar_HDR__
#define __tsoft_advbar_HDR__
//---------------------------------------------------------------------------
#include "ADVBAR.H"
#include "FRAMEPAN.H"
#if __BORLANDC__ > 0x0550
#include <Vcl.Comctrls.hpp>
#else
#include <Vcl/Comctrls.hpp>
#endif
//---------------------------------------------------------------------------
//enum TProgressBarOrientation { pbHorizontal, pbVertical };
//enum TAlignment { taCenter,taLeftJustify, taRightJustify }; //Classes::taCenter

class PACKAGE TAdvancedBar : public TGraphicControl
{
private:
	bool Block;
	Graphics::TBitmap *FBitmap;

	void __fastcall SetOrientation(TProgressBarOrientation Value);
	TProgressBarOrientation FOrientation;

	void __fastcall SetBorderKind(TBorderKind Value);
	TBorderKind FBorderKind;
	void __fastcall SetBorderSize(TBorderSize Value);
	TBorderSize FBorderSize;

	void __fastcall ForceRepaint(void);
	void __fastcall PaintBar();

    TRect  FInnerRect, FBackRect, FForeRect;
    void __fastcall CalculatePixelWidth(void);
    int   FPixelWidth;
    void __fastcall SetBarForeColor(TColor Value);
    TColor FBarForeColor;
    void __fastcall SetBarBackColor(TColor Value);
    TColor FBarBackColor;

    void __fastcall SetMin(int Value);
    int   FMin;
    void __fastcall SetPosition(int Value);
    int   FPos;
    void __fastcall SetMax(int Value);
    int   FMax;
    void __fastcall CalculatePercentDone(void);
    float FPercent;

    void __fastcall SetTextForeColor(TColor Value);
    TColor FTextForeColor;
    void __fastcall SetTextBackColor(TColor Value);
    TColor FTextBackColor;
    void __fastcall SetShowText(bool Value);
    bool FShowText;
    void __fastcall SetTextSuffix(AnsiString Value);
    AnsiString FTextSuffix;
    void __fastcall SetTextAlignment(TAlignment Value);
    TAlignment FTextAlignment;

    void __fastcall PaintText();
public:
    __fastcall  TAdvancedBar(TComponent* Owner);
    virtual void __fastcall Paint(void);
    __fastcall ~TAdvancedBar(void);
__published:
    __property Align;
    __property TProgressBarOrientation Orientation = {read=FOrientation,write=SetOrientation,default=pbHorizontal};
    __property TBorderKind BorderKind = {read=FBorderKind,write=SetBorderKind,default=abkLowered};
    __property TBorderSize BorderSize = {read=FBorderSize,write=SetBorderSize,default=absSingle};
    __property TColor TextForeColor = {read=FTextForeColor,write=SetTextForeColor,default=clHighlightText};
    __property TColor TextBackColor = {read=FTextBackColor,write=SetTextBackColor,default=clBtnFace};
    __property ParentFont;
    __property Font;
    __property bool ShowText = {read=FShowText,write=SetShowText,default=false};
    __property AnsiString TextSuffix = {read=FTextSuffix,write=SetTextSuffix};
    __property TAlignment TextAlignment = {read=FTextAlignment,write=SetTextAlignment,default=taCenter};

    __property TColor BarForeColor = {read=FBarForeColor,write=SetBarForeColor,default=clHighlight};
    __property TColor BarBackColor = {read=FBarBackColor,write=SetBarBackColor,default=clBtnFace};
    __property int Min = {read=FMin,write=SetMin,default=0};
    __property int Position = {read=FPos,write=SetPosition,default=0};
    __property int Max = {read=FMax,write=SetMax,default=100};
    __property Visible;
};

//---------------------------------------------------------------------------
#endif
