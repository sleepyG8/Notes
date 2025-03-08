#include <Windows.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    HANDLE newfile;
    char *pointer1 = argv[1];
    LPCSTR filename = "NOTES.txt";

    if (strcmp(pointer1, "new") == 0){
        newfile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (newfile == INVALID_HANDLE_VALUE) {
            printf("cannot create NOTES.txt file");
        }
    }
    else if (strcmp(pointer1, "add") == 0) {
        DWORD byteswritten;
        DWORD timestamp;

        char data[1025];
        char store[1025]; 

        time_t currenttime = time(0);
        char *timestring = ctime(&currenttime);

        char finalString[256];

        newfile = CreateFile(filename, FILE_APPEND_DATA, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        snprintf(finalString, sizeof(finalString), "%s\n", timestring);
        if (newfile == INVALID_HANDLE_VALUE) {
            printf("No NOTES.txt use ./notes.exe new");
        }
        printf("write your note:\n");
        fgets(data, sizeof(data), stdin);;
        strcpy(store, data);
        strcat(store, "\n\n");

        WriteFile(newfile, store, (DWORD)strlen(store), &byteswritten, NULL);
        WriteFile(newfile, finalString, (DWORD)strlen(finalString), &timestamp, NULL);
    } else if (strcmp(pointer1, "read") == 0) {
        char buffer[1025];
        DWORD bytedata;
        time_t currenttime = time(0);
        char *timestring = ctime(&currenttime);


        newfile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        ReadFile(newfile, buffer, (DWORD)sizeof(buffer) - 1, &bytedata , NULL );
        buffer[bytedata] = '\0';
        printf("Your current Notes as of %s\n %s", timestring,  buffer);
    
    } 

CloseHandle(newfile);
}