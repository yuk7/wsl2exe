#ifndef WSL2EXE_COMMON_H_
#define WSL2EXE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif


wchar_t *GetModuleName() {
    wchar_t* modName = (wchar_t*)malloc(sizeof(wchar_t) * _MAX_PATH);

    wchar_t efpath[_MAX_PATH];
    GetModuleFileNameW(NULL, efpath, (sizeof(efpath) / sizeof(efpath[0])));
    
    wchar_t tmp[_MAX_PATH];
    _wsplitpath_s(efpath, tmp, MAX_PATH, tmp, MAX_PATH, modName, MAX_PATH, NULL, 0);

    return modName;
}

#ifdef __cplusplus
}
#endif

#endif