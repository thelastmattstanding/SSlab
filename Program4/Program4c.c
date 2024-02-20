#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int search(int num, int list[], int n)
{
	int i;
	for(i = 0; i < n; ++i)
	{
		if(num == list[i])
		{
			return i;
		}
	}
	return -1;
}

int done(int list[], int n)
{
	int i;
	for(i = 0; i < n; ++i)
	{
		if(list[i] != -1)
		{
			return 0;
		}
	}
	return 1;
}

void main()
{
	int cylnum, head, i = 0, j, k = 0;
	int dmov = 0, index, dir = 1;
	char dp[5];
	int schedule[30], final[30];
	int movement[30];
	
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
				schedule[i] = atoi(dp);
				movement[i] = schedule[i];
				i++;
			}
		}
	}
	printf("\nEnter disk head position : ");
	scanf("%d", &head);
		
	while(1)
	{
		index = search(head, movement, i);
		if(index != -1)
		{
			movement[index] = -1;
			final[k++] = schedule[index];
			if(done(movement, i) == 1)
			{
				break;
			}
		}
		if(head == 0)
		{
			head = 199;
		}
		head = head - dir;
		
		dmov++;
	}
	printf("\nDisk Sequence : ");
	for(j = 0; j < i; ++j)
	{
		printf("%d ", final[j]);
	}
	printf("\nTotal Disk Movement: %d\n", dmov);
}
