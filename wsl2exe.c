/*
 * Copyright (c) 2017-2020 yuk7
 * Author: yuk7 <yukx00@gmail.com>
 *
 * Released under the MIT license
 * http://opensource.org/licenses/mit-license.php
 */

#include <stdio.h>
#include <wchar.h>
#include "wsl2exe_common.h"
#include "wsld.h"

int main()
{
    wchar_t **wargv;
    int wargc;
    wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    wchar_t *modName;
    modName = GetModuleName();

    wchar_t *distName;
    distName = WslGetDefaultDistroName();

    wprintf(L"%S\n", modName);
    wprintf(L"%S", distName);
    
    return 0;
}