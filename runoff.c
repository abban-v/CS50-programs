#include <stdio.h>
#include <string.h>
#include <cs50.h>

typedef struct
{
    char *name;
    int votes;
    bool eliminated;
} candidate;

void get_vote(int voters,int candcount,char *choices[voters][candcount],candidate candidates[]);
bool search(char *votedcandidate, candidate candidates[],int candcount);
void tabulate(candidate candidates[],int candcount,int voters,char *choices[voters][candcount]);
bool winner(candidate candidates[],int candcount,int voters);
void print_winner(candidate candidates[],int candcount);
bool repeatcand(char *votedcandidate,int candcount,int voters,char *choices[voters][candcount],int i,int j);

int main(int argc, char *argv[])
{
    if (argc<2)
    {
        printf("Insufficient number of arguments.\n");
        return 1;
    }
    int candcount=argc-1;
    candidate candidates[candcount];
    for (int i=0;i<candcount;i++)
    {
        candidates[i].name=argv[i+1];
        candidates[i].votes=0;
        candidates[i].eliminated=false;
    }
    int voters=get_int("Enter the number of voters: ");
    char *choices[voters][candcount];
    get_vote(voters,candcount,choices,candidates);
    do
    {
        tabulate(candidates,candcount,voters,choices);
    }
    while (winner(candidates,candcount,voters)==false);
    print_winner(candidates,candcount);
}

void get_vote(int voters,int candcount,char *choices[voters][candcount],candidate candidates[])
{
    for(int i=0;i<voters;i++)
    {
        printf("Voter %i:\n",i+1);
        for (int j=0;j<candcount;j++)
        {
            char *votedcandidate=get_string("Enter rank %i candidate name: ",j+1);
            if (repeatcand(votedcandidate,candcount,voters,choices,i,j)==true)
            {
                printf("Candidate cannot be repeated.\n");
                j--;
                continue;
            }
            if (search(votedcandidate,candidates,candcount)==false)
            {
                printf("Candidate not found\n");
                j--;
                continue;
            }
            else
            {
                choices[i][j]=votedcandidate;
            }
        }
    }
}

bool search(char *votedcandidate, candidate candidates[],int candcount)
{
    for (int i=0;i<candcount;i++)
    {
        if (strcmp(votedcandidate,candidates[i].name)==0)
        {
            return true;
        }
    }
    return false;
}

void tabulate(candidate candidates[],int candcount,int voters,char *choices[voters][candcount])
{
    for (int i=0;i<candcount;i++)
    {
        candidates[i].votes=0;
    }
    for (int i=0;i<voters;i++)
    {
        int rank=0;
        char *currentcand=choices[i][rank];
        for (int j=0;j<candcount;j++)
        {
            if (strcmp(currentcand,candidates[j].name)==0)
            {
                if (candidates[j].eliminated==false)
                {
                    candidates[j].votes++;
                    break;
                }
                else
                {
                    rank++;
                    if (rank>=candcount)
                    {
                        break;
                    }
                    currentcand=choices[i][rank];
                    j=-1;
                    continue;
                }
            }
        }
    }
}

bool winner(candidate candidates[],int candcount,int voters)
{
    int minvotes=voters;
    int maxvotes=0;
    for (int i=0;i<candcount;i++)
    {
        if (candidates[i].votes>maxvotes)
        {
            maxvotes=candidates[i].votes;
        }
        if (candidates[i].votes<minvotes)
        {
            minvotes=candidates[i].votes;
        }
    }
    if (maxvotes>(voters/2))
    {
        return true;
    }
    else
    {
        if (minvotes==maxvotes)
        {
            return true;
        }
        for (int i=0;i<candcount;i++)
        {
            if (candidates[i].votes==minvotes)
            {
                candidates[i].eliminated=true;
            }
        }
        return false;
    }
}

void print_winner(candidate candidates[],int candcount)
{
    int maxvotes=0;
    char *winners[candcount];
    int winnercount=0;
    for (int i=0;i<candcount;i++)
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
            winners[winnercount]=candidates[i].name;
            winnercount++;
        }
    }
    for (int i=0;i<winnercount;i++)
    {
        printf("%s\n",winners[i]);
    }
}

bool repeatcand(char *votedcandidate,int candcount,int voters,char *choices[voters][candcount],int i,int j)
{
    for (int k=0;k<j;k++)
    {
        if (strcmp(votedcandidate,choices[i][k])==0)
        {
            return true;
        }
    }
    return false;
}
