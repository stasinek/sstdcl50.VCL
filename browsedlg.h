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
#ifndef BrowseDlgH
#define BrowseDlgH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <shlobj.h>
#include <shellapi.h>
//---------------------------------------------------------------------------
typedef enum BrowseFlag { bdBrowseForComputer,bdBrowseForPrinter,//bdStatusText
	                      bdDontGoBelowDomain,bdReturnFsAncestors,
                          bdReturnFsDirs }TBrowseFlag;
typedef Set<TBrowseFlag,bdBrowseForComputer,bdReturnFsDirs>TBrowseFlags;
typedef enum BrowseRoot { brRecycleBin, brControlPanel,brDesktop,brDesktopDir,brDrives,
	                      brFonts,brNetHood,brNetwork,brPersonal,brPrinters,
                          brPrograms,brRecent,brSendTo,brStartMenu,
                          brStartUp,brTemplates }TBrowseRoot;

class PACKAGE TBrowseDialog : public TComponent
{
private:
   TBrowseRoot FRoot;							//Root dir
   int FIconIndex;                              //Icon index in the system
   AnsiString FInitialPath;                      //initial dir to browse from
   void __fastcall SetInitialPath(String Str);
   AnsiString FTitle;                      		//Title of the dialog box
   void __fastcall SetTitle(String Str);
   AnsiString FPathName, FFolderName;           //Folder selected by user
   TBrowseFlags FOptions;                       //options

   static int __stdcall BrowseCallbackProc(HWND hwnd, UINT uMsg,LPARAM lParam,LPARAM lpData);
protected:
   BROWSEINFO FBrowseInfo;
public:
        __fastcall TBrowseDialog(TComponent* Owner);
   int  __fastcall Execute(void);
        __fastcall ~TBrowseDialog();
__published:
   __property AnsiString Title          = {read=FTitle,write=SetTitle};
   __property int IconIndex             = {read=FIconIndex};
   __property TBrowseRoot Root          = {read=FRoot,write=FRoot,default=brDesktop};
   __property TBrowseFlags Options      = {read=FOptions,write=FOptions};
   __property AnsiString InitialPath    = {read=FInitialPath,write=SetInitialPath};
   __property AnsiString PathName       = {read=FPathName,write=FPathName};
   __property AnsiString FolderName     = {read=FFolderName,write=FFolderName};
//   __property AnsiString StatusText   = {read=FStatusText,write=SetStatusText};
//   AnsiString FStatusText;						//Status text to display
//   void __fastcall SetStatusText(AnsiString Str);
};
//---------------------------------------------------------------------------
#endif
