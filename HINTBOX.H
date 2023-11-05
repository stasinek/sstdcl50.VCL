/***************************************************************************/
/*                      THintBox version 0.85                              */
/***************************************************************************/

//---------------------------------------------------------------------------
#ifndef __HINTBOX_h__
#define __HINTBOX_h__
//---------------------------------------------------------------------------
#if __BORLANDC__ > 0x0551
#include <Vcl.Comctrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Classes.hpp>
#else
#include <Vcl/Comctrls.hpp>
#include <Vcl/Controls.hpp>
#include <Vcl/Graphics.hpp>
#include <Vcl/Classes.hpp>
#endif
//---------------------------------------------------------------------------
const int iAlignLeft   = 0;                         // Align Left
const int iAlignCenter = 1;                         // Align Center
const int iAlignRight  = 2;                         // Align Right
//---------------------------------------------------------------------------
// Added the 05/24-1999 by JC
//---------------------------------------------------------------------------
class PACKAGE THintBox : public TGraphicControl
{
private:
    void __fastcall ForceRepaint(void);
    Graphics::TBitmap *FBitmap;
     void __fastcall DrawBoxEx();
     void __fastcall DrawBoxFrame();
     void __fastcall TextOutEx(int X,int Y,AnsiString *lpTextValue);
    TSize __fastcall TextExtentEx(AnsiString *lpTextValue);

     void __fastcall SetColor(TColor Value);
    TColor  BkColor;
     void __fastcall SetShadowColor(TColor Value);
    TColor  ShColor;
     void __fastcall SetShadowSize(int Value);
     int    iShadowSize;
     void __fastcall SetFormatting(bool Value);
     bool   bFormatting;
     void __fastcall SetHintBox(bool Value);
     bool   bDrawBox;
     Classes::TStrings *__fastcall GetLines();
     void __fastcall SetLines(Classes::TStrings *Value);
     Classes::TStrings *FLines;
     void __fastcall SetFont(TFont *Value);
    TFont *FFont, *OFont;
     void virtual __fastcall Parse();
     void virtual __fastcall ParseLine(int index);
    TList *AlignList;
     int  __fastcall FindFirstChar(AnsiString *lpTextValue,char cFind,int iOldIndex,int ongroup);
    TStringList *TextList;        
public:
     __fastcall  THintBox(TComponent* Owner);
    virtual void __fastcall Paint();
            void __fastcall Update();
     __fastcall ~THintBox();
__published:
    __property TColor Color = {read=BkColor, write=SetColor,default=clInfoBk};
    __property bool DrawBox = {read=bDrawBox, write=SetHintBox,default=true};
    __property int ShadowSize = {read=iShadowSize, write=SetShadowSize,default=4};
    __property TColor ShadowColor = {read=ShColor, write=SetShadowColor,default=clGray};
    __property TFont *Font = {read=FFont, write=SetFont};
    __property bool Formatting = {read=bFormatting, write=SetFormatting,default=true};
    __property Classes::TStrings *Lines = {read=FLines, write=SetLines};

    __property Align;
    __property Enabled;
    __property PopupMenu;
    __property OnClick;
    __property OnDblClick;
    __property OnDragDrop;
    __property OnDragOver;
    __property OnEndDrag;
    __property OnMouseDown;
    __property OnMouseMove;
    __property OnMouseUp;
    __property OnStartDrag;
    __property Visible;
};
//---------------------------------------------------------------------------
#endif


