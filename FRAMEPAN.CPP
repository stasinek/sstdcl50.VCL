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
#include "framepan.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TRamka *)
{
    new TRamka(NULL);
}
//---------------------------------------------------------------------------

namespace Framepan
{
        void __fastcall PACKAGE Register()
        {
        TComponentClass classes[1] = {__classid(TRamka)};
        RegisterComponents("User", classes, 0);
        }
}
//---------------------------------------------------------------------------

__fastcall TRamka::TRamka(TComponent* Owner)
    : TGraphicControl(Owner)
{
FBorderKind = bRaised;
FBorderSize = bSingle;
     FColor = clNone;
     Height = 200;
      Width = 100;
ControlStyle = ControlStyle << csCaptureMouse << csClickEvents << csDoubleClicks << csReplicatable << csFramed;
Canvas->Brush->Color = this->Color;
}
//---------------------------------------------------------------------------

void __fastcall TRamka::Paint(void)
{
RECT thisrect;
  thisrect.left = 0;
   thisrect.top = 0;
 thisrect.right = ClientRect.Right;
thisrect.bottom = ClientRect.Bottom;

if (Color!=clNone)
   {::FillRect(Canvas->Handle,&thisrect,Canvas->Brush->Handle);
   }
PaintBorder(Canvas->Handle,&InnerRECT,&thisrect,FBorderKind,FBorderSize);
}
//---------------------------------------------------------------------------

RECT *__fastcall TRamka::PaintBorder(HDC hdc, RECT *retrect, RECT *thisrect,TBorderKind ABorderKind,TBorderSize ABorderSize) {
HBRUSH hbrush; HPEN hpen;
POINT SSize;

static SBlock = false;
while (SBlock==true) Application->ProcessMessages();
SBlock = true;

SSize.x = thisrect->right - thisrect->left; SSize.y = thisrect->bottom - thisrect->top;

switch (ABorderKind)
   {
    case bRect:
         if (ABorderSize==bSingle)
            {
             hbrush = CreateSolidBrush(GetSysColor(COLOR_WINDOWFRAME));
             RECT temprect = *thisrect;
             temprect.left++; temprect.top++; temprect.right--; temprect.bottom--;
             ::FrameRect(hdc,&temprect,hbrush);
             DeleteObject(hbrush);
            }
         else
            {
             hbrush = CreateSolidBrush(GetSysColor(COLOR_WINDOWFRAME));
             RECT temprect = *thisrect;
             temprect.left++; temprect.top++; temprect.right--; temprect.bottom--;
             ::FrameRect(hdc,&temprect,hbrush);
             temprect.left++; temprect.top++; temprect.right--; temprect.bottom--;
             ::FrameRect(hdc,&temprect,hbrush);
             DeleteObject(hbrush);
            }
    break;
    case bLowered:
         if (ABorderSize==bSingle)
            {
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNHIGHLIGHT));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,0,SSize.y-1,NULL);
               ::LineTo(hdc,SSize.x,SSize.y-1);
             ::MoveToEx(hdc,SSize.x-1,0,NULL);
               ::LineTo(hdc,SSize.x-1,SSize.y);
             DeleteObject(hpen);
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,0,SSize.y-1,NULL);
               ::LineTo(hdc,0,0);
               ::LineTo(hdc,SSize.x,0);
             DeleteObject(hpen);
            }
         else
            {
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNHIGHLIGHT));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,0,SSize.y-1,NULL);
               ::LineTo(hdc,SSize.x,SSize.y-1);
             ::MoveToEx(hdc,SSize.x-1,0,NULL);
               ::LineTo(hdc,SSize.x-1,SSize.y);
             DeleteObject(hpen);
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,0,SSize.y-2,NULL);
               ::LineTo(hdc,0,0);
               ::LineTo(hdc,SSize.x-1,0);
             DeleteObject(hpen);
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DDKSHADOW));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,1,SSize.y-3,NULL);
               ::LineTo(hdc,1,1);
               ::LineTo(hdc,SSize.x-2,1);
             DeleteObject(hpen);
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DLIGHT));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,1,SSize.y-2,NULL);
               ::LineTo(hdc,SSize.x-2,SSize.y-2);
               ::LineTo(hdc,SSize.x-2,0);
             DeleteObject(hpen);
            }
    break;
    case bRaised:
         if (ABorderSize==bSingle)
            {
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,0,SSize.y-1,NULL);
               ::LineTo(hdc,SSize.x,SSize.y-1);
             ::MoveToEx(hdc,SSize.x-1,0,NULL);
               ::LineTo(hdc,SSize.x-1,SSize.y);
             DeleteObject(hpen);
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNHIGHLIGHT));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,0,SSize.y-1,NULL);
               ::LineTo(hdc,0,0);
               ::LineTo(hdc,SSize.x,0);
             DeleteObject(hpen);
            }
         else
            {
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DDKSHADOW));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,0,SSize.y-1,NULL);
               ::LineTo(hdc,SSize.x,SSize.y-1);
             ::MoveToEx(hdc,SSize.x-1,0,NULL);
               ::LineTo(hdc,SSize.x-1,SSize.y);
             DeleteObject(hpen);
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DLIGHT));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,0,SSize.y-2,NULL);
               ::LineTo(hdc,0,0);
               ::LineTo(hdc,SSize.x-1,0);
             DeleteObject(hpen);
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNHIGHLIGHT));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,1,SSize.y-3,NULL);
               ::LineTo(hdc,1,1);
               ::LineTo(hdc,SSize.x-2,1);
             DeleteObject(hpen);
             hpen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW));
             SelectObject(hdc,hpen);
             ::MoveToEx(hdc,1,SSize.y-2,NULL);
               ::LineTo(hdc,SSize.x-2,SSize.y-2);
               ::LineTo(hdc,SSize.x-2,0);
             DeleteObject(hpen);
            }
    break;
    case bkNone:
    retrect->left = thisrect->left;
    retrect->right = thisrect->right;
    retrect->top = thisrect->top;
    retrect->bottom = thisrect->bottom;
    break;
   }
if (ABorderSize==bSingle)
   {
    retrect->left = thisrect->left+1;
    retrect->right = thisrect->right-1;
    retrect->top = thisrect->top+1;
    retrect->bottom = thisrect->bottom-1;
   }
else
   {
    retrect->left = thisrect->left+2;
    retrect->right = thisrect->right-2;
    retrect->top = thisrect->top+2;
    retrect->bottom = thisrect->bottom-2;
   }
SBlock = false; return retrect;
}
//---------------------------------------------------------------------------

void __fastcall TRamka::SetBorderKind(TBorderKind ABorderKindValue)
{
if (ABorderKindValue==FBorderKind)
    return;
FBorderKind = ABorderKindValue;
Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TRamka::SetBorderSize(TBorderSize ABorderSizeValue)
{
if (ABorderSizeValue==FBorderSize)
    return;
FBorderSize = ABorderSizeValue;
Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TRamka::SetColor(TColor AColorValue)
{
if (AColorValue==FColor)
    return;
FColor = AColorValue;
Canvas->Brush->Color = FColor;
Repaint();
}
//---------------------------------------------------------------------------

__fastcall TRamka::~TRamka(void)
{
}
//---------------------------------------------------------------------------
