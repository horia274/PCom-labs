#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "lib.h"
#include "parity.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(void)
{
	msg r;
	int i, res, count_errors = 0;
	
	printf("[RECEIVER] Starting.\n");
	init(HOST, PORT);
	
	for (i = 0; i < COUNT; i++) {
		/* wait for message */
		res = recv_message(&r);
		if (res < 0) {
			perror("[RECEIVER] Receive error. Exiting.\n");
			return -1;
		}

		/* verific daca paritatea mesajului primit este aceeasi
		   cu cea calculata de sender */
		
		if (r.parity != find_parity_popcnt(r.payload)) {
			printf("[RECEIVER] Parity is different.\n");
			count_errors++;
		}
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

	printf("[RECEIVER] Number of corrupted messages: %d.\n", count_errors);
	printf("[RECEIVER] Finished receiving..\n");
	return 0;
}
