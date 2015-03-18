@ECHO OFF
rem echo Rozpoczeto zbieranie statystyk
rem cloc --skip-win-hidden --quiet --by-file-by-lang --out="%1\doc\ProjStat.txt" --exclude-dir=doc,FormBuilder,Instalator,libs,LuaJIT-2.0.2,makedoc,makeversion,obj,out,SFML,TGUI,tools --exclude-list-file="%1\doc\exlude.txt" --not-match-f=opensdf %1 1>nul
rem echo Zakonczono zbieranie statystyk
ECHO "Obliczanie numeru wersji"
SETLOCAL

FOR /F "tokens=*" %%i in ('DATE /T') do SET data=%%i
FOR /F "tokens=*" %%i in ('TIME /T') do SET czas=%%i

DEL /F /Q git_version.h
ECHO #define TIMESTAMP "%data%%czas%" >> git_version.h

IF NOT "%GIT_BIN%" == "" GOTO version
ECHO "Zmienna srodowiskowa GIT_BIN nie jest ustawiona. GIT_BIN musi wskazywac na folder bin dla aplikacji git."
GOTO end

:version
FOR /F "tokens=*" %%i in ('CALL "%GIT_BIN%\git" describe --tags') do SET version=%%i
ECHO #define GIT_VERSION "%version%">> git_version.h

FOR /F "tokens=1-5 delims=.-" %%A IN ("%version%") DO (
ECHO #define VERSION_MAJOR               %%A >> git_version.h
ECHO #define VERSION_MINOR               %%B >> git_version.h
ECHO #define VERSION_REVISION            %%C >> git_version.h
ECHO #define VERSION_BUILD               %%D >> git_version.h
ECHO #define VERSION_COMMIT              %%E >> git_version.h
)

:end
ECHO "Zakonczono obliczanie numeru wersji"