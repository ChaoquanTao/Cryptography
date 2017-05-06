#include<stdio.h>
#include<stdlib.h>
int main()
{
    void encrypt();
	void decode();
	void calculateCharFreq();

    int choice;
    printf("please input your choice:\n");
        printf("\t1. encrypt\n\t2.decode\n\t3.calculate character frequence\n\t4.quit&exit\n");
    scanf("%d",&choice);
    getchar();
    while(1)
    {
        switch(choice)
        {
            case 1:
                encrypt();
                break;
            case 2:
            	decode();
            	break;
            case 3:
            	calculateCharFreq();
            	break;
            case 4:
            	return 0;
            default:break;
        }
                printf("please input your choice:\n");
        printf("\t1. encrypt\n\t2.decode\n\t3.calculate character frequence\n\t4.quit&exit\n");
        scanf("%d",&choice);

        getchar();

    }
    return 0;
}

