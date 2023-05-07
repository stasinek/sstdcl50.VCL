/****************************************************************************/
/* THintBox version 0.85 05/09-1999 Jeppe Cramon      		   				*/
/* -----------------------------------------------------------------------  */
/* What is it: This is a quick implementation of the HintBox's that you can */
/* see in many Lotus products (for instance Lotus SmartSuite). 				*/
/*                                                                          */
/* How to install it: Go to the "Component" Menuitem and select "Install    */
/* -----------------------------------------------------------------------  */
/* Component...". Click the "Browse" button next to the  					*/
/*               "Unit file name:". Choose "HintBox.cpp".                   */
/*               Choose the apporpriate package to install THintBox in 		*/
/*               to, from the "Package file name" combobox (normally:  		*/
/*               dclusr35.bpk or dclusr40.bpk)                         		*/
/*               THintBox will register it self in the "Samples"       		*/
/*               palette.                                              		*/
/*                                                                          */
/* -----------------------------------------------------------------------  */
/* Add support for HTML tags.                                               */
/* This means that THintBox, now is able to display HTML formatted text.    */
/* So far only a very minor fraction of the HTML standard is supported:     */
/*               Center Text - <CENTER>..Text..</CENTER>                    */
/*               Line break  - <BR>                                         */
/*               Bold        - <B>..Text..</B>                              */
/*               Italic      - <I>..Text..</I>                              */
/*               Underline   - <U>..Text..</U>                              */
/*               StrikeOut   - <STRIKE>..Text..</STRIKE>                    */
/*                                                                          */
/* NEW: You can now also choose if THintBox should draw it's hintbox.       */
/* Setting the DrawHintBox property to false will make it look like a label */
/* but with all the HintBox features ;-)                     			    */
/****************************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#include <Windows.hpp>
#pragma hdrstop
#include "HINTBOX.H"
#pragma package(smart_init)
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(THintBox *)
{
        new THintBox(NULL);
}
//---------------------------------------------------------------------------

namespace Hintbox
{
        void __fastcall PACKAGE Register()
        {
        TComponentClass classes[1] = {__classid(THintBox)};
        RegisterComponents("User", classes, 0);
        }
}
//---------------------------------------------------------------------------

__fastcall THintBox::THintBox(TComponent* Owner)
    : TGraphicControl(Owner)
{
    BkColor = clInfoBk;
    ShColor = clGray;
iShadowSize = 4;
bFormatting = true;
   bDrawBox = true;
    FBitmap = new Graphics::TBitmap;
     Height = 200;
FBitmap->Height = 0;
      Width = 150;
 FBitmap->Width = 0;
     FLines = new TStringList();
   TextList = NULL;
  AlignList = NULL;
      FFont = new TFont();
      OFont = new TFont();
}
//---------------------------------------------------------------------------

void __fastcall THintBox::Paint()
{
RECT thisrect;
  thisrect.left = 0;
   thisrect.top = 0;
 thisrect.right = ClientRect.Right;
thisrect.bottom = ClientRect.Bottom;
if (thisrect.right!=FBitmap->Width || thisrect.bottom!=FBitmap->Height)
   {
    this->ForceRepaint();
    return;
   }
else
   {::GetClipBox(this->Canvas->Handle,&thisrect);
    ::BitBlt(this->Canvas->Handle,
             thisrect.left,thisrect.top,thisrect.right-thisrect.left,thisrect.bottom-thisrect.top,
             FBitmap->Canvas->Handle,
             thisrect.left,thisrect.top,
             SRCCOPY);
   }
}
//---------------------------------------------------------------------------

void __fastcall THintBox::ForceRepaint(void)
{
RECT thisrect;
  thisrect.left = 0;
   thisrect.top = 0;
 thisrect.right = ClientRect.Right;
thisrect.bottom = ClientRect.Bottom;
 FBitmap->Width = thisrect.right; FBitmap->Height = thisrect.bottom;

 DrawBoxEx();

::BitBlt(this->Canvas->Handle,
         0,0,thisrect.right,thisrect.bottom,
         FBitmap->Canvas->Handle,
         0,0,
         SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall THintBox::DrawBoxFrame()
{
static TRect tempRect;

if (bDrawBox)
   {
    FBitmap->Canvas->Brush->Style = bsSolid;
    // Draw shadow
    FBitmap->Canvas->Brush->Color = clBtnFace;
    tempRect = ClientRect;
    tempRect.Top = tempRect.Bottom - iShadowSize;
    tempRect.Right = iShadowSize;
    FBitmap->Canvas->FillRect(tempRect);
    tempRect = ClientRect;
    tempRect.Bottom = iShadowSize;
    tempRect.Left = tempRect.Right - iShadowSize;
    FBitmap->Canvas->FillRect(tempRect);

    FBitmap->Canvas->Brush->Color = ShColor;
    tempRect = ClientRect;
    tempRect.Top = tempRect.Bottom - iShadowSize;
    tempRect.Left += iShadowSize;
    FBitmap->Canvas->FillRect(tempRect);
    tempRect = ClientRect;
    tempRect.Top += iShadowSize;
    tempRect.Left =  tempRect.Right - iShadowSize;
    FBitmap->Canvas->FillRect(tempRect);
    // Draw hint frame
    tempRect = ClientRect;
    tempRect.Right -= iShadowSize;
    tempRect.Bottom -= iShadowSize;
    FBitmap->Canvas->Brush->Color = BkColor;
    FBitmap->Canvas->Rectangle(tempRect.Left,tempRect.Top,tempRect.Right,tempRect.Bottom);
    FBitmap->Canvas->Brush->Style = bsClear;
   }
else
   {
    FBitmap->Canvas->Brush->Style = bsSolid;
    tempRect = ClientRect;
    FBitmap->Canvas->Brush->Color = Parent->Brush->Color;
    FBitmap->Canvas->FillRect(tempRect);
    // Set brush style
    FBitmap->Canvas->Brush->Style = bsClear;
   }
}
//---------------------------------------------------------------------------

void __fastcall THintBox::DrawBoxEx()
{
/*
// Reset font style
FBitmap->Canvas->Font->Assign(OFont);
// Reset font style
if (!TextList)
   {Parse();
   }
this->DrawBoxFrame();
// Stop painting if there's no text available
if (FLines->Count == 0)
    return;
TSize size;                             					    // Size (used in TextExtent)
static AnsiString Caption;                     					// Used for quick porting of the old component, that used TPanel's Caption.
static AnsiString asTmp;                       					// Tmp. string (used in TextExtent)
static TRect Rect;
Rect = ClientRect;
int iLastSpace, iPos1, iPos2, iLineNo = 0, iListCount;         	// Startindex, endindex and number of lines drawn
// Set start coordinates
if (bDrawBox)
   {Rect.Left = Rect.Left + 5;
    Rect.Right = Rect.Right - iShadowSize - 5;
    Rect.Top = Rect.Top + 5;
    Rect.Bottom = Rect.Bottom - iShadowSize - 5;
   }
if (bFormatting)
   { FBitmap->Canvas->Font->Style = FBitmap->Canvas->Font->Style.Clear();
     iListCount = TextList->Count;
   }
else iListCount = FLines->Count;
// Loop through all the lines
for (int iLoop = 0, iLength; iLoop < iListCount; iLoop++)
    {
     if (bFormatting) Caption = TextList->Strings[iLoop];
     else
     Caption = FLines->Strings[iLoop];
     // Init this run
     iLength = Caption.Length();
        size = TextExtentEx(&Caption);
     // Skip the line if it's empty
     if (Caption=="")
         goto CONTINUE;
     if ((Rect.Top+size.cy*(iLineNo+1))>=Rect.Bottom)
         return;
     if (size.cx < (Rect.Right-Rect.Left))
        {
         iPos1 = 1;
         iPos2 = iLength+1;
        }
     else
        {
        for (iPos2 = 1, iLastSpace = 0, asTmp = ""; iLastSpace+iPos2<=iLength; )
            {
             asTmp += Caption.SubString(iLastSpace+iPos2,1);
               size = TextExtentEx(&asTmp);
             // Make sure it doesn't extend the frames bottom
             if (size.cx >= (Rect.Right-Rect.Left))
                {
                 int  isBreakWord = true;

                 for (int p = asTmp.Length(); p>=1 ? size.cx >= (Rect.Right-Rect.Left) : false; size = TextExtentEx(&asTmp))
                     {
                      asTmp.SetLength(--p);
                     }
                  if (asTmp.LastDelimiter("<") > asTmp.LastDelimiter(">"))
                     {
                      asTmp.SetLength(asTmp.LastDelimiter("<")-1);
                      isBreakWord = false;
                     }
                  if (asTmp.LastDelimiter(" ") > asTmp.LastDelimiter("<"))
                  if (asTmp.LastDelimiter(" ") > asTmp.LastDelimiter(">"))
                     {
                      asTmp.SetLength(asTmp.LastDelimiter(" ")-1);
                      isBreakWord = false;
                     }
                  if (isBreakWord)
                     {
                      asTmp[asTmp.Length()] = '-';
                      iLastSpace-=2;
                     }
                // get text size
                size = TextExtentEx(&asTmp);
                // out it
                if (bFormatting)
                {
                 switch((int)AlignList->Items[iLoop])
                      {
                       case iAlignLeft:
                            TextOutEx(Rect.Left,Rect.Top+size.cy*iLineNo,&asTmp);
                       break;
                       case iAlignCenter:
                            TextOutEx(Rect.Left+(Rect.Right-Rect.Left-size.cx)/2, Rect.Top+size.cy*iLineNo,&asTmp);
                       break;
                       case iAlignRight:
                            TextOutEx(Rect.Right-size.cx,Rect.Top+size.cy*iLineNo,&asTmp);
                       break;
                      }
                }
                else
                   {FBitmap->Canvas->TextOut(Rect.Left,Rect.Top+size.cy*iLineNo,asTmp);
                   }
                if ((Rect.Top+size.cy*(++iLineNo+1))>=Rect.Bottom)
                    return;
                iLastSpace += asTmp.Length()+1;
                asTmp.SetLength(0);
                iPos2 = 1;
               }
            else iPos2++;
           }
         iPos1 = iLastSpace +1;
         iPos2 = iPos1 + iPos2;

         if (iPos2-iPos1==0)
             continue;
        }
     size = TextExtentEx(&Caption.SubString(iPos1+1,iPos2-iPos1));
     // Write the rest of the string (or the entire string, incase there was no WordWrapping required)
     // Make sure it doesn't extend the frames bottom
     if ((Rect.Top+size.cy*(iLineNo+1))>=Rect.Bottom) return;
     else
        {
         if (bFormatting)
         {
          switch((int)AlignList->Items[iLoop])
               {
                case iAlignLeft :
                     TextOutEx(Rect.Left, Rect.Top+size.cy*iLineNo,&Caption.SubString(iPos1,iPos2-iPos1));
                break;
                case iAlignCenter :
                     TextOutEx(Rect.Left+(Rect.Right-Rect.Left-size.cx)/2, Rect.Top+size.cy*iLineNo,&Caption.SubString(iPos1,iPos2-iPos1));
                break;
                case iAlignRight :
                     TextOutEx(Rect.Right-size.cx, Rect.Top+size.cy*iLineNo,&Caption.SubString(iPos1,iPos2-iPos1));
                break;
               }
        }
        else
           {FBitmap->Canvas->TextOut(Rect.Left,Rect.Top+size.cy*iLineNo,Caption.SubString(iPos1,iPos2-iPos1));
           }
       }
CONTINUE:
   iLineNo++;
  } // end for
*/
}
//---------------------------------------------------------------------------

void __fastcall THintBox::SetFont(TFont *Value)
{
OFont->Assign(Value);
FFont->Assign(Value);
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall THintBox::SetColor(TColor Value)
{
if (Value==BkColor)
    return;
BkColor = Value;
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall THintBox::SetShadowColor(TColor Value)
{
if (Value==ShColor)
    return;
ShColor = Value;
ForceRepaint();
}
//---------------------------------------------------------------------------

Classes::TStrings *__fastcall THintBox::GetLines()
{
return FLines;
}
//---------------------------------------------------------------------------

void __fastcall THintBox::SetLines(Classes::TStrings *Value)
{
FLines->Assign(Value);
Update();
}
//---------------------------------------------------------------------------

void __fastcall THintBox::SetShadowSize(int Value)
{
if (Value==iShadowSize || Value < 0)
    return;
 Width += Value-iShadowSize;
Height += Value-iShadowSize;
iShadowSize = Value;
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall THintBox::Parse()
{
if (!TextList)
   { TextList = new TStringList();
    AlignList = new TList();
   }
else
   { TextList->Clear();
    AlignList->Clear();
   }
if (FLines->Count==0)
    return;
for (int iLoop = 0; iLoop < FLines->Count; iLoop++)
    {ParseLine(iLoop);
    }
}
//---------------------------------------------------------------------------

#define GROUP_LAST     (DWORD)0x00
#define GROUP_FIRST    (DWORD)0xFF

int __fastcall THintBox::FindFirstChar(AnsiString *lpTextValue, char cFind, int iOldIndex, int ongroup)
{
char * asTmp = lpTextValue->c_str();

for (int iIndex = iOldIndex-1, iLength = lpTextValue->Length(); iIndex < iLength; iIndex++)
    {
     if (asTmp[iIndex]!=cFind) continue;
     else
     if (ongroup==GROUP_LAST)
        {
         if (iIndex+1 < iLength ? asTmp[iIndex+1]!=cFind : true)
             return iIndex+1;
        }
     else return iIndex+1;
    }
return 0;
}
//---------------------------------------------------------------------------

void __fastcall THintBox::ParseLine(int index)
{

static AnsiString asText;
int iLastPos = 1, iEndPos, iStartPos;
asText = FLines->Strings[index];
int iAlign = iAlignLeft;
int iEndOfTagAlign = iAlign;        // Used to set the proper align

for (;;)
    {
   // Start parsing the line
   // Check if it contains a  tag
   // Find the start of the tag
//SEARCH_AGAIN:
   if (asText=="")
      {
        TextList->Add(asText);
       AlignList->Add((void*)iAlign);
       return;
      }
   if ((iStartPos = FindFirstChar(&asText,'<', iLastPos,GROUP_LAST))==0)
      {
      // It didn't contain a start of tag
        TextList->Add(asText);
       AlignList->Add((void*)iAlign);
       return;
      }
   else
   if ((iEndPos = FindFirstChar(&asText,'>', iLastPos,GROUP_FIRST))==0)
      {
        TextList->Add(asText);
       AlignList->Add((void*)iAlign);
       return;
      }
   else
   if (iEndPos < iStartPos)
      {
       iLastPos = iEndPos+1;
       continue;
      }
   static AnsiString asTmp;
   asTmp = asText.SubString(iStartPos+1, iEndPos-iStartPos-1).UpperCase();

   int isCode=0, newiAlign = iAlign;

   if (asTmp == "BR")
      {isCode = 1;}
   else
   if (asTmp == "RIGHT")
      {isCode = 2;
       iEndOfTagAlign = iAlignRight;
            newiAlign = iAlignRight;
      }
   else
   if (asTmp == "/RIGHT")
      {isCode = 3;
       newiAlign = iAlignLeft;
      }
   else
   if (asTmp == "CENTER")
      {isCode = 2;
       iEndOfTagAlign = iAlignCenter;
            newiAlign = iAlignCenter;
      }
   else
   if (asTmp == "/CENTER")
      {isCode = 3;
       newiAlign = iAlignLeft;
      }

   if (isCode==0)
      {
       if (asTmp!="B" && asTmp!="/B" && asTmp!="I" && asTmp!="/I" && asTmp!="U" && asTmp!="/U" &&asTmp!="STRIKE" && asTmp!="/STRIKE" && asTmp!="A" && asTmp!="/A")
          {
              asText = asText.Delete(iStartPos,iEndPos-iStartPos+1).TrimLeft();
            iLastPos = iStartPos+1;
          }
       else iLastPos = iEndPos+1;
      }
   else
   if (isCode==1)
      { TextList->Add(asText.SubString(1, iStartPos-1));
       AlignList->Add((void*)iAlign);
       asText = asText.SubString(iEndPos+1, asText.Length()-iEndPos).TrimLeft();
       iLastPos = 1;
       iAlign = newiAlign;
      }
   else
   if (isCode==2)
      {if (iStartPos!=1)
          {// We're starting on a new line, so move the start of the string to a line for it self
           asTmp = asText.SubString(1, iStartPos-1);
           AlignList->Add((void*)iAlign);
            TextList->Add(asText.SubString(1, iStartPos-1));
          }
       asText = asText.SubString(iEndPos+1, asText.Length()-iEndPos).TrimLeft();
       iLastPos = 1;
       iAlign = newiAlign;
      }
   else
   if (isCode==3)
      { TextList->Add( asText.SubString(1, iStartPos-1));
       AlignList->Add((void*)iEndOfTagAlign);
           asText = asText.SubString(iEndPos+1, asText.Length()-iEndPos).TrimLeft();
         iLastPos = 1;
       iAlign = newiAlign;
       if (asText=="")
           return;
      }
  } // end while(1)
}
//---------------------------------------------------------------------------

TSize __fastcall THintBox::TextExtentEx(AnsiString *lpTextValue)
{
static TSize tmpSize; tmpSize.cx = 0; tmpSize.cy = 0;
static AnsiString asText;

if (!bFormatting)
    return FBitmap->Canvas->TextExtent(*lpTextValue);

asText = *lpTextValue;
int iLastPos = 1, iEndPos, iStartPos;

static TFontStyles nStyle, oStyle;
oStyle = FBitmap->Canvas->Font->Style;

for (;;)
    {
  // Start parsing the line
  // Check if it contains a  tag
  // Find the start of the tag
//SEARCH_AGAIN:
   if (asText.Length()==0)
      {
       // Reset style
       FBitmap->Canvas->Font->Style = oStyle;
       return tmpSize;
      }
   if ((iStartPos = FindFirstChar(&asText,'<', iLastPos,GROUP_LAST))==0)
      {
      // It didn't contain a start of tag
       TSize size = FBitmap->Canvas->TextExtent(asText);
       tmpSize.cx += size.cx;
       // Check if we need to update cy
       if (size.cy > tmpSize.cy)
           tmpSize.cy = size.cy;
       // Reset style
       FBitmap->Canvas->Font->Style = oStyle;
       return tmpSize;
      }
   else
   if ((iEndPos = FindFirstChar(&asText,'>', iLastPos,GROUP_FIRST))==0)
      {
       // It didn't contain an end of tag
       TSize size = FBitmap->Canvas->TextExtent(asText);
       tmpSize.cx += size.cx;
       // Check if we need to update cy
       if (size.cy > tmpSize.cy)
           tmpSize.cy = size.cy;
       // Reset style
       FBitmap->Canvas->Font->Style = oStyle;
       return tmpSize;
      }
   else
      {
       if (iEndPos < iStartPos)
          {
           iLastPos = iEndPos+1;
           continue;
          }
      }
   static AnsiString asTmp;
   asTmp = asText.SubString(iStartPos+1, iEndPos-iStartPos-1).UpperCase();
   // Save old font
   nStyle = FBitmap->Canvas->Font->Style;
   //
   int isCode=0;

   if (asTmp == "B")
      {isCode =true;
       nStyle = nStyle << fsBold;
      }
   else
   if (asTmp == "I")
      {isCode =true;
       nStyle = nStyle << fsItalic;
      }
   else
   if (asTmp == "U")
      {isCode =true;
       nStyle = nStyle << fsUnderline;
      }
   else
   if (asTmp == "STRIKE")
      {isCode =true;
       nStyle = nStyle << fsStrikeOut;
      }
   else
   if (asTmp == "A")
      {isCode =true;
       nStyle = nStyle << fsBold << fsUnderline;
      }
   else
   if (asTmp == "/B")
      {isCode =true;
       nStyle = nStyle >> fsBold;
      }
   else
   if (asTmp == "/I")
      {isCode =true;
       nStyle = nStyle >> fsItalic;
      }
   else
   if (asTmp == "/U")
      {isCode =true;
       nStyle = nStyle >> fsUnderline;
      }
   else
   if (asTmp == "/STRIKE")
      {isCode =true;
       nStyle = nStyle >> fsStrikeOut;
      }
   if (asTmp == "/A")
      {isCode =true;
       nStyle = nStyle >> fsBold >> fsUnderline;
      }
   if (isCode==true)
      {// Get extents of current text
       TSize size = FBitmap->Canvas->TextExtent(asText.SubString(1,iStartPos-1));
       tmpSize.cx += size.cx;
       // Check if we need to update cy
       if (size.cy > tmpSize.cy)
           tmpSize.cy = size.cy;
       // Skip the <..> part
       asText = asText.SubString(iEndPos+1,asText.Length()-iEndPos);
       iLastPos = 1;
       // Set new font
       FBitmap->Canvas->Font->Style = nStyle;
      }
   else
      {// Unsupported tag
       // Get extents of current text
       TSize size = FBitmap->Canvas->TextExtent(asText.SubString(1,iEndPos));
       tmpSize.cx += size.cx;
       asText = asText.SubString(iEndPos+1, asText.Length()-iEndPos);
       // Check if we need to update cy
       if (size.cy > tmpSize.cy)
           tmpSize.cy = size.cy;
       iLastPos = 1;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall THintBox::TextOutEx(int X, int Y, AnsiString *lpTextValue)
{
static TSize tmpSize; tmpSize.cx = X;
static AnsiString asText;
int iLastPos = 1, iEndPos, iStartPos;
asText = *lpTextValue;

static TFontStyles nStyle, oStyle;
oStyle = FBitmap->Canvas->Font->Style;
TColor nColor, oColor = FBitmap->Canvas->Font->Color;

for (;;)
    {
// Start parsing the line
// Check if it contains a  tag
// Find the start of the tag
//SEARCH_AGAIN:
   if (asText.Length()==0)
       return;
   if ((iStartPos = FindFirstChar(&asText,'<', iLastPos,GROUP_LAST))==0)
      {FBitmap->Canvas->TextOut(tmpSize.cx,Y,asText);
       return;
      }
   else
   if ((iEndPos = FindFirstChar(&asText,'>', iLastPos,GROUP_FIRST))==0)
      {FBitmap->Canvas->TextOut(tmpSize.cx,Y,asText);
       return;
      }
   else
      {
       if (iEndPos < iStartPos)
          {
           iLastPos = iEndPos+1;
           continue;
          }
      }
   static AnsiString asTmp;
   asTmp = asText.SubString(iStartPos+1, iEndPos-iStartPos-1).UpperCase();
   // Save old font
   nStyle = FBitmap->Canvas->Font->Style;
   nColor = FBitmap->Canvas->Font->Color;
   //
   int isCode =false;

   if ( asTmp == "B")
      {isCode =true;
       nStyle = nStyle << fsBold;
      }
   else
   if ( asTmp == "I")
      {isCode =true;
       nStyle = nStyle << fsItalic;
      }
   else
   if ( asTmp == "U")
      {isCode =true;
       nStyle = nStyle << fsUnderline;
      }
   else
   if ( asTmp == "STRIKE")
      {isCode =true;
       nStyle = nStyle << fsStrikeOut;
      }
   else
   if ( asTmp == "A")
      {isCode =true;
       nStyle = nStyle << fsBold << fsUnderline;
       nColor = clBlue;// RGB(0,0,255);
      }
   if ( asTmp == "/B")
      {isCode =true;
       nStyle = nStyle >> fsBold;
      }
   else
   if ( asTmp == "/I")
      {isCode =true;
       nStyle = nStyle >> fsItalic;
      }
   else
   if ( asTmp == "/U")
      {isCode =true;
       nStyle = nStyle >> fsUnderline;
      }
   else
   if ( asTmp == "/STRIKE")
      {isCode =true;
       nStyle = nStyle >> fsStrikeOut;
      }
   else
   if ( asTmp == "/A")
      {isCode =true;
       nStyle = nStyle >> fsBold >> fsUnderline;
       nColor = oColor;
      }
   if (isCode==true)
      {
       FBitmap->Canvas->TextOut(tmpSize.cx,Y,asText.SubString(1,iStartPos-1));
       tmpSize.cx += FBitmap->Canvas->TextExtent(asText.SubString(1,iStartPos-1)).cx;
       // Skip the <..> part
       asText = asText.SubString(iEndPos+1,asText.Length()-iEndPos);
       iLastPos = 1;
       // Set new font
       FBitmap->Canvas->Font->Style = nStyle;
       FBitmap->Canvas->Font->Color = nColor;
      }
   else
      {// Unsupported tag
       FBitmap->Canvas->TextOut(tmpSize.cx,Y, asText.SubString(1,iEndPos));
       tmpSize.cx += FBitmap->Canvas->TextExtent(asText.SubString(1,iEndPos)).cx;
       asText = asText.SubString(iEndPos+1,asText.Length()-iEndPos);
       iLastPos = 1;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall THintBox::SetFormatting(bool Value)
{
if (Value == bFormatting)
    return;
bFormatting = Value;
Update();
}
//---------------------------------------------------------------------------

void __fastcall THintBox::Update()
{
if (bFormatting)
    Parse();
ForceRepaint();
}
//---------------------------------------------------------------------------

void __fastcall THintBox::SetHintBox(bool Value)
{
if (Value==bDrawBox)
    return;
bDrawBox = Value;
ForceRepaint();
}
//---------------------------------------------------------------------------

__fastcall THintBox::~THintBox()
{
if (FFont)
    delete FFont;
if (OFont)
    delete OFont;
if (FLines)
    delete FLines;
if (TextList)
    delete TextList;
if (AlignList)
    delete AlignList;
if (FBitmap)
    delete FBitmap;
}
//---------------------------------------------------------------------------

