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

#define PORT 4444
#define SIZE 4096

int client_socket;
struct sockaddr_in server_address, client_address;
int address_length = sizeof(struct sockaddr_in);

void client_creation(int domain, int type, int protocol, int port, u_int32_t internet_address)
{

    /* initializing a server socket */
    client_socket = socket(domain, type, protocol);
    if (client_socket < 0)
    {
        printf("Socket creation Unsuccessful");
    }

    /* initializing server address */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = domain;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = internet_address;
}

int main()
{
    system("clear");
    client_creation(AF_INET, SOCK_STREAM, IPPROTO_TCP, PORT, INADDR_ANY);
    /* code */
    int ret = connect(client_socket, (struct sockaddr *)&server_address, address_length);

    while (1)
    {
        /* code */
        char buffer[SIZE];
        bzero(buffer, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);
        printf("%s", buffer);

        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, sizeof(buffer), 0);
        if (!strcmp(buffer, "exit\n"))break;

        bzero(buffer, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);
        printf("Server says:- %s", buffer);
        bzero(buffer, sizeof(buffer));
    }

    close(client_socket);
}
