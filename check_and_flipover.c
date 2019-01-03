#include <stdio.h>

//extern int gameboard[9][9];    //use gameboard[1][1]~gameboard[8][8]
unsigned long long shift(int i, int j)
{
	unsigned long long temp=1;
	return temp<<(((8-i)<<3)+(8-j));
}
int check_legal_flip(int row, int column, int color, int flip, unsigned long long *my_board, unsigned long long *opponent_board)
{
	int legal=0;
	int opponent_color;
	int i,j;
	unsigned long long int temp=1;
	unsigned long long board[3];
	if(color==1)
		opponent_color=2;
	else
		opponent_color=1;
	board[color]=*my_board;
	board[opponent_color]=*opponent_board;
	/*check empty*/
//	if(gameboard[row][column]!=0)
//		return legal;
	if((board[1]&shift(row,column))!=0 || (board[2]&shift(row,column))!=0)
		return legal;	//return 0;
	/*check up*/
	for(i=row-1;i>0;--i)
		if((board[opponent_color]&shift(i,column))==0){
	//	printf("%llx\n",board[color]);
			if((board[color]&shift(i,column))!=0 && i!=row-1){
	//	printf("345\n");
				legal=1;
				if(flip==0)
					return legal;
				for(j=i+1;j<row;++j){
//					gameboard[j][column]=color;
					board[color]|=shift(j,column);
					board[opponent_color]&=~shift(j,column);
				}
			}
			break;
		}
	/*check down*/
	for(i=row+1;i<=8;++i)
		if((board[opponent_color]&shift(i,column))==0){
			if((board[color]&shift(i,column))!=0 && i!=row+1){
				legal=1;
				if(flip==0)
					return legal;
				for(j=i-1;j>row;--j){
//					gameboard[j][column]=color;
					board[color]|=shift(j,column);
					board[opponent_color]&=~shift(j,column);
				}
			}
			break;
		}
	/*check right*/
	for(i=column+1;i<=8;++i)
		if((board[opponent_color]&shift(row,i))==0){
			if((board[color]&shift(row,i))!=0 && i!=column+1){
				legal=1;
				if(flip==0)
					return legal;
				for(j=i-1;j>column;--j){
//					gameboard[row][j]=color;
					board[color]|=shift(row,j);
					board[opponent_color]&=~shift(row,j);
				}
			}
			break;
		}
	/*check left*/
	for(i=column-1;i>0;--i)
		if((board[opponent_color]&shift(row,i))==0){
			if((board[color]&shift(row,i))!=0 && i!=column-1){
				legal=1;
				if(flip==0)
					return legal;
				for(j=i+1;j<column;++j){
//					gameboard[row][j]=color;
					board[color]|=shift(row,j);
					board[opponent_color]&=~shift(row,j);
				}
			}
			break;
		}
	/*check upper right*/
	for(i=1;(row-i)>0 && (column+i)<=8;++i)
		if((board[opponent_color]&shift((row-i),(column+i)))==0){
			if((board[color]&shift((row-i),(column+i)))!=0 && i!=1){
				legal=1;
				if(flip==0)
					return legal;
				for(j=i-1;j>0;--j){
//					gameboard[(row-j)][(column+j)]=color;
					board[color]|=shift((row-j),(column+j));
					board[opponent_color]&=~shift((row-j),(column+j));
				}
			}
			break;
		}
	/*check bottom left*/
	for(i=1;(row+i)<=8 && (column-i)>0;++i)
		if((board[opponent_color]&shift((row+i),(column-i)))==0){
			if((board[color]&shift((row+i),(column-i)))!=0 && i!=1){
				legal=1;
				if(flip==0)
					return legal;
				for(j=i-1;j>0;--j){
//					gameboard[(row+j)][(column-j)]=color;
					board[color]|=shift((row+j),(column-j));
					board[opponent_color]&=~shift((row+j),(column-j));
				}
			}
			break;
		}
	/*check upper left*/
	for(i=1;(row-i)>0 && (column-i)>0;++i)
		if((board[opponent_color]&shift((row-i),(column-i)))==0){
			if((board[color]&shift((row-i),(column-i)))!=0 && i!=1){
				legal=1;
				if(flip==0)
					return legal;
				for(j=i-1;j>0;--j){
//					gameboard[(row-j)][(column-j)]=color;
					board[color]|=shift((row-j),(column-j));
					board[opponent_color]&=~shift((row-j),(column-j));
				}
			}
			break;
		}
	/*chech bottom right*/
	for(i=1;(row+i)<=8 && (column+i)<=8;++i)
		if((board[opponent_color]&shift((row+i),(column+i)))==0){
			if((board[color]&shift((row+i),(column+i)))!=0 && i!=1){
				legal=1;
				if(flip==0)
					return legal;
				for(j=i-1;j>0;--j){
//					gameboard[(row+j)][(column+j)]=color;
					board[color]|=shift((row+j),(column+j));
					board[opponent_color]&=~shift((row+j),(column+j));
				}
			}
			break;
		}
	if(legal){
//		gameboard[row][column]=color;
		board[color]|=shift(row,column);
		*my_board=board[color];
		*opponent_board=board[opponent_color];
	}
	return legal;
}
