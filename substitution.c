#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int lettercheck(char *arg);
int search(char letter);

int main(int argc, char *argv[])
{
    if (argc!=2)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }
    if (lettercheck(argv[1])==0)
    {
        return 1;
    }
    char *key=argv[1];
    char *plaintext=get_string("Enter text to be ciphered: ");
    char *ciphertext=malloc(strlen(plaintext)+1);
    for (int i=0,n=strlen(plaintext)+1;i<n;i++)
    {
        char letter=plaintext[i];
        int index;
        if (isalpha(letter))
        {
            index=search(letter);
            if (index==-1)
            {
                printf("ERROR\n");
                return 1;
            }
        }
        else
        {
            ciphertext[i]=plaintext[i];
            continue;
        }
        if islower(plaintext[i])
        {
            ciphertext[i]=tolower(key[index]);
        }
        else
        {
            ciphertext[i]=toupper(key[index]);
        }
    }
    printf("ciphertext: %s\n",ciphertext);
    free(ciphertext);
}

int lettercheck(char *arg)
{
    if (strlen(arg)!=26)
    {
        printf("Key should be 26 letters.\n");
        return 0;
    }
    for (int i=0,n=strlen(arg);i<n;i++)
    {
        char letter=arg[i];
        if (!isalpha(letter))
        {
            printf("Only letters\n");
            return 0;
        }
        for (int j=0;j<i;j++)
        {
            if (letter==tolower(arg[j]) || letter==toupper(arg[j]))
            {
                printf("Repetition of letters\n");
                return 0;
            }
        }
    }
    return 1;
}

int search(char letter)
{
    if islower(letter)
    {
        return letter-'a';
    }
    else if isupper(letter)
    {
        return letter-'A';
    }
    else
    {
        return -1;
    }
}
