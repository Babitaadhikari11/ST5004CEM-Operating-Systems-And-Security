/*task 3 hospital patient file management system*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_USERS 3
/* stores login details and hospital user role */
struct User {
        char username[30];
        char password[30];
        char role[20];
};
/*SUBTASK: USER AUTHENTICATION*/
/* checks username and password entered by user */
int login(struct User users[], struct User *currentUser) {
        char username[30];
        char password[30];
      printf(" hospital secure file system login \n");
	printf("username: ");
        scanf("%s", username);
	printf("password: ");
        scanf("%s", password);
/*check login details*/
	for(int i= 0;i< MAX_USERS;i++) {
/*strcmp() is used for comparing two null terminated strings */
                if (strcmp(username,users[i].username)==0 &&
                    strcmp(password,users[i].password)==0){
/*successfull Login*/
			*currentUser= users[i];
                        printf("\nlogin successful.\n");
                        printf("logged in as: %s\n", currentUser->role);
                        return 1; /*return 1 if logged in*/
          }
        }
      printf("\nlogin failed. invalid username or password.\n");
        return 0;
}
/*SUB TASK: AUDIT LOGGING*/
/*records user activity in audit log file*/
void write_log(char username[],char action[],char filename[]){ /*TAKES 3 values for username action and what file was affected*/
        FILE *logFile; /*pointer */
        time_t currentTime;
        logFile=fopen("audit_log.txt", "a");/*open audit_log.txt*/
        if(logFile== NULL){
                printf("audit log could not be opened.\n");
                return;
        }
        time(&currentTime);
	/*this writes log record into audit_log text ie. username, action perfomed on which file*/
        fprintf(logFile, "user: %s | action: %s | file: %s | time: %s",username, action, filename, ctime(&currentTime));
        fclose(logFile);/*file close*/
}
/*SUB TASK: FILE CREATION*/
/* creates a new hospital patient file */
void create_file(struct User currentUser) {/*recieve current user*/
        FILE *file;
        char filename[50]; /*for file name*/
        printf("\n create hospital file \n");
        printf("enter file name to create: ");
        scanf("%s", filename);
        file =fopen(filename, "w");
        if (file== NULL) {
                printf("file could not be created.\n");
                write_log(currentUser.username, "failed to create file", filename);
                return;
     }
        fprintf(file, "hospital file '%s' created by %s\n", filename, currentUser.username);
        fclose(file);
        printf("file created successfully.\n");
        write_log(currentUser.username, "created file", filename);
}
/*SUB TASK: FILE WRITING*/
/* writes patient information into an existing hospital file */
void write_file(struct User currentUser) {
        FILE *file;
        char filename[50];
        char text[300];
        printf("\n write hospital file\n");
        printf("enter file name to write: ");
        scanf("%s", filename);
        file = fopen(filename, "a");
        if (file == NULL) {
                printf("file could not be opened.\n");
                write_log(currentUser.username, "failed to write file", filename);
                return;
        }
        getchar();/*remove leftover line*/
        printf("enter patient information: ");
        fgets(text, sizeof(text), stdin);
        fprintf(file, "%s", text);
        fclose(file);
        printf("file written successfully.\n");
        write_log(currentUser.username, "wrote to file", filename);
}
int main(){
        struct User users[MAX_USERS] = {{"admin", "admin123", "admin"},
                {"doctor", "doctor123", "doctor"},
                {"nurse", "nurse123", "nurse"}
        };
        struct User currentUser;
        int loggedIn;
        loggedIn= login(users, &currentUser);
	/*stop program if login fails*/
        if (loggedIn== 0){

                return 0;
        }
	/*record scessfull logins*/
	write_log(currentUser.username, "logged in", "system");
        printf("\nwelcome to hospital patient file management system.\n");
	/*logged in user can create file*/
	create_file(currentUser);
	write_file(currentUser);
        return 0;
}
