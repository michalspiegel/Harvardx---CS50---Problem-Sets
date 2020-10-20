#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
int MAX = 9;

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[9];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);



int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}




bool vote(string name)          //Update vote totals given a new vote

{   
    // Lineary check if the name given is in the candidates.names array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0) 
        {
            // If yes, +1 vote to the given candidate
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}



void print_winner(void)       //Print the winner (or winners) of the election

{
    //Indexes of the biggest numbers in the candidates.votes
    int biggest = 0;
  
    // Check for the biggest value
    for (int i = 0; i < candidate_count; i++)
    {
        if (biggest < candidates[i].votes)
        {
            biggest = candidates[i].votes;
        }
    }
    
    
    // Print out the name/s that have the most votes 
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidate[i].votes == biggest)
        {
            printf("%s\n", candidates[i].name);
        }    
    }    
}

