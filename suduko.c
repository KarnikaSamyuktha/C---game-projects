#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#define n 9

void printboard(int board[n][n]){
   for (int i=0;i<n;i++){
      if ((i)%3==0){
         
         printf(" _________________________\n|");
         
      }
      else {
      printf(" _  _  _  _  _  _  _  _  _ ");
      printf("\n|");}
      for(int j=0;j<n;j++){
         printf("%d |",board[i][j]);
      }
      printf("\n");
   }
   printf(" _________________________\n|");
} 

int issafemove(int board[n][n],int row,int col,int num){
   for (int x=0;x<n;x++){
      if (board[x][col]==num || board[row][x]==num){
         return 0;
      }
   }
   int startrow = row - (row%3), startcol = col - (col%3);
   for (int i=0;i<3;i++){
      for (int j=0;j<3;j++){
         if (board[i+startrow][j+startcol]==num) return 0;
      }
   }
   return 1;
}

void removedigits(int board[n][n],int count){
   while (count>0){
      int i = rand()%n;
      int j = rand()%n;
      if (board[i][j]!=0){
         board[i][j]=0;
         count--;
      }      
   }
   play_suduko(board);
}
int isfull(int board[n][n]){
   for (int i=0;i<n;i++){
      for (int j=0;j<n;j++){
         if (board[i][j]!=0) return 0;
      }
   }
   return 1;
}

void play_suduko(int board[n][n]){
   int num,row,col,loop=0;
   char reply;
   printf("enter the number and position where you want to make the move...eg;num row col...:");
   scanf("%d %d %d",&num,&row,&col);
   if (board[row][col]==0 && issafemove(board,row,col,num)==1) {board[row][col]=num;
   printboard(board);
   while (loop!=1){
   printf("would you like to change the last move(y/n):");
   scanf(" %c",&reply);
   if (reply=='n'){
      loop=1;
   if (isfull(board)==0){
      play_suduko(board);}}
   else if (reply=='y'){
      loop=1;
      if (isfull(board)==0){
       board[row][col]=0;
       play_suduko(board);}
   }
   else {
     printf("----Enter valid reply----\n");
   }}
   }
   else {
      if (isfull(board)==0){
      if (board[row][col]!=0){
      printf("\n------MAKE A CORRECT MOVE, THE POSITION IS ALREADY OCCUPIED------\n");}
      else if (issafemove(board,row,col,num)==0){
         printf("\n------THE MOVE CAN NOT BE MADE, TRY SOME OTHER MOVE------\n");}
      
      play_suduko(board);}
      else if(isfull(board)==1){
         printf("\n-------------COMPLETED--------------\n");
         char ans;
         printf("\n----WOULD YOU LIKE TO PLAY ANOTHER GAME (Y/N)----");
         scanf("%c",&ans);
         if (ans=='Y') removedigits(board,40);
         else printf("\n----------THANK YOU-------------\n");     
      }} 
}

int main(){
   int board[n][n]={0};
   board[0][1]=board[3][0]=board[7][2]=board[5][5]=board[8][6]=7;
   board[0][2]=board[2][6]=board[4][5]=board[2][6]=board[5][8]=board[7][0]=board[6][7]=board[8][4]=2;
   board[1][2]=board[0][5]=board[2][8]=board[6][0]=4;
   board[1][0]=board[7][1]=3;
   board[2][0]=board[1][5]=board[5][3]=8;
   board[2][1]=board[1][6]=board[5][7]=board[6][5]=board[7][8]=1;
   board[2][5]=board[6][6]=6;
   board[2][7]=board[3][8]=board[6][2]=board[7][6]=board[8][5]=5;
   board[2][2]=board[1][5]=board[3][7]=board[4][0]=9;
   printf("Lets begin\n");
   printboard(board);
   play_suduko(board);
   
}