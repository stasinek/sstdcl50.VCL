//---------------------------------------------------------------------------
#ifndef exeresH
#define exeresH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Windows.hpp>
#include "handlelist.h"
//---------------------------------------------------------------------------
class PACKAGE TExeResource : public TComponent
{
private:
    enum TKind { rkBITMAP,rkCURSOR,rkICON,rkSTRING };

  HANDLE __fastcall GetHandle(char *ARes);
    void __fastcall ClearHandleList(void);
    class THandleList FHandleList;
	void __fastcall SetLibFileName(AnsiString ALibFileName);
	AnsiString FLibFileName;
	HINSTANCE Fhinst;
	void __fastcall SetKind(TKind AKind);
	TKind FKind;
	void __fastcall SetLibLoaded(bool ALibLoaded);
	bool FLibLoaded;
	int  FSizeX, FSizeY;
	RECT FSize;
protected:
public:
	__fastcall  TExeResource(TComponent* Owner);
	__property HANDLE Handle[char *ARes] = {read=GetHandle};
	__fastcall ~TExeResource(void);
__published:
	__property TKind Kind = {read=FKind,write=SetKind,default=rkBITMAP};
	__property AnsiString LibFileName = {read=FLibFileName,write=SetLibFileName};
	__property bool LibLoaded = {read=FLibLoaded,write=SetLibLoaded,default=false};
	__property int SizeX = {read=FSizeX,write=FSizeX,default=16};
	__property int SizeY = {read=FSizeY,write=FSizeY,default=16};
};
//---------------------------------------------------------------------------
#endif
