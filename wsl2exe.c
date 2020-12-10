/*
 * Copyright (c) 2017-2020 yuk7
 * Author: yuk7 <yukx00@gmail.com>
 *
 * Released under the MIT license
 * http://opensource.org/licenses/mit-license.php
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "wsl2exe_common.h"
#include "wsld.h"

#define ARRAY_LENGTH(a) (sizeof(a)/sizeof(a[0]))

int main()
{
    wchar_t **wargv;
    int wargc;
    wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    wchar_t *modName;
    modName = GetModuleName();

    wchar_t *distName;
    distName = WslGetDefaultDistroName();

    size_t total = wcslen(modName);
    for (int i = 1; i < wargc; i++) {
        total++; //for space
        total += wcslen(wargv[i]);
    }

    size_t totalSize = (sizeof(wchar_t) * (total + 1));
    wchar_t *command = (wchar_t*)malloc(totalSize);
    wcscat_s(command, totalSize ,modName);

    for (int i = 1; i < wargc; i++) {
        wcscat_s(command, totalSize ,L" ");
        wcscat_s(command, totalSize ,wargv[i]);
    }

    HRESULT hr;
    DWORD exitCode = 1;
    hr = WslLaunchInteractive(distName, command, true, &exitCode);
    if (hr == S_OK) {
        return exitCode;
    } else {
        return hr;
    }
}