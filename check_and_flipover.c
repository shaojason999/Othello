extern int gameboard[9][9];    //use gameboard[1][1]~gameboard[8][8]
extern unsigned long long int board[3];

int check_legal(int row, int column, int color)
{
	int legal=0;
	int opponent_color;
	int i,j;
	unsigned long long int temp=1;
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
				for(j=i+1;j<row;++j){
					gameboard[j][column]=color;
					board[color]|=temp<<(((8-j)<<3)+(8-column));
					board[opponent_color]&=~(temp<<(((8-j)<<3)+(8-column)));
				}
			}else
				break;
	/*check down*/
	for(i=row+1;i<=8;++i)
		if(gameboard[i][column]!=opponent_color)
			if(gameboard[i][column]==color && i!=(row+1)){
				legal=1;
				for(j=i-1;j>row;--j){
					gameboard[j][column]=color;
					board[color]|=temp<<(((8-j)<<3)+(8-column));
					board[opponent_color]&=~(temp<<(((8-j)<<3)+(8-column)));
				}
			}else
				break;
	/*check right*/
	for(i=column+1;i<=8;++i)
		if(gameboard[row][i]!=opponent_color)
			if(gameboard[row][i]==color && i!=(column+1)){
				legal=1;
				for(j=i-1;j>column;--j){
					gameboard[row][j]=color;
					board[color]|=temp<<(((8-row)<<3)+(8-j));
					board[opponent_color]&=~(temp<<(((8-row)<<3)+(8-j)));
				}
			}else
				break;
	/*check left*/
	for(i=column-1;i>0;--i)
		if(gameboard[row][i]!=opponent_color)
			if(gameboard[row][i]==color && i!=(column-1)){
				legal=1;
				for(j=i+1;j<column;++j){
					gameboard[row][j]=color;
					board[color]|=temp<<(((8-row)<<3)+(8-j));
					board[opponent_color]&=~(temp<<(((8-row)<<3)+(8-j)));
				}
			}else
				break;
	/*check upper right*/
	for(i=1;(row-i)>0 && (column+i)<=8;++i)
		if(gameboard[row-i][column+i]!=opponent_color)
			if(gameboard[row-i][column+i]==color && i!=1){
				legal=1;
				for(j=i-1;j>0;--j){
					gameboard[row-j][column+j]=color;
					board[color]|=temp<<(((8-(row-j))<<3)+(8-(column+j)));
					board[opponent_color]&=~(temp<<(((8-(row-j))<<3)+(8-(column+j))));
				}
			}else
				break;
	/*check bottom left*/
	for(i=1;(row+i)<=8 && (column-i)>0;++i)
		if(gameboard[row+i][column-i]!=opponent_color)
			if(gameboard[row+i][column-i]==color && i!=1){
				legal=1;
				for(j=i-1;j>0;--j){
					gameboard[row+j][column-j]=color;
					board[color]|=temp<<(((8-(row+j))<<3)+(8-(column-j)));
					board[opponent_color]&=~(temp<<(((8-(row+j))<<3)+(8-(column-j))));
				}
			}else
				break;
	/*check upper left*/
	for(i=1;(row-i)>0 && (column-i)>0;++i)
		if(gameboard[row-i][column-i]!=opponent_color)
			if(gameboard[row-i][column-i]==color && i!=1){
				legal=1;
				for(j=i-1;j>0;--j){
					gameboard[row-j][column-j]=color;
					board[color]|=temp<<(((8-(row-j))<<3)+(8-(column-j)));
					board[opponent_color]&=~(temp<<(((8-(row-j))<<3)+(8-(column-j))));
				}
			}else
				break;
	/*chech bottom right*/
	for(i=1;(row+i)<=8 && (column+i)<=8;++i)
		if(gameboard[row+i][column+i]!=opponent_color)
			if(gameboard[row+i][column+i]==color && i!=1){
				legal=1;
				for(j=i-1;j>0;--j){
					gameboard[row+j][column+j]=color;
					board[color]|=temp<<(((8-(row+j))<<3)+(8-(column+j)));
					board[opponent_color]&=~(temp<<(((8-(row+j))<<3)+(8-(column+j))));
				}
			}else
				break;
	if(legal){
		gameboard[row][column]=color;
		board[color]|=temp<<(((8-row)<<3)+(8-column));
	}
	return legal;
}
