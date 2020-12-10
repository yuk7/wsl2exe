/*
 * Copyright (c) 2017-2020 yuk7
 * Author: yuk7 <yukx00@gmail.com>
 *
 * Released under the MIT license
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef WSLD_H_
#define WSLD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

// WSL APIs declarations. Old mingw-w64 may not have wslapi.h
HRESULT WINAPI WslIsDistributionRegistered (PCWSTR);
HRESULT WINAPI WslRegisterDistribution (PCWSTR,PCWSTR);
HRESULT WINAPI WslUnregisterDistribution (PCWSTR);
HRESULT WINAPI WslConfigureDistribution (PCWSTR,ULONG,INT);
HRESULT WINAPI WslGetDistributionConfiguration (PCWSTR,ULONG*,ULONG*,INT*,PSTR*,ULONG*);
HRESULT WINAPI WslLaunchInteractive (PCWSTR,PCWSTR,BOOL,DWORD*);
HRESULT WINAPI WslLaunch (PCWSTR,PCWSTR,BOOL,HANDLE,HANDLE,HANDLE,HANDLE*);

#define LXSS_BASE_RKEY L"Software\\Microsoft\\Windows\\CurrentVersion\\Lxss"
#define MAX_DISTRO_NAME_SIZE 50
#define _MAX_DISTRO_NAME_SIZE (MAX_DISTRO_NAME_SIZE + 1)
#define MAX_BASEPATH_SIZE 128
#define UUID_SIZE 38
#define _UUID_SIZE (UUID_SIZE + 1)


wchar_t *WslGetDefaultDistroUuid() {
    wchar_t* uuid = (wchar_t*)malloc(sizeof(wchar_t) * _UUID_SIZE);

    HKEY hKey;
    LONG rres;
    if(RegOpenKeyExW(HKEY_CURRENT_USER, LXSS_BASE_RKEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD dwType;
        DWORD dwSize = (_UUID_SIZE*sizeof(wchar_t));

        rres = RegQueryValueExW(hKey, L"DefaultDistribution", NULL, &dwType, (LPBYTE)uuid, &dwSize);
    }

    return uuid;
}

wchar_t *WslGetDistroNameFromUuid(wchar_t *uuid) {
    wchar_t* name = (wchar_t*)malloc(sizeof(wchar_t) * _MAX_DISTRO_NAME_SIZE);

    wchar_t RKey[_MAX_PATH];
    wcscpy_s(RKey,(sizeof(RKey)/sizeof(RKey[0])),LXSS_BASE_RKEY);
    wcscat_s(RKey,(sizeof(RKey)/sizeof(RKey[0])),L"\\");
    wcscat_s(RKey,(sizeof(RKey)/sizeof(RKey[0])),uuid);

    HKEY hKey;
    LONG rres;
    if(RegOpenKeyExW(HKEY_CURRENT_USER, RKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD dwType;
        DWORD dwSize = (_MAX_DISTRO_NAME_SIZE*sizeof(wchar_t));

        rres = RegQueryValueExW(hKey, L"DistributionName", NULL, &dwType, (LPBYTE)name, &dwSize);
    }

    return name;
}

wchar_t *WslGetDefaultDistroName() {
    wchar_t *uuid;
    uuid = WslGetDefaultDistroUuid();

    wchar_t *name;
    name = WslGetDistroNameFromUuid(uuid);
    free(uuid);

    return name;
}

 unsigned long WslExec(wchar_t *DistroName, wchar_t *command, char *result, long unsigned int *len)
 {
     HANDLE hProcess;
     HANDLE hOutTmp,hOut;
     HANDLE hInTmp,hIn;
     SECURITY_ATTRIBUTES sa;
     sa.nLength = sizeof(sa);
     sa.bInheritHandle = TRUE;
     sa.lpSecurityDescriptor = NULL;
    
    CreatePipe(&hOut, &hOutTmp, &sa, 0);
    CreatePipe(&hIn, &hInTmp, &sa, 0);
    if(WslLaunch(DistroName, command, 1, hInTmp, hOutTmp, hOutTmp, &hProcess))
    {
        return 100000;
    }
    CloseHandle(hInTmp);
    CloseHandle(hOutTmp);

    WaitForSingleObject(hProcess, INFINITE);
    unsigned long exitcode;
    GetExitCodeProcess(hProcess, &exitcode);

    if(!ReadFile(hOut, result, *len, len, NULL))
    {
        return 200000;
    }

    if(result[(strrchr(result, '\0') - result) - 1] == '\n')
    {
        result[(strrchr(result, '\0') - result) - 1] = '\0';
    }
    
    CloseHandle(hIn);
    CloseHandle(hOut);
    CloseHandle(hProcess);

    return exitcode;
 }

#ifdef __cplusplus
}
#endif

#endif
