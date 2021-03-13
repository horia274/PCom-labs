# STOP and WAIT Protocol

## msg struct

Am modificat structura astfel:
* code - codul mesajul trimit (am pus macro-uri in fisierul *lib.h*)
* len - lungimea mesajul trimis de la sender catre receiver
* file_name - fisierul din care se transmite informatia
* payload - mesajul propriu-zis

## Sender

Am creat urmatoarele functii:
* send_title - are rolul de a trimit receptorului numele fisierului
* send_size - trimite receptorului dimensiunea fisierului (ma pozitionez la
finalul acestui fisier si folosesc *lseek* pentru a-i afla dimensiunea)
* send_text - trimite un calup de *MAX_LEN* bytes din continutul fisierului;
ca logica, tin minte din fiecare fisier cati bytes am trimis pentru a relua
transmisia din acel punct

## Receiver

Am creat urmatoarele functii:
* receive_title - primeste numele fisierului trimis de sender si creaza
fisierul in folder-ul *receiver*, folosind *O_TRUNC*, pentru a sterge un eventual
continut anterior
* receive_size - primeste dimensiunea fisierului
* receive_text - primeste o bucata din fisier si actualizeaza numarul de bytes
primiti de la respectivul fisier; mai departe ii scrie in fisierul creat
anterior, pe care il deschid in modul *O_APPEND*
* receive_message - verifica codul mesajului primit de la sender si apeleaza
una din functiile de mai sus

## Flow

Am testat functionalitatea trimitand simultan continutul a doua fisiere,
*file1* si *file2* din directorul *sender*. Am folosit comanda
*diff sender/file_num receiver/file_num*, unde *num* poate fi 1 sau 2, pentru a
vedea ca fisierele sunt identice

