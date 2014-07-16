rem echo Rozpoczeto generowanie numeru wersji
rem SubWCRev.exe %1 ..\svn_version.h.tmpl %1svn_version.h
rem echo Zakonczono generowanie numeru wersji
echo Rozpoczeto zbieranie statystyk
cloc --skip-win-hidden --quiet --by-file-by-lang --out="\doc\ProjStat.txt" --exclude-dir=out,allegro,Debug,doc,obj,SFML,parser,tools,TGUI --exclude-ext=.cppcheck,.sln,.rc,.sdf,.txt,.tmpl,.vsproj,.filters,.user,.suo ./
echo Zakonczono zbieranie statystyk