#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"
#include "utils.h"

#define HOST "127.0.0.1"
#define PORT 10001

void receive_title(msg r, char *file_path) {
  printf("[recv] Got msg with payload: <%s>, sending ACK...\n", r.payload);
  snprintf(file_path, r.len + strlen("receiver/"), "receiver/%s", r.payload);

  int fd = open(file_path, O_CREAT | O_TRUNC, 0664);
  DIE(fd < 0, "cannot open receiver file");
  close(fd);
}

void receive_size(msg r, int *dim) {
  char *end_ptr;

  printf("[recv] Got msg with payload: <%s>, sending ACK...\n", r.payload);
  *dim = strtol(r.payload, &end_ptr, 10);
}

void receive_text(msg r, char *file_path, int dim, int *count_bytes, int *is_received) {
  int fd = open(file_path, O_WRONLY | O_APPEND);
  DIE(fd < 0, "cannot open receiver file");

  write(fd, r.payload, r.len - 1);
  (*count_bytes) += r.len - 1;
  if (*count_bytes >= dim) {
    *is_received = 1;
  }

  printf("[recv] Got message with payload: <%s>, sending ACK...\n", r.payload);
  close(fd);
}

void receive_message(msg r, char *file_path, int *dim, int *count_bytes, int *is_received) {
  if (recv_message(&r) < 0) {
    perror("Receive error ...\n");
    exit(-1);
  }
  
  switch (r.code) {
    case MSG_TYPE_FILENAME:
      receive_title(r, file_path);
      break;
    
    case MSG_TYPE_SIZE:
      receive_size(r, dim);
      break;

    case MSG_TYPE_TEXT:
      receive_text(r, file_path, *dim, count_bytes, is_received);
      break;

    default:
      printf("code unknown");
      exit(-1);
  }
}

void send_ack() {
  msg r;

  sprintf(r.payload, "%s", "ACK");
  r.len = strlen(r.payload) + 1;
  r.code = MSG_TYPE_ACK;
  send_message(&r);
  printf("[recv] ACK sent\n");
}

int main(int argc,char** argv){
  msg r;
  char file_path1[MAX_LEN_NAME + strlen("receiver/")];
  char file_path2[MAX_LEN_NAME + strlen("receiver/")];
  int is_received1 = 0, is_received2 = 0;
  int count_bytes1 = 0, count_bytes2 = 0;
  int dim1, dim2;

  init(HOST, PORT);

  /* receive title 1 */
  receive_message(r, file_path1, &dim1, &count_bytes1, &is_received1);

  /* send ACK */
  send_ack();

  /* receive dimension 1 */
  receive_message(r, file_path1, &dim1, &count_bytes1, &is_received1);

  /* send ACK */
  send_ack();

  /* receive title 2 */
  receive_message(r, file_path2, &dim2, &count_bytes2, &is_received2);

  /* send ACK */
  send_ack();

  /* receive size 2 */
  receive_message(r, file_path2, &dim2, &count_bytes2, &is_received2);

  /* send ACK */
  send_ack();

  while (!is_received1 && !is_received2) {
    if (!is_received1) {
      /* receive text */
      receive_message(r, file_path1, &dim1, &count_bytes1, &is_received1);

      /* send ACK */
      send_ack();
    }

    if (!is_received2) {
      /* receive text */
      receive_message(r, file_path2, &dim2, &count_bytes2, &is_received2);

      /* send ACK */
      send_ack();
    }
  }

  return 0;
}
