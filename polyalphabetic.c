#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], char key[])
{
    int i, j = 0;
    int keyLength = strlen(key);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyBase = isupper(key[j % keyLength]) ? 'A' : 'a';

            text[i] = ((text[i] - base +
                        (key[j % keyLength] - keyBase)) % 26) + base;

            j++;
        }
    }
}

void decrypt(char text[], char key[])
{
    int i, j = 0;
    int keyLength = strlen(key);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyBase = isupper(key[j % keyLength]) ? 'A' : 'a';

            text[i] = ((text[i] - base -
                        (key[j % keyLength] - keyBase) + 26) % 26) + base;

            j++;
        }
    }
}

int main()
{
    char message[100];
    char key[100];

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the key: ");
    scanf("%99s", key);

    encrypt(message, key);

    printf("\nEncrypted message: %s", message);

    decrypt(message, key);

    printf("Decrypted message: %s", message);

    return 0;
}