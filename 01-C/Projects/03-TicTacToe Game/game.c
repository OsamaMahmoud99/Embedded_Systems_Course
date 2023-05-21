#include <stdio.h>
#include <stdlib.h>

#define PLAYGROUND_SIZE    5

#define PLAYER_ONE        'X'
#define PLAYER_TWO        'O'
#define NO_WINNER         'N'
#define WINNER            'W'

#define CELL_BUSY         0xFE
#define INVALID_CHOICE    0xFF

char playground[PLAYGROUND_SIZE][PLAYGROUND_SIZE] = {{' ',' ',' ', ' ',' '},{' ',' ',' ',' ',' '},
                                                     {' ',' ',' ',' ',' '},{' ',' ',' ', ' ', ' '},
                                                     {' ',' ',' ', ' ', ' '}
                                                     };

void render_playground(void);
int get_player_input(void);
char judge(void);


int main()
{
    char winner;
    int choice;
    int no_empty_cells = PLAYGROUND_SIZE*PLAYGROUND_SIZE;
    char current_player = PLAYER_ONE;
    int err_msg=0;

    while(no_empty_cells != 0)
    {
        winner = judge();
        render_playground();
        if(err_msg == CELL_BUSY){
            printf("Please choose another cell\n");
        }
        else if(err_msg == INVALID_CHOICE){
            printf("Try Again selected cell out of range\n");
        }

        if(winner != NO_WINNER){
            printf("%c has won the game !\n",winner);
            return 0;
        }

        err_msg = 0;
        choice = get_player_input();

        if(choice == CELL_BUSY || choice == INVALID_CHOICE){
            err_msg = choice;
        }
        else{
            playground[choice/10 - 1][choice%10 - 1] = current_player;
            current_player = current_player==PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE;
            no_empty_cells--;
        }

    }
}

void render_playground(void){
    system("cls");
    printf("\n");
    for(int i=0; i<PLAYGROUND_SIZE; ++i){
        printf("%c | %c | %c | %c | %c\n",playground[i][0],playground[i][1],playground[i][2]
                                          ,playground[i][3],playground[i][4]);
    }
}

int get_player_input(void){
    int choice;
    scanf("%d",&choice);

    switch(choice){
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
        if(playground[choice/10 - 1][choice%10 - 1] != ' '){
            return CELL_BUSY;
        }
        break;
    default:
        return INVALID_CHOICE;
    }

    return choice;
}

char judge(void){

    int counter = 1;
    for(int i=0; i<PLAYGROUND_SIZE-1; ++i)
    {
        if(playground[0][0] != ' '){
            if( (playground[i][i] == playground[i+1][i+1])){
                counter++;
            }
        }
        if(counter == PLAYGROUND_SIZE){
             return playground[i][i];
        }
    }

    counter = 1;
    for(int i=0,j=PLAYGROUND_SIZE-1; i<PLAYGROUND_SIZE-1; ++i,--j)
    {
        if(playground[0][PLAYGROUND_SIZE-1] != ' '){
            if(playground[i][j] == playground[i+1][j-1]){
                counter++;
            }
        }

        if(counter == PLAYGROUND_SIZE){
            return playground[i][j];
        }
    }

    for(int i=0; i<PLAYGROUND_SIZE; i++){

        //for rows
        counter = 1;
        for(int j=0; j<PLAYGROUND_SIZE-1; ++j){
            if(playground[i][0] != ' '){

                if( playground[i][j] == playground[i][j+1]){
                    counter++;
                }
            }
            if(counter == PLAYGROUND_SIZE){
                return playground[i][0];
            }
        }

        //for cols
        counter = 1;
        for(int j=0; j<PLAYGROUND_SIZE-1; ++j){
            if(playground[0][i] != ' '){

                if( playground[j][i] == playground[j+1][i]){
                    counter++;
                }
            }
            if(counter == PLAYGROUND_SIZE){
                return playground[0][i];
            }
        }
    }

    return NO_WINNER;
}