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
#ifndef __SYSTRAY_h__
#define __SYSTRAY_h__
//---------------------------------------------------------------------------
#if __BORLANDC__ > 0x0551
#include <Classes.hpp>
#else
#include <Vcl/Classes.hpp>
#endif

#define ICON_ID 		WM_USER+1
#define TWMNOTIFYICON	WM_USER+2
//---------------------------------------------------------------------------
class PACKAGE TSysTray : public TComponent
{
private:
    HWND WndHandle;
    void *DefProc;
    void *WndProcInstance;

    void __fastcall SetIcon(TIcon *AIcon);
    Graphics::TIcon *FIcon;
    void __fastcall SetVisible(bool AVisible);
    bool FVisible;
    void __fastcall SetHint(String AHint);
    AnsiString FHint;
    void __fastcall SetPopupMenu(TPopupMenu *APopupMenu);
    TPopupMenu *FPopupMenu;

protected:
	//WndProc subclassed
MESSAGE void __fastcall SubWndProc(Messages::TMessage &Message);
public:
    __fastcall  TSysTray(TComponent* Owner);
    void __fastcall AddIcon();
    void __fastcall ChangeIcon();
    void __fastcall RemoveIcon();
    __fastcall ~TSysTray();

__published:
    __property bool Visible = {read=FVisible, write=SetVisible,default=false};
    __property TIcon *Icon = {read=FIcon, write=SetIcon,default=NULL};
    __property AnsiString Hint = {read=FHint, write=SetHint};
    __property TPopupMenu *PopupMenu = {read=FPopupMenu, write=SetPopupMenu,default=NULL};
};
//---------------------------------------------------------------------------
#endif
