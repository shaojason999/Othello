/*First hand is 2(black), second hand is 1(white), blank is 3*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEPTH 4

//int gameboard[9][9];	//use gameboard[1][1]~gameboard[8][8]
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
	int i;
	int count=0;
	unsigned long long check=1;
	check<<=63;
	for(i=0;i<64;++i){
		if((true_board[color]&check)!=0)
			++count;
		check>>=1;
	}
	return count;
}
void show_gameboard()
{
	int i;
	unsigned long long check=1;
	check<<=63;
	printf(" | 1 2 3 4 5 6 7 8\n");
	printf("------------------\n");
	for(i=0;i<64;++i){
		if(i%8==0)
			printf("%d| ",i/8+1);
		if((true_board[1]&check)!=0)
			printf("1 ");
		else if((true_board[2]&check)!=0)
			printf("2 ");
		else
			printf("0 ");
		if(i%8==7)
			printf("\n");
		check>>=1;
	}
}
void alpha_beta(int alpha, int beta, int my_color, unsigned long long my_board, unsigned long long opponent_board)	//row and column is from 1 to 8
{
	unsigned long long check=1;
	unsigned long long temp_board[3];
	int opponent_color;
	check<<=63;
	/*init set*/
	if(my_color==1)
		opponent_color=2;
	else
		opponent_color=1;
	temp_board[my_color]=my_board;
	temp_board[opponent_color]=opponent_board;

	if(depth<DEPTH){
		m=alpha;
		for(i=0;i<64;++i)
			if((my_board&check)==0 && (opponent_board&check)==0)
				if(check_legal_flip(i/8+1,i%8+1,my_color,1,&temp_board[my_color],&temp_board[opponent_color])){	//check and flip
					++depth;
					t=-alpha_beta(-beta,-m,opponent_color, temp_board[opponent_color], temp_board[my_color]);
					--depth;
					if(t>m)
						m=t;
					if(m>=beta)
						return m;
					temp_board[my_color]=my_board;
					temp_board[opponent_color]=opponent_board;
				}

//		if(i==64){
//			printf("no legal move, pass\n");
//			return;
		}
	}

}
void init()
{
//	memset(gameboard,0,sizeof(gameboard));
	memset(hash,0,sizeof(hash));
//	gameboard[4][4]=gameboard[5][5]=1;
//	gameboard[4][5]=gameboard[5][4]=2;
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
				alpha_beta(computer_color);

/*				for(row=1;row<=8;++row)
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
*/			}
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
