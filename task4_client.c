/* task 4 subtask 2: basic tcp client */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main() {
        int clientSocket;
        struct sockaddr_in serverAddress;
        char message[BUFFER_SIZE];
        char response[BUFFER_SIZE];
        /* create socket for client */
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket < 0) {
                printf("socket creation failed.\n");
                return 1;
        }
        printf("client socket created successfully.\n");
        /* set server address details */
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        /* connect client to server */
        if (connect(clientSocket,
                    (struct sockaddr *)&serverAddress,
                    sizeof(serverAddress)) < 0) {
                printf("connection to server failed.\n");
                close(clientSocket);
                return 1;
        }
        printf("connected to hospital server successfully.\n");
        /* take request message from hospital staff */
        printf("enter message for server: ");
        fgets(message, BUFFER_SIZE, stdin);
        /* send message to server */
        send(clientSocket, message, strlen(message), 0);
        printf("request sent to server.\n");
        /* receive response from server */
        memset(response, 0, BUFFER_SIZE);
        recv(clientSocket, response, BUFFER_SIZE, 0);
        printf("server response: %s\n", response);
        /* close client socket */
        close(clientSocket);
        printf("client closed.\n");
        return 0;
}
