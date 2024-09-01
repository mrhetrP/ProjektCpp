Kód pro správnou kompilaci vyžaduje verzi c++ kompilátoru 14.0.2 a nainstalovanou knihovnu "ncurses".

semestrální projekt CPP 2024 - Petr Doležal

motivace: 
Přestože jsem původně pracoval na jiném projektu, rozhodl jsem se v průběhu prázdnin, naprogramovat místo něj vlastní databázi/zápisník pro potřeby mé aktuální výplně času, a to jest správa zděděné nemovitosti a nemovitosti církve, kterou navštěvuji. Databáze/zápisník má pomoci s hlídáním termínů smluv a vybavení jednotlivých bytů (a prozatím pouze těmi).

zpracování: 
Organizace probíhá na úrovni jednotlivých bytů (proto pojmenování hlavní logiky "flatsmanager"), kde každý byt má svou adresu, číslo bytu, smlouvy (od kdy do kdy a údaje o nájemníkovi) a  jednotlivé vybavení (název a unikátní id v rámci jedné adresy). Podle adresy, čísla bytu a nájemníků lze byty vyhledávat a kontrolovat tak například při předávání bytu jestli vše sedí a jestli stávající nájemníci mají platné smlouvy. Frontend je řešený pomocí knihovny "ncurses", která poskytuje textové rozhraní v dedikovaném okně s možností pozicovat text a vytvářet menu, díky němuž má uživatel přehled, jaké funkce jsou mu k dispozici. Což se hodí při méně častém používání aplikace a v případě že aplikaci používá někdo jiný než její tvůrce.

možná (a pravděpodobná) rozšiřitelnost:
Poměrně jednoduchou implementací bude rozšíření informací ohledně nájemníků tak, aby byly okamžitě k dipozici všechny potřebné informace k podpisu jakékoliv smlouvy. Podobně je pak možné rozšířit informace o bytech (výměry, dispozice, atd...). Větším a možná mírně složitějším úkolem pak bude rozšíření o jednu úroveň výš, vytvořením entity samotných domů, jejichž součástí by byly aktuálně implementované byty a i všechny nebytové prostory. Jisté změny by ocenil i frontend aplikce (scrolování, určtité změny ve formátování atp.)

závěr:
Kód je věřím dobrým základem pro budoucí implementaci, jeho hlavní hodnotu však vidím hlavně v tom že je už v aktuální chvíli prakticky využíván (přiložený csv soubor je pouze test souborem).
