#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <dirent.h>

#define PORT 4444
#define SIZE 4096
#define MAX_CLIENT 31

int server_socket, client_socket;
struct sockaddr_in server_address, client_address;
int address_length = sizeof(struct sockaddr_in);
int count;


void server_creation(int domain, int type, int protocol, int port, u_int32_t internet_address, int max_client)
{

    int option_value = 1;

    /* initializing a server socket */
    server_socket = socket(domain, type, protocol);
    if (server_socket < 0)
    {
        printf("Socket creation Unsuccessful");
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value)) < 0)
    {
        perror("setsockoption_value");
        exit(EXIT_FAILURE);
    }

    /* initializing server address */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = domain;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = internet_address;

    /* binding the address to the socket */
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Binding Unsuccessful");
    }

    /* server in the listen mode */
    if (listen(server_socket, max_client) < 0)
    {
        printf("Listen Unsuccessful");
    }
    printf("\nServer Ready\n");
}

void client_handle()
{
   while (1)
   {
        char buffer[SIZE];
        send(client_socket,"Enter a message:- ",sizeof("Enter a message:- "),0);
        recv(client_socket,buffer,sizeof(buffer),0);
        printf("Client %d says:- %s",count,buffer);
        if (!strcmp(buffer, "exit\n"))
        {
            printf("Disconnecting Client...");
            sleep(5);
            break;
        }
        send(client_socket,buffer,sizeof(buffer),0);
        memset(buffer,0,strlen(buffer));
   }
   printf("\nClient %d Disconnected\n",count);
}

int main(int argc,char* argv[])
{
    system("clear");
    server_creation(AF_INET, SOCK_STREAM, IPPROTO_TCP, PORT, INADDR_ANY, MAX_CLIENT);
       
    while (1)
    {
       client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_length);
       printf("Connection accepted from %s:%d\n",inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
       count++;
       pid_t pid=0;
       pid= fork();
       if (pid==0) //child process
       {
        close(server_socket);
        client_handle();
        close(client_socket);
        break;
       }
       else
       {
           close(client_socket);
       }
    }
    close(server_socket);
    
}
