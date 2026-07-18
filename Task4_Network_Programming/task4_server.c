/* task 4 subtask 1: basic tcp server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
        int serverSocket;
        int clientSocket;
        struct sockaddr_in serverAddress;
        struct sockaddr_in clientAddress;
        socklen_t clientLength;
        char buffer[BUFFER_SIZE];

        /* create socket for server */
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (serverSocket < 0) {
                printf("socket creation failed.\n");
                return 1;
        }

        printf("server socket created successfully.\n");

        /* set server address details */
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(PORT);

        /* bind socket with port number */
        if (bind(serverSocket,
                 (struct sockaddr *)&serverAddress,
                 sizeof(serverAddress)) < 0) {
                printf("bind failed.\n");
                close(serverSocket);
                return 1;
        }

        printf("server bind successful on port %d.\n", PORT);

        /* listen for client connection */
        if (listen(serverSocket, 5) < 0) {
                printf("listen failed.\n");
                close(serverSocket);
                return 1;
        }

        printf("hospital server is waiting for client connection...\n");

        clientLength = sizeof(clientAddress);

        /* accept client connection */
        clientSocket = accept(serverSocket,
                              (struct sockaddr *)&clientAddress,
                              &clientLength);

        if (clientSocket < 0) {
                printf("client connection failed.\n");
                close(serverSocket);
                return 1;
        }

        printf("client connected successfully.\n");

        /* receive message from client */
        memset(buffer, 0, BUFFER_SIZE);
        recv(clientSocket, buffer, BUFFER_SIZE, 0);

        printf("client request: %s\n", buffer);

        /* send response to client */
        send(clientSocket,
             "message received by hospital server",
             strlen("message received by hospital server"),
             0);

        printf("response sent to client.\n");

        close(clientSocket);
        close(serverSocket);

        printf("server closed.\n");

        return 0;
}
