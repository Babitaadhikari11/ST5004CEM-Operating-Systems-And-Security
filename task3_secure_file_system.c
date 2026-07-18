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
	/*file permissions*/
	 int canCreate;
        int canWrite;
        int canRead;
        int canDelete;
	/*ENCRYPTION permission*/
	int canEncrypt;
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
	        /* checks if current user is allowed to create files */
        if (currentUser.canCreate == 0) {
                printf("permission denied. you cannot create files.\n");
                write_log(currentUser.username, "permission denied create file", "none");
                return;
        }
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
	        /* checks if current user is allowed to write files */
        if (currentUser.canWrite == 0) {
                printf("permission denied. you cannot write files.\n");
                write_log(currentUser.username, "permission denied write file", "none");
                return;
        }
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
/*SUB TASK: FILE READING*/
/* reads and displays hospital file content */
void read_file(struct User currentUser) {
        FILE *file;
        char filename[50];
        int ch; /* FOR STORING one character at a time*/
        printf("\n read hospital file\n");
	        /* checks if current user is allowed to read files */
        if (currentUser.canRead == 0) {
                printf("permission denied. you cannot read files.\n");
                write_log(currentUser.username, "permission denied read file", "none");
                return;
        }
        printf("enter file name to read: ");
        scanf("%s", filename);
        file = fopen(filename, "r");/*r enables read mode*/
        if (file == NULL) {
                printf("file could not be opened or does not exist.\n");
                write_log(currentUser.username, "failed to read file", filename);
              return;
        }
        printf("\n file content \n");
        while ((ch = fgetc(file)) != EOF) { /*EOF means end of file*/
                printf("%c", ch);
        }
        printf("\nend of file \n");
        fclose(file);
        write_log(currentUser.username, "read file", filename);
}
/*SUB TASK: FILE DELETION*/
/* deletes an existing hospital file */
void delete_file(struct User currentUser) {
        char filename[50];
        printf("\ndelete hospital file \n");
	        /* checks if current user is allowed to delete files */
        if (currentUser.canDelete == 0) {
                printf("permission denied. you cannot delete files.\n");
                write_log(currentUser.username, "permission denied delete file", "none");
                return;
        }
        printf("enter file name to delete: ");
        scanf("%s", filename);
        if (remove(filename) == 0) {
                printf("file deleted successfully.\n");
                write_log(currentUser.username, "deleted file", filename);
        } else {
                printf("file could not be deleted or does not exist.\n");
                write_log(currentUser.username, "failed to delete file", filename);
        }
}
/*SUB TASK: ENCRYTPION.DECRITPION*/
/* encrypts or decrypts a hospital file using simple xor method */
void encrypt_decrypt_file(struct User currentUser) {
        FILE *file;
        char filename[50];
        char data[1000];
        int key = 7; /*KEY USED FOR ENCRYption and decryption*/
        int i = 0;/*tracking current position*/
        int ch;
        printf("\n encrypt or decrypt hospital file \n");
        /* checks if current user is allowed to encrypt or decrypt files */
        if (currentUser.canEncrypt == 0) {
                printf("permission denied. you cannot encrypt or decrypt files.\n");
                write_log(currentUser.username,
                          "permission denied encrypt or decrypt file",
                          "none");
                return;
        }
        printf("enter file name to encrypt or decrypt: ");
        scanf("%s", filename);
        file = fopen(filename, "r");
        if (file == NULL) {
                printf("file could not be opened or does not exist.\n");
                write_log(currentUser.username,
                          "failed to encrypt or decrypt file",
                          filename);
                return;
        }
        /* reads file and changes each character using xor key */
        while ((ch = fgetc(file)) != EOF && i < 999) {
                data[i] = ch ^ key;
                i++;
        }
        data[i] = '\0';
        fclose(file);
        file = fopen(filename, "w");
        if (file == NULL) {
                printf("file could not be opened for saving.\n");
                write_log(currentUser.username,
                          "failed to save encrypted or decrypted file",
                          filename);
                return;
        }
        fprintf(file, "%s", data);
        fclose(file);
        printf("file encryption or decryption completed.\n");
        write_log(currentUser.username,
                  "encrypted or decrypted file",
                  filename);
}

int main(){
/*encryptiiona decription added for doctor, nurse and admin*/
        struct User users[MAX_USERS] = {{"admin", "admin123", "admin",1,1,1,1,1},
	/*permission 1=allowed, 0 =not allowed*/
                {"doctor", "doctor123", "doctor",1,1,1,0,1},
                {"nurse", "nurse123", "nurse",0,0,1,0,0}
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
	/*READING FILE CONTENT*/
	read_file(currentUser);
	delete_file(currentUser);
	/* allows logged in user to encrypt or decrypt a hospital file */
	encrypt_decrypt_file(currentUser);
	/* read file after encryption */

read_file(currentUser);

/* decrypt the same hospital file second time */

encrypt_decrypt_file(currentUser);

/* read file again after decryption */

read_file(currentUser);
        return 0;
}
