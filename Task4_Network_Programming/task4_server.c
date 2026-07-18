/* task 4 subtask 1: basic tcp server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define TOTAL_PATIENTS 3
/* stores sample hospital patient records */
struct Patient {
        int id;
        char name[50];
        char condition[50];
        char labStatus[80];
};
/* sample patient data used by hospital server */
struct Patient patients[TOTAL_PATIENTS] = {
        {101, "ramesh thapa", "fever", "blood test pending"},
        {102, "sita gurung", "fracture", "x-ray completed"},
        {103, "arjun kc", "breathing problem", "oxygen level test urgent"}
};
/*Authentication*/
int check_login(char username[], char password[], char role[]) {

        if (strcmp(username, "admin") == 0 &&

            strcmp(password, "admin123") == 0) {

                strcpy(role, "admin");

                return 1;

        }

        if (strcmp(username, "doctor") == 0 &&

            strcmp(password, "doctor123") == 0) {

                strcpy(role, "doctor");

                return 1;

        }

        if (strcmp(username, "nurse") == 0 &&

            strcmp(password, "nurse123") == 0) {

                strcpy(role, "nurse");

                return 1;

        }

        return 0;

}
/* searches patient details using patient id */
void find_patient(int id, char response[]) {
        int i;
        for (i = 0; i < TOTAL_PATIENTS; i++) {
                if (patients[i].id == id) {
                        sprintf(response,
                                "patient %d found: name %s, condition %s",
                                patients[i].id,
                                patients[i].name,
                                patients[i].condition);
                        return;
                }
        }
        strcpy(response, "patient id not found");
}


/* searches lab status using patient id */
void find_lab(int id, char response[]) {
        int i;
        for (i = 0; i < TOTAL_PATIENTS; i++) {
                if (patients[i].id == id) {
                        sprintf(response,
                                "lab status for patient %d: %s",
                                patients[i].id,
                                patients[i].labStatus);
                        return;
                }
        }
        strcpy(response, "lab record not found for this patient id");
}
/* processes client command and prepares server response */
void process_request(char request[], char response[], int *loggedIn, char role[]) {
        int patientId;
        char username[50];
        char password[50];
        char alertMessage[BUFFER_SIZE];

        /* validates empty request */
        if (strlen(request) == 0) {
                strcpy(response, "empty request is not allowed");
        }

        /* show available commands */
        else if (strncmp(request, "HELP", 4) == 0) {
                strcpy(response,
                       "commands: LOGIN user pass, PATIENT id, LAB id, BED, ALERT message, EXIT");
        }

        /* handles login command */
        else if (sscanf(request, "LOGIN %s %s", username, password) == 2) {
                if (check_login(username, password, role) == 1) {
                        *loggedIn = 1;
                        sprintf(response, "login successful. role: %s", role);
                } else {
                        strcpy(response, "login failed. invalid username or password");
                }
        }

        /* added: block hospital commands before login */
        else if (*loggedIn == 0) {
                strcpy(response, "please login first using LOGIN username password");
        }

        /* handle patient information request */
        else if (sscanf(request, "PATIENT %d", &patientId) == 1) {
                if (patientId <= 0) {
                        strcpy(response, "invalid patient id");
                } else {
                        find_patient(patientId, response);
                }
        }

        /* handle lab status request */
        else if (sscanf(request, "LAB %d", &patientId) == 1) {
                if (patientId <= 0) {
                        strcpy(response, "invalid patient id");
                } else {
                        find_lab(patientId, response);
                }
        }

        /* handle bed availability request */
        else if (strncmp(request, "BED", 3) == 0) {
                strcpy(response,
                       "beds available: emergency 4, icu 2, general 8");
        }

        /* handle emergency alert message */
        else if (sscanf(request, "ALERT %[^\n]", alertMessage) == 1) {
                sprintf(response,
                        "emergency alert received: %s",
                        alertMessage);
        }

        /* handle exit command */
        else if (strncmp(request, "EXIT", 4) == 0) {
                strcpy(response, "goodbye. connection closed");
        }

        /* handle invalid command */
        else {
                strcpy(response,
                       "invalid command. type HELP to see valid commands");
        }
}
int main() {
        int serverSocket;
        int clientSocket;
	/* added: stores login status of connected client */
        int loggedIn = 0;
        struct sockaddr_in serverAddress;
        struct sockaddr_in clientAddress;
        socklen_t clientLength;
       /* char buffer[BUFFER_SIZE];*/
	char request[BUFFER_SIZE];
        char response[BUFFER_SIZE];
	/* added: stores role after successful login */
        char role[30] = "guest";
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
	/* keep receiving commands until client exits */
        while (1) {
                memset(request, 0, BUFFER_SIZE);
                memset(response, 0, BUFFER_SIZE);
                /* receive request from client */
                if (recv(clientSocket, request, BUFFER_SIZE, 0) <= 0) {
                        printf("client disconnected.\n");
                        break;
                }
                /* remove new line from input */
                request[strcspn(request, "\n")] = '\0';
                printf("client request: %s\n", request);
		/* added: process request with login status and role */

                process_request(request, response, &loggedIn, role);
                /* process command and prepare response */
               /* process_request(request, response);*/
                /* send response back to client */
                send(clientSocket, response, strlen(response), 0);
                printf("response sent to client.\n");
                /* close connection if client sends exit */
                if (strncmp(request, "EXIT", 4) == 0) {
                        break;
                }
        }

        /* receive message from client 
        memset(buffer, 0, BUFFER_SIZE);
        recv(clientSocket, buffer, BUFFER_SIZE, 0);

        printf("client request: %s\n", buffer);

        /* send response to client 
        send(clientSocket,
             "message received by hospital server",
             strlen("message received by hospital server"),
             0);

        printf("response sent to client.\n");
*/

        close(clientSocket);
        close(serverSocket);

        printf("server closed.\n");

        return 0;
}
