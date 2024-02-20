#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
	char name[30];
	struct file *next;
}file;

file *head;

file* search(char name[])
{
	file *seeker = head;
	while(seeker != NULL)
	{
		if(strcmp(seeker->name, name) == 0)
		{
			break; 
		}
		seeker = seeker->next;
	}
	return seeker;
}

void create_file()
{
	file *newfile = (file *)malloc(sizeof(file));
	char name[30];
	printf("Enter File Name : ");
	scanf("%s", &name);
	if(search(name) != NULL)
	{
		printf("\nFile name already exists!"); 
	}
	else
	{
		strcpy(newfile->name,name);
		newfile->next = head;
		head = newfile;	
	}
}

void delete_file()
{
	char name[30];
	printf("Enter File Name: ");
	scanf("%s", &name);
	file *find = search(name);
	if(find == NULL)
	{
		printf("\nFile does not exist!");
	}
	else
	{
		file *seeker = head;
		if(find == head)
		{
			head = head->next;
		}
		else
		{
			while(seeker->next != find)
			{
				seeker = seeker->next;
			}
			seeker->next = find->next;
		}
		free(find);
		printf("\nFile %s Deleted!", name);
	}
}

void display()
{
	file *seeker = head;
	while(seeker != NULL)
	{
		printf("%s\n", seeker->name);
		seeker = seeker->next;
	}
}

void main()
{
	int choice;
	char name[30];
	head = NULL;
	do
	{
		printf("\n\n~MENU~\n");
		printf("1. Create File\n2. Delete File\n3. Search Directory\n4. Display Files\n5. Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: create_file();
				printf("\nFile Created!");
				break;
			case 2: delete_file();
				break;
			case 3: printf("Enter File Name: ");
				scanf("%s", &name);				
				if(search(name) == NULL)
				{
					printf("\nFile Not Found!");
				}
				else
				{
					printf("\nFile %s Found In Directory!", name);
				}
				break;
			case 4: display();
				break;
			case 5: break;

			default: printf("\nInvalid Choice!");			
		}
	}while(choice != 5);	
}
