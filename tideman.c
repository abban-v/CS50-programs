#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    char *name;
    int votes;
} candidate;

typedef struct
{
    char *winner;
    char *loser;
    int margin;
} graph;

typedef struct
{
    char *candidate1;
    char *candidate2;
} pair;

void printwinner(graph wins[],int pairnum,int candcount,candidate candidates[]);
void vote(int voters,int candcount, char *choices[voters][candcount],candidate candidates[]);
bool search(char *currentcand,int candcount, candidate candidates[]);
void creategraph(int voters,int candcount,candidate candidates[],char *choices[voters][candcount],graph wins[],int pairnum);
void tabulate(candidate candidates[],int candcount,int voters, char *choices[voters][candcount],char *candidate1,char *candidate2);
void reset(candidate candidates[],int candcount);
void createpair(candidate candidates[], int candcount,int pairnum,pair pairs[]);
bool searchwinner(char *winner,char *winners[],int winnercount);
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
    }
    int voters=get_int("Enter number of voters: ");
    char *choices[voters][candcount];
    vote(voters,candcount,choices,candidates);
    int pairnum=candcount*(candcount-1)/2;
    graph wins[pairnum];
    creategraph(voters,candcount,candidates,choices,wins,pairnum);
    printwinner(wins,pairnum,candcount,candidates);
}

void printwinner(graph wins[],int pairnum,int candcount,candidate candidates[])
{
    int maxmargin=0;
    int maxindex;
    char *marginwinner;
    char *losers[pairnum];
    for (int i=0;i<pairnum;i++)
    {
        losers[i]=wins[i].loser;
        if (wins[i].margin>maxmargin)
        {
            maxmargin=wins[i].margin;
        }
    }
    bool found=false;
    for (int i=0;i<candcount;i++)
    {
        found=false;
        for (int j=0;j<pairnum;j++)
        {
            if (strcmp(candidates[i].name,losers[j])==0)
            {
                found=true;
                break;
            }
        }
        if (found==false)
        {
            printf("%s\n",candidates[i].name);
            return;
        }
    }
    char *winners[candcount];
    int winnercount=0;
    for (int i=0;i<pairnum;i++)
    {
        if (maxmargin==wins[i].margin)
        {
            if (maxmargin==0)
            {
                if (searchwinner(wins[i].winner,winners,winnercount)==false)
                {
                    winners[winnercount]=wins[i].winner;
                    winnercount+=1;
                    printf("%s\n",wins[i].winner);
                    continue;
                }
                if (searchwinner(wins[i].loser,winners,winnercount)==false)
                {
                    winners[winnercount]=wins[i].loser;
                    winnercount+=1;
                    printf("%s\n",wins[i].loser);
                    continue;
                }
            }
            if (searchwinner(wins[i].winner,winners,winnercount)==false)
            {
                winners[winnercount]=wins[i].winner;
                winnercount+=1;
                printf("%s\n",wins[i].winner);
            }
        }
    }
    return;
}

bool searchwinner(char *winner,char *winners[],int winnercount)
{
    for (int i=0;i<winnercount;i++)
    {
        if (strcmp(winner,winners[i])==0)
        {
            return true;
        }
    }
    return false;
}

void vote(int voters,int candcount, char *choices[voters][candcount],candidate candidates[])
{
    for (int i=0;i<voters;i++)
    {
        printf("Voter %i: \n",i+1);
        for (int j=0;j<candcount;j++)
        {
            char *votedcandidate=get_string("Enter rank %i candidate name: ",j+1);
            if (repeatcand(votedcandidate,candcount,voters,choices,i,j)==true)
            {
                printf("Candidate cannot be repeated.\n");
                j--;
                continue;
            }
            if (search(votedcandidate,candcount,candidates)==false)
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

bool search(char *currentcand,int candcount, candidate candidates[])
{
    for (int i=0;i<candcount;i++)
    {
        if (strcmp(currentcand,candidates[i].name)==0)
        {
            return true;
        }
    }
    return false;
}

void creategraph(int voters,int candcount,candidate candidates[],char *choices[voters][candcount],graph wins[],int pairnum)
{
    pair pairs[pairnum];
    createpair(candidates,candcount,pairnum,pairs);
    for (int i=0;i<pairnum;i++)
    {
        reset(candidates,candcount);
        char *candidate1=pairs[i].candidate1;
        char *candidate2=pairs[i].candidate2;
        tabulate(candidates,candcount,voters,choices,candidate1,candidate2);
        int votes1=-1;
        int index1=-1;
        int votes2=-1;
        int index2=-1;
        for (int j=0;j<candcount;j++)
        {
            if (strcmp(candidate1,candidates[j].name)==0)
            {
                votes1=candidates[j].votes;
                index1=j;
            }
            if (strcmp(candidate2,candidates[j].name)==0)
            {
                votes2=candidates[j].votes;
                index2=j;
            }
        }
        if (votes1>votes2)
        {
            wins[i].winner=candidates[index1].name;
            wins[i].loser=candidates[index2].name;
            wins[i].margin=votes1-votes2;
        }
        else
        {
            wins[i].winner=candidates[index2].name;
            wins[i].loser=candidates[index1].name;
            wins[i].margin=votes2-votes1;
        }
    }
}

void tabulate(candidate candidates[],int candcount,int voters, char *choices[voters][candcount],char *candidate1,char *candidate2)
{
    int rank=0;
    for (int i=0;i<voters;i++)
    {
        rank=0;
        char *currentcand=choices[i][rank];
        for (int j=0;j<candcount;j++)
        {
            if (strcmp(currentcand,candidates[j].name)==0 && (strcmp(candidates[j].name,candidate1)==0 || strcmp(candidates[j].name,candidate2)==0))
            {
                candidates[j].votes++;
                break;
            }
            if (j==candcount-1)
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

void reset(candidate candidates[],int candcount)
{
    for (int i=0;i<candcount;i++)
    {
        candidates[i].votes=0;
    }
}

void createpair(candidate candidates[], int candcount,int pairnum,pair pairs[])
{
    int i=0;
    for (int j=0;j<candcount;j++)
    {
        for (int k=j+1;k<candcount;k++)
        {
            pairs[i].candidate1=candidates[j].name;
            pairs[i].candidate2=candidates[k].name;
            i++;
        }
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
