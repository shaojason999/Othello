/*First hand is 1(black), second hand is 2(white), blank is 3*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int gameboard[9][9];	//use gameboard[1][1]~gameboard[8][8]
int move;

void init()
{
	memset(gameboard,0,sizeof(gameboard));
	gameboard[4][4]=gameboard[5][5]=2;
	gameboard[4][5]=gameboard[5][4]=1;
	move=0;
}
int count_color(int color)
{
	int i,j;
	int count=0;
	for(i=1;i<9;++i)
		for(j=1;j<9;++j)
			if(gameboard[i][j]==color)
				++count;
	return count;
}
void show_gameboard()
{
	int i,j;
	printf(" | 1 2 3 4 5 6 7 8\n");
	printf("------------------\n");
	for(i=1;i<9;++i){
		printf("%d| ",i);
		for(j=1;j<9;++j)
			printf("%d ",gameboard[i][j]);
		printf("\n");
	}
}
int check_legal(int row, int column, int color)
{
	int legal=0;
	int opponent_color;
	int i,j;
	if(color==1)
		opponent_color=2;
	else
		opponent_color=1;
	/*check empty*/
	if(gameboard[row][column]!=0)
		return legal;
	/*check up*/
	for(i=row-1;i>0;--i)
		if(gameboard[i][column]!=opponent_color)
			if(gameboard[i][column]==color && i!=(row-1)){
				legal=1;
				for(j=i+1;j<row;++j)
					gameboard[j][column]=color;
			}else
				break;
	/*check down*/
	for(i=row+1;i<=8;++i)
		if(gameboard[i][column]!=opponent_color)
			if(gameboard[i][column]==color && i!=(row+1)){
				legal=1;
				for(j=i-1;j>row;--j)
					gameboard[j][column]=color;
			}else
				break;
	/*check right*/
	for(i=column+1;i<=8;++i)
		if(gameboard[row][i]!=opponent_color)
			if(gameboard[row][i]==color && i!=(column+1)){
				legal=1;
				for(j=i-1;j>column;--j)
					gameboard[row][j]=color;
			}else
				break;
	/*check left*/
	for(i=column-1;i>0;--i)
		if(gameboard[row][i]!=opponent_color)
			if(gameboard[row][i]==color && i!=(column-1)){
				legal=1;
				for(j=i+1;j<column;++j)
					gameboard[row][j]=color;
			}else
				break;
	/*check upper right*/
	for(i=1;(row-i)>0 && (column+i)<=8;++i)
		if(gameboard[row-i][column+i]!=opponent_color)
			if(gameboard[row-i][column+i]==color && i!=1){
				legal=1;
				for(j=i-1;j>0;--j)
					gameboard[row-j][column+j]=color;
			}else
				break;
	/*check bottom left*/
	for(i=1;(row+i)<=8 && (column-i)>0;++i)
		if(gameboard[row+i][column-i]!=opponent_color)
			if(gameboard[row+i][column-i]==color && i!=1){
				legal=1;
				for(j=i-1;j>0;--j)
					gameboard[row+j][column-j]=color;
			}else
				break;
	/*check upper left*/
	for(i=1;(row-i)>0 && (column-i)>0;++i)
		if(gameboard[row-i][column-i]!=opponent_color)
			if(gameboard[row-i][column-i]==color && i!=1){
				legal=1;
				for(j=i-1;j>0;--j)
					gameboard[row-j][column-j]=color;
			}else
				break;
	/*chech bottom right*/
	for(i=1;(row+i)<=8 && (column+i)<=8;++i)
		if(gameboard[row+i][column+i]!=opponent_color)
			if(gameboard[row+i][column+i]==color && i!=1){
				legal=1;
				for(j=i-1;j>0;--j)
					gameboard[row+j][column+j]=color;
			}else
				break;
	if(legal)
		gameboard[row][column]=color;
	return legal;
}
int game(int turn)
{
	int player1_color,computer_color;
	int row,column;
	init();
	if(turn==0){	//player1 first
		player1_color=2;
		computer_color=1;
	}else{
		player1_color=1;
		computer_color=2;
	}
	while((move++)<64){
		if(turn==0){
			while(scanf("%d %d",&row,&column)){
				if(check_legal(row,column,player1_color)){
					system("clear");
					show_gameboard();
					printf("player: %d %d\n",row,column);
					printf("next move: color %d\n",computer_color);
					break;
				}else
					printf("illegal move, try again\n");
			}
			turn=1;
		}else if(turn==1){
			for(row=1;row<=8;++row)
				for(column=1;column<=8;++column)
					if(check_legal(row,column,computer_color)){
						show_gameboard();
						printf("computer: %d %d\n",row,column);
						printf("next move: color %d\n",player1_color);
						row=100;
						break;
					}
			if(row==9){
				printf("no legal move, pass\n");
				move--;
			}
			turn=0;
		}
	}
	int i,j;	//temporarily used for count color
	i=count_color(player1_color);
	j=count_color(computer_color);
	if(i>j)
		printf("player1 win\n");
	else if(i<j)
		printf("computer win\n");
	else
		printf("draw\n");
}
int main()
{
	int player,turn;
	printf("1 player or 2 player: ");
	scanf("%d",&player);
	if(player==1){
		printf("0: You first, 1: Computer first: ");
		scanf("%d",&turn);
		if(turn==0)
			game(0);
		else
			game(1);

	}
	else if(player==2){
			
	}

}
