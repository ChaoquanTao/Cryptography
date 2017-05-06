#include <stdio.h>
#include<stdlib.h>
#include<math.h>

#define NUM  5
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	void init_lfsr(int *);
	void print_sequence(int *);
	void encrypt(int *);
	int reg[NUM] ;
	int choice ;
	while(1){
	
		printf("\nplease input your choice:\n");
		printf("\t1.init lfsr   2.print sequence   3.encrpt text   4.exit\n");
		scanf("%d",&choice);
		getchar();
		switch(choice){
			case 1:
				init_lfsr(reg);
				break;
			case 2:
				print_sequence(reg);
				break;
			case 3:
				encrypt(reg);
				break;
			case 4:
				exit(2); 
				
		}
	}
	return 0;
}

void init_lfsr(int *reg){
	void print_sequence(int *r);
	
	printf("please input initial sequence:\n");
	for(int i=0; i<NUM; i++){
		scanf("%d",&reg[i]);
		reg[i]%=2;
		getchar();
	}

/*
for(int i=0; i<2; i++)
		for(int j=0; j<2; j++)
			for(int k=0; k<2; k++)
				for(int m=0; m<2; m++)
					for(int n=0; n<2; n++)
					{
						reg[0]=i;reg[1]=j;reg[2]=k;reg[3]=m,reg[4]=n;
							printf("\ninitial sequence is :\n");
							for(int i=0; i<NUM; i++){
								printf("%d",reg[i]);
								//getchar();
							}
							printf("\n");
						print_sequence(reg);
	 				}
*/
	printf("initial sequence is :\n");
	for(int i=0; i<NUM; i++){
		printf("%d",reg[i]);
		//getchar();
	}
	printf("\n");

}

void print_sequence(int *r){
	int temp ;
	int count = 0 ;
	int change_row = 0;
	
	int *reg = (int *)malloc(NUM*sizeof(int));
	if(reg == NULL) exit(4);
	for(int i=0; i<NUM; i++){
		reg[i] = r[i];
	}
	int a[38] ;
	int ct=0; 
	while(count <= pow(2,NUM)+5){
		
//		printf("%d ",reg[0]);
		a[ct++] = reg[0] ;
		printf("%d ",a[ct-1]);
		change_row ++ ;
		if(change_row % 20 == 0)
			printf("\n") ; 
	
		temp = (reg[0]+reg[3])%2;
		int i;
		for( i=0; i<NUM-1; i++){
			reg[i] = reg[i+1] ;
		}
		reg[i] = temp ;
		count++ ;
	}
	
	for(int i=5; i<38; i++){
		int t =  i;
		int j ;
		for(j=0;j<5;j++){
			if(a[j]!=a[t]){
				break ;
				
			}
			t++;
		}
			if(5==j){
				printf("\nquery length:%d\n",i) ;
				break ;
			}
		
	}
	
	free(reg);	
}

void encrypt(int *r){
	
	FILE *fp1,*fp2 ;
	int plain ;
	int cypher ;
	int temp ;
	
	int *reg = (int *)malloc(NUM*sizeof(int));
	if(reg == NULL) exit(4);
	for(int i=0; i<NUM; i++){
		reg[i] = r[i];
	}
	
	if((fp1 = fopen("plain.txt","r"))==NULL){
		printf("can't open file plian.txt!");
		exit(0);
	}
	
	if((fp2 = fopen("cypher.txt","a"))==NULL){
		printf("can't open file cypher.txt!");
		exit(1);
	}
//	 fseek(fp1,0L,SEEK_SET);	
//	fscanf(fp1,"%d",&plain);
	char ch[1];
    ch[0] = fgetc(fp1);
//	printf("char:%c\n",ch[0]);
	plain = atoi(ch);
//	printf("plain:%d\n",plain);
	while(!feof(fp1)){
		cypher = (plain + reg[0])%2 ;
		fprintf(fp2,"%d",cypher);
		printf("%d",cypher);
		
		temp = (reg[0]+reg[3])%2;
		int i;
		for( i=0; i<NUM-1; i++){
			reg[i] = reg[i+1] ;
		}
		reg[i] = temp ;
		
		//fscanf(fp1,"%d",&plain);
		ch[0] = fgetc(fp1);
//	printf("char:%c\n",ch[0]);
	plain = atoi(ch);
//	printf("plain:%d\n",plain);
	}
	
	fclose(fp1);
	fclose(fp2);
	
	free(reg);	
}


