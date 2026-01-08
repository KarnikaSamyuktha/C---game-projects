#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayinstructions(){
    printf("Gamerules:\n");
    printf("Type: R for Rock\n");
    printf("      P for Paper\n");
    printf("      S for Scissors\n");
    printf("The winner would be the one who gets 5 POINTS first\n");
}

int main(){
    printf("Welcome to the game!\n");
    displayinstructions();
    char s;
    printf("Ready to start!?(Y for yes,N for no):\n");
    scanf("%c",&s);
    if (s=='Y'){
        int player_score=0;
        int comp_score=0;
        int i=1;
        while (player_score<5 && comp_score<5){
            printf("--------------------------------------------\n");
            char player_throw;
            printf("%dth play,type your throw:",i);
            scanf(" %c",&player_throw);
            char comp_throw;
            int num= rand()%3;
            if (num==0) comp_throw='R';
            else if (num==1) comp_throw='P';
            else comp_throw='S';
            if ((player_throw=='R'&& comp_throw=='S')||(player_throw=='S'&& comp_throw=='P')||(player_throw=='P'&& comp_throw=='R')) player_score++;
            else if ((player_throw=='S'&& comp_throw=='R')||(player_throw=='P'&& comp_throw=='S')||(player_throw=='R'&& comp_throw=='P')) comp_score++;
            printf("\nComputer Thorw= %c, Player Throw=%c",comp_throw,player_throw);
            printf("\nPLAYER SCORE= %d",player_score);
            printf("\nCOMPUTER SCORE= %d\n",comp_score);
            printf("--------------------------------------------\n");
            if (comp_score!=5 && player_score!=5){
            printf("Next Move Now\n");}
            i++;
        }
        printf("--------------------------------------------\n");
        if (player_score>comp_score) printf("CONGRATS! You Have Won\n");
        else printf(":( Computer Has Won\n");
        printf("---------------------------------------------");
    }
    return 0;
}
