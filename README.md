# wsl2exe
Use command in WSL from exe executable

## Demo
![demo](https://user-images.githubusercontent.com/29954265/101806072-dd3e3580-3b56-11eb-9620-5a591df89b24.gif)

## 💻Requirements
* Windows 10 1709 Fall Creators Update 64bit or later.
* Windows Subsystem for Linux feature is enabled.

### [⬇Download](https://github.com/yuk7/wsl2exe/releases/latest)

## 📝How-to-Use
#### 1. [Download the exe](https://github.com/yuk7/wsl2exe/releases/latest) with the required functions.

"wsl2exe.exe" is the normal version, and "wsl2exe_ap.exe" has the function to convert the argument path.

#### 2. Rename it to the name of the command you want to execute it.

For example, if you want to run "vim" in wsl, rename it to "vim.exe".

## wsl2exe_ap.exe
wsl2exe_ap.exe considers the argument containing the backslash as the Windows path, converts it, and run it.

Some paths cannot be converted, in which case an error will be displayed.

The path recognition & translation algorithm is still tentative and subject to change.


## 📄License
[MIT](https://github.com/yuk7/wsl2exe/blob/main/LICENSES.md)

Copyright (c) 2017-2020 yuk7