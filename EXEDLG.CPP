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
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
#pragma hdrstop
#include "exedlg.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TExeDialog *)
{
    new TExeDialog(NULL);
}
//---------------------------------------------------------------------------
namespace Exedlg
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TExeDialog)};
        RegisterComponents("User", classes, 0);
    }
}
//---------------------------------------------------------------------------

__fastcall TExeDialog::TExeDialog(TComponent* Owner)
    : TComponent(Owner)
{
if (dynamic_cast<TWinControl*>(Owner)) FOwner = dynamic_cast<TWinControl*>(Owner)->Handle;
else
      FOwner = NULL;
FLibFileName = "";
 FDialogName = "";
  FLibLoaded = false;
      Fhinst = NULL;
     FHandle = NULL;
    FVisible = false;

ON_ENABLE = NULL;
ON_PAINT = NULL;
ON_CLOSE = NULL;
ON_HIDE = NULL;
ON_SHOW = NULL;
ON_CREATE = NULL;
ON_DESTROY = NULL;
ON_RESIZE = NULL;
ON_ACTIVATE = NULL;
ON_KEYDOWN = NULL;
ON_KEYUP = NULL;
ON_COMMAND = NULL;
ON_DBLCLICK = NULL;
}
//---------------------------------------------------------------------------

void   __fastcall TExeDialog::SetLibLoaded(bool ALibLoaded)
{
if (FLibLoaded==ALibLoaded)
	return;
if (Fhinst!=NULL)
   {FreeLibrary(Fhinst);
    Fhinst =NULL;}
if (FLibFileName=="")
   {FLibLoaded = ALibLoaded;
    return;}
if (ALibLoaded==true)
   {
    Fhinst = LoadLibraryEx(FLibFileName.c_str(),NULL,
			 LOAD_WITH_ALTERED_SEARCH_PATH|LOAD_LIBRARY_AS_DATAFILE);
   }
FLibLoaded = ALibLoaded;
}
//---------------------------------------------------------------------------

void __fastcall TExeDialog::SetLibFileName(AnsiString ALibFileName)
{
if (ALibFileName==FLibFileName)
	return;
if (Fhinst!=NULL)
   {FreeLibrary(Fhinst);
    Fhinst =NULL;}
if (ALibFileName=="")
   {FLibFileName = ALibFileName;
    return;}
if (FLibLoaded==true)
   {
	Fhinst = LoadLibraryExA(ALibFileName.c_str(),NULL,
      		 			  LOAD_WITH_ALTERED_SEARCH_PATH|
						  LOAD_LIBRARY_AS_DATAFILE);
   }
FLibFileName = ALibFileName;
}
//---------------------------------------------------------------------------

void __fastcall TExeDialog::SetDialogName(AnsiString ADialogName)
{
if (ADialogName==FDialogName)
	return;
if (FLibLoaded==false)
   {
	Fhinst = LoadLibraryExA(FLibFileName.c_str(),NULL,
						   LOAD_WITH_ALTERED_SEARCH_PATH|
						   LOAD_LIBRARY_AS_DATAFILE);
   }
if (FHandle!=NULL)
   {DestroyWindow(FHandle);
    FHandle = NULL;}
FHandle = CreateDialogParam(Fhinst,ADialogName.c_str(),FOwner,(DLGPROC)&DoDialogProc,(LPARAM)this);
if (FHandle!=NULL)
   {
    if (FVisible==true)
    	DoDialogProc(FHandle,SW_SHOW,NULL,NULL);
   }
if (FLibLoaded==false)
   {
   	if (Fhinst!=NULL)
       {FreeLibrary(Fhinst);
        Fhinst =NULL;}
   }
FDialogName = ADialogName;
}
//---------------------------------------------------------------------------

void __fastcall TExeDialog::SetVisible(bool AVisible)
{
if (FHandle!=NULL)
   {
    if (AVisible==true)
        if (IsWindowVisible(FHandle)==false)
		 	DoDialogProc(FHandle,SW_SHOW,NULL,NULL);
    else
        if (IsWindowVisible(FHandle)==true)
       	 	DoDialogProc(FHandle,SW_HIDE,NULL,NULL);
   }
FVisible = AVisible;
}
//---------------------------------------------------------------------------

bool __fastcall TExeDialog::GetVisible()
{
return FVisible;
}
//---------------------------------------------------------------------------

__fastcall TExeDialog::~TExeDialog()
{
DialogName = ""; LibFileName = "";
}
//---------------------------------------------------------------------------

BOOL CALLBACK TExeDialog::DoDialogProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam) {
static TExeDialog *thisDialog;

switch (uMsg)
  {
	case WM_INITDIALOG:
         thisDialog = (TExeDialog*)lParam;
         if (thisDialog->ON_CREATE!=NULL)
         	 thisDialog->ON_CREATE(WM_NCCREATE,wParam,lParam);
    break;
	case WM_ENABLE:
         if (thisDialog->ON_ENABLE!=NULL)
         	 thisDialog->ON_ENABLE(uMsg,wParam,lParam);
    break;
    case WM_PAINT:
         if (thisDialog->ON_PAINT!=NULL)
         	 thisDialog->ON_PAINT(uMsg,wParam,lParam);
         return false;
    break;
    case SW_SHOW:
         if (thisDialog->ON_SHOW!=NULL)
         	 thisDialog->ON_SHOW(uMsg,wParam,lParam);
         if (IsWindowVisible(hwndDlg)==false)
         	 ShowWindow(hwndDlg,SW_SHOW);
         return false;
    break;
    case SW_HIDE:
         if (thisDialog->ON_HIDE!=NULL)
         	 thisDialog->ON_HIDE(uMsg,wParam,lParam);
         if (IsWindowVisible(hwndDlg)==true)
         	 ShowWindow(hwndDlg,SW_HIDE);
         return false;
    break;
    case WM_CLOSE:
         if (thisDialog->ON_CLOSE!=NULL)
         	 thisDialog->ON_CLOSE(uMsg,wParam,lParam);
         ShowWindow(hwndDlg,SW_HIDE);
         return false;
    break;
    case WM_DESTROY:
         if (thisDialog->ON_DESTROY!=NULL)
         	 thisDialog->ON_DESTROY(uMsg,wParam,lParam);
    break;
/*    case WM_SIZE:
         if (thisDialog->ON_RESIZE)
         	 thisDialog->ON_RESIZE(uMsg,wParam,lParam);
    break;  */
    case WM_SETFOCUS:
         if (thisDialog->ON_ACTIVATE!=NULL)
         	 thisDialog->ON_ACTIVATE(uMsg,wParam,lParam);
    break;
    case WM_KILLFOCUS:
         if (thisDialog->ON_DEACTIVATE!=NULL)
         	 thisDialog->ON_DEACTIVATE(uMsg,wParam,lParam);
    break;
    case WM_KEYUP:
         if (thisDialog->ON_KEYUP!=NULL)
         	 thisDialog->ON_KEYUP(uMsg,wParam,lParam);
    break;
    case WM_KEYDOWN:
         if (thisDialog->ON_KEYDOWN!=NULL)
         	 thisDialog->ON_KEYDOWN(uMsg,wParam,lParam);
    break;
    case WM_CHAR:
         if (thisDialog->ON_KEYPRESS!=NULL)
         	 thisDialog->ON_KEYPRESS(uMsg,wParam,lParam);
    break;
    case WM_COMMAND:
         if (thisDialog->ON_COMMAND!=NULL)
         	 thisDialog->ON_COMMAND(uMsg,wParam,lParam);
    break;
    case WM_LBUTTONDBLCLK:
         if (thisDialog->ON_DBLCLICK!=NULL)
         	 thisDialog->ON_DBLCLICK(uMsg,wParam,lParam);
    break;
    case WM_MOUSEMOVE:
         if (thisDialog->ON_MOUSEMOVE!=NULL)
         	 thisDialog->ON_MOUSEMOVE(uMsg,wParam,lParam);
    break;
    default:
         if (thisDialog!=NULL)
         	 if (thisDialog->ON_DEFAULT!=NULL)
         	 	 thisDialog->ON_DEFAULT(uMsg,wParam,lParam);
		 return false;
    break;
  }
return FALSE;
}
//---------------------------------------------------------------------------

