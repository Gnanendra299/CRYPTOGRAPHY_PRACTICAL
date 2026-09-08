#include <stdio.h>
#include <string.h>
#include <ctype.h>

void getOrder(char key[], int order[])
{
    int i, j;
    int len = strlen(key);

    for (i = 0; i < len; i++)
    {
        order[i] = 0;

        for (j = 0; j < len; j++)
        {
            if (key[j] < key[i] ||
                (key[j] == key[i] && j < i))
            {
                order[i]++;
            }
        }
    }
}

void encryptColumnar(char text[], char key[], char result[])
{
    int len = strlen(text);
    int cols = strlen(key);
    int rows = (len + cols - 1) / cols;
    int order[100];
    int i, r, c;
    int index = 0;

    getOrder(key, order);

    for (i = 0; i < cols; i++)
    {
        for (c = 0; c < cols; c++)
        {
            if (order[c] == i)
            {
                for (r = 0; r < rows; r++)
                {
                    int pos = r * cols + c;

                    if (pos < len)
                    {
                        result[index++] = text[pos];
                    }
                }
            }
        }
    }

    result[index] = '\0';
}

void decryptColumnar(char cipher[], char key[], char result[])
{
    int len = strlen(cipher);
    int cols = strlen(key);
    int rows = (len + cols - 1) / cols;
    int order[100];
    char table[100][100];

    int i, r, c;
    int index = 0;

    getOrder(key, order);

    /* Fill the table column by column */
    for (i = 0; i < cols; i++)
    {
        for (c = 0; c < cols; c++)
        {
            if (order[c] == i)
            {
                for (r = 0; r < rows; r++)
                {
                    int pos = r * cols + c;

                    if (pos < len)
                    {
                        table[r][c] = cipher[index++];
                    }
                }
            }
        }
    }

    /* Read table row by row */
    index = 0;

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < cols; c++)
        {
            int pos = r * cols + c;

            if (pos < len)
            {
                result[index++] = table[r][c];
            }
        }
    }

    result[index] = '\0';
}

int main()
{
    char message[1000];
    char key1[100];
    char key2[100];

    char intermediate[1000];
    char encrypted[1000];
    char decryptedStep1[1000];
    char decrypted[1000];

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    message[strcspn(message, "\n")] = '\0';

    printf("Enter first key: ");
    scanf("%99s", key1);

    printf("Enter second key: ");
    scanf("%99s", key2);

    /* First transposition */
    encryptColumnar(message, key1, intermediate);

    /* Second transposition */
    encryptColumnar(intermediate, key2, encrypted);

    printf("\nIntermediate text: %s\n", intermediate);
    printf("Encrypted message: %s\n", encrypted);

    /* Reverse second transposition */
    decryptColumnar(encrypted, key2, decryptedStep1);

    /* Reverse first transposition */
    decryptColumnar(decryptedStep1, key1, decrypted);

    printf("Decrypted message: %s\n", decrypted);

    return 0;
}