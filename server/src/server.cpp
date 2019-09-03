#include "../include/data.h"
#include "server.h"
int main(){
	init_server();
	
	pthread_t listen_t;
    pthread_t send_t;
	pthread_create(&listen_t, NULL, listen_thread_function, NULL);
	pthread_create(&send_t, NULL, send_thread_function, NULL);

	char command[1024];
	while(1) {
		scanf("%s", command);
		exec_cmd(command);
	}
}
