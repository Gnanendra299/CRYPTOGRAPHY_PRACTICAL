#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(char key[])
{
    int used[26] = {0};
    int row = 0, col = 0;
    int i;
    char ch;

    for (i = 0; key[i] != '\0'; i++)
    {
        ch = toupper(key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A'])
        {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;

            col++;

            if (col == 5)
            {
                col = 0;
                row++;
            }
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A'])
        {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;

            col++;

            if (col == 5)
            {
                col = 0;
                row++;
            }
        }
    }
}

void displayMatrix()
{
    int i, j;

    printf("\nPlayfair Matrix:\n");

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%c ", matrix[i][j]);
        }

        printf("\n");
    }
}

void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void prepareText(char input[], char output[])
{
    int i = 0;
    int j = 0;

    while (input[i] != '\0')
    {
        if (isalpha(input[i]))
        {
            char first = toupper(input[i]);

            if (first == 'J')
                first = 'I';

            if (input[i + 1] != '\0' && isalpha(input[i + 1]))
            {
                char second = toupper(input[i + 1]);

                if (second == 'J')
                    second = 'I';

                output[j++] = first;

                if (first == second)
                {
                    output[j++] = 'X';
                    i++;
                }
                else
                {
                    output[j++] = second;
                    i += 2;
                }
            }
            else
            {
                output[j++] = first;
                output[j++] = 'X';
                i++;
            }
        }
        else
        {
            i++;
        }
    }

    output[j] = '\0';
}

void encrypt(char text[])
{
    int i;
    int r1, c1, r2, c2;

    for (i = 0; text[i] != '\0'; i += 2)
    {
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2)
        {
            text[i] = matrix[r1][(c1 + 1) % 5];
            text[i + 1] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            text[i] = matrix[(r1 + 1) % 5][c1];
            text[i + 1] = matrix[(r2 + 1) % 5][c2];
        }
        else
        {
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}

void decrypt(char text[])
{
    int i;
    int r1, c1, r2, c2;

    for (i = 0; text[i] != '\0'; i += 2)
    {
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2)
        {
            text[i] = matrix[r1][(c1 + 4) % 5];
            text[i + 1] = matrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            text[i] = matrix[(r1 + 4) % 5][c1];
            text[i + 1] = matrix[(r2 + 4) % 5][c2];
        }
        else
        {
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}

int main()
{
    char key[100];
    char input[200];
    char prepared[200];

    printf("Enter the key: ");
    scanf("%99s", key);

    printf("Enter the message: ");
    scanf("%199s", input);

    generateMatrix(key);

    displayMatrix();

    prepareText(input, prepared);

    printf("\nPrepared message: %s\n", prepared);

    encrypt(prepared);

    printf("Encrypted message: %s\n", prepared);

    decrypt(prepared);

    printf("Decrypted message: %s\n", prepared);

    return 0;
}