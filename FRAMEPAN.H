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
#ifndef __framepan_HDR__
#define __framepan_HDR__
//---------------------------------------------------------------------------
#include <Controls.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <Windows.hpp>
//---------------------------------------------------------------------------

enum TBorderKind { abkNone, abkRect, abkLowered, abkRaised };
enum TBorderSize { absSingle, absDouble };

class PACKAGE TRamka : public TGraphicControl
{
private:
    bool RBlock;
    void __fastcall SetBorderKind(TBorderKind Value);
    TBorderKind FBorderKind;
    void __fastcall SetBorderSize(TBorderSize Value);
    TBorderSize FBorderSize;
    void __fastcall SetColor(TColor Value);
    TColor FColor;
public:
    static RECT *__fastcall PaintBorder(HDC hdc, RECT *retrect, RECT *thisrect, TBorderKind ABorderKind, TBorderSize ABorderSize);
    RECT InnerRECT;
    __fastcall TRamka(TComponent* Owner);
    virtual void __fastcall Paint(void);
    __fastcall ~TRamka(void);
    __property Canvas;
__published:
    __property Align;
    __property Visible;
    __property TBorderKind BorderKind = {read=FBorderKind, write=SetBorderKind};
    __property TBorderSize BorderSize = {read=FBorderSize, write=SetBorderSize};
    __property TColor Color = {read=FColor,write=SetColor};
    __property OnMouseDown;
    __property OnMouseMove;
    __property OnMouseUp;
    __property OnClick;
    __property OnDblClick;
    __property Caption;
    __property ClientHeight;
    __property ClientWidth;
    __property ControlState;
    __property ControlStyle;
    __property Cursor;
    __property DesktopFont;
    __property DragCursor;
    __property DragMode;
    __property Enabled;
    __property Height;
    __property Hint;
    __property IsControl;
    __property Left;
    __property MouseCapture;
    __property Name;
    __property Parent;
    __property ParentColor;
    __property ParentFont;
    __property ParentShowHint;
    __property PopupMenu;
    __property ScalingFlags;
    __property ShowHint;
    __property Top;
    __property Width;
    __property WindowProc;
};

//---------------------------------------------------------------------------
#endif
