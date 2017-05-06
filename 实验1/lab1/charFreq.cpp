#include<stdio.h>
#include<stdlib.h>


void calculateCharFreq(){

	char filename[10]={'\0'};
	char ch;
	FILE * fp;
	float sum=0;
	float freq[26]={0};
	float charNum[26]={0};

	printf("please input the filename  you wanna staticstic frequence:\n ");
	//getchar();
	gets(filename);
	//getchar();
	if((fp =fopen(filename,"r"))==NULL)
	{
		printf("can't open %s!\n",filename);
		exit(0);
	}

	ch = fgetc(fp);
	while(ch != EOF){
		if('a'<=ch &&ch<='z') {
			charNum[ch-97]++;
			sum++;
			//printf("charNum:%f\tsum:%f\n",charNum[ch-97],sum);
		}

		else if(ch>='A' && ch<='Z'){
			charNum[ch-65]++;
			sum++;
		}
    //printf("%c\n",ch);
		ch=fgetc(fp);
	}
    fclose(fp);
	//char t = 0;
	int count=0;
	for(int i=0;i<26;i++){

		freq[i] = charNum[i]/sum;
		//printf("charNUm:%f\tsum:%f\tfreq:%f\n",charNum[i],sum,freq[i]);
		printf("%c(%c):%.3f\t",i+65,i+97,freq[i]);
		count++;
		if(count==6){
			printf("\n");
			count=0;
		}
	}

    printf("\n\n");
}

