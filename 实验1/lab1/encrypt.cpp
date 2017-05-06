#include<stdlib.h>
#include<stdio.h>

void encrypt()
{
	int gcd(int,int);

    printf("please input secret key\n");
    printf("k1:");

    int k1,k2;
    scanf("%d",&k1);
    getchar();
    while(k1<0 || k1>=26)
    {
        printf("illegal k1!please input agian!\n");
        printf("k1:");
        scanf("%d",&k1);
        getchar();
    }

    printf("k2:");
    scanf("%d",&k2);
    getchar();
    while(gcd(k2,26)!=1)
    {
        printf("illegal k2!please input agian!");
        printf("k2:");
        scanf("%d",&k2);
        getchar();
    }

  //  char plainText[100]={'\0'};
  //  char cypherText[100]={'\0'};
    printf("open  the plain text file\n");
    //scanf("%s",plainText);
	FILE *fplain,*fcypher;
	if((fplain =fopen("plain.txt","a+"))==NULL)
	{
		printf("can't open plain.txt!\n'");
		exit(0);
	}
	if((fcypher = fopen("cypher.txt","a"))==NULL)
	{
		printf("can't open cypher.txt!\n'");
		exit(0);
	}
    //int i;
    char plainText = fgetc(fplain);
    char cypherText;
    //for(i=0; plainText[i]!='\0'; i++)
   // printf("%c",plainText);
    while(plainText != EOF)
    {
      //  printf("old:%d\n",plainText[i]);
        if(65<=plainText&& plainText<=90 )
        {
        //	printf(".......................");
        //    plainText[i]-=65;
            cypherText = ((plainText-65)*k2+k1)%26+65;
            fputc(cypherText,fcypher);
          //  printf("new:%d\n",cypherText[i]);
        }

        else if(97<=plainText && plainText<=122 )
        {
            //plainText[i]-=97;
            cypherText = ((plainText-97)*k2+k1)%26+97;
            fputc(cypherText,fcypher);
         //   printf("new:%d\n",cypherText[i]);
        }
        else
            {
            	cypherText=plainText;
				fputc(cypherText,fcypher);
			}
		plainText = fgetc(fplain);
        //    printf("%c\t%c",plainText[i],cypherText[i]);}
    }
    fclose(fplain);
    fclose(fcypher);

    printf("cipher text has been written into cypher.txt!\n");
  //  printf("%s\n\n",cypherText);
}

