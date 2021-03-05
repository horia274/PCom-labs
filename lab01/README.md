# CAT & TAC

## CAT

Ma pozitionez la sfarsitul fisierului pentru a vedea cati bytes *dim* ocupa. Apoi
aloc memorie de *dim* bytes unui buffer si citesc intreg continutul din fisier in
acel buffer, urmand apoi sa il afisez la *stdout*.

## TAC

Ma pozitionez la ultimul caracter din fisier. Citesc caracter cu caracter, de la
dreapta spre stanga, pana dau de caracterul *'\n'*. In acelasi timp, numar cate
caractere am citit, *count_bytes*. Acum citesc de unde am ramas, intr-un *buffer*,
*count_bytes* bytes, pentru a obtine ultima linie din fisier, dupa care o afisez
la *stdout*. Repet acelasi procedeu pana cand se termina fisierul.
