# Forwarding

Astept sa primesc un pachet. In momentul in care un mesaj este receptionat, extrag
structurile *struct ether_header* si *struct iphdr* din el. Verific ca mesajul sa
nu contina erori, adica *checksum*-ul sa fie 0, iar timpul de "expirare" sa ramana
minim 1. Ulterior gasesc cea mai buna ruta specifica adresei IP destinatie,
care se calculeaza luand toate intrarile din tabela de rutare si verificand
daca adresa curenta are acelasi prefix cu cea data ca parametru (se face operatia
de *si pe biti, &* intre adresa IP si masca). Dintre cele valide se alege cea
cu masca maxima.

Acum se recalculeaza *ttl*-ul si *checksum*-ul, iar apoi se gasesc adresele MAC
pentru noua sursa si noua destinatie, completand campurile din structura *ether_hdr*.
Sursa va contine interfata de la *best_route*, iar destinatia va fi MAC-ul adresei
intoarse de functia *get_arp_entry*. 

In final se trimite pachetul pe interfata de la *best_route*.
