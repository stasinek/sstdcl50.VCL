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
/*
SHOWING:
     CompanyName
     FileDescription
     FileVersion
     InternalName
     LegalCopyright
     LegalTrademarks
     OriginalFilename
     ProductName
     ProductVersion
     Comments
     MajorVersion
     MinorVersion
     Release
     Build

*/
#include <vcl.h>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#pragma hdrstop
#include "exeinfo.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TExeInformation *)
{
    new TExeInformation(NULL);
}
//---------------------------------------------------------------------------
namespace Exeinfo
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TExeInformation)};
		RegisterComponents("User", classes, 0);
	}
}
//---------------------------------------------------------------------------
__fastcall TExeInformation::TExeInformation(TComponent* Owner)
	: TComponent(Owner)
{

}
//---------------------------------------------------------------------------
void   __fastcall TExeInformation::SetSorry(AnsiString ASorry)
{
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetFileVersion(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"FileVersion",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetMajorVersion(){
char cstr[MAX_PATH], helper[MAX_PATH];
char* p;
	strcpy(cstr, GetFileVersion().c_str());
p = strtok(cstr, ".");
if (p!=NULL) return AnsiString(p);
else
return "";
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetMinorVersion(){
char cstr[MAX_PATH], helper[MAX_PATH];
char* p;
	strcpy(cstr, GetFileVersion().c_str());
	strtok(cstr, ".");
p = strtok(NULL, ".");
if (p!=NULL) return AnsiString(p);
else
return "";
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetRelease(){
char cstr[MAX_PATH], helper[MAX_PATH];
char* p;
	strcpy(cstr, GetFileVersion().c_str());
	strtok(cstr, ".");
	strtok(NULL,".");
p = strtok(NULL,".");
if (p!=NULL) return AnsiString(p);
else
return "";
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetBuild(){
char cstr[MAX_PATH], helper[MAX_PATH];
char* p;
	strcpy(cstr, GetFileVersion().c_str());
	strtok(cstr, ".");
	strtok(NULL, ".");
	strtok(NULL, ".");
p = strtok(NULL, ".");
if (p!=NULL) return AnsiString(p);
else
return "";
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetCompanyName(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"CompanyName",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetFileDescription(){
#if __BORLANDC__ <= 0x551
char *src= Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"FileDescription",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetInternalName(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"InternalName",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetLegalCopyright(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"LegalCopyright",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetLegalTrademarks(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"LegalTrademarks",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetOriginalFilename(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"OriginalFilename",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetProductName(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"ProductName",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetProductVersion(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"ProductVersion",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TExeInformation::GetComments(){
#if __BORLANDC__ <= 0x551
char *src = Application->ExeName.c_str();
int len = strlen(src)+1;
char  helper[MAX_PATH];
memmove(helper,src,len);
#else
char  helper[MAX_PATH];
wcstombs(helper, Application->ExeName.c_str(),Application->ExeName.Length());
#endif
char cstr[MAX_PATH];
GetFileVersionField(helper,"Comments",cstr,MAX_PATH,NULL);
return AnsiString(cstr);
}
//---------------------------------------------------------------------------
//Function to get information from the file.

int __fastcall TExeInformation::GetFileVersionField(char *afilename, char *ainfo, char *aret, int aretmax, DWORD *adwver)
{
DWORD hVersion;
DWORD vis = GetFileVersionInfoSize(afilename,&hVersion);
if (vis==0)
   {return 0;
   }
void *vData = (void *)LocalAlloc(LPTR,vis+1);
if (!GetFileVersionInfo(afilename,hVersion,vis,vData))
   {LocalFree(vData);
	return 0;
   }
 unsigned int vsize;
 char *ver;
 char *transblock;
 char *vername = (char*)LocalAlloc(LPTR,256);
strcpy(vername,"\\VarFileInfo\\Translation");
if (!VerQueryValue(vData,vername,(void**)&transblock,&vsize))
   {LocalFree(vername);
	LocalFree(vData);
	return 0;
   }
// Swap the words so wsprintf will print the lang-charset in the correct format.
*(DWORD *)transblock = MAKELONG(HIWORD(*(DWORD *)transblock), LOWORD(*(DWORD *)transblock));
wsprintf(vername,"\\StringFileInfo\\%08lx\\%s",*(DWORD *)transblock,ainfo);
if (!VerQueryValue(vData,vername,(void**)&ver,&vsize))
   {LocalFree(vername);
	LocalFree(vData);
	return 0;
   }
// ie. we'll try to copy the \0 in vData, but we'll leave space
int verlen = strlen(ver);
if (verlen+1>aretmax) verlen=aretmax-1;
memmove(aret,ver,verlen);
aret[verlen]=0;
// The following code converts a string like 1.0 or 1.1.5 into
// a DWORD where the first digit is the leading byte, and so on.
// It discards version numbers greater than 255, and discards
// anything after the fourth version sub-part.
if (adwver==NULL)
   {LocalFree(vername);
	LocalFree(vData);
	return 0;
   }
char *first = ver, *next = ver;
unsigned int places = 0;
*adwver = 0;

for (int atend=false; atend==false; first = ++next)
	{
	 while (*next!=0 && *next!='.' && *next!=',') next++;
		if (*next==0)
			atend = true;
	 *next= 0;
	 for (int i = 0; atend==false;i++)
		 { if (first[i]<'0' || first[i]>'9')
			  {atend=true;
			   if (i==0)
				   break;
			   *adwver <<8; first[i]=0;
			   ((BYTE*)adwver)[3] = atoi(first);
			   places++;
               break;
              }
         }
      if (places==4)
          atend = true;
    }
for (int i = places; i < 4; i++)
     *adwver = *adwver<<8;

LocalFree(vername);
LocalFree(vData);
return true;
}
//---------------------------------------------------------------------------

