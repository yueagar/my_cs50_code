#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// MY OWN FUNCTION PROTOTYPES
bool hasCycle(int W, int L);

int main(int argc, char *argv[])
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
    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char *name = malloc(50 * sizeof(char));
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

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
bool vote(int rank, char name[], int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        };
    };
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        };
    };
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            };
        };
    };
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) // Selection sort
{
    int sorted = 0;
    while (sorted < pair_count)
    {
        int highestStrength = 0;
        int higherPosition;
        pair toLowerPosition;
        pair toHigherPosition;
        for (int i = sorted; i < pair_count; i++)
        {
            int strength = preferences[pairs[i].winner][pairs[i].loser];

            if (strength > highestStrength)
            {
                highestStrength = strength;
                higherPosition = i;
                toLowerPosition = pairs[i];
                toHigherPosition = pairs[sorted];
            };
        };
        // swap
        pairs[sorted] = toLowerPosition;
        pairs[higherPosition] = toHigherPosition;
        sorted++;
    };
    return;
}

// A recursive function to determine whether a cycle exists between W and L.
bool hasCycle(int W, int L)
{
    if (locked[L][W])
    {
        return true; // very obviously, a cycle forms between L and W as W->L and L->W, i.e. W->L->W
    };
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[L][i] && hasCycle(W, i))
        {
            return true; // a cycle forms between L and W as W->L, L->i and i->...->W, i.e. W->L->i->...->W, where ... are some possible candidates in between and tested in the recursion.
        };
    };
    return false; // return false as default as it passes the checks for the presence of cycle above
};

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!hasCycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        };
    };
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool won = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                won = false; // A source point should not have other points pointing to it in the graph.
            };
        };
        if (won)
        {
            printf("%s\n", candidates[i]);
            break;
        };
    };
    return;
}