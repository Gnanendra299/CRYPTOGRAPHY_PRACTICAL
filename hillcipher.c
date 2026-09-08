#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod26(int value)
{
    value = value % 26;

    if (value < 0)
        value += 26;

    return value;
}

int modInverse(int determinant)
{
    int i;

    determinant = mod26(determinant);

    for (i = 1; i < 26; i++)
    {
        if ((determinant * i) % 26 == 1)
            return i;
    }

    return -1;
}

void encrypt(char text[], int key[2][2])
{
    int i;
    int x, y;

    for (i = 0; text[i] != '\0'; i += 2)
    {
        x = text[i] - 'A';
        y = text[i + 1] - 'A';

        text[i] = mod26(key[0][0] * x +
                        key[0][1] * y) + 'A';

        text[i + 1] = mod26(key[1][0] * x +
                            key[1][1] * y) + 'A';
    }
}

void decrypt(char text[], int key[2][2])
{
    int determinant;
    int inverseDeterminant;
    int inverse[2][2];
    int i;
    int x, y;

    determinant = key[0][0] * key[1][1] -
                  key[0][1] * key[1][0];

    inverseDeterminant = modInverse(determinant);

    inverse[0][0] = mod26(inverseDeterminant * key[1][1]);
    inverse[0][1] = mod26(-inverseDeterminant * key[0][1]);
    inverse[1][0] = mod26(-inverseDeterminant * key[1][0]);
    inverse[1][1] = mod26(inverseDeterminant * key[0][0]);

    for (i = 0; text[i] != '\0'; i += 2)
    {
        x = text[i] - 'A';
        y = text[i + 1] - 'A';

        text[i] = mod26(inverse[0][0] * x +
                        inverse[0][1] * y) + 'A';

        text[i + 1] = mod26(inverse[1][0] * x +
                            inverse[1][1] * y) + 'A';
    }
}

int main()
{
    char message[100];
    int key[2][2];
    int i;

    printf("Enter the message (letters only): ");
    scanf("%99s", message);

    for (i = 0; message[i] != '\0'; i++)
    {
        message[i] = toupper(message[i]);
    }

    if (strlen(message) % 2 != 0)
    {
        strcat(message, "X");
    }

    printf("Enter the 2x2 key matrix:\n");

    printf("Enter key[0][0]: ");
    scanf("%d", &key[0][0]);

    printf("Enter key[0][1]: ");
    scanf("%d", &key[0][1]);

    printf("Enter key[1][0]: ");
    scanf("%d", &key[1][0]);

    printf("Enter key[1][1]: ");
    scanf("%d", &key[1][1]);

    int determinant = key[0][0] * key[1][1] -
                      key[0][1] * key[1][0];

    if (modInverse(determinant) == -1)
    {
        printf("\nInvalid key matrix!\n");
        printf("The determinant must have an inverse modulo 26.\n");
        return 1;
    }

    encrypt(message, key);

    printf("\nEncrypted message: %s\n", message);

    decrypt(message, key);

    printf("Decrypted message: %s\n", message);

    return 0;
}