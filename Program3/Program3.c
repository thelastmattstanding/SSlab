#include<stdio.h>
#include<stdlib.h>

void main()
{
	int process_no, resource_no;
	int i, j, k = 0, flag = 0, counter = 0;
	
	printf("Enter the total number of processes : ");
	scanf("%d", &process_no);
	printf("Enter the total number of resources : ");
	scanf("%d", &resource_no);
	
	int alloc_matrix[process_no][resource_no], max_matrix[process_no][resource_no], need_matrix[process_no][resource_no];
	int available[resource_no], work[resource_no], finish[process_no], sequence[process_no];
	
	printf("\nEnter resources allocated for each process : ");
	for(i = 0; i < process_no; i++)
	{
		printf("\nP%d: \n", i+1);
		for(j = 0; j < resource_no; j++)
		{
			printf("R%d: ", j + 1);
			scanf("%d", &alloc_matrix[i][j]);
		}
	}
	
	printf("\nEnter the maximum number of resources that can be allocated to each process : ");
	for(i = 0; i < process_no; i++)
	{
		printf("\nP%d: \n", i+1);
		for(j = 0; j < resource_no; j++)
		{
			printf("R%d: ", j + 1);
			scanf("%d", &max_matrix[i][j]);
			if(max_matrix[i][j] < alloc_matrix[i][j])
			{
				printf("Error! Maximum resources cannot be less than allocated resources!");
				exit(0);
			}
			else
			{
				need_matrix[i][j] = max_matrix[i][j] - alloc_matrix[i][j];
			}
		}
	}
	
	printf("\nEnter the number of resources currently available : \n");
	for(i = 0; i < resource_no; ++i)
	{
		printf("R%d: ", i + 1);
		scanf("%d", &available[i]);
		work[i] = available[i];
	}
	
	for(i = 0; i < process_no; ++i)
	{
		finish[i] = 0;
	}
	i = 0;
	do
	{
		counter++;
		if(finish[i] == 0)
		{
			for(j = 0; j < resource_no; j++)
			{
				if(need_matrix[i][j] > work[j])
				{
					flag = 1;
				}
			}
			
			if(flag == 0)
			{
				for(j = 0; j < resource_no; j++)
				{
					work[j] += alloc_matrix[i][j];
				}
				finish[i] = 1;
				sequence[k++] = i + 1;
				counter = 0;
			}
			else
			{
				flag = 0;
			}
		}
		i++;
		if( i == process_no )
		{
			i = 0;
		}
	}while(counter < process_no);
	if(k < process_no)
	{
		printf("\nSystem is Unsafe!\n");
		for(i = 0; i < k; ++i)
		{
			printf("P%d ", sequence[i]);
		}
	}
	else
	{
		printf("\nSafe Sequence: ");
		for(i = 0; i < k; ++i)
		{
			printf("P%d ", sequence[i]);
		}
			
	}	
}
