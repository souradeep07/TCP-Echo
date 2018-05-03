#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PENDING 5
#define SIZE64 64

int main()
{

	int sockserver;
	int sockclient;
	int recvMsgSize;
	char echobuffer[SIZE64];
	struct sockaddr_in clientaddr;
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=PF_INET;
	serveraddr.sin_port=htons(9502);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if((sockserver=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("Error creating socket\n");
		exit(1);
	}else{ printf("Socket instance created\n"); }


	if(bind(sockserver,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0){
		printf("error binding.\n");
		exit(1);
	}else{ printf("binding success\n"); }
	if(listen(sockserver,PENDING)<0){
		printf("Error opening port for listening\n");
		exit(1);
	}else{ printf("Listening\n"); }

	unsigned int clientl=sizeof(clientaddr);

	while(1){

		if ((sockclient = accept(sockserver, (struct sockaddr *) &clientaddr,&clientl)) < 0){
			printf("Error accepting\n");
			exit(1);
		}
		else{
			printf("ACCEPTED\n");
		}
		if ((recvMsgSize = recv(sockclient, &echobuffer, SIZE64, 0)) < 0){
			printf("recv() failed\n") ;
			exit(1);
		}
		else{
			printf("RECEIVED\n");
			echobuffer[recvMsgSize]='\0';
		}

		while (recvMsgSize > 0 )
		{
			if (send(sockclient, &echobuffer, recvMsgSize, 0) != recvMsgSize)
				printf("send() failed\n");
			else
				printf("Sent successful\n");

			if ((recvMsgSize = recv(sockclient, &echobuffer, SIZE64, 0)) < 0)
				printf("RECV() FAILED\n");
			else{
				printf("\nReceived by server: %s\n",echobuffer);
			}
		}
		close(sockclient);
	}
	close(sockserver);
}
