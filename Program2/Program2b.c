#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
	char name[30];
	struct file *next;
}file;

typedef struct 
{
	char name[30];
	struct dir *next;
	file *head;
	
}dir;


dir *head;

file* search(char name[], dir *searchdir)
{
	file *seeker = searchdir->head;
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

dir* dir_search(char name[])
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

void create_dir()
{
	dir *newdir = (dir *)malloc(sizeof(dir));
	char name[30];
	printf("Enter Directory Name : ");
	scanf("%s", &name);
	if(dir_search(name) != NULL)
	{
		printf("\nDirectory name already exists!"); 
	}
	else
	{
		strcpy(newdir->name,name);
		newdir->next = head;
		head = newdir;
        newdir->head = NULL;
        printf("\nDirectory Created!");
	}
}

void create_file()
{
    char file_name[30], dir_name[30];
    printf("Enter the name of the directory where you wish to place the file: ");
    scanf("%s", &dir_name);
    dir *target_dir = dir_search(dir_name);
    if(target_dir == NULL)
    {
		printf("\nDirectory Not Found!");
    }
    else
    {
        file *newfile = (file *)malloc(sizeof(file));

        printf("Enter File Name : ");
        scanf("%s", &file_name);
        if(search(file_name, target_dir) != NULL)
        {
            printf("\nFile name already exists!"); 
        }
        else
        {
            strcpy(newfile->name,file_name);
            newfile->next = target_dir->head;
            target_dir->head = newfile;
            printf("\nFile Created!");
        }
    }
}

// void create_file()
// {
// 	file *newfile = (file *)malloc(sizeof(file));
// 	char name[30], dir_name[30];
//     printf("Enter Directory Name : ");
//     scanf("%s", &dir_name);
//     dir *target_dir = dir_search(dir_name);
//     if(target_dir == NULL)
//  	{
//         printf("\nDirectory Not Found!");
//     }
//     else
//     {
//         printf("Enter File Name : ");
//         scanf("%s", &name);
//         if(search(name, target_dir) != NULL)
//         {
//             printf("\nFile name already exists!"); 
//         }
//         else
//         {
//             strcpy(newfile->name,name);
//             newfile->next = target_dir->head;
//             target_dir->head = newfile;	
//             printf("\nFile Created!");
//         }
//     }
// }

void delete_dir()
{
	char name[30];
	printf("Enter Directory Name: ");
	scanf("%s", &name);
	dir *find = dir_search(name);
	if(find == NULL)
	{
		printf("\nDirectory does not exist!");
	}
	else
	{
		dir *seeker = head;
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
		file *dir_file = find->head;
		while(dir_file != NULL)
		{
			file *tmp = dir_file;
			dir_file = dir_file->next;
			free(tmp);
		}
		free(find);
		printf("\nDirectory %s Deleted!", name);
	}
}

void delete_file()
{
	char name[30], dir_name[30];
    printf("Enter the name of the directory from which you wish to delete the file: ");
    scanf("%s", &dir_name);
    dir *target_dir = dir_search(dir_name);
    if(target_dir == NULL)
	{
		printf("\nDirectory Not Found!");
    }
    else
    {
        printf("Enter File Name: ");
        scanf("%s", &name);
        file *find = search(name, target_dir);
        if(find == NULL)
        {
            printf("\nFile does not exist!");
        }
        else
        {
            file *seeker = target_dir->head;
            if(find == target_dir->head)
            {
                target_dir->head = target_dir->head->next;
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
}

void display()
{
	dir *seeker = head;
    file *file_seeker;
	while(seeker != NULL)
	{
        file_seeker = seeker->head;
		printf("\n%s : ", seeker->name);
        while(file_seeker !=NULL)
        {
            printf("%s, ", file_seeker->name);
            file_seeker = file_seeker->next;
        }
		seeker = seeker->next;
	}
}

void main()
{
	int choice;
	char name[30], dirname[30];
	head = NULL;
	do
	{
		printf("\n\n~MENU~\n");
		printf("1. Create Directory\n2. Delete Directory\n3. Create File\n4. Delete File\n5. Search Directory\n6. Display Files\n7. Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: create_dir();
				break;
			case 2: delete_dir();
				break;
			case 3: create_file();

				break;
			case 4: delete_file();
				break;
			case 5:printf("Enter Directory Name: ");
                scanf("%s", &dirname);
                dir *target_dir = dir_search(dirname);
                if(target_dir == NULL)
                {
                    printf("\nDirectory Not Found!");
                }
                else
                {
                    printf("Enter File Name: ");
                    scanf("%s", &name);				
                    if(search(name, target_dir) == NULL)
                    {
                        printf("\nFile Not Found!");
                    }
                    else
                    {
                        printf("\nFile %s Found In Directory!", name);
                    }
                }
				break;
			case 6: display();
				break;
			case 7: break;

			default: printf("\nInvalid Choice!");			
		}
	}while(choice != 7);	
}