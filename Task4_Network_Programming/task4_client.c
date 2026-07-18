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
        char request[BUFFER_SIZE];
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
        printf("type HELP to see available commands.\n");

        /* send commands until exit */

        while (1) {

                memset(request, 0, BUFFER_SIZE);

                memset(response, 0, BUFFER_SIZE);

                printf("\nenter command: ");

                fgets(request, BUFFER_SIZE, stdin);

                send(clientSocket, request, strlen(request), 0);

                if (recv(clientSocket, response, BUFFER_SIZE, 0) <= 0) {

                        printf("server disconnected.\n");

                        break;

                }

                printf("server response: %s\n", response);

                request[strcspn(request, "\n")] = '\0';

                if (strncmp(request, "EXIT", 4) == 0) {

                        break;

                }

        }
        /* close client socket */
        close(clientSocket);
        printf("client closed.\n");
        return 0;
}
