/** \mainpage Strona g³ówna
 * <CENTER><H1>
 * <A HREF="http://space-explorers.googlecode.com/">Link do g³ównej strony projektu</A>
 * </H1></CENTER>
 * \section lista_zmian Lista zmian
 * \link milestone-prealppha0_0_1
 * Lista zmian miêdzy wersj¹ 0.0.1 a 0.0.2
 * \endlink
 * 
 * \link milestone-prealppha0_0_2
 * Lista zmian miêdzy wersj¹ 0.0.2 a 0.0.3
 * \endlink
 * 
 * \link milestone-prealppha0_0_3
 * Lista zmian miêdzy wersj¹ 0.0.3 a 0.0.4
 * \endlink
 *
 * \link milestone-prealppha0_0_4
 * Lista zmian miêdzy wersj¹ 0.0.4 a 0.0.5
 * \endlink
 */

/** \page milestone Zmiany miêdzy wersjami
 * \section lista_zmian Lista zmian
 * \li \subpage milestone-prealppha0_0_1 "Lista zmian miêdzy wersj¹ 0.0.1 a 0.0.2" 
 * \li \subpage milestone-prealppha0_0_2 "Lista zmian miêdzy wersj¹ 0.0.2 a 0.0.3" 
 * \li \subpage milestone-prealppha0_0_3 "Lista zmian miêdzy wersj¹ 0.0.3 a 0.0.4"
 * \li \subpage milestone-prealppha0_0_4 "Lista zmian miêdzy wersj¹ 0.0.4 a 0.0.5"
*/

/** \page schemadatafile Schemat pliku opisuj¹cego obiekty
 * \include dataSchema.xsd
*/
/** \page schemasavefile Schemat pliku ze stanem gry
 * \include saveSchema.xsd
*/

/** \page schematutorial Jak napisaæ w³asn¹ wersjê gry ? 
 * \attention Tutorial jest w fazie pisania i mo¿e zawieraæ b³edy merytoryczne i stylistyczne. Przepraszamy za utrudnienia.
 * \section wstep Wstêp
 * Opiszê w tym tutorialu w jaki sposób napisaæ prost¹ wersjê danych do gry. Na potrzeby naszego tutoriala przyjmiemy nastêpuj¹c¹ nazwê tworzonego przez nas pliku: \c wlasny_plik.xml.
 * \section ustawienia W³asny plik danych.
 * Do za³adowania pliku, który utworzymu potrzebne jest ustawienie adresu pliku. Aby to zrobiæ w pliku \c options.xml odnajdujemy wêze³
 * \code
 * <data>dane.xml</data>
 * \endcode
 * nastêpnie zamieniamy nazwê dotychczasowego pliku \c dane.xml na ten który utworzymy \c wlasny_plik.xml. Po tych modyfikacjach w trakcie wczytywania dancyh aplikacja skorzysta z ustawionego przez nas pliku.
 * \section walidacja_dancyh Walidacja danych.
 * Zanim zaczniemy pisaæ plik z danych gry napiszê jak go zwalidowaæ. Aby to zrobiæ musimy pobraæ program do edycji i walidacji plików xml. W programie ustawiamy schemat pliku danych ( \c SchematDanych.xsd ), który znajduje siê w folderze \c doc w g³ównym katalogu gry.
 * \section poczatek Opis pliku danych
 * Zacznijmy od pocz¹tku, g³ównym wêz³em jest \c <Space-Explorers> w nim znajduj¹ siê wszystkie dane gry. W tym wêŸle mo¿na umieœciæ nastêpuj¹ce obiekty:
 * \code
 * <SurowceInfo>
 * <StatekInfo>
 * <TechnologiaInfo>
 * <BudynekInfo>
 * <ObronaInfo>
 * \endcode
 *
 * \subsection surowceinfo_subsection Opis wêz³a SurowceInfo
 * Jednym z piêciu g³ównych obiektów grze jest surowiec. Aby zdefiniowaæ surowiec w nale¿y uzupe³niæ atrybuty wêz³a:
 * \li \c id - Unikalny identyfikator obiektu, nie mo¿e siê powtarzaæ w ¿adnym ze zdefiniowanych obiektów.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 * \li \c powierzchnia - %Powierzchnia jak¹ zajmuje jeden obiekt.
 * \li \c objetosc - Objêtoœæ jak¹ zajmuje jeden obiekt.
 * \li \c masa - %Masa jak¹ posiada jeden obiekt.
 * \li \c tpy - Typ surowca. Wartoœæ 1 oznacza surowiec przyrostowy ( oznacza to, ¿e jego iloœæ bêdzie rosn¹æ z ka¿d¹ jednostk¹ czasu ). Wartoœæ 2 oznacza surowiec iloœciowy ( oznacza to, ¿e jego iloœæ bêdzie sta³a w jednostce czasu ).
 * Oprócz tych atrybutów mo¿na równie¿ ustawiæ opis surowca poprzez wpisanie tekstu do wêz³a. A poni¿ej przyk³adowe wpisy surowca:
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
 * \subsection statekinfo_subsection Opis wêz³a StatekInfo
 * Drugim wa¿nym obiektem jest \c %StatekInfo. %Obiekt ten jest mocno robudowany, zacznê wiêc od opisu podstawowych atrybutów:
 * \li \c id - Unikalny identyfikator obiektu, nie mo¿e siê powtarzaæ w ¿adnym ze zdefiniowanych obiektów.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 * \li \c powierzchnia - %Powierzchnia jak¹ zajmuje jeden obiekt.
 * \li \c objetosc - Objêtoœæ jak¹ zajmuje jeden obiekt.
 * \li \c masa - %Masa jak¹ posiada jeden obiekt.
 * \li \c hangar - Informacja czy podany statek mo¿e byc przechowywany w hangarze innego statku. Wartoœæ 1 pozwala na dodawanie statku do hangaru innego statku. Wartoœæ 2 zabrania tej operacji.
 * Tak jak to by³o z surowcem równiez w statku mo¿na dodaæ opis obiektu wpisuj¹c tekst do wêz³a. 
 * Po za wymienionymi atrybutami musimy wepe³niæ kilka podobiektów, które musz¹ znajdowaæ siê w nastêpuj¹cej kolejnoœci.
 *
 * \subsubsection jednostka_latajaca Opis wêz³a JednostkaLatajacaInfo
 * Pierwszym z podobiektów elementu statek jest \c %JednostkaLatajacaInfo opisuj¹ca parametry dotycz¹ce przemieszczania siê statku.
 * \li \c id - zarezerwowany, ale musi zostaæ poprawnie wype³niony.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c rodzajSilnikaId - Podstawowa wartoœæ os³ony obiektu.
 * \li \c rodzajSilnikaPoziom - Podstawowa wartoœæ pancerza obiektu.
 * \li \c mocSilnika - Podstawowa wartoœæ ataku obiektu.
 * \li \c zuzyciePaliwa - Podstawowa wartoœæ os³ony obiektu.
 * \li \c masaSilnika - Podstawowa wartoœæ pancerza obiektu.
 * \li \c sprawnoscSilnika - Wartoœæ informuj¹ca jaki procent mocy silnika jest przekazywana na napêd statku, 0 = 0%, 1 = 100%. Dopuszczalna jest wartoœæ wiêksza od 1, natomiast wartoœæ mniejsza od 0 jest nie dopuszczalna.
 *
 * \subsubsection jednostka_ataujaca Opis wêz³a JednostkaAtakujacaInfo
 * Kolejnym ze wspomnianych wêz³ów jest \c %JednostkaAtakujacaInfo opisuje ona parametry statku odpowiedzialne na walkê. Weze³ musi sie znajdowaæ w opisywanym statku. Wêze³ posiada nastêpuj¹ce atrybuty:
 * \li \c id - zarezerwowany, ale musi zostaæ poprawnie wype³niony.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c oslona - Podstawowa wartoœæ os³ony obiektu.
 * \li \c pancerz - Podstawowa wartoœæ pancerza obiektu.
 * \li \c atak - Podstawowa wartoœæ ataku obiektu.
 *
 * \subsubsection ladownia Opis wêz³a LadowniaInfo
 * Kolejnym elementem jest \c %LadowniaInfo. Atrybuty tego wêz³a opisuj¹ ³adownie statku s³u¿¹c¹ do przewo¿enia innych surowców.
 * \li \c id - zarezerwowany, ale musi zostaæ poprawnie wype³niony.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c pojemnoscMaksymalna - Maksymalna objêtoœæ przewo¿onych surowców.
 *
 * \subsubsection hangar Opis wêz³a HangarInfo
 * Kolejnym elementem jest \c %HangarInfo. Atrybuty tego wêz³a opisuj¹ hangar statku s³u¿¹cy do przewo¿enia innym statków.
 * \li \c id - zarezerwowany, ale musi zostaæ poprawnie wype³niony.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c pojemnoscMaksymalna - Maksymalna objêtoœæ przewo¿onych statków.
 *
 * \subsection przyklad_statekInfo Przyk³ad statku
 * Poni¿ej zamieszczam przyk³adowe statki:
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
 * <StatekInfo masa="4340" objetosc="960" powierzchnia="1354" poziom="1" id="0x"4 nazwa="Myœliwiec"  hangar="1">
 *  Opis Myœliwca.
 *   <JednostkaLatajacaInfo rodzajSilnikaId="0x1" rodzajSilnikaPoziom="1" mocSilnika="150000" zuzyciePaliwa="300" masaSilnika="1500" sprawnoscSilnika="0.99" id="0x0" nazwa="Nazwa jednostki latajacej Myœliwca">
 *     Opis jednoscki latajacej Myœliwca.
 *   </JednostkaLatajacaInfo>
 *   <JednostkaAtakujacaInfo atak="700" pancerz="300" oslona="100" id="0x0" nazwa="Nazwa Jednostki atakujacej Myœliwca">
 *     Opis jednostki atakujacej Myœliwca.
 *   </JednostkaAtakujacaInfo>
 *  <LadowniaInfo pojemnoscMaksymalna="1000" id="0x0" nazwa="Nazwa ladowni Myœliwca">
 *     Opis ladowni Myœliwca.
 *   </LadowniaInfo>
 *   <HangarInfo pojemnoscMaksymalna="0" id="0x0" nazwa="Nazwa hangaru Myœliwca">
 *     Opis hangaru Myœliwca.
 *   </HangarInfo>
 * </StatekInfo>
 * \endcode
 *
 * \subsection technologiainfo_subsection Opis wêz³a TechnologiaInfo
 * Do zbudowania takiego statku potrzebna jest znajomoœæ odpowiednich technologii, które to definiujemy w nastêpuj¹cy sposób:
 * \li \c id - Unikalny identyfikator obiektu, nie mo¿e siê powtarzaæ w ¿adnym ze zdefiniowanych obiektów.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 *
 * A oto i przyk³ad opisu takiej technologii:
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
 * \subsection budynekinfo_subsection Opis wêz³a BudynekInfo
 * Wêze³ %BudynekInfo reprezentuje opis budynków na planecie. Atrybuty podstawowe takiego budynku to:
 * \li \c id - Unikalny identyfikator obiektu, nie mo¿e siê powtarzaæ w ¿adnym ze zdefiniowanych obiektów.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 * \li \c powierzchnia - %Powierzchnia jak¹ zajmuje jeden obiekt.
 * \li \c objetosc - Objêtoœæ jak¹ zajmuje jeden obiekt.
 * \li \c masa - %Masa jak¹ posiada jeden obiekt.
 *
 * Element %BudynekInfo posiada 2 unikalne dla niego wêz³y. Jeden z nich to Zapotrzebowanie, a drugi to Produkcja, oba zawieraj¹ analogiczne elementy. 
 * Weze³ Zapotrzebowanie odpowiada za opis surowców jakich potrzebuje budynek do dzia³ania. Natomiast wêze³ Produkcja odpowiada za opis jakie surowce wytwarza budynek. 
 * Ka¿de wyst¹pienie wêz³a Zapotrzebowanie lub Produkcja odpowiada za jeden surowiec. W ka¿dym wêŸle Zapotrzebowanie lub Produkcja musi znajdowaæ siê dokladnie jeden wêze³ %Surowce.
 * Wêzê³ %Surowce sk³ada siê z nastêpuj¹cych pól:
 * \li \c id - %Identyfikator surowca.
 * \li \c ilosc - Iloœæ surowca.
 * \li \c opcja - atrybut zarezerwowwany dla aplikacji. Zawsze musi byæ ustawiony na 1.
 *
 * A oto przyk³ady budynków:
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
 * <BudynekInfo masa="1" objetosc="1" powierzchnia="1" poziom="1" id="0x12" nazwa="Elektrownia s³oneczna">
 *  Opis elektrowni s³onecznej.
 *   <Produkcja>
 *     <Surowce id="0x2" ilosc="150" opcja="1"/>
 *   </Produkcja>
 * </BudynekInfo>
 * \endcode
 *
 * \subsection obronainfo_subsection Opis wêz³a ObronaInfo
 * Wêze³ %ObronaInfo reprezentuje opis obiektów obrony planety. Obiekty te ca³y czas znajduj¹ siê na planecie ale potrafi¹ atakowaæ nadlatuj¹ce wrogie floty. Atrybuty podstawowe s¹ analogiczne:
 * \li \c id - Unikalny identyfikator obiektu, nie mo¿e siê powtarzaæ w ¿adnym ze zdefiniowanych obiektów.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c poziom - Podstawowy poziom obiektu przypisywany przy tworzeniu.
 * \li \c powierzchnia - %Powierzchnia jak¹ zajmuje jeden obiekt.
 * \li \c objetosc - Objêtoœæ jak¹ zajmuje jeden obiekt.
 * \li \c masa - %Masa jak¹ posiada jeden obiekt.
 *
 * \subsubsection jednostka_ataujaca Opis wêz³a JednostkaAtakujacaInfo
 * Elementem podrzêdnym jest %JednostkaAtakujacaInfo opisuje ona parametry obrony odpowiedzialne na walkê. Weze³ musi sie znajdowaæ w opisywanej obronie. Wêze³ posiada nastêpuj¹ce atrybuty:
 * \li \c id - zarezerwowany, ale musi zostaæ poprawnie wype³niony.
 * \li \c nazwa - Nazwa obiektu u¿ywana w grze.
 * \li \c oslona - Podstawowa wartoœæ os³ony obiektu.
 * \li \c pancerz - Podstawowa wartoœæ pancerza obiektu.
 * \li \c atak - Podstawowa wartoœæ ataku obiektu.
 *
 * Poni¿ej znajduj¹ siê przyk³adowe obiekty obrony.
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
 * \section lista_zew Link do listy zadañ
 * <A HREF="http://code.google.com/p/space-explorers/issues/list?can=1&q=Milestone%3DPreAlppha0.0.1&sort=priority+-modified&groupby=milestone&colspec=ID+Type+Status+Priority+Owner+Summary&x=priority&y=milestone&cells=tiles">Pe³na lista zadañ dla wersji 0.0.1</A>
 * \section lista_zmian Opis zmian
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=1">[Issue-1]</A> </tt> Przeniesienie projektu na nowy serwer.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=3">[Issue-3]</A> </tt> Dodano bibliotekê TinyXML++ do parsowania plików xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=5">[Issue-5]</A> </tt> Dodano klasê JednostkaAtakujaca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=6">[Issue-6]</A> </tt>  Dodano klasê JednostkaLatajaca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=7">[Issue-7]</A> </tt>  Dodano klasê Surowce.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=8">[Issue-8]</A> </tt>  Dodano klasê Cena.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=9">[Issue-9]</A> </tt>  Dodano klasê Wymagania.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=12">[Issue-12]</A> </tt>  Dodano metodê pobieraj¹c¹ masê obiektów znajduj¹cych siê w ³adowni.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=13">[Issue-13]</A> </tt>  Przebudowano klasê przechowuj¹c¹ listê obiektów.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=14">[Issue-14]</A> </tt>  Rozbudowano klasê Log.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=15">[Issue-15]</A> </tt>  Zaimplenetowano metody atak, pancerz, oslona w klasie JednostkaAtakuj¹ca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=16">[Issue-16]</A> </tt>  Dodano drukowanie œladu stosu razem z komunikatem wyj¹tku.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=18">[Issue-18]</A> </tt>  Zmieniono klasy wyj¹tków.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=21">[Issue-21]</A> </tt>  Dodano klasê Statek.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=23">[Issue-23]</A> </tt>  Zmiana miejsca przechowuj¹cego wymagania.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=25">[Issue-25]</A> </tt>  Dodano klasy LadowniaInfo, StatekInfo.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=26">[Issue-26]</A> </tt>  Rozsze¿enie testów jednostkowych.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=27">[Issue-27]</A> </tt>  Zmiana w tworzeniu logów. 
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=28">[Issue-28]</A> </tt>  Dodano numer wersji programu w pliku wykonywalnym.
 */

/** \page milestone-prealppha0_0_2 Zmiany od wersji 0.0.2 do 0.0.3
 * \section lista_zew Link do listy zadañ
 * <A HREF="http://code.google.com/p/space-explorers/issues/list?can=1&q=Milestone%3DPreAlppha0.0.2&sort=priority+-modified&groupby=milestone&colspec=ID+Type+Status+Priority+Owner+Summary&x=priority&y=milestone&cells=tiles">Pe³na lista zadañ dla wersji 0.0.2</A>
 * \section lista_zmian Opis zmian
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=4">[Issue-4]</A> </tt> Dodano wczytywanie obiektów z pliku xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=11">[Issue-11]</A> </tt> Dodano klasy Budynek i BudynekInfo.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=19">[Issue-19]</A> </tt> Dodano klasy opisuj¹ce wymagania obiektu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=20">[Issue-20]</A> </tt>  Zmiana klasy Log ze statycznej na singleton.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=22">[Issue-22]</A> </tt>  Dodano losowy czynnik do metod klasy JednostkaAtakujaca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=30">[Issue-30]</A> </tt>  Dodano wczytywanie klasy Wymagania oraz klas pochodnych po ZmianaInterfejs z pliku xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=31">[Issue-31]</A> </tt>  Rozdzielono klasê Aplikacja.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=32">[Issue-32]</A> </tt>  Dodano wspó³czynnik kosztu obiektu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=33">[Issue-33]</A> </tt>  Dodano typ surowca.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=36">[Issue-36]</A> </tt>  Dodano klasy Technologia oraz TechnologiaInfo
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=42">[Issue-42]</A> </tt>  Dodano zmiany parametrów dla wybranych klas.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=43">[Issue-43]</A> </tt>  Dodano czas trwania testów.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=46">[Issue-46]</A> </tt>  Zmiana struktury generowania logów.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=47">[Issue-47]</A> </tt>  Dodano wczytywanie klas pochodznych po ZmianaInterfejs z bilbiotek dll.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=48">[Issue-48]</A> </tt>  Dodano walidacje danych w pliku options.xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=50">[Issue-50]</A> </tt>  Zmian sposobu dzi³ania testów.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=51">[Issue-51]</A> </tt>  Zmiana miejsca przechowywania poziomu obiektu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=52">[Issue-52]</A> </tt>  Dodano numer wersji w bibliotekach dll.
 */

/** \page milestone-prealppha0_0_3 Zmiany od wersji 0.0.3 do 0.0.4
 * \section lista_zew Link do listy zadañ
 * <A HREF="http://code.google.com/p/space-explorers/issues/list?can=1&q=Milestone%3DPreAlppha0.0.3&sort=priority+-modified&groupby=milestone&colspec=ID+Type+Status+Priority+Owner+Summary&x=priority&y=milestone&cells=tiles">Pe³na lista zadañ dla wersji 0.0.3</A>
 * \section lista_zmian Opis zmian
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=10">[Issue-10]</A> </tt> Dodano dokumentacje klas projektu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=37">[Issue-37]</A> </tt> Dodano zapis i odczyt stanów gry.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=38">[Issue-38]</A> </tt> Dodano klasê Planeta.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=39">[Issue-39]</A> </tt>  Poprawiono sprawdzanie spe³nienia wymagañ.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=40">[Issue-40]</A> </tt>  Dodano definiecje nazw elementów xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=41">[Issue-41]</A> </tt>  Dodano czas budowy i przeprowadzania badañ.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=49">[Issue-49]</A> </tt>  Dodano obs³ugê systemowych sytuacji wyj¹tkowcyh.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=54">[Issue-54]</A> </tt>  Gruntowna refaktoryzacja kodu.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=55">[Issue-55]</A> </tt>  Dodano klasê PodstawoweParametry.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=57">[Issue-57]</A> </tt>  Dodano now¹ klasê zmian.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=60">[Issue-60]</A> </tt>  Dodano klasê Flota.
 */

 /** \page milestone-prealppha0_0_4 Zmiany od wersji 0.0.4 do 0.0.5
 * \section lista_zew Link do listy zadañ
 * <A HREF="http://code.google.com/p/space-explorers/issues/list?can=1&q=Milestone%3DPreAlppha0.0.4&sort=priority+-modified&groupby=milestone&colspec=ID+Type+Status+Priority+Owner+Summary&x=priority&y=milestone&cells=tiles">Pe³na lista zadañ dla wersji 0.0.4</A>
 * \section lista_zmian Opis zmian
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=56">[Issue-56]</A> </tt> Dodano obiekt Obrona.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=58">[Issue-58]</A> </tt> 
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=59">[Issue-59]</A> </tt>
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=61">[Issue-61]</A> </tt>  Zmieniono rodzaj indeksy przechowywanych obiektów.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=62">[Issue-62]</A> </tt>  Dodano listê misji dla klasy Flota.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=63">[Issue-63]</A> </tt>  Walidacja plików xml
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=64">[Issue-64]</A> </tt>  Analiza klasy Statek, wydzielenie nowej klasy Hangar do transportu obiektów.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=66">[Issue-66]</A> </tt>  Zmiana tworzenia kosztu obiektu
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=67">[Issue-67]</A> </tt>  Zaostrzenie kryteriów poprawnoœci plików xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=68">[Issue-68]</A> </tt>  Tworzenie schematu plików xml.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=69">[Issue-69]</A> </tt>  Analiza i implementacja nowego sposobu zapewniania tranzakcyjnoœci metod.
 * \li <tt> <A HREF="http://code.google.com/p/space-explorers/issues/detail?id=70">[Issue-70]</A> </tt>  Utworzenie instalatora.
 */
