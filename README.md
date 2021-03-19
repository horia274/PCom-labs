# PCom-labs

Repo-ul contine implementarile personale din cadrul laboratorului de *Protocoale
de comunicatii*. Enunturile exercitiilor se gasesc [aici](https://ocw.cs.pub.ro/courses/pc), la sectiunea
*Laboratoare*.

## Continut laburi

Pe scurt, fiecare lab a avut ca scop urmatoarele aspecte, iar mai multe detalii
se pot gasi in *readme-ul* aferent fiecarui lab:

* lab01:
  * notiuni generale despre Linux si despre limbajul C
  * implementarea utilitarelor *cat* si *tac*

* lab02:
  * protocolul STOP and WAIT
  * implementarea unui sistem care simuleaza transmisia si receptia simultana
  a continutului a doua fisiere (merge pentru oricat de multe fisiere); sender-ul
  transmite iar receiver-ul primeste si scrie continul intr-un fisier

* lab03:
  * protocolul fereastra glisanta
  * simularea unei transmisii in stilul acestui protocol - sender-ul trimite *w*
  mesaje, apoi asteapta de la receiver cate un ACK pentru fiecare mesaj, iar
  in momentul in care il primeste, continua sa transmita inca un mesaj; in final
  sender-ul va receptiona ultimele *w* ACK-uri de la receiver
  * o modalitate de detectie a erorilor de transmisie - *Longitudinal Redundancy Check (Parity Word)*
