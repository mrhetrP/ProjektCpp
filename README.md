semestrální projekt CPP 2024 - Petr Doležal

motivace: přestože jsem původně pracoval na jiném projektu, rozhodl jsem se v průběhu prázdnin, naprogramovat místo něj vlastní databázi/zápisník pro potřeby mé aktuální výplně času, a to jest správa zděděné nemovitosti
a nemovitosti církve, kterou navštěvuji. Databáze/zápisník má pomoci s hlídáním termínů smluv a vybavení jednotlivých bytů (a prozatím pouze těch).

zpracování: organizace probíhá na úrovni jednotlivých bytů (proto pojmenování hlavní logiky "flatsmanager"), kde každý byt má svéou adresu, číslo bytu, smlouvy (od kdy do kdy a údaje o nájemníkovi) a  jednotlivé vybavení 
(název a unikátní id v rámci jedné adresy). Podle adresy, čísla bytu a nájemníků lze byty vyhledávat a kontrolovat tak například při předávání bytu jestli vše sedí a jestli stávající nájemníci mají platné smlouvy. Frontend je řešený pomocí
knihovny "ncurses", která poskytuje textové rozhraní v dedikovaném okně s možností pozicovat text a vytvářet menu, díky němuž má uživatel přehled, jaké funkce jsou mu k dispozici. Což se hodí při méně
častém používání aplikace a v případě že aplikaci používá někdo jiný než její tvůrce.

překážky při realizaci: 
