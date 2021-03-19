#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(void)
{
	msg r;
	int i, res;
	
	printf("[RECEIVER] Starting.\n");
	init(HOST, PORT);
	
	for (i = 0; i < COUNT; i++) {
		/* wait for message */
		res = recv_message(&r);
		if (res < 0) {
			perror("[RECEIVER] Receive error. Exiting.\n");
			return -1;
		}
	
		/* verifica daca se pierde vreun pachet */

		// char *copy = strdup(r.payload);
		// char *check = strtok(copy, " ");
		// check = strtok(NULL, " ");
		// check = strtok(NULL, " ");

		// if (atoi(check) != i) {
		// 	printf("message number %d is lost\n", i);
		// 	return -1;
		// }

		printf("[RECEIVER] Receive message <%s>.\n", r.payload);
		
		/* send ACK */
		sprintf(r.payload, "ACK");
		r.len = strlen(r.payload) + 1;
		res = send_message(&r);
		if (res < 0) {
			perror("[RECEIVER] Send ACK error. Exiting.\n");
			return -1;
		}
		printf("[RECEIVER] Send ACK message <%s>.\n", r.payload);
	}

	printf("[RECEIVER] Finished receiving..\n");
	return 0;
}
