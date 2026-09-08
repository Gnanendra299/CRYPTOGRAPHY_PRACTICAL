#include <stdio.h>
#include <string.h>

void encrypt(char text[], int rails, char result[])
{
    int len = strlen(text);
    int row = 0;
    int direction = 1;
    int index = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        result[index++] = text[i];

        if (row == 0)
            direction = 1;
        else if (row == rails - 1)
            direction = -1;

        row += direction;
    }

    result[index] = '\0';
}

void decrypt(char cipher[], int rails, char result[])
{
    int len = strlen(cipher);
    int pattern[1000];
    int row = 0;
    int direction = 1;
    int i, r;
    int index = 0;

    /* Determine the rail pattern */
    for (i = 0; i < len; i++)
    {
        pattern[i] = row;

        if (row == 0)
            direction = 1;
        else if (row == rails - 1)
            direction = -1;

        row += direction;
    }

    /* Read ciphertext row by row */
    for (r = 0; r < rails; r++)
    {
        for (i = 0; i < len; i++)
        {
            if (pattern[i] == r)
            {
                result[i] = cipher[index++];
            }
        }
    }

    result[len] = '\0';
}

int main()
{
    char message[1000];
    char encrypted[1000];
    char decrypted[1000];
    int rails;

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    message[strcspn(message, "\n")] = '\0';

    printf("Enter the number of rails: ");
    scanf("%d", &rails);

    if (rails < 2)
    {
        printf("Number of rails must be at least 2.\n");
        return 1;
    }

    if (rails >= strlen(message))
    {
        printf("Number of rails must be less than the message length.\n");
        return 1;
    }

    encrypt(message, rails, encrypted);

    printf("\nEncrypted message: %s\n", encrypted);

    decrypt(encrypted, rails, decrypted);

    printf("Decrypted message: %s\n", decrypted);

    return 0;
}