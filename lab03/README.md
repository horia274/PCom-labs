# Fereastra glisanta

## Implementare protocol

### Fisierul send.c

Am calculat *w* cu formula *w = (speed * delay * 1000) / (sizeof(msg) * 8)* iar apoi
am trimis *w* mesaje. Ulterior pentru fiecare mesaj trimis astept confirmare, iar
cand o primesc trimit urmatorul mesaj. In final primesc ultimele confirmari (ACK),
pentru ultimele *w* mesaje trimise.

### Fisierul recv.c

Primesc mesajul si trimit ACK, la fel ca la labul trecut.


## Detectia erorilor

Am implementat functia *find_parity_popcnt* in fisierul *parity.c* care calculeaza
paritatea numarului de biti setati dintr-un string dat ca parametru.

In cadrul structurii *msg*, am mai adaugat un camp care imi tine rezultatul
functiei *find_parity_popcnt* aplicat pe mesajul curent. Astfel, sender-ul va
trimite un mesaj cu tot cu paritatea numarului de biti setati, iar receiver-ul
va primi mesajul si va calcula din nou paritatea numarului de biti setati al
mesajului receptionat. Daca se intampla ca aceste doua rezultate sa difere, este
clar ca s-a produs o eroare in trimiterea mesajului.

Am tot schimbat valoarea lui *CORRUPT*, care imi zice un procent din mesajele
care vor fi "corupte", iar rezultatul obtinut in urma testarii este foarte
aproape de realitate.


## Bonus - trimiterea mai unui numar de mesaje mai mare decat *w*

Am crescut valoarea lui *COUNT* la 10 000 si valoarea lui *w* la 1000. Din formula,
pentru *SPEED = 10* si *DELAY = 10* se obtine *w = 8*, deci am trimis mult mai
mult decat ar fi putut procesa. Pentru a testa daca se pierde vreun pachet am
adaugat urmoarele linii de cod in fisicerul **recv.c**, intre partea de
*primire mesaj* si partea de *trimitere ACK*:


```
char *copy = strdup(r.payload);
char *check = strtok(copy, " ");
check = strtok(NULL, " ");
check = strtok(NULL, " ");

if (atoi(check) != i) {
    printf("message number %d is lost\n", i);
    return -1;
}
```

Practic verific daca indicele mesajului receptionat corespunde cu cel care ar fi
trebuit sa fie primit in acel moment.

Din ce am observat, nu se pierde niciun mesaj si totul functioneaza normal. :(
