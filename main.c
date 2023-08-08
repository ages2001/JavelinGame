#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LIMIT 100

void sortAthletes(char ***players, int **distances);

int main() {
    int numberOfPlayers, *distances;
    char **playerNames;

    do {
        printf("\nEnter the number of players (at least 8): ");
        scanf("%d", &numberOfPlayers);

        if (numberOfPlayers <= 0)
            printf("Invalid number!\n");
        else if (numberOfPlayers < 8)
            printf("In the competition, there must be at least 8 players!\n");
    } while (numberOfPlayers < 8);

    playerNames = (char **) malloc(sizeof(char *) * (numberOfPlayers + 1));
    distances = (int *) malloc(sizeof(int) * (numberOfPlayers + 1));

    fflush(stdin);
    printf("\n");
    for (size_t i = 0; i < numberOfPlayers; i++) {
        playerNames[i] = (char *) malloc(sizeof(char) * STR_LIMIT);
        printf("Enter the player %zu name-surname: ", i + 1);
        scanf(" %[^\n]", playerNames[i]);
    }

    printf("\nFirst Round\n-----------");
    for (size_t j = 0; j < 3; j++) { // First round
        printf("\n");
        for (size_t i = 0; i < numberOfPlayers; i++) {
            int distance;
            printf("Enter player %zu's %zu. try: ", i + 1, j + 1);
            scanf("%d", &distance);

            if (j == 0)
                distances[i] = distance;
            else {
                if (distance > distances[i])
                    distances[i] = distance;
            }
        }
    }

    distances[numberOfPlayers] = -1;
    sortAthletes(&playerNames, &distances);

    int numberOfFinalPlayers = 0;

    for (size_t i = 0; i < numberOfPlayers; i++) {
        if (i < 8 || distances[i] > 50)
            numberOfFinalPlayers++;
    }

    playerNames = (char **) realloc(playerNames, sizeof(char *) * (numberOfFinalPlayers + 1));
    distances = (int *) realloc(distances, sizeof(int) * (numberOfFinalPlayers + 1));

    printf("\nFinal players     Distance\n-------------     --------");
    for (size_t i = 0; i < numberOfFinalPlayers; i++)
        printf("\n%s           %d", playerNames[i], distances[i]);

    printf("\n\nFinal Round\n-----------");
    for (size_t j = 0; j < 3; j++) { // Final round
        printf("\n");
        for (int i = numberOfFinalPlayers - 1; i >= 0; i--) {
            int distance;
            printf("Enter player %d's %zu. try: ", numberOfFinalPlayers - i, j + 1);
            scanf("%d", &distance);

            if (j == 0)
                distances[i] = distance;
            else {
                if (distance > distances[i])
                    distances[i] = distance;
            }
        }
    }

    distances[numberOfFinalPlayers] = -1;
    sortAthletes(&playerNames, &distances);

    printf("\nAthletes who won gold, silver, and bronze medals, respectively: \n\n");
    printf("\n WINNERS           Distance\n*********          ********");
    for (size_t i = 0; i < 3; i++)
        printf("\n%s            %d", playerNames[i], distances[i]);

    printf("\n");

    for (size_t i = 0; i < numberOfPlayers; i++)
        free(playerNames[i]);
    free(playerNames);
    free(distances);

    printf("\nJavelin Game completed successfully!\n");

    return 0;
}

void sortAthletes(char ***players, int **distances) {
    size_t length = 0;
    while ((*distances)[length] != -1) length++;

    for (size_t i = 0; i < length - 1; i++) { // Selection sort
        int biggestDistance = (*distances)[i];
        size_t biggestIndex = i;
        for (size_t j = i + 1; j < length; j++) {
            if ((*distances)[j] > biggestDistance) {
                biggestDistance = (*distances)[j];
                biggestIndex = j;
            }
        }
        int tempDistance = (*distances)[i];
        (*distances)[i] = (*distances)[biggestIndex];
        (*distances)[biggestIndex] = tempDistance;

        char *tempPlayer = (*players)[i];
        (*players)[i] = (*players)[biggestIndex];
        (*players)[biggestIndex] = tempPlayer;
    }
}
