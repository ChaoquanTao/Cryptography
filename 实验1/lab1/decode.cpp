#include<stdlib.h>
#include<stdio.h>
void decode()
{
	int gcd(int ,int);
	int inverse(int);

//	char cypherText[100]={'\0'};
//	char plainText[200]={'\0'};
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

	int inverse_k2 = inverse(k2);

	printf("open the cypher txt!\n");
//	scanf("%s",cypherText);

	FILE *fplain,*fcypher;
	if((fplain =fopen("plain1.txt","a"))==NULL)
	{
		printf("can't open plain.txt!\n'");
		exit(0);
	}
	if((fcypher = fopen("cypher.txt","r"))==NULL)
	{
		printf("can't open cypher.txt!\n'");
		exit(0);
	}
    //int i;
    char cypherText = fgetc(fcypher);
    char plainText;
    //for(i=0; plainText[i]!='\0'; i++)
  //  printf("%c",plainText);

//	int i;
  //  for(i=0; cypherText[i]!='\0'; i++)
  while(cypherText!=EOF)
    {
      //  printf("old:%d\n",plainText[i]);
        if(65<=cypherText&& cypherText<=90 )
        {
        //	printf(".......................");
        //    plainText[i]-=65;
            int t= cypherText-65-k1 ;
            if(t<0){
                int i=1;
                while(t<0){
                    t+=26 * i ;
                    i++;
                }
            }
            plainText = ((t*inverse_k2)%26)+65;
            fputc(plainText,fplain);
          //  printf("new:%d\n",cypherText[i]);
        }

        else if(97<=cypherText && cypherText<=122 )
        {
            //plainText[i]-=97;
            int t= cypherText-97-k1 ;
            if(t<0){
                int i=1;
                while(t<0){
                    t+=26 * i ;
                    i++;
                }
            }
            plainText = ((t*inverse_k2)%26)+97;

     //      printf("new:%d\n",plainText);
        	fputc(plainText,fplain);
        }
        else
            {
            	plainText=cypherText;
            	fputc(plainText,fplain);
        	}
            //printf("%c\t%c",plainText[i],cypherText[i]);}
        cypherText= fgetc(fcypher);
    }
    fclose(fplain);
    fclose(fcypher);
    printf("plain text has been written into plain1.txt!\n");
  //  printf("%s\n\n",plainText);

}

int gcd(int x, int y)
{
    int t=0;
    //int t1=x;
    //int t2=y;
    while(y!=0)
    {
        t = x%y;
        x = y;
        y = t;
    }
    //printf("%d",x);
    return x;
}

int inverse(int x)
{
	int i;
	for( i=0; i<26; i++)
	{
		if((i*x)%26==1){
			break;
		}
	}
//	printf("%d\n",i);
	return i;
}



