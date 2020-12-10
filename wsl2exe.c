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

    wchar_t **convdWargv;
    convdWargv = malloc(sizeof(wchar_t*) * wargc);

    wchar_t *modNameEscd;
    modNameEscd = WcEscapeQuote(modName);

    //prepare convdWargv
    size_t modNameEscdSize = wcslen(modNameEscd);
    convdWargv[0] = (wchar_t*)malloc(sizeof(wchar_t) * (modNameEscdSize + 1));
    wcscpy_s(convdWargv[0], modNameEscdSize + 1, modNameEscd);

    for (int i = 1; i < wargc; i++) {
        convdWargv[i] = WcEscapeQuote(wargv[i]);
    }


    //launcher
    size_t total = 0;
    for (int i = 0; i < wargc; i++) {
        total++; //for space
        total += wcslen(convdWargv[i]);
    }
    total--;

    size_t totalSize = (sizeof(wchar_t) * (total + 1));
    wchar_t *command = (wchar_t*)malloc(totalSize);
    wcscpy_s(command, totalSize, convdWargv[0]);

    for (int i = 1; i < wargc; i++) {
        wcscat_s(command, totalSize, L" ");
        wcscat_s(command, totalSize, convdWargv[i]);
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