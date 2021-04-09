/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	client mini-server de backup fisiere
*/

#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "helpers.h"

void usage(char*file)
{
	fprintf(stderr,"Usage: %s ip_server port_server file\n",file);
	exit(0);
}

/*
*	Utilizare: ./client ip_server port_server nume_fisier_trimis
*/
int main(int argc,char**argv)
{
	if (argc!=4)
		usage(argv[0]);
	
	int fd;
	struct sockaddr_in to_station;
	char buf[BUFLEN];

	/*Deschidere socket*/
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(sock < 0, "cannot establish connection");
	
	/* Deschidere fisier pentru citire */
	DIE((fd = open(argv[3],O_RDONLY)) == -1, "open file");
	
	/*Setare struct sockaddr_in pentru a specifica unde trimit datele*/
	to_station.sin_family = AF_INET;
	to_station.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], &to_station.sin_addr);
	
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din fisier
	*		trimite pe socket
	*/
	while (1) {
		int count_bytes = read(fd, buf, BUFLEN);
		DIE(count_bytes < 0, "cannot read from client file");

		if (count_bytes == 0) {
			break;
		}
		
		int s = sendto(sock, buf, count_bytes, 0, (struct sockaddr*) &to_station, sizeof(to_station));
		DIE(s < 0, "cannot send current message");
	}
	
	memset(buf, 0, BUFLEN);
	strcpy(buf, "EOF");
	int s = sendto(sock, buf, strlen(buf) + 1, 0, (struct sockaddr*) &to_station, sizeof(to_station));
	DIE(s < 0, "cannot send final message");

	/*Inchidere socket*/
	close(sock);
	
	/*Inchidere fisier*/
	close(fd);

	return 0;
}
