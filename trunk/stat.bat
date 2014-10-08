@ECHO OFF
echo Rozpoczeto zbieranie statystyk
cloc --skip-win-hidden --quiet --by-file-by-lang --out="%1\doc\ProjStat.txt" --exclude-dir=doc,FormBuilder,Instalator,libs,LuaJIT-2.0.2,makedoc,makeversion,obj,out,SFML,TGUI,tools --exclude-list-file="%1\doc\exlude.txt" --not-match-f=opensdf %1 1>nul
echo Zakonczono zbieranie statystyk