/*First hand is 2(black), second hand is 1(white), blank is 3*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEPTH 8
/*modify the parameter here*/
#define PERFECT_SEARCH 18	//the last perfect search depth
#define STAGE_1 depth+move<50	//STAGE_1
#define FORMULA_1 value+mobility*80	//the heuristic of STAGE_1
#define FORMULA_2 value+mobility*120	//the heuristic between STAGE_1 and perfect search

int DEPTH;
int hash[65536];
int move;
int depth;
unsigned long long int true_board[3];
const int weight[64]={120,-20, 20,  5,  5, 20,-20,120,
		      -20,-40, 15, -5, -5, 15,-40,-20,
		       15, 15, 15,  3,  3, 15, 15, 15,
		        5, -5,  3, 20, 20,  3, -5,  5,
		        5, -5,  3, 20, 20,  3, -5,  5,
		       15, 15, 15,  3,  3, 15, 15, 15,
		      -20,-40, 15, -5, -5, 15,-40,-20,
		      120,-20, 20,  5,  5, 20,-20,120};

int check_legal_flip(int row, int column, int my_color, int flip, unsigned long long *, unsigned long long *);
void init_hash_table();

unsigned int hash_function(unsigned long long int board)
{
	board=(board>>32)^(board&0xffffffff);
	board=(board>>16)^(board&0xffff);
	return (unsigned int)board;
}
int count_color(unsigned long long board)
{
	int i;
	int count=0;
	unsigned long long check=1;
	check<<=63;
	for(i=0;i<64;++i){
		if((board&check)!=0)
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
int alpha_beta(int alpha, int beta, int my_color, unsigned long long my_board, unsigned long long opponent_board)	//row and column is from 1 to 8
{
	unsigned long long check=1;
	unsigned long long temp_board[3];
	int opponent_color;
	int i,t,m;
	int row,column;
	int my_count,opponent_count;
	if(my_color==1)
		opponent_color=2;
	else
		opponent_color=1;
	temp_board[my_color]=my_board;
	temp_board[opponent_color]=opponent_board;
	if(depth+move-1==64){	//perfect search
		my_count=count_color(my_board);
		opponent_count=count_color(opponent_board);
		//printf("%d\n",my_count-opponent_count);
		return my_count-opponent_count;
	}
	if(depth==DEPTH){
		int value=0;
		int mobility=0;
		/*weight*/
		for(i=0;i<64;++i){
			value+=((int)(my_board&check)-(int)(opponent_board&check))*weight[63-i];
			my_board>>=1;
			opponent_board>>=1;
		}
		/*mobility*/
		for(row=1;row<=8;++row)
			for(column=1;column<=8;++column){
				if(check_legal_flip(row,column,my_color,0,&temp_board[my_color],&temp_board[opponent_color])){
					++mobility;
				}
				if(check_legal_flip(row,column,opponent_color,0,&temp_board[opponent_color],&temp_board[my_color])){
					--mobility;
				}
			}
		/*modify the calculate formula parameter here*/
//		printf("%d %d\n",value,mobility);
		if(STAGE_1)
//			return value+mobility*80;
			return FORMULA_1;
		else
//			return value+mobility*120;
			return FORMULA_2;
		
	}
	check=1;
	check<<=63;
	if(depth<DEPTH){
		m=alpha;
		for(i=0;i<64;++i){
			if((my_board&check)==0 && (opponent_board&check)==0)
				if(check_legal_flip(i/8+1,i%8+1,my_color,1,&temp_board[my_color],&temp_board[opponent_color])){	//check and flip
					++depth;
					t=-alpha_beta(-beta,-m,opponent_color, temp_board[opponent_color], temp_board[my_color]);
					--depth;
					if(t>m)
						m=t;
					if(m>=beta){
						return m;	//cut-off
					}
					temp_board[my_color]=my_board;
					temp_board[opponent_color]=opponent_board;
				}
			check>>=1;
		}
		return m;	
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
	move=4;
}
int game(int turn)
{
	int player_color,computer_color;
	int row,column;
	unsigned int index;
	unsigned long long check=1;
	unsigned long long temp_board[3];
	int i,alpha,beta,m,max_move,legal_move,t;
	int pass=0,flag;
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
		/*last 14 perfect search*/
		if(move==64+1-PERFECT_SEARCH)
			DEPTH=PERFECT_SEARCH;
		if(pass==2)
			break;
		if(turn==0){
			turn=1;
			for(row=1;row<=8;++row)
				for(column=1;column<=8;++column)
					if(check_legal_flip(row,column,player_color,0,&true_board[player_color],&true_board[computer_color])){
						row=100;
						break;
					}
			if(row==9){
				printf("!!!!! no legal move, pass\n");
				++pass;
				--move;
				continue;
			}
			while(scanf("%d %d",&row,&column)){
				pass=0;
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
		}else if(turn==1){
			turn=0;
			if(move<=2){	//opening book
				index=hash_function(true_board[1]+true_board[2]);
				row=hash[index]>>4;
				column=hash[index]&7;
				check_legal_flip(row,column,computer_color,1,&true_board[computer_color],&true_board[player_color]);
				show_gameboard();
				printf("computer: %d %d\t(%d %d)\n",row,column,row-1,column-1);
				printf("next move: color %d\n",player_color);
			}else{
				/*init set*/
				check=1;
				check<<=63;
				temp_board[computer_color]=true_board[computer_color];
				temp_board[player_color]=true_board[player_color];
				depth=0;
				alpha=-100000;
				beta=100000;
				m=alpha;
				max_move=-1;
				flag=0;
				for(i=0;i<64;++i){
					if((true_board[computer_color]&check)==0 && (true_board[player_color]&check)==0){
						if(check_legal_flip(i/8+1,i%8+1,computer_color,1,&temp_board[computer_color],&temp_board[player_color])){	//check and flip
							pass=0;
							++depth;
							t=-alpha_beta(-beta,-m,player_color,temp_board[player_color],temp_board[computer_color]);
							--depth;
							flag=1;
							if(t>m){
								m=t;
								max_move=i;	//if DEPTH=0, next move is the first legal move(i)
							}
							else{
								legal_move=i;
							}
							temp_board[computer_color]=true_board[computer_color];
							temp_board[player_color]=true_board[player_color];
						}
					}
					check>>=1;
				}
				if(flag==0){
					printf("no legal move, pass\n");
					++pass;
					--move;
					continue;
				}
				else{
					if(max_move!=-1){
						row=max_move/8+1;
						column=max_move%8+1;
					}else{
						row=legal_move/8+1;
						column=legal_move%8+1;
					}
					check_legal_flip(row,column,computer_color,1,&true_board[computer_color],&true_board[player_color]);	//real move
					show_gameboard();
					printf("computer:%d %d\t(%d %d)\n",row,column,row-1,column-1);
					printf("next move: color %d\n",player_color);
				}
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
		}
	}
	int player_count,computer_count;
	player_count=count_color(true_board[player_color]);
	computer_count=count_color(true_board[computer_color]);
	if(player_count>computer_count)
		printf("player1 win: %d:%d\n",player_count,computer_count);
	else if(computer_count>player_count)
		printf("computer win: %d:%d\n",computer_count,player_count);
	else
		printf("draw\n");
}
int main()
{
	int player,turn;
	printf("Search depth: ");
	scanf("%d",&DEPTH);
	printf("0: You first, 1: Computer first: ");
	scanf("%d",&turn);
	if(turn==0)
		game(0);
	else
		game(1);

}
