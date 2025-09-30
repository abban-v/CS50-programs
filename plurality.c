#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    char *name;
    int votes;
} candidate;

bool updatevote(char *vote,candidate candidates[],int candcount);
void print_winner(int candcount,candidate candidates[]);

int main(int argc, char *argv[])
{
    if (argc<2 || argc>9)
    {
        printf("Check amount of candidates.\n");
        return 1;
    }
    int candcount=argc-1;
    candidate candidates[candcount];
    for (int i=0;i<candcount;i++)
    {
        candidates[i].name=argv[i+1];
        candidates[i].votes=0;
    }
    int voters=get_int("Enter number of voters: ");
    for (int i=0;i<voters;i++)
    {
        char *choice=get_string("Enter vote: ");
        if (vote(choice,candidates,candcount)==false)
        {
            printf("Candidate not present.\n");
            i--;
        }
    }
    print_winner(candcount,candidates);
}

bool vote(char *vote,candidate candidates[],int candcount)
{
    for (int i=0;i<candcount;i++)
    {
        if (strcmp(candidates[i].name,vote)==0)
        {
            candidates[i].votes+=1;
            return true;
        }
    }
    return false;
}

void print_winner(int candcount,candidate candidates[])
{
    int maxvotes=0;
    for(int i=0;i<candcount;i++)
    {
        if (candidates[i].votes>maxvotes)
        {
            maxvotes=candidates[i].votes;
        }
    }
    for (int i=0;i<candcount;i++)
    {
        if (candidates[i].votes==maxvotes)
        {
            printf("%s\n",candidates[i].name);
        }
    }
}
