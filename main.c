/*First hand is 2(black), second hand is 1(white), blank is 3*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int gameboard[9][9];	//use gameboard[1][1]~gameboard[8][8]
int hash[65536];
int move;
unsigned long long int true_board[3];

int check_legal_flip(int row, int column, int my_color, int flip, unsigned long long *, unsigned long long *);
void init_hash_table();

unsigned int hash_function(unsigned long long int board)
{
	board=(board>>32)^(board&0xffffffff);
	board=(board>>16)^(board&0xffff);
	return (unsigned int)board;
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
void alpha_beta(int color)
{
	int i,j;
	int row[60],column[60];
	int mobility=0;
//	for(i=1;i<9;++i)
//		for(j=1;j<9;++j)
//			if(check_legal_and_flip(i,j,color,0)){
//				row[mobility]=i;
//				column[mobility++]=j;
//			}


}
void init()
{
	memset(gameboard,0,sizeof(gameboard));
	memset(hash,0,sizeof(hash));
	gameboard[4][4]=gameboard[5][5]=1;
	gameboard[4][5]=gameboard[5][4]=2;
	true_board[1]=0x0000001008000000;
	true_board[2]=0x0000000810000000;
	init_hash_table();
	move=0;
}
int game(int turn)
{
	int player_color,computer_color;
	int row,column;
	unsigned int index;
	init();
	if(turn==0){	//player1 first
		player_color=2;
		computer_color=1;
	}else{
		player_color=1;
		computer_color=2;
	}
	system("clear");
	show_gameboard();
	printf("next move: color 2\n");
	while((move++)<64){
		if(turn==0){
			while(scanf("%d %d",&row,&column)){
				if(row>8 || column>8){
					printf("illegal move, try again\n");
					continue;
				}
				if(check_legal_flip(row,column,player_color,1,&true_board[player_color],&true_board[computer_color])){
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
			if(move<=2){	//opening book
				index=hash_function(true_board[1]+true_board[2]);
				row=hash[index]>>4;
				column=hash[index]&7;
				check_legal_flip(row,column,computer_color,1,&true_board[computer_color],&true_board[player_color]);
				show_gameboard();
				printf("computer: %d %d\t(%d %d)\n",row,column,row-1,column-1);
				printf("next move: color %d\n",player_color);
			}else{
//				alpha_beta(computer_color);
//	board[1]=black;
//	board[2]=white;
				for(row=1;row<=8;++row)
					for(column=1;column<=8;++column)
						if(check_legal_flip(row,column,computer_color,1,&true_board[computer_color],&true_board[player_color])){
							show_gameboard();
							printf("computer: %d %d\t(%d %d)\n",row,column,row-1,column-1);
							printf("next move: color %d\n",player_color);
							row=100;
							break;
						}
				if(row==9){
					printf("no legal move, pass\n");
					move--;
				}
			}
			turn=0;
		}
	}
	int i,j;	//temporarily used for count color
	i=count_color(player_color);
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
