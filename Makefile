CROSS_COMPILE=x86_64-w64-mingw32-
CC=gcc
CFLAGS=--pedantic -Wall -Wno-implicit-function-declaration --static
DLLTOOL=dlltool

all: wsl2exe.exe wsl2exe_ap.exe

wsl2exe.exe: libwslapi.a
	${CROSS_COMPILE}${CC} ${CFLAGS} wsl2exe.c -L./ -lwslapi -o wsl2exe.exe

wsl2exe_ap.exe: libwslapi.a
	${CROSS_COMPILE}${CC} ${CFLAGS} wsl2exe_ap.c -L./ -lwslapi -o wsl2exe_ap.exe

libwslapi.a:
	${CROSS_COMPILE}${DLLTOOL} -d wslapi.def -l libwslapi.a

clean:
	@echo -e '\e[1;31mCleaning files...\e[m'
	-rm wsl2exe.exe
	-rm wsl2exe_ap.exe
	-rm libwslapi.a