#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	int cylnum, head, i = 0, j;
	int dmov = 0;
	char dp[5];
	int schedule[30];
	
	printf("Enter the total number of cylinders : ");
	scanf("%d", &cylnum);
	printf("Enter total schedule (Type 'stop' when done):\n");
	while(1)
	{
		scanf("%s", dp);
		if(strcmp(dp, "stop") == 0)
		{
			break;
		}
		else
		{
			if(atoi(dp) >= cylnum)
			{
				printf("Error! Value is outside disk positions!\n");
			}
			else
			{
				schedule[i++] = atoi(dp);
			}
		}
	}
	printf("\nEnter disk head position : ");
	scanf("%d", &head);
		
	for(j = 0; j < i; ++j)
	{
		dmov += abs(schedule[j] - head);
		head = schedule[j];
	}
	printf("\nDisk Sequence : ");
	for(j = 0; j < i; ++j)
	{
		printf("%d ", schedule[j]);
	}
	printf("\nTotal Disk Movement: %d\n", dmov);
}
