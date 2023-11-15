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
#include <vcl.h>
#if __BORLANDC__ > 0x551
#include <System.SysUtils.hpp>
#include <Classes.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#else
#include <VCL/SysUtils.hpp>
#include <VCL/Classes.hpp>
#include <VCL/Dialogs.hpp>
#include <VCL/Classes.hpp>
#include <VCL/Forms.hpp>
#include <VCL/Dialogs.hpp>
#endif
#include <shlobj.h>
#include <shellapi.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "BROWSEDLG.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TBrowseDialog *)
{
	new TBrowseDialog(NULL);
}
//---------------------------------------------------------------------------

namespace Browsedlg
{
	void __fastcall PACKAGE Register()
	{
   	TComponentClass classes[1] = {__classid(TBrowseDialog)};
		RegisterComponents("User", classes, 0);
	}
}
//---------------------------------------------------------------------------

__fastcall TBrowseDialog::TBrowseDialog(TComponent* Owner)
	: TComponent(Owner)
{
       FRoot = brDesktop;
FInitialPath = "";
      FTitle = "Select a directory...";
FOptions.Clear();
}
//---------------------------------------------------------------------------

int __fastcall TBrowseDialog::Execute()
{
LPMALLOC pMalloc;
if (NOERROR!=SHGetMalloc(&pMalloc))
   {return 0;
   }
int Root_CSIDL;
switch((int)FRoot)
  {
   case brDesktop:	Root_CSIDL=CSIDL_DESKTOP;
   break;
   case brDesktopDir:  	Root_CSIDL=CSIDL_DESKTOPDIRECTORY;
   break;
   case brDrives:	Root_CSIDL=CSIDL_DRIVES;
   break;
   case brRecycleBin:  	Root_CSIDL=CSIDL_BITBUCKET;
   break;
   case brControlPanel:	Root_CSIDL=CSIDL_CONTROLS;
   break;
   case brFonts:	Root_CSIDL=CSIDL_FONTS;
   break;
   case brNetHood:	Root_CSIDL=CSIDL_NETHOOD;
   break;
   case brNetwork:	Root_CSIDL=CSIDL_NETWORK;
   break;
   case brPersonal:	Root_CSIDL=CSIDL_PERSONAL;
   break;
   case brPrinters:	Root_CSIDL=CSIDL_PRINTERS;
   break;
   case brPrograms:	Root_CSIDL=CSIDL_PROGRAMS;
   break;
   case brRecent:	Root_CSIDL=CSIDL_RECENT;
   break;
   case brSendTo:	Root_CSIDL=CSIDL_SENDTO;
   break;
   case brStartMenu:   	Root_CSIDL=CSIDL_STARTMENU;
   break;
   case brStartUp:	Root_CSIDL=CSIDL_STARTUP;
   break;
   case brTemplates:   	Root_CSIDL=CSIDL_TEMPLATES;
   break;
  }
LPITEMIDLIST pidlRootFolder;
LPSTR pszTempName = (char*)malloc(MAX_PATH);
if (NOERROR!=SHGetSpecialFolderLocation(GetActiveWindow(), Root_CSIDL,&pidlRootFolder))
   {pMalloc->Free(pidlRootFolder);
    pMalloc->Release();
    return 0;
   }
memset(&FBrowseInfo,0x00,sizeof(FBrowseInfo));
FBrowseInfo.hwndOwner = GetActiveWindow();
FBrowseInfo.pidlRoot = pidlRootFolder;
FBrowseInfo.pszDisplayName = pszTempName;

if (FTitle!="")
    FBrowseInfo.lpszTitle = FTitle.c_str();
if (FOptions.Contains(bdBrowseForComputer))
    FBrowseInfo.ulFlags=FBrowseInfo.ulFlags|BIF_BROWSEFORCOMPUTER;
if (FOptions.Contains(bdBrowseForPrinter))
    FBrowseInfo.ulFlags=FBrowseInfo.ulFlags|BIF_BROWSEFORPRINTER;
if (FOptions.Contains(bdDontGoBelowDomain))
    FBrowseInfo.ulFlags=FBrowseInfo.ulFlags|BIF_DONTGOBELOWDOMAIN;
if (FOptions.Contains(bdReturnFsAncestors))
    FBrowseInfo.ulFlags=FBrowseInfo.ulFlags|BIF_RETURNFSANCESTORS;
if (FOptions.Contains(bdReturnFsDirs))
    FBrowseInfo.ulFlags=FBrowseInfo.ulFlags|BIF_RETURNONLYFSDIRS;
FBrowseInfo.lpfn = BrowseCallbackProc;
FBrowseInfo.lParam = (long)this;
LPITEMIDLIST pidlBrowseReturn = SHBrowseForFolder(&FBrowseInfo);
if (pidlBrowseReturn==NULL)
   {pMalloc->Free(pidlRootFolder);
    pMalloc->Release();
    delete pszTempName;
    return 0;
   }
FIconIndex  = FBrowseInfo.iImage;
FFolderName = pszTempName;
if (SHGetPathFromIDList(pidlBrowseReturn,pszTempName))
   {FPathName = pszTempName;
   }
pMalloc->Free(pidlBrowseReturn);
pMalloc->Free(pidlRootFolder);
pMalloc->Release();
delete pszTempName;
return 1;
}
//---------------------------------------------------------------------------
void __fastcall TBrowseDialog::SetTitle(String ATitleStr)
{
FTitle = ATitleStr;
}
//---------------------------------------------------------------------------
void __fastcall TBrowseDialog::SetInitialPath(String AInitialPathStr)
{
FInitialPath = AInitialPathStr;
}
//---------------------------------------------------------------------------
int __stdcall TBrowseDialog::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam,LPARAM lpData)
{
if (uMsg==BFFM_INITIALIZED)
   {
    //Set the status text when the dialog box is displayed
/*   	SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,
       			(LPARAM)reinterpret_cast<TBrowseDialog *>
				(lpData)->FStatusText.c_str());
*/    //Set the initial dir if it exists
    SendMessage(hwnd,BFFM_SETSELECTION,TRUE,
     			(LPARAM)reinterpret_cast<TBrowseDialog *>
   				(lpData)->FInitialPath.c_str());
   }
return 0;
}
//---------------------------------------------------------------------------

__fastcall TBrowseDialog::~TBrowseDialog(void)
{
}
//---------------------------------------------------------------------------


