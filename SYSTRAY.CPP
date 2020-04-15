/*---------------------------------------------------------------------------
Program :	SysTray.h	Version 1.0
		TSysTray Component for BCB1
Author :	Michel Leunen
Email :		leu@rtbf.be
		Michel.Leunen@village.uunet.be
Date :		21/07/1998
Description :	Component for Borland C++ Builder V1 that places an icon in
		the Systray (near the clock).
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <shellapi.h>
#include "systray.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TSysTray *)
{
	new TSysTray(NULL);
}
//---------------------------------------------------------------------------
namespace Systray
{
    void __fastcall PACKAGE Register()
    {
	    TComponentClass classes[1] = {__classid(TSysTray)};
        RegisterComponents("User", classes, 0);
    }
}
//---------------------------------------------------------------------------
__fastcall TSysTray::TSysTray(TComponent* Owner)
	: TComponent(Owner)
{
FHint = "Some Hint";
FIcon = new Graphics::TIcon;
FVisible = false;

if (dynamic_cast<TWinControl *>(Owner))
   {
    TWinControl *WinCtl = dynamic_cast<TWinControl *>(Owner);
    WndHandle = WinCtl->Handle;
    DefProc = reinterpret_cast<void*>(GetWindowLong(WndHandle,GWL_WNDPROC));
    WndProcInstance = MakeObjectInstance(SubWndProc);
    SetWindowLong(WndHandle,GWL_WNDPROC,reinterpret_cast<long>(WndProcInstance));
   }
}
//---------------------------------------------------------------------------
__fastcall TSysTray::~TSysTray()
{
if (WndHandle!=NULL)
   {
    SetWindowLong(WndHandle,GWL_WNDPROC,reinterpret_cast<long>(DefProc));
    FreeObjectInstance(WndProcInstance);
   }
delete FIcon;
}
//---------------------------------------------------------------------------

void __fastcall TSysTray::SetVisible(bool AVisible)
{
if (FVisible==AVisible)
    return;
if (AVisible==true) AddIcon();
else
    RemoveIcon();
}
//---------------------------------------------------------------------------

void __fastcall TSysTray::SetIcon(TIcon *AIcon)
{
FIcon->Assign(AIcon);
}
//---------------------------------------------------------------------------
void __fastcall TSysTray::SetPopupMenu(TPopupMenu *APopupMenu)
{
FPopupMenu = APopupMenu;
}
//---------------------------------------------------------------------------
void __fastcall TSysTray::SetHint(String AHint)
{
FHint = AHint;
}
//---------------------------------------------------------------------------
void __fastcall TSysTray::AddIcon() 			// Add Icon to the tray
{
NOTIFYICONDATA TNID;
TNID.cbSize = sizeof(NOTIFYICONDATA);
  TNID.hWnd = WndHandle;
   TNID.uID = ICON_ID;
TNID.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
 TNID.hIcon = FIcon->Handle;
TNID.uCallbackMessage = TWMNOTIFYICON;
strcpy(TNID.szTip,FHint.c_str());
Shell_NotifyIcon(NIM_ADD,&TNID);
FVisible = true;
}
//---------------------------------------------------------------------------
void __fastcall TSysTray::RemoveIcon()        	// Remove Icon from the tray
{
NOTIFYICONDATA TNID;
TNID.cbSize = sizeof(NOTIFYICONDATA);
  TNID.hWnd = WndHandle;
   TNID.uID = ICON_ID;
Shell_NotifyIcon(NIM_DELETE,&TNID);
FVisible = false;
}
//---------------------------------------------------------------------------
void __fastcall TSysTray::ChangeIcon()			// Change Icon or Hint
{
NOTIFYICONDATA TNID;
TNID.cbSize = sizeof(NOTIFYICONDATA);
  TNID.hWnd = WndHandle;
   TNID.uID = ICON_ID;
TNID.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
 TNID.hIcon = FIcon->Handle;
TNID.uCallbackMessage = TWMNOTIFYICON;
strcpy(TNID.szTip,FHint.c_str());
Shell_NotifyIcon(NIM_MODIFY,&TNID);
FVisible = true;
}
//---------------------------------------------------------------------------
void __fastcall TSysTray::SubWndProc(Messages::TMessage &Message)
{
if (Message.Msg==TWMNOTIFYICON)
   {
    UINT MouseMessage;
    MouseMessage = (UINT)Message.LParam;
    UINT MessageID;
    MessageID = Message.WParam;

    if (MessageID==ICON_ID)
       {
   	    if (MouseMessage==WM_RBUTTONDOWN)
           {
            POINT pt;
            GetCursorPos(&pt);
            SetForegroundWindow(WndHandle);
            FPopupMenu->Popup(pt.x,pt.y);
	        PostMessage(WndHandle,WM_NULL,0,0);
           }
    	else
        if (MouseMessage==WM_LBUTTONDBLCLK)
           {
            //execute method onClick of the first element in Popupmenu
            FPopupMenu->DispatchPopup(FPopupMenu->Items->Items[0]->Handle);
           }
       }
   }
//send other messages to old WndProc
#if __BORLANDC__ <= 0x551
Message.Result = CallWindowProcA(reinterpret_cast<FARPROC>(DefProc),
		   WndHandle,Message.Msg,Message.WParam,
				   Message.LParam);
#else
Message.Result = CallWindowProcA(reinterpret_cast<WNDPROC>(DefProc),
		   WndHandle,Message.Msg,Message.WParam,
				   Message.LParam);
#endif
}
//---------------------------------------------------------------------------
