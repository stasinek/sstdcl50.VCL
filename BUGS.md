Najbardziej prawdopodobne Ÿród³a AV
FRAMEPAN PaintBorder gubi pióra GDI przy ka¿dym rysowaniu. Ta sama funkcja rysuje ramki w TAdvancedBar i TBarGraph. Pasek postêpu odœwie¿any przy ka¿dym pliku wyczerpuje limit 10 000 obiektów GDI po kilku tysi¹cach odœwie¿eñ, a potem VCL sypie siê w losowym miejscu. W programie do kopiowania to mój faworyt.
BARGRAPH traktuje jedn¹ strukturê jak tablicê. FBarData[i] dla i > 0 pisze poza przydzielon¹ pamiêæ. Do tego LocalAlloc(LMEM_MOVEABLE) zwraca uchwyt, a kod u¿ywa go jak wskaŸnika.
EXEINFO czyta zwolnion¹ pamiêæ. W ga³êzi BCB5 wskaŸnik pochodzi z obiektu tymczasowego. Jeœli exe nie ma zasobu wersji, wszystkie pola zwracaj¹ œmieci.
SYSTRAY wywala siê przy klikniêciu bez przypiêtego menu. Nie ma Notification(), wiêc menu usuniête z formy zostaje wisz¹cym wskaŸnikiem.
EXEDLG ma jeden statyczny wskaŸnik thisDialog na wszystkie instancje. Po usuniêciu komponentu zostaje wisz¹cy wskaŸnik.
FRAMEPAN (TRamka): ramka niezale¿na od motywu

Z³e

Linie 118–204: SelectObject(hdc, hpen) i zaraz DeleteObject(hpen), gdy pióro jest wci¹¿ wybrane w DC. Windows odmawia usuniêcia wybranego obiektu (DeleteObject zwraca 0), wiêc ka¿de pióro wycieka, czyli 2–4 na ka¿de rysowanie. Na koniec w DC Canvasa zostaje obce pióro, o którym TCanvas nie wie. Poprawny wzorzec: HPEN old = SelectObject(hdc, hpen); … SelectObject(hdc, old); DeleteObject(hpen);.
Linia 207: case bkNone: zamiast abkNone. bkNone to sta³a z innego typu VCL, która przypadkiem ma wartoœæ 0, dlatego siê kompiluje. Dodatkowo kod w liniach 214–227 i tak nadpisuje retrect, wiêc przy braku ramki wnêtrze kurczy siê o 1–2 px.
Linie 120–201: linie rysowane od wspó³rzêdnej 0, a nie od thisrect->left/top. PaintBorder jest publiczne i statyczne, wiêc przy prostok¹cie, który nie zaczyna siê w (0,0), ramka l¹duje w z³ym miejscu.

Potencjalnie z³e

Linie 87–89: static bool SBlock + while (SBlock) Application->ProcessMessages();. W jednym w¹tku pêtla nigdy siê nie krêci, bo nic w œrodku nie pompuje komunikatów. Jeœli jednak ktoœ zawo³a to z w¹tku roboczego (np. pasek postêpu z w¹tku kopiuj¹cego), to ProcessMessages w w¹tku pobocznym koñczy siê katastrof¹. Ta blokada niczego nie chroni, lepiej j¹ usun¹æ.
Nag³ówek, linie 71–96: opublikowane Parent, WindowProc, ControlStyle, ControlState, IsControl, MouseCapture, ScalingFlags, Name. Te w³aœciwoœci nie powinny trafiaæ do DFM ani do Inspektora Obiektów. Dwuklik na WindowProc w Inspektorze podmieni procedurê okna, a Parent w DFM rozwi¹zuje siê przez fixupy. Zostawi³bym tylko zdarzenia myszy, Align, Visible, Hint, PopupMenu, Cursor, Enabled.
Linie 63–65: w³asne Color przes³ania TControl::Color, a ParentColor dalej steruje tym ukrytym. To myl¹ce.

Do rozwa¿enia

Celem by³o „niezale¿nie od motywu”, a kod wszêdzie u¿ywa GetSysColor, czyli kolorów ze schematu u¿ytkownika. Jeœli chcesz pe³nej niezale¿noœci, dodaj w³aœciwoœci HighlightColor, ShadowColor, DarkShadowColor z domyœlnymi wartoœciami jak w Win95.
Rysowanie przez Canvas->Pen zamiast surowego GDI rozwi¹zuje problem wycieków samo z siebie i dzia³a identycznie w BCB5 i RAD.
ADVBAR (TAdvancedBar)

Z³e

Linie 107–109, 289–307: kolejnoœæ ³adowania z DFM. W³aœciwoœci czytaj¹ siê w kolejnoœci Min, Position, Max. Jeœli w designerze ustawisz Max=1000 i Position=500, to przy ³adowaniu Position trafia na jeszcze domyœlne Max=100, makro SETMINMAXVALUE je odrzuca i pozycja zostaje 0. Rozwi¹zanie: w csLoading przyjmowaæ wartoœci bez sprawdzania, a w Loaded() je przyci¹æ.
Linie 221–306: ka¿dy setter wo³a ForceRepaint(), który rysuje bezpoœrednio na Canvas->Handle. Przy kontrolce bez Parenta (new TAdvancedBar(this) przed ustawieniem Parent) VCL rzuca wyj¹tek „Control has no parent window”. Przy Position ustawianym z w¹tku roboczego GDI jest wo³ane z obcego w¹tku. Setter powinien zrobiæ tylko Invalidate(), a rysowaæ Paint().

Potencjalnie z³e

Linia 114: ta sama pêtla while (Block) ProcessMessages() co w ramce.
SetMax poni¿ej aktualnej pozycji zostawia FPos > FMax, procent przekracza 100 i prostok¹t t³a ma ujemn¹ szerokoœæ.

Do rozwa¿enia

Zmiana Font w Inspektorze nie odœwie¿a kontrolki. Obs³u¿ CM_FONTCHANGED.
Œrodkowanie tekstu w linii 181 nie dodaje FInnerRect.Left.
BARGRAPH (TBarGraph): najwiêcej b³êdów pamiêci

Z³e

Linia 64: FBarData = new TBarDataStruct() tworzy jedn¹ strukturê. W liniach 374, 378, 403, 439, 463, 479 i 518 kod u¿ywa jej jak tablicy FBarData[i], gdzie i to numer s³upka. Ka¿de i > 0 to zapis poza blokiem, czyli uszkodzona sterta. Pomiesza³y siê tu dwa pojêcia: s³upki (kolejne pomiary w czasie) i serie (kolory w s³upku). SetBarDataCount (linia 526) ustawia liczbê serii, a nie s³upków.
Linia 548: LocalAlloc(LMEM_MOVEABLE, …) zwraca uchwyt, nie wskaŸnik. Potrzebny by³by LocalLock albo po prostu LPTR. Zapis Item[0] w nastêpnej linii pisze pod adres uchwytu.
Linie 574–576: SetCount(0) zapisuje Item[-1], wiêc Clr() psuje stertê.
Linie 599–601: Set ma odwrócony warunek. Add wo³a Set(Count, …), wiêc SetCount(Count) nic nie robi i licznik nigdy nie roœnie. Dla AIndex < Count z kolei obcina dane.
Linie 487–492: ++Count bez realokacji, a bufor ma 8 elementów. Zapis do Item[8..15] wychodzi poza blok.
Linia 378: FBarData[i+1] dla ostatniego s³upka wychodzi poza zakres.
Linia 408: if (X-=EBarWidth < FCanvasRect.Right) przez priorytet operatorów oznacza X -= (EBarWidth < Right), czyli odejmuje 0 albo 1.
Linia 518: Shift() kopiuje strukturê razem ze wskaŸnikiem Item. Dwie struktury dziel¹ bufor, co przy zwalnianiu daje podwójne LocalFree.
Linie 225 i 293: dzielenie ca³kowite przez FBarHigherValue. BarScale=0 przechodzi walidacjê (linia 454) i koñczy siê wyj¹tkiem EDivByZero.
Linie 57–58 a 113–115: w konstruktorze Color=clBlack, GridColor=clGreen, a w deklaracji default=clGreen i default=clBlack. Wartoœci s¹ zamienione, wiêc kolory równe „domyœlnym” nie zapisz¹ siê do DFM i po wczytaniu wyjd¹ inne.

Do rozwa¿enia

Ten komponent wymaga przepisania warstwy danych, a nie ³atania. Proponujê tablicê s³upków (np. TList albo w³asny bufor ko³owy na N pomiarów), w ka¿dym s³upku sta³¹ tablicê serii, a Shift() jako przesuniêcie indeksu bufora ko³owego bez kopiowania.
Pixels[X][Y] w pêtli jest bardzo wolne. MoveTo/LineTo z psDot albo SetPixelV na HDC bitmapy bêd¹ szybsze, a w BCB5 to wci¹¿ czyste API.
EXEINFO (TExeInformation)

Z³e

Linie 99, 165, 181 i ka¿da kopia w ga³êzi BCB5: char *src = Application->ExeName.c_str();. ExeName to w³aœciwoœæ z getterem, który zwraca tymczasowy AnsiString. Ten obiekt znika po œredniku, wiêc strlen(src) i memmove czytaj¹ zwolnion¹ pamiêæ. Zwykle „dzia³a”, bo mened¿er pamiêci Borlanda jeszcze nie nadpisa³ bloku. To klasyczny b³¹d C++Buildera.
Linie 105, 171 i kolejne w ga³êzi RAD: wcstombs(…, Length()) bez terminatora, a helper le¿y na stosie. Œcie¿ka koñczy siê œmieciami.
Linie 107–109 i ka¿dy getter: gdy GetFileVersionField zwróci 0 (brak zasobu wersji, brak bloku Translation, brak danego pola), cstr jest niezainicjalizowany, a AnsiString(cstr) czyta stos do przypadkowego zera. Brak zasobu wersji jest czêsty w projektach bez w³¹czonego Version Info. Wystarczy cstr[0] = 0 przed wywo³aniem.
Linie 367–368: *adwver <<8; to instrukcja bez efektu (mia³o byæ <<=), a ka¿da czêœæ zapisuje ten sam bajt [3]. Ostatnia czêœæ wersji jest pomijana. Dziœ nikt nie podaje adwver, wiêc to martwy kod, ale b³êdny.

Do rozwa¿enia

Wszystkie 10 getterów da siê zast¹piæ jednym. Zamiast Application->ExeName + wcstombs u¿yj GetModuleFileNameA(HInstance, buf, MAX_PATH). To dzia³a identycznie w BCB5, BCB6 i RAD, bez #if i bez Unicode. Wszystkie pola mo¿esz wczytaæ raz do pamiêci podrêcznej.
W³aœciwoœci z write=SetSorry zapisuj¹ siê do DFM. Dlatego w About widzia³eœ dane „Inprise BCB.EXE”: w designerze Application to IDE. Dodaj stored=false.
Linia 58 nag³ówka: TExeInformation:: przed nazw¹ metody w deklaracji klasy. BCB5 to przyjmuje, nowy kompilator clang mo¿e odrzuciæ. Usuniêcie kwalifikacji nic nie kosztuje.
EXERES (TExeResource) + handlelist.h

Z³e

Linie 134–137: gdy LibFileName jest puste (tak jak w About), robi LoadLibraryEx(""), dostaje NULL i LoadImage(NULL, …) szuka w zasobach systemowych, a nie w exe. Do zasobów w³asnego exe trzeba podaæ HInstance. Dlatego ExeResource1 w About nic nie ³aduje.
Linia 113–115: DeleteObject na ikonach i kursorach (powinno byæ DestroyIcon/DestroyCursor). Co gorsze, obrazy za³adowane z LR_SHARED w ogóle nie wolno zwalniaæ.
Linia 156–157: LocalReAlloc(…, strlen(…)) bez +1 obcina terminator, a odczyt napisu wychodzi poza blok.
Linia 167: przy nieudanym ³adowaniu Count = 0 wyrzuca wszystkie wczeœniej zapamiêtane uchwyty bez zwolnienia. Powinno byæ Count = index.
Linia 77–80: SetLibLoaded(true) nigdy nie ustawia FLibLoaded = true.
Linia 186: destruktor robi LibFileName = "", ale gdy nazwa ju¿ jest pusta, setter wychodzi od razu i ClearHandleList siê nie wykonuje. Zostaje wyciek.

Potencjalnie z³e

Linie 160–165: ikony z LR_SHARED z biblioteki zwolnionej zaraz po za³adowaniu mog¹ straciæ wa¿noœæ.
handlelist.h: pe³ne definicje metod w nag³ówku bez inline. Nag³ówek w³¹cza i pakiet, i ka¿da forma u¿ywaj¹ca EXERES, co daje zdublowane symbole przy linkowaniu. size_t rzutowane na DWORD przestanie dzia³aæ w Win64.

Do rozwa¿enia

Cel, czyli ikony spójne z systemem, ³atwiej osi¹gn¹æ przez SHGetFileInfo (ikona dowolnego pliku lub folderu w stylu bie¿¹cego systemu) albo ExtractIconEx z shell32.dll. Oba dzia³aj¹ od Win95 i w BCB5.
SYSTRAY (TSysTray): dlaczego nie dzia³a w nowszych systemach

Z³e

Linie 154 i 161: FPopupMenu->Popup bez sprawdzenia NULL powoduje AV przy prawym klikniêciu, gdy menu nie przypiêto. Items->Items[0] przy pustym menu te¿.
Brak Notification()/FreeNotification: usuniesz PopupMenu z formy, FPopupMenu zostaje wisz¹cym wskaŸnikiem i nastêpne klikniêcie daje AV.
Linie 109 i 133: strcpy(TNID.szTip, …) bez limitu. szTip ma 64 albo 128 znaków zale¿nie od nag³ówków, wiêc d³u¿szy Hint przepe³nia stos.
Kolejnoœæ w DFM: Visible jest zadeklarowane przed Icon i Hint. Z Visible=true w designerze AddIcon() wykonuje siê w trakcie ³adowania z pust¹ ikon¹ i tekstem „Some Hint”. PóŸniejsze SetIcon/SetHint nie wo³aj¹ ChangeIcon(), wiêc w zasobniku zostaje pusty slot. To najpewniej jest g³ówny powód „nie dzia³a”. Dodawanie ikony trzeba przenieœæ do Loaded().
Destruktor (linie 64–72) nie wywo³uje RemoveIcon(). Po zamkniêciu programu zostaje „duch” ikony, który znika dopiero po najechaniu mysz¹.

Potencjalnie z³e

Linie 54–60: subclassing okna formy przez SetWindowLong w konstruktorze. Gdy VCL odtworzy uchwyt formy (RecreateWnd przy zmianie BorderStyle, FormStyle, ShowInTaskBar, a w RAD tak¿e przy zmianie DPI monitora), komunikaty id¹ do nieistniej¹cego okna. Jeœli ktoœ po Tobie podpi¹³ siê pod tê sam¹ procedurê, przywrócenie DefProc w destruktorze wytnie go z ³añcucha, a jego zapamiêtany wskaŸnik wska¿e zwolniony ObjectInstance. Do tego w designerze komponent podpina siê pod okno projektanta IDE.
Brak obs³ugi TaskbarCreated (RegisterWindowMessage("TaskbarCreated")): po restarcie Explorera albo przy starcie programu z autostartu, zanim pasek zadañ jest gotowy, ikona siê nie pojawia i nie wraca.
GetWindowLong/SetWindowLong z rzutowaniem na long przestanie dzia³aæ w Win64.

Do rozwa¿enia

W³asne ukryte okno przez AllocateHWnd(SubWndProc) zamiast subclassingu formy usuwa ca³y problem z odtwarzaniem uchwytu, dzia³a z ka¿dym Ownerem (te¿ z DataModule) i jest dostêpne w BCB5.
ZeroMemory(&TNID, sizeof(TNID)) przed wype³nieniem struktury, WM_APP zamiast WM_USER i nawiasy w #define.
W RAD 10.1 jest gotowy TTrayIcon (Vcl.ExtCtrls). Mo¿esz z niego podejrzeæ rozwi¹zania, nawet jeœli zostajesz przy w³asnym komponencie dla BCB5.
HINTBOX (THintBox): czytnik HTML

Stan obecny: ca³e cia³o DrawBoxEx() (linie 169–311) jest zakomentowane, wiêc komponent rysuje tylko pust¹ bitmapê, bez ramki i bez tekstu. Domyœlam siê, ¿e zakomentowa³eœ je podczas polowania na AV. Jeœli tak, winowajca jest tutaj:

Z³e (w zakomentowanym kodzie)

Linie 228–245: gdy pojedynczy znak jest szerszy ni¿ obszar tekstu (w¹ska kontrolka albo du¿y ShadowSize, przez co szerokoœæ wychodzi ujemna), pêtla skraca asTmp do pustego napisu, a asTmp[asTmp.Length()] = '-' pisze do asTmp[0]. Pusty AnsiString ma wskaŸnik danych NULL, wiêc to AV. Dodatkowo iLastSpace -= 2 przy pustym napisie cofa indeks i pêtla mo¿e siê zawiesiæ.
Linia 283 i 294–300: &Caption.SubString(…), czyli adres obiektu tymczasowego. BCB5 to przepuszcza, clang w RAD zg³osi b³¹d.

Z³e (w aktywnym kodzie)

Settery wo³aj¹ ForceRepaint(), ten sam problem co w ADVBAR: wyj¹tek bez Parenta, rysowanie poza WM_PAINT.
Linia 60 nag³ówka: void Update() ma tê sam¹ sygnaturê co wirtualne TControl::Update, wiêc nadpisuje je bez s³owa virtual. VCL wo³a Update() w wielu miejscach i za ka¿dym razem uruchamia siê parsowanie HTML i przerysowanie.

Potencjalnie z³e

(int)AlignList->Items[i] / (void*)iAlign przestanie dzia³aæ w Win64.
Statyczne zmienne w metodach s¹ wspólne dla wszystkich instancji.
Zmiana Font->Size w Inspektorze nie wywo³uje odœwie¿enia, bo TFont nie ma podpiêtego OnChange.

Do rozwa¿enia: jak to uproœciæ. Dziœ s¹ trzy osobne parsery tego samego (ParseLine, TextExtentEx, TextOutEx) i ka¿dy dzia³a trochê inaczej. Na przyk³ad brakuj¹ce else w liniach 629 i 730 nie szkodzi tylko przypadkiem. Prostszy uk³ad:

Jedna funkcja tokenizuj¹ca zamienia ca³y tekst na listê fragmentów. Ka¿dy fragment ma tekst, styl (B/I/U/S/A), wyrównanie i znacznik „nowa linia”.
£amanie wierszy robione jest na tych fragmentach, s³owo po s³owie, z jednym TextExtent na s³owo zamiast na ka¿dy znak.
Rysowanie to prosty przebieg po gotowych wierszach.

Taki podzia³ przeniesie siê te¿ 1:1 do Qt czy FLTK, bo tylko krok 3 zale¿y od biblioteki graficznej.

EXEDLG (TExeDialog)

Z³e

Linia 185: static TExeDialog *thisDialog jest wspólny dla wszystkich dialogów. Dwa komponenty powoduj¹, ¿e zdarzenia trafiaj¹ do z³ego obiektu, a po usuniêciu jednego zostaje wisz¹cy wskaŸnik. Rozwi¹zanie: w WM_INITDIALOG zapisaæ wskaŸnik przez SetWindowLong(hwnd, DWL_USER, lParam) i odczytywaæ go dla ka¿dego komunikatu.
Linie 203 i 210: case SW_SHOW: / case SW_HIDE: jako komunikaty. SW_SHOW = 5 = WM_SIZE, a SW_HIDE = 0 = WM_NULL. Ka¿da zmiana rozmiaru odpala ON_SHOW i pokazuje ukryty dialog, a ka¿de PostMessage(WM_NULL) go chowa. Dlatego case WM_SIZE musia³ zostaæ zakomentowany: kompilator zg³asza³ zdublowan¹ etykietê. Potrzebne s¹ w³asne komunikaty (WM_APP+n) albo osobne metody.
Linie 161–166: klasyczne „wisz¹ce else”. else wi¹¿e siê z wewnêtrznym if, wiêc Visible=true przy ju¿ widocznym oknie je chowa, a Visible=false nic nie robi.

Potencjalnie z³e

Linia 63: uchwyt Ownera pobrany w konstruktorze, ten sam problem z RecreateWnd co w SysTray.
Biblioteka zwalniana zaraz po CreateDialogParam (linie 147–152): kontrolki dialogu ³aduj¹ce póŸniej zasoby z tego hInstance dostan¹ niewa¿ny modu³.
BROWSEDLG (TBrowseDialog)

Z³e

Linia 122: gdy SHGetSpecialFolderLocation zawiedzie, pMalloc->Free(pidlRootFolder) zwalnia niezainicjalizowany wskaŸnik. To AV albo uszkodzona sterta. Na tej œcie¿ce wycieka te¿ pszTempName.
Linie 149 i 160: delete na pamiêci z malloc (linia 120). W BCB5 przechodzi, bo oba korzystaj¹ z tej samej sterty, ale to niezdefiniowane zachowanie. Wystarczy zwyk³a tablica char buf[MAX_PATH] na stosie.

Potencjalnie z³e

Linie 52 i 54 nag³ówka: settery przyjmuj¹ String, a w³aœciwoœci s¹ typu AnsiString. W BCB5 to ten sam typ, w RAD (String = UnicodeString) ju¿ nie.
lParam = (long)this przestanie dzia³aæ w Win64.
W repo le¿y browsedlg OLD.cpp. Nie jest w pakiecie, ale warto go przenieœæ poza katalog Ÿróde³, ¿eby nie pomyliæ plików.
Zgodnoœæ BCB5 - RAD 10.x
Twój projekt RAD ma ustawione _TCHARMapping=char. Dziêki temu makra WinAPI (LoadLibraryEx, CreateDialogParam, NOTIFYICONDATA, BROWSEINFO) rozwijaj¹ siê do wersji A i kod siê kompiluje. Przy domyœlnym wchar_t posypie siê w dziesi¹tkach miejsc. Bezpieczniej wo³aæ jawnie wersje …A (ShellExecuteA, LoadLibraryExA, NOTIFYICONDATAA). To dzia³a w obu œrodowiskach niezale¿nie od ustawieñ. W kodzie ju¿ tak robisz, ale niekonsekwentnie, np. GetFileVersionInfoSizeA obok GetFileVersionInfo.
Próg __BORLANDC__ > 0x551 w ka¿dym nag³ówku ma ten sam b³¹d co w About: BCB6 (0x560) wpada w ga³¹Ÿ Vcl.*. Proponujê dwa progi: >= 0x610 dla ró¿nic String/Unicode (C++Builder 2009) i >= 0x640 dla przestrzeni nazw Vcl. (XE2). Najproœciej by³oby jednak wszêdzie dawaæ samo #include <vcl.h> i usun¹æ rêczne listy nag³ówków. vcl.h dzia³a w BCB5, w BCB6 i w RAD, o ile w opcjach projektu RAD s¹ ustawione unit scope names.
Application->ExeName + wcstombs zast¹p przez GetModuleFileNameA. Jedna œcie¿ka kodu dla wszystkich wersji, bez #if.
Litera³y przekazywane jako char* (np. "FileVersion"): w parametrach u¿yj const char*. BCB5 nie ma nic przeciwko, a clang przestanie ostrzegaæ.
Ogólny wzorzec dla wszystkich kontrolek graficznych: setter tylko zmienia pole i wo³a Invalidate(), a ca³e rysowanie dzieje siê w Paint(). Usuwa to jednoczeœnie wyj¹tki „no parent window”, rysowanie poza WM_PAINT, pêtle ProcessMessages i problemy z w¹tkami. Dzia³a identycznie we wszystkich wersjach VCL.

Kolejnoœæ, w jakiej bym to bra³: FRAMEPAN (wyciek piór, kilka linii poprawek, a naprawia te¿ ADVBAR i BARGRAPH), potem SYSTRAY (Loaded(), sprawdzenie NULL, Notification), potem EXEINFO i EXERES (bo z nich korzysta About), a BARGRAPH na koñcu, bo tam trzeba przebudowaæ strukturê danych.