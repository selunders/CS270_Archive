#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> /* for sockaddr_un struct */
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

char playerChoice = 'x';
int playerWins = 0;
int computerChoice;
int computerWins = 0;
int draws = 0;
void getGuess(char *);

int main()
{
    srand(time(NULL));
    while (playerChoice != 'q')
    {
        do
        {
            printf("Y: Enter your guess (r, s, p) or q to quit: ");
            getGuess(&playerChoice);
            // printf("\n");
        } while (playerChoice != 'r' && playerChoice != 's' && playerChoice != 'p' && playerChoice != 'q');
        if (playerChoice == 'q')
        {
            printf("R: Final results: you = %i, computer = %i, draws = %i\n\n", playerWins, computerWins, draws);
            printf("R: thanks for playing!\n");
            return 0;
        }
        computerChoice = rand() % 3;

        switch (computerChoice)
        {
        case 'r': // Rock
            switch (playerChoice)
            {
            case 'r':
                printf("You chose rock, computer chose rock, a draw!\n\n");
                ++draws;
                break;
            case 'p':
                printf("You chose paper, computer chose rock, you win!\n\n");
                ++playerWins;
                break;
            case 's':
                printf("You chose scissors, computer chose rock, computer wins!\n\n");
                ++computerWins;
                break;
            default:
                printf("Whoops, that's an error...\n");
                break;
            }
            break;
        case 'p': // Paper
            switch (playerChoice)
            {
            case 'r':
                printf("You chose rock, computer chose paper, computer wins!\n\n");
                ++computerWins;
                break;
            case 'p':
                printf("You chose paper, computer chose paper, a draw!\n\n");
                ++draws;
                break;
            case 's':
                printf("You chose scissors, computer chose paper, you win!\n\n");
                ++playerWins;
                break;
            default:
                printf("Whoops, that's an error...\n");
                break;
            }
            break;
        case 's': // Scissors
            switch (playerChoice)
            {
            case 'r':
                printf("You chose rock, computer chose scissors, you win!\n\n");
                ++playerWins;
                break;
            case 'p':
                printf("You chose paper, computer chose scissors, computer wins!\n\n");
                ++computerWins;
                break;
            case 's':
                printf("You chose scissors, computer chose scissors, a draw!\n\n");
                ++draws;
                break;
            default:
                printf("Whoops, that's an error...\n");
                break;
            }
            break;
        default:
            break;
        }
    }
}

void getGuess(char *pChoice)
{
    // *pChoice = getch();
    scanf(" %c", pChoice);
}