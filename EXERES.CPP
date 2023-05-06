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
#include <Windows.hpp>
#pragma hdrstop
#include "exeres.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TExeResource *)
{
        new TExeResource(NULL);
}
//---------------------------------------------------------------------------
namespace Exeres
{
        void __fastcall PACKAGE Register()
        {
        TComponentClass classes[1] = {__classid(TExeResource)};
        RegisterComponents("User", classes, 0);
        }
}
//---------------------------------------------------------------------------

__fastcall TExeResource::TExeResource(TComponent* Owner)
    : TComponent(Owner)
{
       FKind = rkBITMAP;
FLibFileName = "";
      Fhinst = NULL;
  FLibLoaded = false;
      FSizeX = 16;
      FSizeY = 16;
}
//---------------------------------------------------------------------------

void   __fastcall TExeResource::SetLibLoaded(bool ALibLoaded)
{
if (ALibLoaded==FLibLoaded)
    return;
if (Fhinst!=NULL)
   {FreeLibrary(Fhinst);
    Fhinst = NULL;
   }
if (FLibFileName=="")
   {FLibLoaded = ALibLoaded;
    return;
   }
if (ALibLoaded==true)
   {Fhinst = LoadLibraryEx(FLibFileName.c_str(),NULL,
			 LOAD_WITH_ALTERED_SEARCH_PATH|LOAD_LIBRARY_AS_DATAFILE);
   }
}
//---------------------------------------------------------------------------

void __fastcall TExeResource::SetLibFileName(AnsiString ALibFileName)
{
if (ALibFileName==FLibFileName)
    return;

ClearHandleList();

if (Fhinst!=NULL)
   {FreeLibrary(Fhinst);
    Fhinst = NULL;
   }
if (ALibFileName=="")
   {FLibFileName = ALibFileName;
    return;
   }
if (FLibLoaded==true)
   {Fhinst = LoadLibraryEx(ALibFileName.c_str(),NULL,
      		 LOAD_WITH_ALTERED_SEARCH_PATH|LOAD_LIBRARY_AS_DATAFILE);
   }
FLibFileName = ALibFileName;
}
//---------------------------------------------------------------------------

void __fastcall TExeResource::ClearHandleList(void)
{
for (int i = 0; i < FHandleList.Count; i++)
    {
     if (FHandleList.Handle[i]==NULL) continue;
     else
     if (Kind==rkSTRING) LocalFree(FHandleList.Handle[i]);
     else
     DeleteObject(FHandleList.Handle[i]);
    }
FHandleList.Count = 0;
}
//---------------------------------------------------------------------------

HANDLE __fastcall TExeResource::GetHandle(char *ARes) {
bool exists = false;
int   index = 0;
for (;index < FHandleList.Count; index++)
    {
     if (strcmp(FHandleList.Caption[index],ARes)==0)
        {exists = true;
         break;
        }
    }
if (exists==true)
    return FHandleList.Handle[index];

if (FLibLoaded==false)
   {Fhinst = LoadLibraryEx(FLibFileName.c_str(),NULL,
     		  LOAD_WITH_ALTERED_SEARCH_PATH|LOAD_LIBRARY_AS_DATAFILE);
   }
FHandleList.Count = index + 1;
switch (FKind)
   {
    case rkBITMAP:
      	 FHandleList.Handle[index] = LoadImage(Fhinst,ARes,IMAGE_BITMAP,
          			         FSizeX,FSizeY,LR_SHARED);
    break;
    case rkCURSOR:
	 FHandleList.Handle[index] = LoadImage(Fhinst,ARes,IMAGE_CURSOR,
         			         FSizeX,FSizeY,LR_SHARED);
    break;
    case rkICON:
	 FHandleList.Handle[index] = LoadImage(Fhinst,ARes,IMAGE_ICON,
           			         FSizeX,FSizeY,LR_SHARED);
    break;
    case rkSTRING:
	 FHandleList.Handle[index] = LocalAlloc(LPTR,8192);
         LoadString(Fhinst,atoi(ARes),(char*)FHandleList.Handle[index],8192);
         FHandleList.Handle[index] = LocalReAlloc(FHandleList.Handle[index],
                                                  strlen((char*)FHandleList.Handle[index]),LMEM_MOVEABLE);
    break;
   }
if (FLibLoaded==false)
   {if (Fhinst!=NULL)
       {FreeLibrary(Fhinst);
        Fhinst = NULL;
       }
   }
if (FHandleList.Handle[index]==NULL)
   {FHandleList.Count = 0;
    return NULL;
   }
       FHandleList.Caption[index] = ARes;
return FHandleList.Handle[index];
}
//---------------------------------------------------------------------------

void __fastcall TExeResource::SetKind(TKind AKind)
{
if (FKind==AKind)
    return;
        ClearHandleList();
FKind = AKind;
}
//---------------------------------------------------------------------------

__fastcall TExeResource::~TExeResource()
{
LibFileName = "";
}
//---------------------------------------------------------------------------
