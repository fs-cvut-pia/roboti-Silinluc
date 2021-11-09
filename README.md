# pia1-roboti-starter
Robot hledá cestu bludištěm

Tento program spouští robota, posílá ho na cestu skrz několik různých bludišť a počítá kolik potřebuje robot kroků a nárazů do překážek k nalezení cesty do cíle.

Třída Bludiste popisuje bludiště jako matici polí mezi kterými se robot může přesouvat kroky do stran, nahoru a dolů. Některé pole jsou ale stěny, tam robot narazí a nikam se nepohne. Tato třída obsahuje všechny metody, které robot může pro procházení bludiště využít - posun v 4 směrech, určení aktuální polohy a určení, zdali se nacházíme v cíli. Třída počítá každý krok a náraz robota.

BludisteOdkryte pak poskytuje i kompletní informaci o jakémkoli poli bludiště - kde je cíl a kde leží zdi. Robot si pak může naplánovat nejkratší cestu dopředu.

Robota ovšem musíte naprogramovat vy! Uděláte to implementováním rozhraní Prohledavac jakožto vlastní odvozené třídy. Zde jsou předepsané metody pro "nastartování" a "vypnutí" robota - nemusíte je využít, ale pokud nevrátí true, bude program hlásit chybu robota. Dále metoda vracející jméno robota a především metody pro jednotlivý krok vyhledání cesty v bludišti (ve skutečnosti ale v této metodě můžete udělat klidně více kroků po polích, třída Bludiste si to stejně spočítá...).

Jak bude váš "robot" fungovat uvnitř už je jen na vás :)
