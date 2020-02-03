#include<stdio.h>
#include<stdlib.h>
int hantei(int x,char reverse[][2], int color);
void display();
int board[8][8]={};//8*8の盤面0を代入

int main(void)
{
	FILE *fpr;
	char data1[64][2],data2[64][2];
	char white[64][2]={0},black[64][2]={0};
	char a;
	char filename[100];
	int i=0;
	int x,y;
	//初期配置　//１が白　//-1が黒
	board[3][3]=1;
	board[3][4]=-1;
	board[4][3]=-1;
	board[4][4]=1;
	printf("棋譜を入力-->");
	scanf("%s",filename);
	
	if((fpr = fopen(filename,"r"))==NULL)
	{
		printf("ファイルが開けません\n");
		exit(1);
	}
	//[i]で[64][2]に一文字ずつ入れる
	while(fscanf(fpr,"%s\t%s",data1[i],data2[i])!=EOF)
	{
		//printf("%d\t%d\n",data1[i][2],data2[i][2]);
		i++;
	}
	fclose(fpr);
	//先手をblackの配列に入れる
	if(data1[0][0]=='-')
	{
		for(x=0;x<=63;x++)
		{
			for(y=0;y<2;y++)
			{
				white[x][y]=data1[x+1][y];
				black[x][y]=data2[x][y];
				//printf("%d\t%d\n",white[x][y],black[x][y]);
			}
		}
	}
	//後手をwhiteの配列に入れる
	else
	{
		for(x=0;x<=63;x++)
		{
			for(y=0;y<2;y++)
			{
				black[x][y]=data1[x][y];
				white[x][y]=data2[x][y];
			}
		}
	}
	for(x=0;x<=63;x++)
	{
		if(black[x][0]==0)//配列の中身が0になった場合終わり
		{
			break;
		}
		if(black[x][0]!='-')
		{
			board[black[x][0]-'a'][black[x][1]-49]=-1;
			hantei(x,black,-1);
			//printf("%d\n",hantei(x,black,-1));
			display();
		}
		if(white[x][0]==0)//配列の中身が0になった場合終わり
		{
			break;
		}
		if(white[x][0]!='-')
		{
			board[white[x][0]-'a'][white[x][1]-49]=1;//両方ASCIIコードで入る
			hantei(x,white,1);
			//printf("%d\n",hantei(x,white,1));
			display();
		}
		
	}
	return 0;
}
//周りの確認（左上，左，左下，上，下，右下，右，右上の順番で)をし、裏返すことが可能なら、黒→白になるのは1、白→黒になるのは-1を配列boardに代入する関数
int hantei(int x,char reverse[][2], int color)
{
	int i,j,k;
	int row=reverse[x][0]-'a';
	int column=reverse[x][1]-49;
	int temp_x[8],temp_y[8];
	//周りの確認（左上，左，左下，上，下，右下，右，右上の順番）
	for(i=-1;i<=1;i++)
	{
		for(j=-1;j<=1;j++)	
		{
			int look_x = row+i;
			int look_y = column+j;
			int rn=0;
			while(1)
			{
				//8×8以上の盤面を見たら終了
				if(look_x < 0 || look_x > 7 || look_y < 0 || look_y > 7)
				{
					break;
				}
				//配列boardの要素に0が入っていたら終了
				else if(board[look_x][look_y] == 0)
				{
					break;	
				}
				else if(board[look_x][look_y] == color)
				{
					if(rn > 0)
					{
						//自分の石を見つけたら終了
						for(k = 0;k < rn;k++)
						{
							board[temp_x[k]][temp_y[k]] = color;
						}
					}	
					break;	
				}
				else 
				{
					temp_x[rn] = look_x;
					temp_y[rn] = look_y;
					rn++;
					look_x = look_x + i;
					look_y = look_y + j;
				}	
			}
		}
	}	
	
	return 0;		
}
//オセロ盤面表示関数
void display()
{
	int x,y,white=0,black=0,sum_othello=0;
	for(x=0;x<=7;x++)
	{
		for(y=0;y<=7;y++)
		{
			if(board[y][x] == 1)
			{
				white++;
			}
			if(board[y][x] == -1)
			{
				black++;
			}
		}
	}
	sum_othello=white+black;
	if(sum_othello == 64)
	{
		printf("  a b c d e f g h\n");
		for(x=0;x<=7;x++)
		{
			if(x+1 < 9)
			{
				printf("%d",x+1);
			}
			for(y=0;y<=7;y++)
			{
				if(board[y][x] == 1)
				{
					printf("⚪️");
				}
				if(board[y][x] == -1)
				{
					printf("⚫️");
				}
			}
			printf("\n");
		}
		printf("黒%d 対 白%d\n",black,white);
		printf("\n");
	}
	return;
}

