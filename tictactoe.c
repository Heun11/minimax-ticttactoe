#include<stdio.h>

struct Move {int i,j;};

//#define MIN(a,b) (((a)<(b))?(a):(b))
//#define MAX(a,b) (((a)>(b))?(a):(b))

int max(int a, int b)
{
	return (a>b)?a:b;
}

int min(int a, int b)
{
	return (a<b)?a:b;
}

void printBoard(char board[3][3])
{
	printf("\n");
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%c ", board[i][j]);
		}
	printf("\n");
	}
	printf("\n");
}

int checkLeft(char board[3][3])
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]=='-'){return 1;}
		}
	}
	return 0;
}

int checkWinner(char board[3][3])
{
	char player='X', opponent='O';
	for(int r=0;r<3;r++){
		if(board[r][0]==board[r][1]&&board[r][1]==board[r][2]){
			if(board[r][0]==player){return +10;}
			else if(board[r][0]==opponent){return -10;}
		}
	}

	for(int c=0;c<3;c++){
		if(board[0][c]==board[1][c]&&board[1][c]==board[2][c]){
			if(board[0][c]==player){return +10;}
			else if(board[0][c]==opponent){return -10;}
		}
	}

	if(board[0][0]==board[1][1]&&board[1][1]==board[2][2]) {
		if(board[0][0]==player){return +10;}
		else if(board[0][0]==opponent){return -10;}
	}

	if(board[0][2]==board[1][1]&&board[1][1]==board[2][0]) {
		if(board[0][2]==player){return +10;}
		else if(board[0][2]==opponent){return -10;}
	}
	return 0;
}

int minimax(char board[3][3], int depth, int isMax)
{
	int score=checkWinner(board);
	if(score==10||score==-10){return score;}
	if(!checkLeft(board)){return 0;}

	if(isMax==1){
		int best=-1000;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]=='-'){
					board[i][j]='X';
					best=max(best, minimax(board, depth+1, 0));
					board[i][j]='-';
				}
			}
		}
		return best;
	}
	else{
		int best=1000;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]=='-'){
					board[i][j]='O';
					best=min(best, minimax(board, depth+1, 1));
					board[i][j]='-';
				}
			}
		}
		return best;

	}
}

struct Move bestMove(char board[3][3])
{
	int bestVal=-1000;
	int moveVal;
	struct Move bestMove;
	bestMove.i=-1;
	bestMove.j=-1;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]=='-'){
				board[i][j]='X';
				moveVal=minimax(board,0,0);
				board[i][j]='-';
				if(moveVal>bestVal){
					bestMove.i=i;
					bestMove.j=j;
					bestVal=moveVal;
				}
			}
		}
	}
	return bestMove;
}

void aiMove(char board[3][3])
{
	struct Move move=bestMove(board);
	board[move.i][move.j]='X';
	printf("%d %d\n", move.i,move.j);
}

void game()
{
	char board[3][3]={{'-','-','-'},{'-','-','-'},{'-','-','-'}};
	char winner = '-';
	char onTurn = 'X';
	while(winner=='-'){
		printBoard(board);
		if(checkWinner(board)!=0||checkLeft(board)==0){break;}
		printf("player %c is on turn\n", onTurn);

		if(onTurn=='X'){
			aiMove(board);
			onTurn='O';
		}
		else{
			int i,j;
			scanf("%d%d", &i, &j);
			if(board[i][j]=='-'&&(j>=0&&i>=0&&j<3&&i<3)){
				board[i][j]='O';
				onTurn='X';
			}
			else{continue;}
		}
	}
	winner=checkWinner(board);
	if(winner==10||winner==-10){
		if(winner==10){printf("player X won\n");}
		else{printf("player O won\n");}
	}
	else{
		printf("tie\n");
	}
}

int main()
{
	game();
	return 0;
}

