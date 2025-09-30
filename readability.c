#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
float read_level(string s);
int main(void)
{
    string sentences=get_string("Enter the sentences: ");
    float index=read_level(sentences);
    int indexint= round(index);
    if (indexint<1)
    {
        printf("Before Grade 1\n");
    }
    else if (indexint>=16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n",indexint);
    }


}
float read_level(string s)
{
    int letters=0;
    int words=0;
    int sentences=0;
    for(int i=0,n=strlen(s);i<strlen(s);i++)
    {
        if (isspace(s[i]))
        {
            if ((i!=0 && isspace(s[i-1]))||i==0||i==n-1)
            {
                continue;
            }
            words+=1;
        }
        else if (isalpha(s[i]))
        {
            letters+=1;
        }
        else if (s[i]=='.'||s[i]=='?'||s[i]=='!')
        {
            if (s[i+1]==0)
            {
                words+=1;
            }
            if (s[i-1]=='.')
            {
                continue;
            }
            sentences+=1;
        }
    }
    printf("%i %i %i\n", letters,words,sentences);
    float standard=100.0;
    float factor=standard/words;
    float L=factor*letters;
    float S=factor*sentences;
    printf("%f %f %f\n",L,S, 0.0588 * L - 0.296 * S - 15.8);
    return 0.0588 * L - 0.296 * S - 15.8;
}
