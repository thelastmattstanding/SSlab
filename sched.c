#include<stdio.h>

void fcfs()
{
	int n;
	printf("\nNumber of Processes: ");
	scanf("%d", &n);
	int i, j, k;
	float avgw = 0, avgt = 0;
	int TAT[n];
	int WT[n];
	int BT[n];
	
	for(i = 0; i < n; ++i)
	{
		BT[i] = 0;
		WT[i] = 0;
		TAT[i] = 0;
	}

	printf("Enter burst time for :\n") ;

	for(i = 0; i < n; ++i)
	{
		printf("P%d: ", i + 1);
		scanf("%d", &BT[i]);			

		for(j = 0; j < BT[i]; ++j)
		{
			for(k = i + 1; k < n; ++k)
			{
				WT[k] = WT[k] + 1;
			}
		}
		TAT[i] = BT[i] + WT[i];
		avgw = avgw + WT[i];
		avgt = avgt + TAT[i];
	}
	avgw = avgw / n;
	avgt = avgt / n;
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
	int n;
	printf("\nNumber of Processes: ");
	scanf("%d", &n);
	int i, j, k;
	float avgw = 0, avgt = 0;
	int TAT[n];
	int WT[n];
	int BT[n], BTs[n];
	
	for(i = 0; i < n; ++i)
	{
		BT[i] = 0;
		BTs[i] = 0;
		WT[i] = 0;
		TAT[i] = 0;
	}
	printf("Enter burst time for:\n");
	for(i = 0; i < n; ++i)
	{
		printf("P%d: ", i + 1);
		scanf("%d", &BT[i]);
		BTs[i] = BT[i];				
	}

	int temp;
	for(i = 0; i < n; ++i)
	{
		for(j = i + 1; j < n; ++j)
		{
			if(BTs[i] > BTs[j])
			{
				temp = BTs[i];
				BTs[i] = BTs[j];
				BTs[j] = temp;
			}
		}
	}


	for(i = 0; i < n; ++i)
	{		
		for(j = 0; j < BTs[i]; ++j)
		{
			for(k = i + 1; k < n; ++k)
			{
				WT[k] = WT[k] + 1;
			}
		}
		TAT[i] = BTs[i] + WT[i];
		avgw = avgw + WT[i];
		avgt = avgt + TAT[i];
	}
	avgw = avgw / n;
	avgt = avgt / n;
	printf("\nPROCESS\tBT\tTAT\tWT");
	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < n; ++j)
		{
			if(BT[i] == BTs[j])
			{
				printf("\nP%d     \t%d\t%d\t%d", (i+1), BT[i],TAT[j], WT[j]);
			}
		}	
	}
		
	printf("\nAverage Waiting Time: %f", avgw);
	printf("\nAverage Turnaround Time: %f", avgt);	
}

void priority()
{
	int n;
	printf("\nNumber of Processes: ");
	scanf("%d", &n);
	int i, j, k;
	float avgw = 0, avgt = 0;
	int TAT[n];
	int WT[n];
	int BT[n];
	int P[n];
	int ID[n];
	
	for(i = 0; i < n; ++i)
	{
		BT[i] = 0;
		WT[i] = 0;
		TAT[i] = 0;
		ID[i] = i;
	}
	printf("Enter burst time for:\n");
	for(i = 0; i < n; ++i)
	{
		printf("P%d: ", i + 1);
		scanf("%d", &BT[i]);			
	}
	printf("Enter priority for: \n");
	for(i = 0; i < n; ++i)
	{
		printf("P%d: ", i + 1);
		scanf("%d", &P[i]);			
	}
	int temp;
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
		for(j = 0; j < BT[i]; ++j)
		{
			for(k = i + 1; k < n; ++k)
			{
				WT[k] = WT[k] + 1;
			}
		}
		TAT[i] = BT[i] + WT[i];
		avgw = avgw + WT[i];
		avgt = avgt + TAT[i];
	}
	avgw = avgw / n;
	avgt = avgt / n;
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
			case 4 : priority();
				break;
			case 5: break;
			default: printf("\nUnknown Choice!");
		}
	}while(choice != 5);
}
