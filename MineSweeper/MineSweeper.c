/*Terminal version of classic Mine Sweeper game.*/

/*Player chooses difficulty level that affects board size.
  Game iterates and Player chooses a row and a column (bassically a cell).
  If cell contains a mine, game is over.
  If row #0 is chosen, game exits.
  If all cells not containing a mine are revealed, PLayer wins.
  Whenever game terminates, player is asked to restart.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 24   /*Maximum matrix dimension*/

char game[SIZE][SIZE];        /*Matrix containing game data*/
char displayed[SIZE][SIZE];   /*Matrix containing data displayed to Player*/

/*Matricies and game data initialization*/
void start (int size){
	int i, j, k, n, f;    /*i, k, counter for rows*/
	                      /*j, n counter for columns*/ 
	                      /*f counter for mines surrounding a certain cell*/
	int mines;            /*counter for mines placed*/
	int total_mines;      /*total mines that must be placed in current game*/
	double MAX_MINES=0.2; /*mines fulfillment percentage*/

	/*Zero data initialization*/
	for (i=0; i<size; i++) 
	{
		for (j=0; j< size; j++)
			displayed[i][j]='0';
	}
	for (i=0; i<size; i++)
	{
		for (j=0; j< size; j++)
			game[i][j]='0';
	}

	srand(time(NULL));
	total_mines = (size*size) * MAX_MINES;

	/*Mine placing*/
	for (mines=1; mines<=total_mines; mines++)
	{
		i = rand()%(size);
		j = rand()%(size);
		if (game[i][j]=='*')
			mines--;
		else
			game[i][j]='*';
	}
	/*Number placing by checking every cell and its surrounding cells*/
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			/*Cell is in the middle of the board*/
			if (i>=1 && i<=size-2 && j>=1 && j<=size-2)
			{
				if (game[i][j]!='*')
				{
					for (k=i-1, f=0; k<=i+1; k++)
					{
						for (n=j-1; n<=j+1; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
			
			/*Cell is on the top of the board*/
			if (i==0 && j>=1 && j<=size-2)
			{
				if (game[i][j]!='*')
				{
					for (k=i, f=0; k<=i+1; k++)
					{
						for (n=j-1; n<=j+1; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
			/*Cell is on the bottom of the board*/
			if (i==size-1 && j>=1 && j<=size-2)
			{
				if (game[i][j]!='*')
				{
					for (k=i-1, f=0; k<=i; k++)
					{
						for (n=j-1; n<=j+1; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
			/*Cell is on the left size of the board*/
			if (i>=1 && i<=size-2 && j==0)
			{
				if (game[i][j]!='*')
				{
					for (k=i-1, f=0; k<=i+1; k++)
					{
						for (n=j; n<=j+1; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
			/*Cell is on the right size of the board*/
			if (i>=1 && i<=size-2 && j==size-1)
			{
				if (game[i][j]!='*')
				{
					for (k=i-1, f=0; k<=i+1; k++)
					{
						for (n=j-1; n<=j; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
			/*Top left corner cell*/
			if (i==0 && j==0)
			{
				if (game[i][j]!='*')
				{
					for (k=i, f=0; k<=i+1; k++)
					{
						for (n=j; n<=j+1; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
			/*Top right corner cell*/
			if (i==0 && j==size-1)
			{
				if (game[i][j]!='*')
				{
					for (k=i, f=0; k<=i+1; k++)
					{
						for (n=j-1; n<=j; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
			/*Bottom left corner cell*/
			if (i==size-1 && j==0)
			{
				if (game[i][j]!='*')
				{
					for (k=i-1, f=0; k<=i; k++)
					{
						for (n=j; n<=j+1; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
			/*Bottom right corner cell*/
			if (i==size-1 && j==size-1)
			{
				if (game[i][j]!='*')
				{
					for (k=i-1, f=0; k<=i; k++)
					{
						for (n=j-1; n<=j; n++)
						{
							if (game[k][n]=='*')
								f++;
						}
					}
					game[i][j]='0'+f;
				}
			}
		}
	}
}

/*Victory condition check*/
int mine_check (int size)
{
	int i, j, k=0;         /*i counter for rows*/
	                       /*j counter for columns*/ 
	                       /*k counter for revealed cells not containing a mine*/
	int total_mines;
	double MAX_MINES=0.2;  /*mines fulfillment percentage*/

	total_mines = (size*size) * MAX_MINES;

	for (i=0; i<size; i++)  /*checks if cell is revealed and if it's not a mine*/
	{
		for (j=0; j< size; j++) 
		{
			if (displayed[i][j]=='1' && game[i][j]!='*')
				k++;
		}
	}
	if (k==(size*size)-total_mines)  /*total cells without a mine*/
	{
		printf("Congratulations you have solved the puzzle!\n");
		return 1;
	}
	else
		return 0;
}

/*Print Player board depending on Displayed Data matrix*/
void print_board (int size)
{
	int i, j;
	char watchable[SIZE][SIZE];   /*matrix of characters to be printed*/

	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			if (displayed[i][j]=='0')  /*Not revealed cell*/
			{
				watchable[i][j]='-';
			}
			else /* displayed==1 */    /*revealed cell*/
			{
				watchable[i][j]=game[i][j];
			}
		}
	}
	/*Print watchable matrix*/
	for (j=0; j<=size; j++)
	{
		if (j==0)
			printf("     ");
		else
			printf("%3d", j);
	}
	printf("\n\n");
	
	for (i=0; i<size; i++)
	{
		for (j=-1; j<size; j++)
		{
			if (j==-1)
				printf("%3d  ", i+1);
			else
				printf("%3c", watchable[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*Printing of game data when game is over*/
void print_solution (int size)
{
	int i, j;
	
	for (j=0; j<=size; j++)
	{
		if (j==0)
			printf("     ");
		else
			printf("%3d", j);
	}
	printf("\n\n");
	
	for (i=0; i<size; i++)
	{
		for (j=-1; j<size; j++)
		{
			if (j==-1)
				printf("%3d  ", i+1);
			else
				printf("%3c", game[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	char difficulty;      /* difficulty level input */
	int row, col;         /* row & column input */
	int difficulty_size;  /* board size based on difficulty */
	int flag;             /* Victory condition flag */
	char again;           /* restart input */
	
	do
	{
		do
		{
			printf("1. EASY (E,e)\n");
			printf("2. MEDIUM (M,m)\n");
			printf("3. EXPERT (X,x)\n");
			printf("Enter difficulty level: ");
			scanf(" %c", &difficulty);

			switch (difficulty)
			{
				case 'E':    /*difficulty EASY*/
				case 'e': {
					difficulty_size=6;
					start(difficulty_size);
					break;
				}
				case 'M':    /*epipedo dyskolias MEDIOUM*/
				case 'm': {
					difficulty_size=12;
					start(difficulty_size);
					break;
				}
				case 'X':    /*epipedo dyskolias EXPERT*/
				case 'x': {
					difficulty_size=24;
					start(difficulty_size);
					break;
				}

				default: {printf("Invalid selection.\n\n");}
			}
                  do
                  {
                    print_board(difficulty_size);

                    printf("Row> ");
                    scanf("%d", &row);
                    if (row==0)  	 /*exit game*/
                    {
                      printf("You selected to interrupt");
                      printf(" the current puzzle!\n\n");
                      break;
                    }
                    printf("Col> ");
                    scanf("%d", &col);

                    while (row<1||row>difficulty_size)
                    {
                      if (row==0)  /*exit game*/
                      {
                        printf("You selected to interrupt");
                        printf(" the current puzzle!\n");
                        break;
                      }
                      printf("Invalid Row. Try again!\n");
                      printf("Row> ");
                      scanf("%d", &row);
                    }
                    if (row==0)
                      break;
                    while (col<1||col>difficulty_size)
                    {
                      printf("Invalid Column. Try again!\n");
                      printf("Col> ");
                      scanf("%d", &col);
                    }

                    /*user to machine position convertion*/
                    displayed[row-1][col-1]='1';

                    if (displayed[row-1][col-1]=='1' &&
                        game[row-1][col-1]=='*')  /*cell contained mine*/
                    {
                      printf("Oops! You have selected a mine.\n");
                      print_solution(difficulty_size);
                      break;
                    }

                    flag=mine_check(difficulty_size);
                    if (flag==1)     /*Victory condition*/
                    {
                      print_solution(difficulty_size);
                      break;
                    }
                    else
                      continue;

                  }while ((row>=1 && row<=difficulty_size)&&
                          (col>=1 && col<=difficulty_size));
		}while(difficulty!='E' && difficulty!='e'&& difficulty!='M' &&
			difficulty!='m' && difficulty!='X' && difficulty!='x');		
		/*Loop while difficulty input is not defined*/

		do    /*Restart game question*/
		{
			printf("Play again? (y/n) ");
			scanf(" %c", &again);
			printf("\n");
			if (again=='N' || again=='n')  /*exit program*/
				break;
		}while(again!='Y' && again!='y');  /*Restart-input not defined*/
	}while(again=='Y' || again=='y');      /*Game loop*/

	return 0;
}
