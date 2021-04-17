# TCP Protocol

## Client

Creaza un **socket TCP** pentru a se conecta la server. Apoi completeaza
structura **struct sockaddr_in** cu adresa server-ului la care se va conecta
ulterior,
folosind functia **connect**.

Acum clientul va citi de la tastatura un sir de caractere si va trimite pe
socket-ul creat anterior, catre server. Dupa care primeste raspunsul de la
acesta si procesul se reia.

In final clientul va inchide conexiunea, socket-ul creat anterior.

## Server

Creaza **socket-ul fictiv**, completeaza structura **sockaddr_in** si face **bind**.

Ulterior, foloseste metoda **listen** pentru a sti de la cati clienti poate
primi cereri. Pentru **run_echo_server**, va apela pentru un client, iar pentru
**run_chat_server**, pentru doi. Acesta va primi informatia de la unul din clientii
sai si o va transmite la celalalt.

Daca cei doi clienti sunt "egali", practic va transmite informatia inapoi la client.
Daca nu, se simuleaza un chat intre cei doi.
