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

wchar_t *WcEscapeQuote(wchar_t *in) {
    size_t length = wcslen(in);
    if (wcsstr(in, L" ") != NULL) {
        length += 2; //add doublequote later
    }

    //search backslash '\' or '"'
    for(int i = 0; in[i] != L'\0'; i++) {
        if(in[i] == L'\"' || in[i] == L'\\') {
            length++;
        }
    }

    wchar_t* out =  (wchar_t*)malloc(sizeof(wchar_t) * (length + 1));
    out[length] = L'\0';

    int location = 0;
    if (wcsstr(in, L" ") != NULL) {
        out[0] = L'\"';
        out[length - 1] = L'\"';
        location++;
        length--;
    }

    for (int i = 0; location < length; i++) {
        //append backslash for escaping
        if(in[i] == L'\"' || in[i] == L'\\') {
            out[location] = L'\\';
            location++;
        }
        out[location] = in[i];
        location++;
    }

    return out;
}

#ifdef __cplusplus
}
#endif

#endif