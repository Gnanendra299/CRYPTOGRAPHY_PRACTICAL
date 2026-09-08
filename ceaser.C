#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], int key){
    int i;
for (i = 0; text[i] != '\0'; i++){
        if (isupper(text[i])){
            text[i] = ((text[i] - 'A' + key) % 26) + 'A';}
        else if (islower(text[i])){
            text[i] = ((text[i] - 'a' + key) % 26) + 'a';}
    }
}

void decrypt(char text[], int key){
    int i;
for (i = 0; text[i] != '\0'; i++){
        if (isupper(text[i])){
            text[i] = ((text[i] - 'A' - key + 26) % 26) + 'A';}
        else if (islower(text[i])){
            text[i] = ((text[i] - 'a' - key + 26) % 26) + 'a';}
    }
}

int main(){
    char message[100];
    int key;

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the key: ");
    scanf("%d", &key);

    key = key % 26;

    encrypt(message, key);

    printf("\nEncrypted message: %s", message);

    decrypt(message, key);

    printf("Decrypted message: %s", message);

    return 0;
}