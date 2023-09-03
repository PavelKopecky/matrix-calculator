# Maticová kalkulačka
Autor: Pavel Kopecký, kopecp14

## Specifikace

Maticová kalkulačka je implementována jako *konzolová aplikace*. Uživatel může vytvářet nové matice, mazat
provádět nad maticemi různé operace a
ukládat aktuální stav kalkulačky do souboru a později i stav kalkulačky opět nahrát.
Vstup z konzole bude vyžadován v postfix formátu [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation), konec vstupu bude potvrzen
novým řádkem -- `\n`. Zpracování výrazu bude probíhat nad polymorfním stromem AST.

Mezi podporované operace patří: sčítání, odčítání, násobení, transpozice, sloučení, oříznutí, nalezení inverze, výpočet determinantu,
určení hodnosti a GEM, pokud jsou tyto operace definovány.

Uživatel může zároveň vypsat všechny aktuálně uložené matice, vypsat konkrétní matici nebo zobrazit stručný manuál.
Příkazy (`load`, `exit`, `help`, ...) budou volány běžným způsobem (název příkazu + případný parametr), výpočty jako takové budou zadávány v postfix formátu.

### Příklad běhu:
```
 >...
 $status
 > No user-defined matrices currently saved.
 $[[1, 2], [1, 3]] A =
 $A
 > | 1 2 |
 > | 1 3 |
 $[[1, 0, 0], [0, 1, 0], [0, 0, 1]] E =
 $[[2, 1, 5], [3, 2, 1], [7, 1, 0]] E +
 > | 3 1 5 |
 > | 3 3 2 |
 > | 7 1 1 |
 $A GEM
 > | 1 2 |
 > | 0 1 |
 $A
 > | 1 2 |
 > | 1 3 |
 $A GEM A =
 $A
 > | 1 2 |
 > | 0 1 |
 $save myMatricies.matx
 > Calculator saved successfully.
 $exit
 > Closing application.
```

## Polymorfismus

Polymorfismus bude implementován na úrovni abstraktní třídy CMatrix. Tato třída bude mít tři potomky - CDiagonalMatrix, CSparseMatrix a CDenseMatrix.
Implementace výpisu matice do konzole, či způsob uložení do souboru se bude lišit podle třídy.

Hlavním rozdílem mezi třídami je způsob uložení dat.
CDiagonalMatrix - diagonální matice - bude mít strukturu jednoduchého vektoru - diagonály. Ve třídě CSparseMatrix budou uloženy takové matice,
u nichž je počet nenulových prvků menší nebo roven počtu nižšího z počtu řádků/sloupců.
Řídké matice budou reprezentovány jako vektor trojic čísel (m_Row, m_Col, m_Val) - řádek, sloupec, hodnota. Nakonec husté matice jakožto objekty třídy CDenseMatrix
budou uloženy jako uloženy jako vektory m vektorů s n prvky, kde m je počet řádků a n počet sloupců.

Zároveň bude polymorfismus implementován na úrovni binárních i unárních operátorů. Základ nám bude tvořit abstraktní třída CBinaryOperator, resp. CUnaryOperator, která nám bude zastřešovat
konkrétní binární, resp. unární operátory. Tyto třídy obsahují abstraktní metodu
execute, která vykoná danou operaci. Výhodou je, že v argumentech můžeme využívat pouze reference na CMatrix, není nutné vytvářet různé třídy pro různé typy matix.

Konkrétní výpočet se bude realizovat nad polymorfním stromem AST, kde parent node bude obsahovat unární/binární operátor (výsledek operace je
vždy matice) a child nodes budou matice, nad kterými bude operace vykonána. Strom bude rekurzivně zpracováván odspodu. Př:

```
A = B * TR C - infix
C TR B * A = - postfix

       (=)
      /   \
    (*)   (A)
   /   \
 (B)    (TR)
          \
          (C)
```
Tedy bude muset existovat třida, která bude obsahovat pointery na operátory i matice. Tuto třídu nazveme CAbstractNode, jejíž členy nám budou tvořit AST. Tvorbu a zpracování tohoto
stromu nám obstarává třída CParser. CAbstractNode obsahuje metodu evaluate, která vyhodnotí hodnotu daného objektu. Pokud je objekt matice, vrací se přímo tato matice,
pokud je operátor, zavolá se se konkrétní operátor, jehož operandy jsou child nodes daného objektu, na které se opět zavolá metoda evaluate. To, jakého je daný node typu zjistíme podle toho,
který z pointerů je ne-nullový.