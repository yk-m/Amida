/*** k/*** kadai7.c PNM ファイル出力プログラム ***/
/*** s12169 2J34 松尾祐佳 ***/ 
#include<stdio.h> 
#include<stdlib.h> 

#define MAX_FNAME 256 /* ファイル名の最大長 */ 
#define MAX_PIXEL 256 /* 扱える最大画素数 */ 

/* PNM ヘッダ構造体 */ 
typedef struct { 
	int Magic; /* マジックナンバー：整数部のみ */ 
	int HSize; /* 横画素数 */ 
	int VSize; /* 縦画素数 */ 
	int MaxY; /* 最大輝度 */ 
} PNMHeader; 

/* PBM/PGM ファイル出力関数 */ 
int WritePNMMonoFile(char fname[],PNMHeader head,unsigned char y[][MAX_PIXEL]) 
{
	int i, j;
	FILE *out;
	out=fopen(fname,"wb");
	if (out==NULL) return -1;
	if (head.Magic != 1 && head.Magic != 2) return -1;
	if (head.HSize <= 0 || head.VSize <= 0 || head.HSize > MAX_PIXEL || head.VSize > MAX_PIXEL) return -1;
	
	fprintf(out,"P%d\n%d %d\n", head.Magic, head.HSize, head.VSize);
	
	if (head.Magic != 1 && head.Magic != 4) fprintf(out,"%d\n", head.MaxY);
	
	for (i=0; i<head.VSize; i++) {
		for (j=0; j<head.HSize; j++) {
			fprintf(out,"%d\n", y[i][j]);
		}
	}
	
	fclose(out);
	return 0; 
}

int main(void) 
{
	PNMHeader head_b; /* サンプル 2 値画像 yb に対する PNM ヘッダ */ 
	PNMHeader head_g; /* サンプル濃淡画像 yg に対する PNM ヘッダ */ 
	
	unsigned char yb[MAX_PIXEL][MAX_PIXEL]= {
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}, 
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1}
	}; 
	 
	 /* サンプル濃淡画像 */ 
	unsigned char yg[MAX_PIXEL][MAX_PIXEL]= {
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		 72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72,36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}, 
		{255,255,255,255,218,218,218,218,182,182,182,182,145,145,145,145,109,109,109,109, 
		72, 72, 72, 72, 36, 36, 36, 36, 0, 0, 0, 0}
	};
	
	char fname_b[MAX_FNAME], fname_g[MAX_FNAME];
	
	printf("2値画像のファイル名: ");
	gets(fname_b);
	printf("濃淡画像のファイル名: ");
	gets(fname_g);
	
	head_b.Magic = 1;
	head_b.HSize = 24;
	head_b.VSize = 20;
	
	head_g.Magic = 2;
	head_g.HSize = 32;
	head_g.VSize = 15;
	head_g.MaxY = 255;
	
	WritePNMMonoFile(fname_b, head_b, yb);
	WritePNMMonoFile(fname_g, head_g, yg);
	
	return 0; 
} 

/* 実行結果 

2値画像のファイル名: ex0202.pbm
濃淡画像のファイル名: ex0202.pgm

*/