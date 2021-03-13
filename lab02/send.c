#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"
#include "utils.h"

#define HOST "127.0.0.1"
#define PORT 10000

#define FULL_FILE_NAME_1 "sender/file1"
#define FULL_FILE_NAME_2 "sender/file2"
#define FILE_NAME_1 "file1"
#define FILE_NAME_2 "file2"

void send_title(char *complete_file_name, char *file_name) {
  msg t;
  
  printf("[send] Sending title...\n");
  sprintf(t.file_name, "%s", complete_file_name);
  sprintf(t.payload, "%s", file_name);
  t.len = strlen(t.payload) + 1;
  t.code = MSG_TYPE_FILENAME;
  send_message(&t);
}

int send_size(char *complete_file_name) {
  msg t;
  
  printf("[send] Sending file size...\n");
  sprintf(t.file_name, "%s", complete_file_name);

  int fd = open(complete_file_name, O_RDONLY);
  DIE(fd < 0, "cannot open input file");
  int dim = lseek(fd, 0, SEEK_END);

  sprintf(t.payload, "%d", dim);
  t.len = strlen(t.payload) + 1;
  t.code = MSG_TYPE_SIZE;
  send_message(&t);

  close(fd);

  return dim;
}

void send_text(char *complete_file_name, int dim, int *read_bytes, int *is_sent) {
  msg t;
  int check_read;

  printf("[send] Sending file content...\n");
  memset(t.payload, 0, MAX_LEN);
  
  int fd = open(complete_file_name, O_RDONLY);
  DIE(fd < 0, "cannot open sender file");

  lseek(fd, *read_bytes, SEEK_SET);
  check_read = read(fd, t.payload, MAX_LEN - 1);
  DIE(check_read < 0, "cannot read from input file");
  t.len = strlen(t.payload) + 1;

  (*read_bytes) += t.len - 1;
  if (*read_bytes >= dim) {
    *is_sent = 1;
  }

  t.code = MSG_TYPE_TEXT;
  sprintf(t.file_name, "%s", complete_file_name);
  send_message(&t);

  close(fd);
}

void check_response() {
  msg t;
  
  if (recv_message(&t) < 0) {
    perror("Receive error ...\n");
    exit(-1);
  }
  printf("[send] Got reply with payload: <%s>\n", t.payload);
}

int main(int argc,char** argv){
  int count_bytes1 = 0, count_bytes2 = 0;
  int is_sent1 = 0, is_sent2 = 0, dim1, dim2;

  init(HOST, PORT);

  /* send title 1 */
  send_title(FULL_FILE_NAME_1, FILE_NAME_1);

  /* check response */
  check_response();

  /* send size 1 */
  dim1 = send_size(FULL_FILE_NAME_1);

  /* check response */
  check_response();

  /* send title 2 */
  send_title(FULL_FILE_NAME_2, FILE_NAME_2);

  /* check response */
  check_response();

  /* send size 2 */
  dim2 = send_size(FULL_FILE_NAME_2);

  /* check respons */
  check_response();

  while (!is_sent1 && !is_sent2) {
    if (!is_sent1) {
      /* send text */
      send_text(FULL_FILE_NAME_1, dim1, &count_bytes1, &is_sent1);

      /* check respons */
      check_response();
    }

    if (!is_sent2) {
      /* send text */
      send_text(FULL_FILE_NAME_2, dim2, &count_bytes2, &is_sent2);

      /* check respons */
      check_response();  
    } 
  }

  return 0;
}
