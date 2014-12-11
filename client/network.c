/*
 * network.c
 *
 * Richard Degenne - Adrien Deprez
 * 09/12/14
 *
 * Header for the network.c file.
 */

# include "network.h"

/*
 * build_request()
 *
 * Build the string that will be sent to the server
 */

void build_request(req_t* req_p, char buffer[MAX_REQ]) {
	char buff[MAX_REQ];
	int cursor = 0;
	int argc, i;

	// Building request buffer up
	switch(req_p->type) { // Request type
		case PLACE_REQ:
			strcpy(buff, "PLACE ");
			cursor = 6;
			argc = 5;
			break;
		case FIRE_REQ:
			strcpy(buff, "FIRE ");
			cursor = 5;
			argc = 2;
			break;
		default:
			printf("Invalid request code.\n");
			exit(EXIT_FAILURE);
	}
	
	for(i=0 ; i<argc ; ++i) { // Arguments
		strcpy(buff + cursor*sizeof(char),strcat(req_p->args[i],(i == argc-1)?"":" "));
		cursor += strlen(req_p->args[i]);
	}
	buff[cursor] = '\0'; // End of request character
	strcpy(buffer, buff);
}


/*
 * init_connection()
 *
 * Opens a socket to the host server.
 */
void init_connection(int* sfd_p, struct sockaddr_in* addr_p) {
	
	check(*sfd_p = socket(AF_INET, SOCK_STREAM, 0), "Error creating socket");

	addr_p->sin_family = AF_INET;
	addr_p->sin_port = htons(SERVER_PORT);
	inet_aton(SERVER_ADDR, &(addr_p->sin_addr));
	
	check(connect(*sfd_p, (struct sockaddr*)addr_p, sizeof(*addr_p)), "Error connecting");
}

/*
 * send_request()
 *
 * Sends a request.
 */
 void send_request(req_t* req_p, char buff_p[MAX_REQ]) {
	char buff[MAX_REQ];
	int sfd;
	struct sockaddr_in addr_s;
	int i;
	struct pollfd pfd;

	pfd.fd = sfd;
	pfd.events = POLLIN; // Waiting for data to read
	pfd.revents = 0;

	build_request(req_p, buff);
	init_connection(&sfd, &addr_s);
	check(send(sfd, buff, strlen(buff)+1, 0), "Error sending");
	if(buff_p != NULL) {
		check(poll(&pfd, 1, TIMEOUT), "Error polling");
		check(recv(sfd, buff_p, MAX_REQ, 0), "Error receiving");
	}
	close(sfd);
}
