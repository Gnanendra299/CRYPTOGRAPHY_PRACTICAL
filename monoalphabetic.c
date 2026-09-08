#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], char key[])
{
    int i;
    char ch;

    for (i = 0; text[i] != '\0'; i++)
    {
        ch = text[i];

        if (isupper(ch))
        {
            text[i] = toupper(key[ch - 'A']);
        }
        else if (islower(ch))
        {
            text[i] = tolower(key[ch - 'a']);
        }
    }
}

void decrypt(char text[], char key[])
{
    int i, j;
    char ch;

    for (i = 0; text[i] != '\0'; i++)
    {
        ch = text[i];

        if (isupper(ch))
        {
            for (j = 0; j < 26; j++)
            {
                if (toupper(key[j]) == ch)
                {
                    text[i] = 'A' + j;
                    break;
                }
            }
        }
        else if (islower(ch))
        {
            for (j = 0; j < 26; j++)
            {
                if (tolower(key[j]) == ch)
                {
                    text[i] = 'a' + j;
                    break;
                }
            }
        }
    }
}

int main()
{
    char message[100];
    char key[27];

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the substitution key: ");
    scanf("%26s", key);

    if (strlen(key) != 26)
    {
        printf("Error: Key must contain exactly 26 letters.\n");
        return 1;
    }

    encrypt(message, key);

    printf("\nEncrypted message: %s", message);

    decrypt(message, key);

    printf("Decrypted message: %s", message);

    return 0;
}