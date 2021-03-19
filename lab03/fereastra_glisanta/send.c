#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc, char *argv[])
{
	msg t;
	int i, res, speed, delay, w;
	char *end_ptr;

	if (argc != 3) {
		printf("wrong number of arguments\n");
		return -1;
	}

	speed = strtol(argv[1], &end_ptr, 10);
	delay = strtol(argv[2], &end_ptr, 10);
	w = (speed * delay * 1000) / (sizeof(msg) * 8);

	init(HOST, PORT);

	printf("[SENDER] Starting.\n");	

	/* trimite primele w cadre */
	for (i = 0; i < w; i++) {
		memset(&t, 0, sizeof(msg));
		sprintf(t.payload, "%s %d", "message number", i);
		t.len = strlen(t.payload) + 1;

		res = send_message(&t);
		if (res < 0) {
			perror("[SENDER] Send error. Exiting.\n");
			return -1;
		}
		printf("[SENDER] Send message <%s>.\n", t.payload);
	}

	/* primeste cate un ACK pentru fiecare iar
	   dupa fiecare ACK primit mai trimite un cadru */

	for (i = w; i < COUNT; i++) {

		/* wait for ACK */
		res = recv_message(&t);
		if (res < 0) {
			perror("[SENDER] Receive error. Exiting.\n");
			return -1;
		}
		printf("[SENDER] Receive ACK message <%s>.\n", t.payload);

		/* cleanup msg */
		memset(&t, 0, sizeof(msg));
		sprintf(t.payload, "%s %d", "message number", i);
		t.len = strlen(t.payload) + 1;
		
		/* send msg */
		res = send_message(&t);
		if (res < 0) {
			perror("[SENDER] Send error. Exiting.\n");
			return -1;
		}
		printf("[SENDER] Send message <%s>.\n", t.payload);
	}

	/* primeste ACK pentru ultimele w mesaje trimise */

	for (i = 0; i < w; i++) {
		/* wait for ACK */
		res = recv_message(&t);
		if (res < 0) {
			perror("[SENDER] Receive error. Exiting.\n");
			return -1;
		}
		printf("[SENDER] Receive ACK message <%s>.\n", t.payload);
	}

	printf("[SENDER] Job done, all sent.\n");
		
	return 0;
}
