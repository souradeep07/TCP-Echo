#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define SIZE64 64


int main()
{
	int sock;
	char echobuffer[SIZE64];
        char buffer[100];
	struct sockaddr_in clientaddr;
	printf("Enter text to send: ");
	scanf ("%[^\n]%*c", buffer);


	
	memset(&clientaddr,0,sizeof(clientaddr));
	clientaddr.sin_family=PF_INET;
	clientaddr.sin_port=htons(9502);
	clientaddr.sin_addr.s_addr=htonl(INADDR_ANY);




	if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("Error creating socket Instance\n");
		exit(1);
	}else{
		printf("Instance of socket created successfully\n");
	}	

	if(connect(sock,(struct sockaddr *)&clientaddr,sizeof(clientaddr))<0){
		printf("Connection failed\n");
		exit(1);
	}else{
		printf("Connected to Server\n");
	}
	

	int stringlength=strlen(buffer);
	
	if(send(sock,&buffer,stringlength,0)!=stringlength){
		printf("ERROR SENDING\n");
		exit(1);
	}else{
		printf("Sent\n");
	}
	
	int totalbytes=0,bytesreceived=0;
	while(totalbytes<stringlength)
	{
		if((bytesreceived=recv(sock,&echobuffer,SIZE64-1,0))<=0){
			printf("Error receiving\n");
			exit(1);
		}else{
			printf("Bytes Received:%d\n",bytesreceived);
		}
	
		
		totalbytes+=bytesreceived;
		echobuffer[bytesreceived]='\0';
		printf("\nReceived from Server: %s\n",echobuffer);

	}

															        
	close (sock);
}
																			
