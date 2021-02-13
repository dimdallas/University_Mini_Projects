/*The program is about drawing a church and its chapel.
  It takes 2 integers as input,
  one for the height of the church and
  one for the windows of the chapel.*/
/*The program was scripted for Programming 101 of my University.
  The point is to play with ASCII characters while while implementing
  double-nested and triple-nested loops*/

#include <stdio.h>

int main (int argc, char *argv[])
{
	int height;                    /* Roof height (number of rows) */
	int i, j, k, n;                /* counters: i=rows, j=columns, k=spaces, n=windows */
	int door_height;
	int door_width;
	int windows_size;              /* church windows (height == width == size) */
	int windows;                   /* chapel windows number */
	int width;                     /* chapel width */
	const int WALL_WINDOW_SPACE=2;
	const int WINDOW_WINDOW_SPACE=1;
	const int WINDOWS_WIDTH=4;

	/*Running constraints
	  HEIGHT >=9 && WINDOWS >=1*/
	do 
	{
		printf("Enter height of roof: ");
		scanf(" %d", &height);
		printf("Enter windows number of chapel: ");
		scanf(" %d", &windows);
	} while (height<9 || windows<1);

	/*Door dimensions*/
	if (height/3>=5)
		door_height = height/3;
	else
		door_height = 5;       /*minimum door height*/
	
	if (height/3>=6)
		door_width = height/3;      
	else
		door_width = 6;        /*minimum door width*/

	/*Church windows' dimensions*/
	windows_size = height/4;
	if (windows_size%2==1)
		windows_size--;        /*to end up with diamond shape*/

	/*Chapel windows' dimensions*/
	if (windows%2==1)
		width= windows*WINDOWS_WIDTH +
		 (windows-1)*WINDOW_WINDOW_SPACE +2*WALL_WINDOW_SPACE+2;
	else
		width= windows*WINDOWS_WIDTH +
		 (windows-1)*WINDOW_WINDOW_SPACE +2*WALL_WINDOW_SPACE+1;

	/*Draw church roof*/
	for (i=1; i<=height; i++)
	{
		for (j=1; j<=i; j++)
		{
			if (j==1)
			{
				for (k=1; k<=(height-i); k++)
					printf(" ");
			}
			printf("/\\");
		}
		/*1st line of chapel roof*/
		if (i==height)
		{
			for (j=1; j<=width; j++)
				printf("_");
		}
		printf("\n");
	}

	/*Draw Church buildig*/
	for (i=1; i<=height; i++)
	{
		/*draw roof-building transaction*/
		if (i==1)
		{
			for (j=1; j<=height*2; j++)
			{
				if (j==1 || j==height*2)
					printf("|");
				else
					printf("~");
			}
		}
		/*draw church windows*/
		if (i>height/4 && i<=windows_size+height/4)
		{
			for (j=1; j<=height*2; j++)
			{
				if (j==1 || j==height*2)
				{
					printf("|");
					continue;
				}
				if (height%2==0)
				{
					/*Draw windows' upper half*/
					if (i<=height/4+windows_size/2)
					{
						if (j==height/2-(i-height/4)+1 || j==3*height/2-(i-height/4)+1)
						{
							printf("/");
						}
						else 
						{
							if (j==height/2+(i-height/4) || j==3*height/2+(i-height/4))
								printf("\\");
							else
								printf(" ");
						}
					}
					/*Draw windows' lower half*/
					else 
					{
						if (j==height/2-windows_size+(i-height/4) || 
							j==3*height/2-windows_size+(i-height/4))
						{
							printf("\\");
						}
						else 
						{
							if (j==height/2+windows_size-(i-height/4)+1 || 
								j==3*height/2+windows_size-(i-height/4)+1)
								printf("/");
							else
								printf(" ");
						}
					}
				}
				else
				{
					/*Draw windows' upper half*/
					if (i<=height/4+windows_size/2)
					{
						if (j==height/2-(i-height/4)+2 || 
							j==3*height/2-(i-height/4)+1)
						{
							printf("/");
						}
						else 
						{
							if (j==height/2+(i-height/4)+1 || 
								j==3*height/2+(i-height/4))
								printf("\\");
							else
								printf(" ");
						}
					}
					/*Draw windows' lower half*/
					else 
					{
						if (j==height/2-windows_size+(i-height/4)+1 || 
							j==3*height/2-windows_size+(i-height/4))
						{
							printf("\\");
						}
						else 
						{
							if (j==height/2+windows_size-(i-height/4)+2 || 
								j==3*height/2+windows_size-(i-height/4)+1)
								printf("/");
							else
								printf(" ");
						}
					}
				}
			}
		}
		/*Draw "empty" space of church building*/
		if ((i>1 && i<=height/4)||
			(i>height/4+windows_size && i<=height-door_height))
		{
			for (j=1; j<=height*2; j++)
			{
				if (j==1 || j==height*2)
					printf("|");
				else
					printf(" ");
			}
		}
		/*Draw 1st door top*/
		if (i==height-door_height+1)
		{
			for (j=1; j<=height*2; j++)
			{
				if (j==1 || j==height*2)
				{
					printf("|");
					continue;
				}
				if (j>=height-door_width/2+3 && j<=height+door_width/2-2)
				{
					printf("_");
					continue;
				}
				else
					printf(" ");
			}
		}
		/*Draw 2nd door stop*/
		if (i==height-door_height+2)
		{
			for (j=1; j<=height*2; j++)
			{
				if (j==1 || j==height*2)
				{	
					printf("|");
					continue;
				}
				if (j==height-door_width/2+2)
				{
					printf("/");
					continue;
				}
				if (j==height+door_width/2-1)
				{
					printf("\\");
					continue;
				}
				else
					printf(" ");
			}
		}
		/*Draw door main body*/
		if (i>height-door_height+2 && i<height)
		{
			for (j=1; j<=height*2; j++)
			{
				/*xeroyli portas*/
				if (i==height-door_height/2+1)
				{
					if (j==height-door_width/2+2)
					{	
						printf("_");
						continue;
					}
					if (j==1 || j==height*2 || 
						j==height-door_width/2+1 || j==height+door_width/2)
						printf("|");
					else
						printf(" ");
				}
				else	
				{	
					if (j==1 || j==height*2 || 
						j==height-door_width/2+1 || j==height+door_width/2)
						printf("|");
					else
						printf(" ");
				}
			}
		}
		/*Draw door bottom*/
		if (i==height)
		{
			for (j=1; j<=height*2; j++)
			{
				if (j==1 || j==height*2 || 
					j==height-door_width/2+1 || j==height+door_width/2)
					printf("|");
				else
					printf("_");
			}
		}
		/*Draw chapel roof*/
		for (j=1; j<=width+1 && i<=height/2; j+=2)
		{
			if (j==1 )
			{
				for (k=i; k>1; k--)
				{
					printf(" ");
				}
			}

			if (j>=1 && j<width)
			{
				printf("\\/");
			}

			if (j==width || j==width+1)
			{
				printf("\\");
			}
		}

		/*Draw chapel main building*/
		for (j=1; j<=width && i>height/2; j++)
		{
			if (j==1)
			{
				/*Draw "empty" space of building*/
				if (i<height)
				{
					for (k=1; k<height/2; k++)
					{
						printf(" ");
					}
				}
				if (i==height)
				{
					for (k=1; k<height/2; k++)
					{
						printf("_");
					}
				}
				printf("|");				
			
				/*--------------------------*/

				/*Draw chapel windows*/
				if (i==3*(height/2)/2)
				{
					printf("  ");
					for (n=1; n<=windows; n++) 
					{
						printf(" /\\ ");
						if (n==windows)
							continue;
						printf(" ");
					}
					if (windows%2==0)
						printf("  |");
					else
						printf("   |");
					break;
				}
				if (i==3*(height/2)/2+1)
				{	
					printf("  ");
					for (n=1; n<=windows; n++)
					{
						printf("|  |");
						if (n==windows)
							continue;
						printf(" ");
					}
					if (windows%2==0)
						printf("  |");
					else
						printf("   |");
					break;
				}
				if (i==3*(height/2)/2+2)
				{
					printf("  ");
					for (n=1; n<=windows; n++)
					{
						printf("|__|");
						if (n==windows)
							continue;
						printf(" ");
					}
					if (windows%2==0)
						printf("  |");
					else
						printf("   |");
					break;
				}
			}	
			
			if (i==height && j<width)
				printf("_");
			if (i<height && j<width)
				printf(" ");
			
			if (j==width)
			{
				printf("|");
			}
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}
