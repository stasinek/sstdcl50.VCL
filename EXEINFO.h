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
#ifndef __EXEINFO_h__
#define __EXEINFO_h__
//---------------------------------------------------------------------------
#include <stdio.h>
#if __BORLANDC__ > 0x551
	#include <Controls.hpp>
#else
	#include <Vcl/Controls.hpp>
#endif
//---------------------------------------------------------------------------
class PACKAGE TExeInformation : public TComponent
{
private:
         void  __fastcall SetSorry(AnsiString ASorry);
    AnsiString __fastcall GetFileDescription();
    AnsiString __fastcall GetFileVersion();
    AnsiString __fastcall GetInternalName();
    AnsiString __fastcall GetLegalCopyright();
    AnsiString __fastcall GetLegalTrademarks();
    AnsiString __fastcall GetOriginalFilename();
    AnsiString __fastcall GetProductName();
    AnsiString __fastcall GetProductVersion();
    AnsiString __fastcall GetCompanyName();
    AnsiString __fastcall GetComments();

    AnsiString __fastcall GetMajorVersion();
    AnsiString __fastcall GetMinorVersion();
    AnsiString __fastcall GetRelease();
    AnsiString __fastcall GetBuild();

    int __fastcall TExeInformation::GetFileVersionField(char*, char*, char*, int, DWORD*);
protected:
public:
    __fastcall TExeInformation(TComponent* Owner);
__published:
    __property AnsiString CompanyName      = {read=GetCompanyName,write=SetSorry};
    __property AnsiString FileDescription  = {read=GetFileDescription,write=SetSorry};
    __property AnsiString FileVersion      = {read=GetFileVersion,write=SetSorry};
    __property AnsiString InternalName     = {read=GetInternalName,write=SetSorry};
    __property AnsiString LegalCopyright   = {read=GetLegalCopyright,write=SetSorry};
    __property AnsiString LegalTrademarks  = {read=GetLegalTrademarks,write=SetSorry};
    __property AnsiString OriginalFilename = {read=GetOriginalFilename,write=SetSorry};
    __property AnsiString ProductName      = {read=GetProductName,write=SetSorry};
    __property AnsiString ProductVersion   = {read=GetProductVersion,write=SetSorry};
    __property AnsiString Comments         = {read=GetComments,write=SetSorry};
    __property AnsiString MajorVersion     = {read=GetMajorVersion,write=SetSorry};
    __property AnsiString MinorVersion     = {read=GetMinorVersion,write=SetSorry};
    __property AnsiString Release          = {read=GetRelease,write=SetSorry};
    __property AnsiString Build            = {read=GetBuild,write=SetSorry};
};
//---------------------------------------------------------------------------
#endif
