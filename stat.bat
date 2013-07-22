echo Rozpoczeto generowanie numeru wersji
SubWCRev.exe %1 ..\svn_version.h.tmpl %1svn_version.h
echo Zakonczono generowanie numeru wersji
echo Rozpoczeto zbieranie statystyk
rem cloc --by-file-by-lang --windows --out="%1doc\ProjStat.txt" --exclude-dir=out,allegro,Debug,doc,obj,SFML,parser --exclude-ext=.cppcheck,.sln,.opensdf,.rc,.sdf,.txt,.tmpl,.vsproj,.filters,.user,.suo ../
echo Zakonczono zbieranie statystyk