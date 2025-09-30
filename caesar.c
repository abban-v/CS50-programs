#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int digcheck(char *arg);
void cipher(char *plaintext, char *ciphertext, int key);

int main(int argc, char *argv[])
{
    if (argc!=2 || digcheck(argv[1])==0)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    int key=atoi(argv[1]);
    key%=26;
    char *plaintext=get_string("Enter text to be ciphered: ");
    char *ciphertext=malloc(strlen(plaintext)+1);
    cipher(plaintext,ciphertext,key);
    printf("ciphertext: %s\n",ciphertext);
    free(ciphertext);
}

int digcheck(char *arg)
{
    for (int i=0,n=strlen(arg);i<n;i++)
    {
        if (!isdigit(arg[i]))
        {
            return 0;
        }
    }
    return 1;
}

void cipher(char *plaintext, char *ciphertext, int key)
{
    for(int i=0,n=strlen(plaintext)+1;i<n;i++)
    {
        char cipherletter;
        if (isalpha(plaintext[i]))
        {
            cipherletter=plaintext[i]+key;
            if (tolower(cipherletter)>'z')
            {
                cipherletter-=26;
            }
            if (tolower(cipherletter)<'a')
            {
                cipherletter+=26;
            }
        }
        else
        {
            cipherletter=plaintext[i];
        }
        ciphertext[i]=cipherletter;
    }
}
