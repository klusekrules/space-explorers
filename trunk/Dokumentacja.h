/** \mainpage Strona g��wna
 * <CENTER><H1>
 * <A HREF="http://space-explorers.googlecode.com/">Link do g��wnej strony projektu</A>
 * </H1></CENTER>
 * \section lista_zmian Lista zmian
 * \link milestone-prealppha0_0_1
 * Lista zmian mi�dzy wersj� 0.0.1 a 0.0.2
 * \endlink
 * 
 * \link milestone-prealppha0_0_2
 * Lista zmian mi�dzy wersj� 0.0.2 a 0.0.3
 * \endlink
 * 
 * \link milestone-prealppha0_0_3
 * Lista zmian mi�dzy wersj� 0.0.3 a 0.0.4
 * \endlink
 *
 * \link milestone-prealppha0_0_4
 * Lista zmian mi�dzy wersj� 0.0.4 a 0.0.5
 * \endlink
 */

/** \page milestone Zmiany mi�dzy wersjami
 * \section lista_zmian Lista zmian
 * \li \subpage milestone-prealppha0_0_1 "Lista zmian mi�dzy wersj� 0.0.1 a 0.0.2" 
 * \li \subpage milestone-prealppha0_0_2 "Lista zmian mi�dzy wersj� 0.0.2 a 0.0.3" 
 * \li \subpage milestone-prealppha0_0_3 "Lista zmian mi�dzy wersj� 0.0.3 a 0.0.4"
 * \li \subpage milestone-prealppha0_0_4 "Lista zmian mi�dzy wersj� 0.0.4 a 0.0.5"
*/

/** \page schemadatafile Schemat pliku opisuj�cego obiekty
 * \include dataSchema.xsd
*/
/** \page schemasavefile Schemat pliku ze stanem gry
 * \include saveSchema.xsd
*/

/** \page schematutorial Jak napisa� w�asn� wersj� gry ? 
 * \attention Tutorial jest w fazie pisania i mo�e zawiera� b�edy merytoryczne i stylistyczne. Przepraszamy za utrudnienia.
 * \section wstep Wst�p
 * Opisz� w tym tutorialu w jaki spos�b napisa� prost� wersj� danych do gry. Na potrzeby naszego tutoriala przyjmiemy nast�puj�c� nazw� tworzonego przez nas pliku: \c wlasny_plik.xml.
 * \section ustawienia W�asny plik danych.
 * Do za�adowania pliku, kt�ry utworzymu potrzebne jest ustawienie adresu pliku. Aby to zrobi� w pliku \c options.xml odnajdujemy w�ze�
 * \code
 * <data>dane.xml</data>
 * \endcode
 * nast�pnie zamieniamy nazw� dotychczasowego pliku \c dane.xml na ten kt�ry utworzymy \c wlasny_plik.xml. Po tych modyfikacjach w trakcie wczytywania dancyh aplikacja skorzysta z ustawionego przez nas pliku.
 * \section walidacja_dancyh Walidacja danych.
 * Zanim zaczniemy pisa� plik z danych gry napisz� jak go zwalidowa�. Aby to zrobi� musimy pobra� program do edycji i walidacji plik�w xml. W programie ustawiamy schemat pliku danych ( \c SchematDanych.xsd ), kt�ry znajduje si� w folderze \c doc w g��wnym katalogu gry.
 * \section poczatek Opis pliku danych
 * Zacznijmy od pocz�tku, g��wnym w�z�em jest \c <Space-Explorers> w nim znajduj� si� wszystkie dane gry. W tym w�le mo�na umie�ci� nast�puj�ce obiekty:
 * \code
 * <SurowceInfo>
 * <StatekInfo>
 * <TechnologiaInfo>
 * <BudynekInfo>
 * <ObronaInfo>
 * \endcode
 *
 * \subsection surowceinfo_subsection Opis w�z�a SurowceInfo
 * Jednym z pi�ciu g��wnych obiekt�w grze jest surowiec. Aby zdefiniowa� surowiec w nale�y uzupe�ni� atrybuty w�z�a:
 * \li \c id - Unikalny identyfikator obiektu, nie mo�e si� powtarza� w �adnym ze zdefiniowanych obiekt�w.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 * \li \c powierzchnia - %Powierzchnia jak� zajmuje jeden obiekt.
 * \li \c objetosc - Obj�to�� jak� zajmuje jeden obiekt.
 * \li \c masa - %Masa jak� posiada jeden obiekt.
 * \li \c tpy - Typ surowca. Warto�� 1 oznacza surowiec przyrostowy ( oznacza to, �e jego ilo�� b�dzie rosn�� z ka�d� jednostk� czasu ). Warto�� 2 oznacza surowiec ilo�ciowy ( oznacza to, �e jego ilo�� b�dzie sta�a w jednostce czasu ).
 * Opr�cz tych atrybut�w mo�na r�wnie� ustawi� opis surowca poprzez wpisanie tekstu do w�z�a. A poni�ej przyk�adowe wpisy surowca:
 * \code {.xml}
 * <SurowceInfo typ="1" masa="1.75" objetosc="15.94" powierzchnia="2.34" poziom="1" id="0x0001" nazwa="Stal">
 *  Opis Stali.
 * </SurowceInfo>
 *
 * <SurowceInfo typ="2" masa="0" objetosc="0" powierzchnia="0" poziom="1" id="0x0002" nazwa="Energia">
 *  Opis Energii.
 * </SurowceInfo>
 * \endcode
 *
 * \subsection statekinfo_subsection Opis w�z�a StatekInfo
 * Drugim wa�nym obiektem jest \c %StatekInfo. %Obiekt ten jest mocno robudowany, zaczn� wi�c od opisu podstawowych atrybut�w:
 * \li \c id - Unikalny identyfikator obiektu, nie mo�e si� powtarza� w �adnym ze zdefiniowanych obiekt�w.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 * \li \c powierzchnia - %Powierzchnia jak� zajmuje jeden obiekt.
 * \li \c objetosc - Obj�to�� jak� zajmuje jeden obiekt.
 * \li \c masa - %Masa jak� posiada jeden obiekt.
 * \li \c hangar - Informacja czy podany statek mo�e byc przechowywany w hangarze innego statku. Warto�� 1 pozwala na dodawanie statku do hangaru innego statku. Warto�� 2 zabrania tej operacji.
 * Tak jak to by�o z surowcem r�wniez w statku mo�na doda� opis obiektu wpisuj�c tekst do w�z�a. 
 * Po za wymienionymi atrybutami musimy wepe�ni� kilka podobiekt�w, kt�re musz� znajdowa� si� w nast�puj�cej kolejno�ci.
 *
 * \subsubsection jednostka_latajaca Opis w�z�a JednostkaLatajacaInfo
 * Pierwszym z podobiekt�w elementu statek jest \c %JednostkaLatajacaInfo opisuj�ca parametry dotycz�ce przemieszczania si� statku.
 * \li \c id - zarezerwowany, ale musi zosta� poprawnie wype�niony.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c rodzajSilnikaId - Podstawowa warto�� os�ony obiektu.
 * \li \c rodzajSilnikaPoziom - Podstawowa warto�� pancerza obiektu.
 * \li \c mocSilnika - Podstawowa warto�� ataku obiektu.
 * \li \c zuzyciePaliwa - Podstawowa warto�� os�ony obiektu.
 * \li \c masaSilnika - Podstawowa warto�� pancerza obiektu.
 * \li \c sprawnoscSilnika - Warto�� informuj�ca jaki procent mocy silnika jest przekazywana na nap�d statku, 0 = 0%, 1 = 100%. Dopuszczalna jest warto�� wi�ksza od 1, natomiast warto�� mniejsza od 0 jest nie dopuszczalna.
 *
 * \subsubsection jednostka_ataujaca Opis w�z�a JednostkaAtakujacaInfo
 * Kolejnym ze wspomnianych w�z��w jest \c %JednostkaAtakujacaInfo opisuje ona parametry statku odpowiedzialne na walk�. Weze� musi sie znajdowa� w opisywanym statku. W�ze� posiada nast�puj�ce atrybuty:
 * \li \c id - zarezerwowany, ale musi zosta� poprawnie wype�niony.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c oslona - Podstawowa warto�� os�ony obiektu.
 * \li \c pancerz - Podstawowa warto�� pancerza obiektu.
 * \li \c atak - Podstawowa warto�� ataku obiektu.
 *
 * \subsubsection ladownia Opis w�z�a LadowniaInfo
 * Kolejnym elementem jest \c %LadowniaInfo. Atrybuty tego w�z�a opisuj� �adownie statku s�u��c� do przewo�enia innych surowc�w.
 * \li \c id - zarezerwowany, ale musi zosta� poprawnie wype�niony.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c pojemnoscMaksymalna - Maksymalna obj�to�� przewo�onych surowc�w.
 *
 * \subsubsection hangar Opis w�z�a HangarInfo
 * Kolejnym elementem jest \c %HangarInfo. Atrybuty tego w�z�a opisuj� hangar statku s�u��cy do przewo�enia innym statk�w.
 * \li \c id - zarezerwowany, ale musi zosta� poprawnie wype�niony.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c pojemnoscMaksymalna - Maksymalna obj�to�� przewo�onych statk�w.
 *
 * \subsection przyklad_statekInfo Przyk�ad statku
 * Poni�ej zamieszczam przyk�adowe statki:
 * \code {.xml}
 *
 * <StatekInfo masa="15300" objetosc="25340" powierzchnia="13468" poziom="1" id="0x3" nazwa="Transportowiec"  hangar="2">
 *  Opis Transportowca.
 *   <JednostkaLatajacaInfo rodzajSilnikaId="0x1" rodzajSilnikaPoziom="1" mocSilnika="516000" zuzyciePaliwa="450" masaSilnika="4600" sprawnoscSilnika="0.93" id="0x0" nazwa="Nazwa jednostki latajacej transportowca">
 *     Opis jednoscki latajacej transportowca.
 *   </JednostkaLatajacaInfo>
 *   <JednostkaAtakujacaInfo atak="90" pancerz="400" oslona="600" id="0x0" nazwa="Nazwa Jednostki atakujacej transportowca">
 *     Opis jednostki atakujacej transportowca.
 *   </JednostkaAtakujacaInfo>
 *  <LadowniaInfo pojemnoscMaksymalna="13000" id="0x0" nazwa="Nazwa ladowni transportowca">
 *     Opis ladowni transportowca.
 *   </LadowniaInfo>
 *   <HangarInfo pojemnoscMaksymalna="5000" id="0x0" nazwa="Nazwa hangaru transportowca">
 *     Opis hangaru transportowca.
 *   </HangarInfo>
 * </StatekInfo>
 *
 * <StatekInfo masa="4340" objetosc="960" powierzchnia="1354" poziom="1" id="0x"4 nazwa="My�liwiec"  hangar="1">
 *  Opis My�liwca.
 *   <JednostkaLatajacaInfo rodzajSilnikaId="0x1" rodzajSilnikaPoziom="1" mocSilnika="150000" zuzyciePaliwa="300" masaSilnika="1500" sprawnoscSilnika="0.99" id="0x0" nazwa="Nazwa jednostki latajacej My�liwca">
 *     Opis jednoscki latajacej My�liwca.
 *   </JednostkaLatajacaInfo>
 *   <JednostkaAtakujacaInfo atak="700" pancerz="300" oslona="100" id="0x0" nazwa="Nazwa Jednostki atakujacej My�liwca">
 *     Opis jednostki atakujacej My�liwca.
 *   </JednostkaAtakujacaInfo>
 *  <LadowniaInfo pojemnoscMaksymalna="1000" id="0x0" nazwa="Nazwa ladowni My�liwca">
 *     Opis ladowni My�liwca.
 *   </LadowniaInfo>
 *   <HangarInfo pojemnoscMaksymalna="0" id="0x0" nazwa="Nazwa hangaru My�liwca">
 *     Opis hangaru My�liwca.
 *   </HangarInfo>
 * </StatekInfo>
 * \endcode
 *
 * \subsection technologiainfo_subsection Opis w�z�a TechnologiaInfo
 * Do zbudowania takiego statku potrzebna jest znajomo�� odpowiednich technologii, kt�re to definiujemy w nast�puj�cy spos�b:
 * \li \c id - Unikalny identyfikator obiektu, nie mo�e si� powtarza� w �adnym ze zdefiniowanych obiekt�w.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 *
 * A oto i przyk�ad opisu takiej technologii:
 * \code {.xml}
 *
 * <TechnologiaInfo poziom="1" id="0xF" nazwa="Technologia komputerowa">
 *  Opis technologii komputerowej.
 * </TechnologiaInfo>
 *
 * <TechnologiaInfo poziom="1" id="0x10" nazwa="Technologia podprzestrzenna">
 *  Opis technologii podprzestrzennej.
 * </TechnologiaInfo>
 * \endcode
 *
 * \subsection budynekinfo_subsection Opis w�z�a BudynekInfo
 * W�ze� %BudynekInfo reprezentuje opis budynk�w na planecie. Atrybuty podstawowe takiego budynku to:
 * \li \c id - Unikalny identyfikator obiektu, nie mo�e si� powtarza� w �adnym ze zdefiniowanych obiekt�w.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 * \li \c powierzchnia - %Powierzchnia jak� zajmuje jeden obiekt.
 * \li \c objetosc - Obj�to�� jak� zajmuje jeden obiekt.
 * \li \c masa - %Masa jak� posiada jeden obiekt.
 *
 * Element %BudynekInfo posiada 2 unikalne dla niego w�z�y. Jeden z nich to Zapotrzebowanie, a drugi to Produkcja, oba zawieraj� analogiczne elementy. 
 * Weze� Zapotrzebowanie odpowiada za opis surowc�w jakich potrzebuje budynek do dzia�ania. Natomiast w�ze� Produkcja odpowiada za opis jakie surowce wytwarza budynek. 
 * Ka�de wyst�pienie w�z�a Zapotrzebowanie lub Produkcja odpowiada za jeden surowiec. W ka�dym w�le Zapotrzebowanie lub Produkcja musi znajdowa� si� dokladnie jeden w�ze� %Surowce.
 * W�z� %Surowce sk�ada si� z nast�puj�cych p�l:
 * \li \c id - %Identyfikator surowca.
 * \li \c ilosc - Ilo�� surowca.
 * \li \c opcja - atrybut zarezerwowwany dla aplikacji. Zawsze musi by� ustawiony na 1.
 *
 * A oto przyk�ady budynk�w:
 * \code {.xml}
 *
 * <BudynekInfo masa="1" objetosc="1" powierzchnia="1" poziom="1" id="0x11" nazwa="Kopalnia Metalu">
 *  Opis kopalni metalu.
 *   <Zapotrzebowanie>
 *     <Surowce id="0x2" ilosc="20" opcja="1"/>
 *   </Zapotrzebowanie>
 *   <Produkcja>
 *     <Surowce id="0x1" ilosc="100" opcja="1"/>
 *   </Produkcja>
 * </BudynekInfo>
 *
 * <BudynekInfo masa="1" objetosc="1" powierzchnia="1" poziom="1" id="0x12" nazwa="Elektrownia s�oneczna">
 *  Opis elektrowni s�onecznej.
 *   <Produkcja>
 *     <Surowce id="0x2" ilosc="150" opcja="1"/>
 *   </Produkcja>
 * </BudynekInfo>
 * \endcode
 *
 * \subsection obronainfo_subsection Opis w�z�a ObronaInfo
 * W�ze� %ObronaInfo reprezentuje opis obiekt�w obrony planety. Obiekty te ca�y czas znajduj� si� na planecie ale potrafi� atakowa� nadlatuj�ce wrogie floty. Atrybuty podstawowe s� analogiczne:
 * \li \c id - Unikalny identyfikator obiektu, nie mo�e si� powtarza� w �adnym ze zdefiniowanych obiekt�w.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 * \li \c powierzchnia - %Powierzchnia jak� zajmuje jeden obiekt.
 * \li \c objetosc - Obj�to�� jak� zajmuje jeden obiekt.
 * \li \c masa - %Masa jak� posiada jeden obiekt.
 *
 * \subsubsection jednostka_ataujaca Opis w�z�a JednostkaAtakujacaInfo
 * Elementem podrz�dnym jest %JednostkaAtakujacaInfo opisuje ona parametry obrony odpowiedzialne na walk�. Weze� musi sie znajdowa� w opisywanej obronie. W�ze� posiada nast�puj�ce atrybuty:
 * \li \c id - zarezerwowany, ale musi zosta� poprawnie wype�niony.
 * \li \c nazwa - Nazwa obiektu u�ywana w grze.
 * \li \c oslona - Podstawowa warto�� os�ony obiektu.
 * \li \c pancerz - Podstawowa warto�� pancerza obiektu.
 * \li \c atak - Podstawowa warto�� ataku obiektu.
 *
 * Poni�ej znajduj� si� przyk�adowe obiekty obrony.
 * \code {.xml}
 *
 * <ObronaInfo masa="900" objetosc="50" powierzchnia="10" poziom="1" id="0x14" nazwa="Wyrzutnia rakiet">
 *  Opis wyrzutni rakiet.
 *   <JednostkaAtakujacaInfo atak="90" pancerz="60" oslona="0" id="0x0" nazwa="Nazwa Jednostki atakujacej wyrzutni rakiet">
 *     Opis jednostki atakujacej wyrzutni rakiet.
 *   </JednostkaAtakujacaInfo>
 * </ObronaInfo>
 *
 * <ObronaInfo masa="60" objetosc="40" powierzchnia="30" poziom="1" id="0x15" nazwa="Tarcza">
 *  Opis tarczy.
 *   <JednostkaAtakujacaInfo atak="0" pancerz="60" oslona="2500" id="0x0" nazwa="Nazwa Jednostki atakujacej tarczy">
 *     Opis jednostki atakujacej tarczy.
 *   </JednostkaAtakujacaInfo>
 * </ObronaInfo>
 * \endcode
 *
*/

/** \page milestone-prealppha0_0_1 Zmiany od wersji 0.0.1 do 0.0.2
 * \section lista_zew Link do listy zada�
 * <A HREF="http://code.google.com/p/space-explorers/issues/list?can=1&q=Milestone%3DPreAlppha0.0.1&sort=priority+-modified&groupby=milestone&colspec=ID+Type+Status+Priority+Owner+Summary&x=priority&y=milestone&cells=tiles">Pe�na lista zada� dla wersji 0.0.1</A>
 * \section lista_zmian Opis zmian
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=1">[Issue-1]</A> </tt> Przeniesienie projektu na nowy serwer.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=3">[Issue-3]</A> </tt> Dodano bibliotek� TinyXML++ do parsowania plik�w xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=5">[Issue-5]</A> </tt> Dodano klas� JednostkaAtakujaca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=6">[Issue-6]</A> </tt>  Dodano klas� JednostkaLatajaca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=7">[Issue-7]</A> </tt>  Dodano klas� Surowce.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=8">[Issue-8]</A> </tt>  Dodano klas� Cena.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=9">[Issue-9]</A> </tt>  Dodano klas� Wymagania.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=12">[Issue-12]</A> </tt>  Dodano metod� pobieraj�c� mas� obiekt�w znajduj�cych si� w �adowni.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=13">[Issue-13]</A> </tt>  Przebudowano klas� przechowuj�c� list� obiekt�w.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=14">[Issue-14]</A> </tt>  Rozbudowano klas� Log.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=15">[Issue-15]</A> </tt>  Zaimplenetowano metody atak, pancerz, oslona w klasie JednostkaAtakuj�ca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=16">[Issue-16]</A> </tt>  Dodano drukowanie �ladu stosu razem z komunikatem wyj�tku.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=18">[Issue-18]</A> </tt>  Zmieniono klasy wyj�tk�w.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=21">[Issue-21]</A> </tt>  Dodano klas� Statek.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=23">[Issue-23]</A> </tt>  Zmiana miejsca przechowuj�cego wymagania.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=25">[Issue-25]</A> </tt>  Dodano klasy LadowniaInfo, StatekInfo.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=26">[Issue-26]</A> </tt>  Rozsze�enie test�w jednostkowych.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=27">[Issue-27]</A> </tt>  Zmiana w tworzeniu log�w. 
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=28">[Issue-28]</A> </tt>  Dodano numer wersji programu w pliku wykonywalnym.
 */

/** \page milestone-prealppha0_0_2 Zmiany od wersji 0.0.2 do 0.0.3
 * \section lista_zew Link do listy zada�
 * <A HREF="http://code.google.com/p/space-explorers/issues/list?can=1&q=Milestone%3DPreAlppha0.0.2&sort=priority+-modified&groupby=milestone&colspec=ID+Type+Status+Priority+Owner+Summary&x=priority&y=milestone&cells=tiles">Pe�na lista zada� dla wersji 0.0.2</A>
 * \section lista_zmian Opis zmian
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=4">[Issue-4]</A> </tt> Dodano wczytywanie obiekt�w z pliku xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=11">[Issue-11]</A> </tt> Dodano klasy Budynek i BudynekInfo.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=19">[Issue-19]</A> </tt> Dodano klasy opisuj�ce wymagania obiektu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=20">[Issue-20]</A> </tt>  Zmiana klasy Log ze statycznej na singleton.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=22">[Issue-22]</A> </tt>  Dodano losowy czynnik do metod klasy JednostkaAtakujaca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=30">[Issue-30]</A> </tt>  Dodano wczytywanie klasy Wymagania oraz klas pochodnych po ZmianaInterfejs z pliku xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=31">[Issue-31]</A> </tt>  Rozdzielono klas� Aplikacja.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=32">[Issue-32]</A> </tt>  Dodano wsp�czynnik kosztu obiektu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=33">[Issue-33]</A> </tt>  Dodano typ surowca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=36">[Issue-36]</A> </tt>  Dodano klasy Technologia oraz TechnologiaInfo
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=42">[Issue-42]</A> </tt>  Dodano zmiany parametr�w dla wybranych klas.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=43">[Issue-43]</A> </tt>  Dodano czas trwania test�w.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=46">[Issue-46]</A> </tt>  Zmiana struktury generowania log�w.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=47">[Issue-47]</A> </tt>  Dodano wczytywanie klas pochodznych po ZmianaInterfejs z bilbiotek dll.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=48">[Issue-48]</A> </tt>  Dodano walidacje danych w pliku options.xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=50">[Issue-50]</A> </tt>  Zmian sposobu dzi�ania test�w.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=51">[Issue-51]</A> </tt>  Zmiana miejsca przechowywania poziomu obiektu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=52">[Issue-52]</A> </tt>  Dodano numer wersji w bibliotekach dll.
 */

/** \page milestone-prealppha0_0_3 Zmiany od wersji 0.0.3 do 0.0.4
 * \section lista_zew Link do listy zada�
 * <A HREF="http://code.google.com/p/space-explorers/issues/list?can=1&q=Milestone%3DPreAlppha0.0.3&sort=priority+-modified&groupby=milestone&colspec=ID+Type+Status+Priority+Owner+Summary&x=priority&y=milestone&cells=tiles">Pe�na lista zada� dla wersji 0.0.3</A>
 * \section lista_zmian Opis zmian
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=10">[Issue-10]</A> </tt> Dodano dokumentacje klas projektu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=37">[Issue-37]</A> </tt> Dodano zapis i odczyt stan�w gry.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=38">[Issue-38]</A> </tt> Dodano klas� Planeta.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=39">[Issue-39]</A> </tt>  Poprawiono sprawdzanie spe�nienia wymaga�.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=40">[Issue-40]</A> </tt>  Dodano definiecje nazw element�w xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=41">[Issue-41]</A> </tt>  Dodano czas budowy i przeprowadzania bada�.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=49">[Issue-49]</A> </tt>  Dodano obs�ug� systemowych sytuacji wyj�tkowcyh.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=54">[Issue-54]</A> </tt>  Gruntowna refaktoryzacja kodu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=55">[Issue-55]</A> </tt>  Dodano klas� PodstawoweParametry.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=57">[Issue-57]</A> </tt>  Dodano now� klas� zmian.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=60">[Issue-60]</A> </tt>  Dodano klas� Flota.
 */

 /** \page milestone-prealppha0_0_4 Zmiany od wersji 0.0.4 do 0.0.5
 * \section lista_zew Link do listy zada�
 * <A HREF="http://code.google.com/p/space-explorers/issues/list?can=1&q=Milestone%3DPreAlppha0.0.4&sort=priority+-modified&groupby=milestone&colspec=ID+Type+Status+Priority+Owner+Summary&x=priority&y=milestone&cells=tiles">Pe�na lista zada� dla wersji 0.0.4</A>
 * \section lista_zmian Opis zmian
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=56">[Issue-56]</A> </tt> Dodano obiekt Obrona.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=58">[Issue-58]</A> </tt> 
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=59">[Issue-59]</A> </tt>
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=61">[Issue-61]</A> </tt>  Zmieniono rodzaj indeksy przechowywanych obiekt�w.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=62">[Issue-62]</A> </tt>  Dodano list� misji dla klasy Flota.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=63">[Issue-63]</A> </tt>  Walidacja plik�w xml
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=64">[Issue-64]</A> </tt>  Analiza klasy Statek, wydzielenie nowej klasy Hangar do transportu obiekt�w.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=66">[Issue-66]</A> </tt>  Zmiana tworzenia kosztu obiektu
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=67">[Issue-67]</A> </tt>  Zaostrzenie kryteri�w poprawno�ci plik�w xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=68">[Issue-68]</A> </tt>  Tworzenie schematu plik�w xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=69">[Issue-69]</A> </tt>  Analiza i implementacja nowego sposobu zapewniania tranzakcyjno�ci metod.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=70">[Issue-70]</A> </tt>  Utworzenie instalatora.
 */
