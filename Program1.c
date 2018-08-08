#include<stdio.h>

int i, j, k, n;
float avgw, avgt;
int TAT[100];
int WT[100];
int BT[100];

void init()
{
	printf("\nNumber of Processes: ");
	scanf("%d", &n);
	avgw = 0;
	avgt = 0;	
	
	for(i = 0; i < n; ++i)
	{
		BT[i] = 0;
		WT[i] = 0;
		TAT[i] = 0;
	}

	printf("Enter Burst Time for :\n") ;
	for(i = 0; i < n; ++i)
	{
		printf("P%d: ", i + 1);
		scanf("%d", &BT[i]);	
	}
}

void find_avg()
{
	for(i = 0; i < n; ++i)
	{
		avgw = avgw + WT[i];
		avgt = avgt + TAT[i];
	}
	avgw = avgw / n;
	avgt = avgt / n;

}

void fcfs()
{

	init();

	for(i = 0; i < n; ++i)
	{		
		for(j = i + 1; j < n; ++j)
		{
			WT[j] = WT[j] + BT[i];
		}
		TAT[i] = BT[i] + WT[i];
	}

	find_avg();

	printf("\nPROCESS\tBT\tTAT\tWT");
	for(i = 0; i < n; ++i)
	{
		printf("\nP%d     \t%d\t%d\t%d", (i+1), BT[i],TAT[i], WT[i]);
		
	}
	printf("\nAverage Waiting Time: %f", avgw);
	printf("\nAverage Turnaround Time: %f", avgt);

}

void sjf()
{
	init();

	int BT_Sorted[n];
	int temp;

	for(i = 0; i < n; ++i)
	{
		BT_Sorted[i] = BT[i];				
	}

	for(i = 0; i < n; ++i)
	{
		for(j = i + 1; j < n; ++j)
		{
			if(BT_Sorted[i] > BT_Sorted[j])
			{
				temp = BT_Sorted[i];
				BT_Sorted[i] = BT_Sorted[j];
				BT_Sorted[j] = temp;
			}
		}
	}

	for(i = 0; i < n; ++i)
	{		
		for(j = i + 1; j < n; ++j)
		{
			WT[j] = WT[j] + BT_Sorted[i]; 
		}
		TAT[i] = BT_Sorted[i] + WT[i];
	}

	find_avg();

	printf("\nPROCESS\tBT\tTAT\tWT");
	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < n; ++j)
		{
			if(BT[i] == BT_Sorted[j])
			{
				printf("\nP%d     \t%d\t%d\t%d", (i+1), BT[i],TAT[j], WT[j]);
			}
		}	
	}
		
	printf("\nAverage Waiting Time: %f", avgw);
	printf("\nAverage Turnaround Time: %f", avgt);	
}

void rr()
{
	init();

	int AT[n];
	int time_quant, remain = n;
	int t_unit = 0, flag = 0;
	int BT_Copy[n];
	int wtime = 0, tatime = 0;

	printf("Enter Arrival Time for: \n");
	for(i = 0; i < n; ++i)
	{
		printf("P%d: ", i + 1);
		scanf("%d", &AT[i]);
		BT_Copy[i] = BT[i];		
	}

	printf("\nEnter Time Quantum: ");
	scanf("%d", &time_quant);
	
	i = 0;
	while(remain != 0)
	{
		if(BT_Copy[i] <= time_quant && BT_Copy[i] > 0)
		{
			t_unit = t_unit + BT_Copy[i];
			BT_Copy[i] = 0;
			flag = 1;
		}

		else if(BT_Copy[i] > 0)
		{
			BT_Copy[i] = BT_Copy[i] - time_quant;
			t_unit = t_unit + time_quant;
		}

		if(BT_Copy[i] == 0 && flag == 1)
		{
			remain--;
			WT[i] = t_unit - AT[i] - BT[i];
			TAT[i] = t_unit - AT[i];
			wtime = wtime + WT[i];
			tatime = tatime + TAT[i];
			flag = 0;
		}

		if(i == n - 1)
		{
			i = 0;
		}
		else if(AT[i + 1] <= t_unit)
		{
			i++;
		}
		else
		{
			i = 0;
		}
	}

	find_avg();

	printf("\nPROCESS\tBT\tTAT\tWT");
	for(i = 0; i < n; ++i)
	{
		printf("\nP%d     \t%d\t%d\t%d", (i+1), BT[i],TAT[i], WT[i]);
		

	}
	printf("\nAverage Waiting Time: %f", avgw);
	printf("\nAverage Turnaround Time: %f", avgt);
	
}

void priority()
{

	init();

	int P[n];
	int ID[n];
	int temp;

	printf("Enter priority for: \n");
	for(i = 0; i < n; ++i)
	{
		printf("P%d: ", i + 1);
		scanf("%d", &P[i]);		
		ID[i] = i;		
	}

	for(i = 0; i < n; ++i)
	{
		for(j = i + 1; j < n; ++j)
		{
			if(P[i] > P[j])
			{
				temp = BT[i];
				BT[i] = BT[j];
				BT[j] = temp;
				temp = P[i];
				P[i] = P[j];
				P[j] = temp;
				temp = ID[i];
				ID[i] = ID[j];
				ID[j] = temp;
			}
		}
	}

	for(i = 0; i < n; ++i)
	{
		for(j = i + 1; j < n; ++j)
		{
			WT[j] = WT[j] + BT[i];
		}
		TAT[i] = BT[i] + WT[i];
	}

	find_avg();

	printf("\nPROCESS\tBT\tTAT\tWT");
	for(i = 0; i < n; ++i)
	{
		printf("\nP%d     \t%d\t%d\t%d", (ID[i]+1), BT[i],TAT[i], WT[i]);
		
	}
	printf("\nAverage Waiting Time: %f", avgw);
	printf("\nAverage Turnaround Time: %f", avgt);

}

void main()
{
	int choice;
	do
	{
		printf("\nMENU\n\n");
		printf("1. FCFS\n2. SJF\n3. Round Robin\n4. Priority\n5. Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1 : fcfs();
				break;
			case 2 : sjf();
				break;
			case 3 : rr();
				break;
			case 4 : priority();
				break;
			case 5: break;
			default: printf("\nUnknown Choice!");
		}
	}while(choice != 5);
}
