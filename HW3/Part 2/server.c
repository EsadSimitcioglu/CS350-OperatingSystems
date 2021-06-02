#include <stdio.h>
#include <string.h>    
#include <stdlib.h>    
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>    
#include <pthread.h> 
#include <time.h>

void *server_handler (void *fd_pointer);

int client_size = 0;
time_t now;
struct tm *tm;


char *p1 = "1"; //protocol code for waiting client can enter or not
char *p2 = "2"; //protocol code for 3rd client
char *p3 = "3"; //protocol code for client can't enter the server
char *p4 = "4"; //protocol code for client's time is up.



int main()
{
 int listenfd, connfd, *new_sock;
 socklen_t clilen;
 struct sockaddr_in cliaddr, servaddr; 

 listenfd = socket(AF_INET,SOCK_STREAM,0);
 
 if (listenfd == -1)
 {
     perror("Could not create Socket \n"); 
 }
 
 puts("Socket Created");
 
 bzero(&servaddr,sizeof (servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = INADDR_ANY;
 servaddr.sin_port = htons(9999);
 
 if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
 {
    perror("bind failed");
    return 1;
}

puts("bind success");
listen(listenfd, 5);

puts("Waiting for connections");
clilen = sizeof(cliaddr);

while ((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)))
{

    printf("Client Size : %d\n",client_size);


    if(client_size==2){
        client_size++;
        write(connfd,p2,1);

        while(client_size==3){
            sleep(2);
            if(client_size==1){
                write(connfd,p1,1);
                break;
            }
        }
    }

    else if(client_size>=3){
        write(connfd,p3,1);
        close(connfd);
    }

    write(connfd,p1,strlen(p1));
    

    puts("Connection accepted");
    client_size++;
    now = time(0);
    if ((tm = localtime (&now)) == NULL) {
        printf ("Error extracting time stuff\n");
        return 1;
    }
    pthread_t server_thread;
    new_sock = malloc(1);
    *new_sock = connfd;
    pthread_create(&server_thread,NULL,server_handler,((void*) new_sock));
}


if (connfd < 0)
{
	perror("Accecpt Failed");
	return 1;
}
return 0;
}

void *server_handler (void *fd_pointer)
{
      //printf("Hello Server Handler \n");
  int sock = *(int *)fd_pointer;
  int number = client_size;
  int start_time = tm->tm_sec;
      //char client_message[2000];
  int read_size, write_size;
  char *message;
  static char client_message[2000];
  message = " \nHello Server Handler \n";
      //message2 = "Test Send \n";


  static int send_once = 0;
  if (send_once < 1)
  {
      //write(sock,message,strlen(message));
      send_once++;
  }

  while((read_size = recv(sock,client_message,2000,0)) > 0)
  {
    now = time(0);
    tm = localtime (&now);

    int current_time = tm->tm_sec;

    if( ((current_time) >= (start_time+10)) ) {
        printf("Client %d disconnected\n",number);
        write(sock,p4,strlen(client_message));
        close(sock);
        client_size--;
        fflush(stdout);
        pthread_exit(NULL);
        break;
    }

    if((start_time>=50 && start_time<60) && (current_time>=0 && current_time<10) && (current_time+60) >= (start_time+10)){
        printf("Client %d disconnected\n",number);
        write(sock,p4,strlen(client_message));
        close(sock);
        client_size--;
        fflush(stdout);
        pthread_exit(NULL);
        break;
    }

    printf("Client %d message is : %s \n",number, client_message);
    write(sock,client_message,strlen(client_message));
    memset(client_message, 0, sizeof (client_message));
}

if(read_size == 0)
{
    printf("Client %d disconnected\n",number);
    client_size--;
    fflush(stdout);
}

free(fd_pointer);

}