# ICMP

## Ping

Pentru a implementa comanda ping, completez campurile structurilor **struct iphdr**
si **struct icmphdr** ale pachetului initializat (asa cum scrie in laborator).
Ulterior astept raspunsul primit de trimiterea acestui pachet si extrag informatiile
primite din aceleasi structuri. In final afisez informatiile la *stdout*.

Tot acest procedeu este inclus intr-o bucla, dupa numarul de pachete care
trebuie trimise la destinatie. In cazul in care acest numar nu este specificat
programul cicleaza.

## Traceroute

Fac exact la fel ca la **ping**, doar ca acum bucla este dupa **ttl** Cresc
ttl-ul la fiecare pachet trimis pana cand nu mai primesc ca raspuns o structura
**struct icmphdr** ce are campul **type** egal cu 11, adica *time exceeded*.
In acest moment am ajuns la destinatia dorita.
