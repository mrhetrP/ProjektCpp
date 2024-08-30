semestrální projekt CPP 2024 - Petr Doležal

motivace: přestože jsem původně pracoval na jiném projektu, rozhodl jsem se v průběhu prázdnin, naprogramovat místo něj vlastní databázi/zápisník pro potřeby mé aktuální výplně času, a to jest správa zděděné nemovitosti
a nemovitosti církve kterou navštěvuji. Databáze/zápisník má pomoci s hlídáním termínů smluv a vybavení jednotlivých bytů (a prozatím pouze těch).

zpracování: organizace probíhá na úrovni jednotlivých bytů (proto pojmenování hlavní logiky "flatsmanager"), kde každý byt má svého nájemníka, smlouvu, adresu a id (číslo bytu v rámci adresy) a jednotlivé vybavení 
(pojmenované jako itemy). Podle adresy, adresy a id a nájemníků lze byty třídit a kontrolovat tak například při předávání bytu jestli vše sedí a jestli stávající nájemníci mají platné smlouvy. Frontend je řešený pomocí
knihovny "ncurses", která poskytuje textové rozhraní v dedikovaném okně s možností "menu" které se může měnit podle kontextu a které především napovídá uživateli možné akce které může vykonávat. Což se hodí při méně
častém používání aplikace a v případě že aplikaci používá někdo jiný než její tvůrce.

překážky při realizaci: 
