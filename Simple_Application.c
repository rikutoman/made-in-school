#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student
{
	int No[20];
	char name[20];
	char num[20];
}student;
void list_display1(student *pstd,int n);
int new_registration_to_list2(student *pstd,int n);
void save_list_into_file3(student *pstd,int n);
int file_from_data_loading4(student *pstd,int n);
void search_data5(student *pstd,int n);
int one_deleting_data6(student *pstd,int n);
void ascending_order_reordering7(student *pstd,int n);
void desc_reordering8(student *pstd,int n);
int main(void)
{
	int n=0;
	int i=0;
	char o[10];
	student std[20];
	char number[10];
	while(1)
	{
		printf("\n");
		printf("################################\n");
		printf("### 名簿作成アプリケーション ###\n");
		printf("################################\n");
		printf("0~8の番号から選択してください\n");
		printf("\n");
		printf("1.名簿の表示\n");
		printf("2.名簿への新規登録\n");
		printf("3.名簿をファイルへ保存\n");
		printf("4.ファイルからデータの読込\n");
		printf("5.学籍番号からデータを検索\n");
		printf("6.学籍番号からデータを1つ削除\n");
		printf("7.学籍番号で並び替え（昇順)\n");
		printf("8.学籍番号で並び替え（降順)\n");
		printf("\n");
		printf("0.終了\n");
		
		printf("※最初の一文字で番号が認識されます　例（83は8になります）\n");
		printf("番号を入力(1〜)--->");
		scanf("%s",o);
		strncpy(number,o,1);
		number[1] = '\0';
		printf("\n");
		
		int rm = number[0] - '0';
		
			switch(rm)
			{
				case 0:
					printf("アプリケーションを終了します\n");
					exit(0);
					break;
				case 1:
					for(i=1;i<=n;i++)
					{
						*std[i-1].No=i;
					}
					for(i=0;i<n;i++)
					{
						list_display1(&std[i],n);
					}
					break;
				case 2:
				n=new_registration_to_list2(&std[n],n);
					break;
				case 3:
					save_list_into_file3(std,n);
					break;
				case 4:
					n=file_from_data_loading4(std,n);
					break;
				case 5:
					search_data5(std,n);
					break;
				case 6:
					n=one_deleting_data6(std,n);
					break;
				case 7:
					ascending_order_reordering7(std,n);
					break;
				case 8:
					desc_reordering8(std,n);
					break;
				default:
					printf("エラー！ 0~8の数字を入力してください\n");
					break;
			}
	}
}

void list_display1(student *pstd,int n)
{
	/*int i=0;
	printf("登録されている人数は【%d】人です\n",n);
	printf("No.\t名前\t学籍番号\n");
	while(i<n)
	{*/
		printf("%d\t%s\t%s\n",*pstd->No,pstd->name,pstd->num);
}
int new_registration_to_list2(student *pstd,int n)
{
	printf("名前を入力してください--->");
	scanf("%s",pstd->name);
	printf("学籍番号を入力してください--->");
	scanf("%s",pstd->num);
	n++;
	return n;
}

void save_list_into_file3(student *pstd,int n){
	
	FILE *fpw; 
	if( (fpw = fopen("student.txt", "w" )) == NULL ){
        printf( "結果ファイルがオープンできませんでした\n" );
        exit(1);
    }
	
	for(int i = 0;i<n;i++){
		fprintf(fpw,"%d\t%s\t%s\n",*pstd[i].No,pstd[i].name,pstd[i].num);
	}
	printf("student.txtに結果が出力されました\n");
	fclose(fpw);
}
int file_from_data_loading4(student *pstd,int n){
	FILE *fpr;
	int i=0;
	if( (fpr = fopen("student.txt", "r" )) == NULL ){
        printf( "結果ファイルがオープンできませんでした\n" );
        exit(1);
    }
	printf("No.\t名前\t学籍番号\n");
	while(fscanf(fpr,"%d\t%s\t%s",(pstd+i)->No,(pstd+i)->name,(pstd+i)->num) != EOF)
	{	
		//printf("%d\t%s\t%s\n",*pstd->No,pstd->name,pstd->num);
		i++;
	}

	printf("student.txtからデータを読み込みました\n");
	fclose(fpr);
	return i;
}
void search_data5(student *pstd,int n){
	int i=0;
	char search[20];
	printf("検索する学籍番号を入力してください．キャンセルは[cancel]->");
	scanf("%s",search);
	while(i<=n){
		if(strcmp(search,pstd[i].num) == 0)
		{
			printf("ーー 一致しました\n");
			
			printf("No.\t名前\t学籍番号\n");
			printf("%d\t%s\t%s\n",*pstd[i].No,pstd[i].name,pstd[i].num);
			break;
		}
		if(strcmp(search,"cancel")==0)
		{	
			printf("キャンセルされました\n");
			break;
		}
		if(i==n)
		{
			printf("--一致するデータが見つかりません\n");
			printf("--見つかりませんでした\n");
			break;
		}
		i++;
	}
}

int one_deleting_data6(student *pstd,int n){
	int i=0;
	char search[20];
	printf("検索する学籍番号を入力してください．キャンセルは[cancel]->");
	scanf("%s",search);
	while(i<=n)
	{
		if(strcmp(search,pstd[i].num) == 0)
		{
			printf("ーー 一致しました\n");
			
			printf("No.\t名前\t学籍番号\n");
			printf("%d\t%s\t%s\n",*pstd[i].No,pstd[i].name,pstd[i].num);
			printf("削除しました\n");
			while(i<n)
			{
				pstd[i]=pstd[i+1];
				i++;
			}
			n=i-1;
			break;
		}
		if(strcmp(search,"cancel")==0)
		{	
			printf("キャンセルされました\n");
			break;
		}
		if(i==n)
		{
			printf("--一致するデータが見つかりません\n");
			printf("--見つかりませんでした\n");
			break;
		}
		i++;
	}
	return n;
}
//昇順
void ascending_order_reordering7(student *pstd,int n){
	int i,j;
	struct student tmp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(strcmp(pstd[i].num,pstd[j].num) > 0)
			{
				
				tmp = pstd[i];
				pstd[i] = pstd[j];
				pstd[j] = tmp;
			}
		}
		
	}
	printf("昇順にソートしました\n");
	
}
//降順
void desc_reordering8(student *pstd,int n){
	int i,j;
	struct student tmp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(strcmp(pstd[i].num,pstd[j].num) < 0)
			{
				tmp = pstd[i];
				pstd[i] = pstd[j];
				pstd[j] = tmp;
			}
		}
		
	}
	printf("降順にソートしました\n");
}
