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
#pragma hdrstop
USERES("dclusr50.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("ADVBAR.CPP");
USERES("ADVBAR.dcr");
USEUNIT("BARGRAPH.CPP");
USERES("BARGRAPH.dcr");
USEUNIT("BROWSEDLG.cpp");
USERES("BROWSEDLG.dcr");
USEUNIT("EXEDLG.CPP");
USERES("EXEDLG.dcr");
USEUNIT("EXEINFO.CPP");
USERES("EXEINFO.dcr");
USEUNIT("EXERES.CPP");
USERES("EXERES.dcr");
USEUNIT("FRAMEPAN.CPP");
USERES("FRAMEPAN.dcr");
USEUNIT("HINTBOX.CPP");
USERES("HINTBOX.dcr");
USEUNIT("SYSTRAY.CPP");
USERES("SYSTRAY.dcr");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Package source.
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
        return 1;
}
//---------------------------------------------------------------------------
