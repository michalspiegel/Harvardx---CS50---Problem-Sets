//TIDEMAN - a voting system - that decides who wins based on preferences that the voters have for the candidates - they rank the candidates

#include <cs50.h>
#include <stdio.h>
#include <string.h>



// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool is_cycle(int winner, int loser);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }


    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}




// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Lineary check if the name given is in the candidates.names array
    for (int i = 0; i < candidate_count; i++)
    {   
        
        //Compare the user_input with names in the candidates array
        if (strcmp(candidates[i], name) == 0)
        {
            
            for (int k = 0; k < rank; k++)
            {
                //find out if the name of the candidate is not already in the ranks candidate of the given voter
                if (ranks[k] == i)
                {
                    return false;
                }

            }
            //If not add the candidate into the ranks array
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}




// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{   
    for (int i = 0; i < candidate_count; i++)
    {
        // i is the preferred candidate over every other that is behind him in the array
        for (int k = 1 + i; k < candidate_count; k++)
        {
            //+ 1 to i's row in the preferences array on index k(because he i won over k) 
            preferences[ranks[i]] [ranks[k]]++;
        }
    }

}




// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {   
        //Make pairs(every possible) out of candidates(like in case of A B C - AB,AC,BC)
        for (int k = 1 + i; k < candidate_count; k++)
        {
            
            //Compare their preferences stats - the one with a bigger preference stat is the winner
            //Comparing is done by switching the i for k - one is a preference stat of the first candidate and the second a preference stat of the second candidate
            if (preferences[i][k] > preferences[k][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = k;
                pair_count++;

            }
            //or if the first preference stat is smaller just switch the winner with loser
            else if (preferences[i][k] < preferences[k][i])
            {
                pairs[pair_count].winner = k;
                pairs[pair_count].loser = i;
                pair_count++;

            }
            //in case the preference stats of both candidates in a pair are equal - don't add them to the pairs array
        }
    }
}




// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{


    //Bubble sort algorithm that sort pairs in downward order based on how strong is their victory of the winner over the loser - how many prefer the winner over the loser
    for (int i = 0; i < pair_count; i++)
    {
        for (int k = 0; k < pair_count - i; k++)
        {
            if (preferences[pairs[k].winner][pairs[k].loser] < preferences[pairs[k + 1].winner][pairs[k + 1].loser])
            {
                pair temp = pairs[k];
                pairs[k] = pairs[k + 1];
                pairs[k + 1] = temp;
            }
        }
    }

}




//Finds out if the pair we are about to lock into the "graph" (locked array) is going to create a cycle in the graph - if yes, it returns false
bool is_cycle(winner, loser)
{
    //Every edge of a cycle leaves clues(loser index) about the position of the next edge in the cycle
    if (winner == loser)
    {
        // If there is a cycle, we should eventually end up where we began in the first place
        return true;
    }
    
    for (int i = 0; i < candidate_count; i++)
    {
    
        if (locked[loser][i] == true)
        {
            //tries is_cycle() for this current setting, considering there can be more true values in a single row
            if (is_cycle(winner,i))
            {
                return true;
            }
            
        }
    }
    return false;
}




// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        
        //if is_cycle returns false - therefore there is no cycle that would be created if we added this edge into the cycle - we can add it into the locked array
        if (!is_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    }
}




// Print the winner of the election
void print_winner(void)
{
    //Winner is the source of the graph - the one who has no arrows pointing toward him in the graph - no one defeated him
    for (int i = 0; i < candidate_count; i++)
    {
        int true_values = 0;
        for (int k = 0; k < candidate_count; k++)
        {
            if (locked[k][i])
            {
                true_values++;
            }
        }
        
        //Therefore his column in the locked 2D array must not cointain but none true values
        if (true_values == 0)
        {
            //In this function we search for such a column and print out the candidate who has one
            printf("%s\n", candidates[i]);
            return;
        }
    }
}


