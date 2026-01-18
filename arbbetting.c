#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char home_team[100];
    char away_team[100];
    double x1;          // Team 1
    char x1_bookmaker[50];
    double x2;          // Team 2
    char x2_bookmaker[50];
    double tie;         // Draw 
    char tie_bookmaker[50];
} Bet;

_Bool isbetgood(Bet thebet)
{
    double sum = 1 / thebet.x1 + 1 / thebet.x2 + 1 / thebet.tie;
    // Check if bet is profitable
    return sum < 1;
}

Bet *nicebetfiltration(FILE *ifile, int *count)
{
    Bet *goodBets = NULL;
    *count = 0;
    Bet tempBet;

    int capacity = 10;

    goodBets = (Bet *)malloc(capacity * sizeof(Bet));

    if (goodBets == NULL)
    {
        printf("Error in memory allocation\n");
        return NULL;
    }

    char line[512];

    //goes through the bets.txt and determines whether the bets present are profitable
    while (fgets(line, sizeof(line), ifile))
    {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, "|");
        if (token == NULL) continue;
        strcpy(tempBet.home_team, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(tempBet.away_team, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        tempBet.x1 = atof(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(tempBet.x1_bookmaker, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        tempBet.x2 = atof(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(tempBet.x2_bookmaker, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        tempBet.tie = atof(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(tempBet.tie_bookmaker, token);

        if (isbetgood(tempBet))
        {
            if (*count >= capacity)
            {
                capacity *= 2;
                Bet *newBets = (Bet *)realloc(goodBets, capacity * sizeof(Bet));
                if (newBets == NULL)
                {
                    printf("Error in memory reallocation\n");
                    free(goodBets);
                    return NULL;
                }
                goodBets = newBets;
            }
            goodBets[*count] = tempBet;
            (*count)++;
        }
    }

    if (*count == 0)
    {
        free(goodBets);
        return NULL;
    }

    return goodBets;
}

int main()
{
    FILE *file = fopen("bets.txt", "r");
    if (file == NULL)
    {
        perror("Could not open file");
        return 1;
    }

    int count = 0, i;
    Bet *goodBets = nicebetfiltration(file, &count);

    if (goodBets != NULL)
    {
        printf("Good Bets:\n");
        for (i = 0; i < count; i++)
        {
            printf("Bet %d: %s vs %s\n", i + 1, goodBets[i].home_team, goodBets[i].away_team);
            printf("  Home Win: Odds=%.2f (Bookmaker: %s)\n", goodBets[i].x1, goodBets[i].x1_bookmaker);
            printf("  Away Win: Odds=%.2f (Bookmaker: %s)\n", goodBets[i].x2, goodBets[i].x2_bookmaker);
            printf("  Draw:     Odds=%.2f (Bookmaker: %s)\n", goodBets[i].tie, goodBets[i].tie_bookmaker);
            printf("\n");
        }
        free(goodBets);
    }
    else
    {
        printf("No good bets found.\n");
    }

    fclose(file);
    return 0;
}



