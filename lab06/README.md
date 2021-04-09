# UDP Sockets

## Flow-ul programului

Clientul si serverul isi creaza un "canal de comunicatie", folosind functia
**socket**. Ulterior, ambii completeaza structura **struct sockaddr_in**, iar
server-ul foloseste functia **bind** pentru a lega socketul creat de structura
anterioara.

Mai departe clientul trimite bucati din fisier, folosind functia **sendto**,
iar cand continutul acestuia se termina, trimite un mesaj ce contine textul
*EOF*. Serverul va folosi functia **recvfrom** pentru a intercepta mesajul de
la client si scrie textul in fisierul corespunzator.

In final se inchid socketii si fisierele deschise.
