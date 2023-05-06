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
#ifndef __exedlg_HDR__
#define __exedlg_HDR__
//---------------------------------------------------------------------------
#if __BORLANDC__ < 0x550
#include <Controls.hpp>
#endif
//---------------------------------------------------------------------------
class PACKAGE TExeDialog : public TComponent
{
//---------------------------------------------------------------------------
private:
//---------------------------------------------------------------------------
	void  __fastcall SetLibFileName		(AnsiString ALibFileName);
	AnsiString FLibFileName;
	void  __fastcall SetDialogName		(AnsiString ADialogName);
	AnsiString FDialogName;
	void  __fastcall SetLibLoaded		(bool ALibLoaded);
		bool FLibLoaded;
	void  __fastcall SetVisible			(bool AVisible);
	bool  __fastcall GetVisible			(void);
		bool FVisible;
//---------------------------------------------------------------------------
protected:
//---------------------------------------------------------------------------
typedef int __fastcall(__closure *MsgEvent)(UINT uMsg,WPARAM wParam,LPARAM lParam);
static BOOL	CALLBACK DoDialogProc		  (HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
//---------------------------------------------------------------------------
       HWND FOwner;
       HWND FHandle;
       HINSTANCE Fhinst;
//---------------------------------------------------------------------------
public:
//---------------------------------------------------------------------------
    __fastcall TExeDialog(TComponent* Owner);
  	__property HWND Owner				   = {read=FOwner};
  	__property HWND Handle				   = {read=FHandle};
    __fastcall ~TExeDialog(void);
//---------------------------------------------------------------------------
	MsgEvent FON_ENABLE;
    MsgEvent FON_CREATE;
    MsgEvent FON_PAINT;
    MsgEvent FON_SHOW;
    MsgEvent FON_HIDE;
    MsgEvent FON_CLOSE;
    MsgEvent FON_DESTROY;
    MsgEvent FON_RESIZE;
    MsgEvent FON_ACTIVATE;
    MsgEvent FON_DEACTIVATE;
    MsgEvent FON_KEYDOWN;
    MsgEvent FON_KEYUP;
	MsgEvent FON_KEYPRESS;
    MsgEvent FON_COMMAND;
    MsgEvent FON_DBLCLICK;
    MsgEvent FON_DEFAULT;
    MsgEvent FON_MOUSEMOVE;
//---------------------------------------------------------------------------
__published:
//---------------------------------------------------------------------------
	__property AnsiString LibFileName 	   = {read=FLibFileName,write=SetLibFileName};
	__property AnsiString DialogName  	   = {read=FDialogName,write=SetDialogName};
	__property bool LibLoaded     		   = {read=FLibLoaded,write=SetLibLoaded};
	__property bool Visible	  		   	   = {read=GetVisible,write=SetVisible};

	__property MsgEvent ON_COMMAND		   = {read=FON_COMMAND,write=FON_COMMAND};
	__property MsgEvent ON_CREATE		   = {read=FON_CREATE,write=FON_CREATE};
	__property MsgEvent ON_ENABLE          = {read=FON_ENABLE,write=FON_ENABLE};
	__property MsgEvent ON_ACTIVATE		   = {read=FON_ACTIVATE,write=FON_ACTIVATE};
	__property MsgEvent ON_DEACTIVATE	   = {read=FON_DEACTIVATE,write=FON_DEACTIVATE};
	__property MsgEvent ON_PAINT           = {read=FON_PAINT,write=FON_PAINT};
	__property MsgEvent ON_SHOW			   = {read=FON_SHOW,write=FON_SHOW};
	__property MsgEvent ON_HIDE            = {read=FON_HIDE,write=FON_HIDE};
	__property MsgEvent ON_RESIZE		   = {read=FON_RESIZE,write=FON_RESIZE};
	__property MsgEvent ON_KEYUP		   = {read=FON_KEYUP,write=FON_KEYUP};
	__property MsgEvent ON_KEYDOWN		   = {read=FON_KEYDOWN,write=FON_KEYDOWN};
	__property MsgEvent ON_KEYPRESS		   = {read=FON_KEYPRESS,write=FON_KEYPRESS};
	__property MsgEvent ON_CLOSE           = {read=FON_CLOSE,write=FON_CLOSE};
	__property MsgEvent ON_DESTROY		   = {read=FON_DESTROY,write=FON_DESTROY};
	__property MsgEvent ON_DBLCLICK  	   = {read=FON_DBLCLICK,write=FON_DBLCLICK};
	__property MsgEvent ON_MOUSEMOVE  	   = {read=FON_MOUSEMOVE,write=FON_MOUSEMOVE};
	__property MsgEvent ON_DEFAULT		   = {read=FON_DEFAULT,write=FON_DEFAULT};
 };
//---------------------------------------------------------------------------
#endif
