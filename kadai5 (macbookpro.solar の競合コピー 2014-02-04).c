/***  kadai5.c  ***/
/***  s12169  2J34  松尾祐佳  ***/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_ARRAY 38

int GetnRow(char map[][MAX_ARRAY])
{
	int i=0;
	while (map[i][0] == '|' || map[i][0] == '*') i++;
	if(map[i][0] == '\0') {
		return i;
	} else {
		return -1;
	}
}

int GetnColumn(char map[][MAX_ARRAY])
{
	int i=0,j=0;
	while (map[0][i] != '\0' && i<MAX_ARRAY) {
		if (map[0][i] == '|') j++;
		if (map[0][i] == '*' && i%2==0) j++;
		i++;
	}
	if(map[0][i] == '\0' ) {
		return j;
	} else {
		return -1;
	}
}

void DisplayAmida(char map[][MAX_ARRAY])
{
	int i,j;
	for (i=0; i<GetnColumn(map); i++){
		printf("   %d",i);
	}
	printf("\n");
	for (i=0; i<GetnRow(map); i++) {
		printf("%2d ",i);
		for (j=0; j<GetnColumn(map)*2-1; j++) {
			if (map[i][j] == ' ') {
				printf("   ");
			} else if (map[i][j] == '-') {
				printf("---");
			} else if (map[i][j] == '*') {
				if (j%2 != 0) {
					printf("***");
				} else {
					printf("*");
				}
			} else if (map[i][j] == '|') {
				printf("|");
			}
		}
		printf("\n");
	}
	for (i=0; i<GetnColumn(map); i++){
		printf("   %c",'A'+i);
	}
	printf("\n");
}

int RemoveBarfromAmida(char map[][MAX_ARRAY],int rmrow,int rmcol)
{
	int row, col, i=-1;
	row = GetnRow(map);
	col = GetnColumn(map);
	if (rmcol >= 0 && rmrow > 0 && rmcol < col-1 && rmrow < row-1 && map[rmrow][2*rmcol+1] == '-') {
		map[rmrow][2*rmcol+1] = ' ';
		return 0;
	} else { 
		return -1;
	}
}

int AddBartoAmida(char map[][MAX_ARRAY],int addrow,int addcol)
{
	int row, col;
	row = GetnRow(map);
	col = GetnColumn(map);
	if (addcol >= 0 && addrow > 0 && addcol < col-1 && addrow < row-1 && map[addrow][2*addcol+1] == ' ' && map[addrow][2*addcol-1] != '-' && map[addrow][2*addcol+3] != '-') {
		map[addrow][2*addcol+1] = '-';
		return 0;
	} else {
		return -1;
	}
}

int GenerateAmida(char map[][MAX_ARRAY], int nrow,int ncol,int nbar)
{
	int i, j, r, c, res;
	if (nrow < 3 || nrow >= MAX_ARRAY || ncol < 2 || ncol > MAX_ARRAY / 2 || nbar < 0 || nbar > (nrow - 2)*(ncol - 1) / 2) return -1;
	for(i=0; i<nrow+1; i++) {
		for(j=0; j<2*ncol; j++) {
			if (j%2 == 0) {
				map[i][j] = '|';
			} else {
				map[i][j] = ' ';
			}
		}
		map[i][2*ncol+1] = '\0';
	}
	for(j=0; j<=2*ncol+1; j++) {
		map[nrow][j] = '\0';
	}
	for (i=0; i<nbar; i++) {
		do {
			r = rand()%(nrow-1) + 1;
			c = rand()%(ncol);
			res = AddBartoAmida(map, r, c);
		} while (res != 0);
	}
	
	return nbar;
}

void InitAmida(char map[][MAX_ARRAY])
{
	static char isRandInit=0;
	int i,j;
	time_t t;
	for(i=0;i<MAX_ARRAY;i++) {
		for(j=0;j<MAX_ARRAY;j++) {
			map[i][j]='\0';
		}
	}
	
	if(!isRandInit) {
		srand((unsigned)time(&t));
		isRandInit=1;
	}
}

int SolveAmida(char map[][MAX_ARRAY],int start)
{
	char solmap[MAX_ARRAY][MAX_ARRAY];
	int row, col;
	int i, j;
	
	row = GetnRow(map);
	col = GetnColumn(map);
	
	if (start < 0 || start > col-1) return -1;
	
	for (i=0; i<MAX_ARRAY; i++) {
		for (j=0; j<MAX_ARRAY; j++) {
			solmap[i][j] = map[i][j];
		}
	}
	
	i=0;
	j=2*start;
	
	while (solmap[i][j] != '\0') {
		solmap[i][j] = '*';
		if (i!=0 && i!=row-1 && j<col*2-2 && solmap[i][j+1] == '-') {
			solmap[i][j+1] = '*';
			solmap[i][j+2] = '*';
			j+=2;
		} else if (i!=0 && i!=row-1 && j!=0 && solmap[i][j-1] == '-') {
			solmap[i][j-1] = '*';
			solmap[i][j-2] = '*';
			j-=2;
		}
		i++;
	}
	DisplayAmida(solmap);
	return j/2;
}

int main(void)
{
	char map[MAX_ARRAY][MAX_ARRAY];
	int a, b, c, res, kind = 0, count = 0, flag = 0;
	
	InitAmida(map);
	while (flag == 0) {
		while (kind < 1 || kind > 6) {
			if (count != 0) printf("処理番号が適切ではありません．\n");
			printf("\n------------------------------処理メニュー------------------------------\n");
			printf("1:作成 2:表示 3:横棒の削除 4:横棒の追加 5:解を求める 6:終了\n");
			printf("処理番号を入力--->");
			scanf("%d", &kind);
			count++;
		}

		if (kind == 1) {
			printf("縦棒の行数，列数と横棒の本数を入力([行数][列数][横棒の本数])--->");
			scanf("%d %d %d", &a, &b, &c);
			res = GenerateAmida(map, a, b, c);
			if (res == -1) printf("指定した条件であみだくじを作成できませんでした．\n");
			else DisplayAmida(map);
		} else if (kind == 2) {
			DisplayAmida(map);
		} else if (kind == 3) {
			printf("横棒を削除する位置を入力([行][列])--->");
			scanf("%d %d", &a, &b);
			res = RemoveBarfromAmida(map, a, b);
			if (res == -1) printf("指定した位置の横棒を削除できませんでした．\n");
		} else if (kind == 4) {
			printf("横棒を追加する位置を入力([行][列])--->");
			scanf("%d %d", &a, &b);
			res = AddBartoAmida(map, a, b);
			if (res == -1) printf("指定した位置に横棒を追加できませんでした．\n");
		} else if (kind == 5) {
			printf("始点の位置を入力([列番号])--->");
			scanf("%d", &a);
			res = SolveAmida(map, a);
			if (res != -1) printf("終点=%c\n",'A'+res);
			else printf("解を求めることができませんでした．\n");
		} else if (kind == 6) {
			flag++;
		}

		kind = 0;
		count = 0;
	}

	return 0;
}

/* 実行結果 

始点の位置を入力([列番号])--->3
   0   1   2   3   4
 0 |   |   |   *   |
 1 |---|   *****   |
 2 |   |   *   |---|
 3 |   *****   |   |
 4 |   *****   |---|
 5 |---|   *****   |
 6 |   |   |   *   |
 7 |---|   |   *****
 8 |   |---|   |   *
 9 |   |   |---|   *
10 |   |---|   *****
11 |---|   *****   |
12 |   |   *   |   |
13 |   *****   |---|
14 *****   |   |   |
15 *   |   |   |   |
   A   B   C   D   E
終点=A

始点の位置を入力([列番号])--->-1

*/