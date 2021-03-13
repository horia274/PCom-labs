#ifndef LIB
#define LIB

#define MAX_LEN 1400
#define MAX_LEN_NAME 20

#define MSG_TYPE_FILENAME 0
#define MSG_TYPE_SIZE 1
#define MSG_TYPE_TEXT 2
#define MSG_TYPE_ACK 3

typedef struct {
  int code, len;
  char file_name[MAX_LEN_NAME];
  char payload[MAX_LEN];
} msg;

void init(char* remote,int remote_port);
void set_local_port(int port);
void set_remote(char* ip, int port);
int send_message(const msg* m);
int recv_message(msg* r);

#endif

