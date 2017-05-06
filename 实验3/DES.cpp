#include <stdio.h>
#include "time.h"
#include "stdlib.h"
#include "string.h"
      
static int IP_Table[64] = { 57,49,41,33,25,17,9,1,
                                 59,51,43,35,27,19,11,3,
                                 61,53,45,37,29,21,13,5,
                                 63,55,47,39,31,23,15,7,
                                 56,48,40,32,24,16,8,0,
                                 58,50,42,34,26,18,10,2,
                                 60,52,44,36,28,20,12,4,
                                 62,54,46,38,30,22,14,6};
 
static int IP_1_Table[64] = {39,7,47,15,55,23,63,31,
           38,6,46,14,54,22,62,30,
           37,5,45,13,53,21,61,29,
           36,4,44,12,52,20,60,28,
           35,3,43,11,51,19,59,27,
           34,2,42,10,50,18,58,26,
           33,1,41,9,49,17,57,25,
           32,0,40,8,48,16,56,24};

static int E_Table[48] = {31, 0, 1, 2, 3, 4,
                  3, 4, 5, 6, 7, 8,
                  7, 8,9,10,11,12,
                  11,12,13,14,15,16,
                  15,16,17,18,19,20,
                  19,20,21,22,23,24,
                  23,24,25,26,27,28,
                  27,28,29,30,31, 0};

static int P_Table[32] = {15,6,19,20,28,11,27,16,
                  0,14,22,25,4,17,30,9,
                  1,7,23,13,31,26,2,8,
                  18,12,29,5,21,10,3,24};

static int S[8][4][16] ={
{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
 
{{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
 
{{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
 
{{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
 
{{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
 
{{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
 
{{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
 
{{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};
 
static int PC_1[56] = {56,48,40,32,24,16,8,
              0,57,49,41,33,25,17,
              9,1,58,50,42,34,26,
              18,10,2,59,51,43,35,
              62,54,46,38,30,22,14,
              6,61,53,45,37,29,21,
              13,5,60,52,44,36,28,
              20,12,4,27,19,11,3};

static int PC_2[48] = {13,16,10,23,0,4,2,27,
              14,5,20,9,22,18,11,3,
              25,7,15,6,26,19,12,1,
              40,51,30,36,46,54,29,39,
              50,44,32,46,43,48,38,55,
              33,52,45,41,49,35,28,31};

static int MOVE_TIMES[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

static unsigned char SubKey[16][48];

void ByteToBit(unsigned char *ch,unsigned char *bit);
void BitToByte(unsigned char *bit,unsigned char *ch);
void Xor(unsigned char *A,unsigned char *B,int len);
void Transform(unsigned char *str,unsigned char *change,int *table,int len);
void Rotatel(unsigned char *str, int loop);
void MakeSubKeys(unsigned char *k);
void F_fun(unsigned char *M,unsigned char *key);
void DES_Encrypt(unsigned char *plain,unsigned char *cipher);
void DES_Decrypt(unsigned char *cipher,unsigned char *plain);



void ByteToBit(unsigned char* ch,unsigned char* bit){
	int i,j;
	for(i=0; i<8; i++){
    	for(j = 0;j< 8; j++){
        	bit[i*8+j] = (*(ch+i)>>j)&1;
    	}
	}
}

void BitToByte(unsigned char *bit, unsigned char *ch)
{
	int i,j;
	memset(ch,0,9);
    for(i=0; i<8; i++){
    	for(j = 0;j< 8; j++){
        	ch[i] |= *(bit + j+8*i)<<j;
    	}
	}
}

void Transform(unsigned char *str,unsigned char *change,int *table,int len){
	int i;
	for(i=0;i<len;i++){
		change[i]=str[table[i]];
	}
}

void Rotatel(unsigned char *str, int loop)
{
    static unsigned char Tmp[256];
    memcpy(Tmp, str, loop);
    memcpy(str, str+loop, 28-loop);
    memcpy(str+28-loop, Tmp, loop);
}
void MakeSubKeys(unsigned char *k){
	unsigned char str[64],key[64],*KL=&key[0],*KR=&key[28];
	int i;
	ByteToBit(k,str);
	Transform(str,key,PC_1,56);
	for(i=0;i<16;i++){
		Rotatel(KL,MOVE_TIMES[i]);
		Rotatel(KR,MOVE_TIMES[i]);
		Transform(key,SubKey[i],PC_2,48);
	}
}

void DES_Encrypt(unsigned char *plain,unsigned char *cipher){
	unsigned char str[256];
	int i;
	unsigned char M[64],*ML=&M[0],*MR=&M[32],Tmp[32];
	ByteToBit(plain,str);
	Transform(str,M,IP_Table,64);
	for(i=0; i<16; i++) 
		{
            memcpy(Tmp, MR, 32);
            F_fun(MR, SubKey[i]);
            Xor(MR, ML,32);
            memcpy(ML, Tmp, 32);
        }
    Transform(M, str, IP_1_Table, 64);
    BitToByte(str,cipher);
}
void DES_Decrypt(unsigned char *cipher,unsigned char *plain){
	unsigned char str[256];
	int i;
	unsigned char M[64],*ML=&M[0],*MR=&M[32],Tmp[32];
	ByteToBit(cipher,str);
	Transform(str,M,IP_Table,64);
	memcpy(ML,M,32);
	memcpy(MR,M+32,32);
	for(i=15; i>=0; i--) 
		{
            memcpy(Tmp, ML, 32);
            F_fun(ML, SubKey[i]);
            Xor(ML, MR,32);
            memcpy(MR, Tmp, 32);
        }
    Transform(M, str, IP_1_Table, 64);
    BitToByte(str, plain);
}


void F_fun(unsigned char *M,unsigned char *key){
	unsigned char str[48],out[48];
	int i,f;
	unsigned char j,k,g;
	Transform(M, str, E_Table, 48);
	Xor(str,key,48);
	memset(out,0,49);
	for(i=0; i<8; i++) 
	{
		g=i*6;
        j = (str[g]<<1) + str[g+5];
        k = (str[g+1]<<3) + (str[g+2]<<2) + (str[g+3]<<1) + str[g+4];
		for(f=0;f<4;f++){
			g=f+4*i;
			out[g]=(S[i][j][k]>>(f))&1;
		}
    }
    Transform(out, M , P_Table, 32);
}

void Xor(unsigned char *A,unsigned char *B,int len)
{
	int i;
    for(i=0; i<len; i++)
        A[i] ^= B[i];
}

int main(){
	int i=0;
	unsigned char K[8]="0110111";
	unsigned char plain[8] ;
	unsigned char cipher[8];
	unsigned char str[8];
	memset(str,0,8);
	MakeSubKeys(K);
	printf("please input the plain text(no more than 7 characters)£º\n");
	scanf("%s",plain);
	printf("the cypher text is\n");
	DES_Encrypt(plain,cipher);
	printf("%s\n",cipher);
	puts("here is the text after decode:\n");
	DES_Decrypt(cipher,str);
	printf("%s\n",str);
	return 0;
}



