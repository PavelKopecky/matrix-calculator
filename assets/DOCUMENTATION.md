<h1>Maticová kalkulačka</h1>

<h3>Popis:</h3>

Jedná se o jednoduchou aplikaci ovládanou pomocí konzole. Uživatel může 
definovat matice a provádět na nich základní operace:

```
Binární operace:
- sčítání
- odčítání
- násobení
- spojení
- oříznutí

Unární operace:
- nalezení determinantu matice
- gaussova eliminační metoda
- nalezení inverzní matice
- nalezení hodnosti matice
- transpozice matice
```

Je možné si definovat pod všemi písmeny definovat různé matice.
V případě zájmu je také možné uložit obsah kalkulačky do souboru a ze
souboru ho následně znovu obnovit. Je také možné všechny momentálně 
uložené matice vypsat.

<h3>Ovládání:</h3>

Jak již bylo zmíněno, aplikace se ovládá pomocí konzole. Požadujeme,
aby uživatel vkádal operace v postfixové notaci, tedy v notaci, kde
operátor předchází operandy. Příklad takového zápisu v rámci kalkulačky
můžeme vidět zde:

```
$[[1,2],[3,4]] [[2,3],[4,5]] + B =
$[[1,0,-7],[-0.99,1,3]] TRA B * C =
```

Pokud by chtěl vypsat pouze výsledek operace, stačí vynechat operátor
přiřazení na konci zápisu. Pokud by chtěl uživatel vypsat konkrétní 
uloženou matici, stačí zadat její jméno do konzole.

Existuje zároveň několik dalších příkazů:

```
exit - uzavře aplikaci
status - vypíše všechny uložené matice
help - zobrazí stručný manuál k použití kalkulačky
rm A - odstraní matici A z databáze

save file.matxt - uloží obsah kalkulačky do souboru file.matxt
load file.matxt - načte ze souboru file.matxt matice v něm uložené
```

<h3>Závěr:</h3>

Pro konkrétní příklad různých běhů aplikace jsem ve složce
`kopecp14/examples` připravil několik vstupů, které by mohl
uživatel zadat. Tyto vstupy můžeme využít k názorné ukázce běhu aplikace.
Dále ve složce `kopecp14/tests` je několik testovacích souborů pro konkrétní
operátory, které mi během tvorby aplikace udržovat aplikaci funkční.
