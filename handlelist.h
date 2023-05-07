//---------------------------------------------------------------------------
#ifndef __handlelist_HDR__
#define __handlelist_HDR__
//---------------------------------------------------------------------------
#include <winbase.h>
//#include <windows.h>
//---------------------------------------------------------------------------

class THandleList
{
private:
    void   __fastcall SetCount		(int ACount);
    int    __fastcall GetCount		(void);
    int FCount;
    HANDLE __fastcall GetHandle		(int index);
    void   __fastcall SetHandle		(int index, HANDLE AHandle);
    size_t FHandle;
    char  *__fastcall GetCaption	(int index);
    void   __fastcall SetCaption	(int index, char *ACaption);
    size_t FCaption;
protected:
public:
  __fastcall  THandleList(void);

  __property int Count 		      = {read=GetCount, write=SetCount};
  __property HANDLE Handle[int index] = {read=GetHandle, write=SetHandle};
  __property char *Caption[int index] = {read=GetCaption, write=SetCaption};

  __fastcall ~THandleList(void);
};
//---------------------------------------------------------------------------

__fastcall THandleList::THandleList()
{
FHandle = (DWORD)LocalAlloc(LPTR,1); FCaption = (DWORD)LocalAlloc(LPTR,1); FCount = 0;
}
//---------------------------------------------------------------------------

HANDLE __fastcall THandleList::GetHandle(int index)
{
return ((void**)FHandle)[index];
}
//---------------------------------------------------------------------------

void   __fastcall THandleList::SetHandle(int index, HANDLE AHandle)
{
((void**)FHandle)[index] = AHandle;
}
//---------------------------------------------------------------------------

int    __fastcall THandleList::GetCount(void)
{
return FCount;
}
//---------------------------------------------------------------------------

void   __fastcall THandleList::SetCount(int ACount)
{
if (ACount==FCount)
    return;
if (FCaption==NULL)
	FCaption=(size_t)LocalAlloc(LPTR,ACount*sizeof(char*));
if (FHandle== NULL)
	FHandle=(size_t)LocalAlloc(LPTR,ACount*sizeof(HANDLE));
if (ACount >FCount)
   {
	FHandle  = (size_t)LocalReAlloc((void*)FHandle, ACount*sizeof(HANDLE),LMEM_MOVEABLE);
    FCaption = (size_t)LocalReAlloc((void*)FCaption, ACount*sizeof(char*),LMEM_MOVEABLE);
    for (int i = FCount; i < ACount; i++)
    	{
		 ((char**)FCaption)[i] = (char*)LocalAlloc(LPTR,1);
		}
	FCount   = ACount;
   }
else // if (ACount <FCount)
   {
	for (int i = ACount; i < FCount; i++)
		{
     	 LocalFree(((char**)FCaption)[i]);
    	}
    FCaption = (DWORD)LocalReAlloc((void*)FCaption, ACount*sizeof(char*),LMEM_MOVEABLE);
    FHandle  = (DWORD)LocalReAlloc((void*)FHandle, ACount*sizeof(HANDLE),LMEM_MOVEABLE);
    FCount   = ACount;
   }
if (ACount==0)
   {
    LocalFree((void*)FCaption);
    FCaption = NULL;
    LocalFree((void*)FHandle);
    FHandle  = NULL;
   }
}
//---------------------------------------------------------------------------

char  *__fastcall THandleList::GetCaption(int index)
{
return ((char**)FCaption)[index];
}
//---------------------------------------------------------------------------

void   __fastcall THandleList::SetCaption(int index, char *ACaption)
{
((char**)FCaption)[index] = (char*)LocalReAlloc(((char**)FCaption)[index], strlen(ACaption)+1, LMEM_MOVEABLE);
((char**)FCaption)[index][0] = '\0';
strcat(((char**)FCaption)[index],ACaption);
}
//---------------------------------------------------------------------------

__fastcall THandleList::~THandleList()
{
Count = 0;
}

#endif