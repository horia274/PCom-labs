/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	mini-server de backup fisiere
*/

#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

#include "helpers.h"


void usage(char*file)
{
	fprintf(stderr,"Usage: %s server_port file\n",file);
	exit(0);
}

/*
*	Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
	int fd;

	if (argc!=3)
		usage(argv[0]);
	
	struct sockaddr_in my_sockaddr, from_station ;
	char buf[BUFLEN];


	/*Deschidere socket*/
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(sock < 0, "cannot establish connection");
	
	/*Setare struct sockaddr_in pentru a asculta pe portul respectiv */
	my_sockaddr.sin_family = AF_INET;
	my_sockaddr.sin_port = htons(atoi(argv[1]));
	my_sockaddr.sin_addr.s_addr = INADDR_ANY;
	
	/* Legare proprietati de socket */
	int b = bind(sock, (struct sockaddr*) &my_sockaddr, sizeof(my_sockaddr));
	DIE(b < 0, "cannot bind informations");
	
	
	/* Deschidere fisier pentru scriere */
	DIE((fd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644)) == -1, "open file");
	
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din socket
	*		pune in fisier
	*/
	while (1) {
		socklen_t socklen = sizeof(from_station);
		memset(buf, 0, BUFLEN);
		int r = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*) &from_station, &socklen);
		DIE(r < 0, "cannot receive message");

		if (!strcmp(buf, "EOF")) {
			break;
		}

		int count_bytes = write(fd, buf, r);
	    DIE(count_bytes < 0, "cannot write to server file");
	}

	/*Inchidere socket*/	
	close(sock);
	
	/*Inchidere fisier*/
	close(fd);

	return 0;
}
