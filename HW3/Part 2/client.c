#include<stdio.h> 
#include<unistd.h>
#include<string.h>    
#include<sys/socket.h>    
#include<arpa/inet.h> 

int main()
{
	int sockfd;
	char buffer[1000];
	char server_reply[2000];
	char server_protocol[1];
	ssize_t n;
	
	struct sockaddr_in servaddr; 

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		perror("Could not create socket");
	}
	
	printf("Created Socket \n");
	bzero(&servaddr,sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr));
	
	while (1)
	{

		memset(server_protocol, 0, sizeof(server_protocol));			

		if(recv(sockfd,server_protocol,1,0 ) < 0)
		{
			puts("Error");
			break;
		}

		if(server_protocol[0]=='2'){
			printf("You are in queue, please wait \n");	
			while(server_protocol[0]=='2'){

				recv(sockfd,server_protocol,1,0) >= 0;	
				sleep(2);

				if(server_protocol[0]=='1'){
					break;
				}
			}
			break;
		}
		else if(server_protocol[0]=='3'){
			printf("Server is full. Please try again later\n");
			return 0;
		}
		else{
			break;
		}
	}

	puts("Connection accepted");

	puts("Press q for exit");

	while(1){

		printf("Enter a Message: ");
		scanf("%s",buffer);

		if(!strcmp(buffer,"q")){
			puts("Leaving server...");
			break;
		}
		
		if (send(sockfd,buffer,strlen(buffer),0) < 0)
		{
			printf("Error \n");
			return 1;
		}
		if(recv(sockfd,server_reply,2000,0 ) < 0)
		{
			puts("Error");
			break;
		}

		if(!strcmp(server_reply,"4")){
			puts("Time is up. Leaving server...");
			break;
		}

		printf("Server Reply: %s \n",server_reply );
		memset(server_reply, 0, sizeof (server_reply));

	}



	close(sockfd);
	return 0;	 
}
