#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
	char name[30];
	struct dir *next;
	struct dir *cont_head;
    char type[30];
	
}dir;

dir *root, *current;

dir *search(char name[], char type[], dir *start)
{
    dir *seeker = start->cont_head;
	while(seeker != NULL)
	{
		if(strcmp(seeker->name, name) == 0 && strcmp(seeker->type, type) == 0)
		{
			break; 
		}
		seeker = seeker->next;
	}
	return seeker;
}

void create(char type[30])
{
    char name[30];
    dir *newdir = (dir *)malloc(sizeof(dir));

    printf("Enter Name : ");
    scanf("%s", name);
    if(search(name, type, current) != NULL)
    {
        printf("\n%s name already exists!", type); 
    }
    else
    {
        strcpy(newdir->name,name);
        newdir->next = current->cont_head;
        current->cont_head = newdir;
        strcpy(newdir->type, type);
        newdir->cont_head = NULL;
        printf("\n%s Created!", type);
    }
}

int delete(char name[], char type[], dir *start)
{
    dir *find = search(name, type, start);
    if(find == NULL)
	{
		printf("\n%s Not Found!", type);
        return -1;
    }
    else
    {
        dir *seeker = start->cont_head;
		if(find == start->cont_head)
		{
            dir *temp = start->cont_head;
			start->cont_head = temp->next;
		}
		else
		{
			while(seeker->next != find)
			{
				seeker = seeker->next;
			}
			seeker->next = find->next;
		}
        if(strcmp(find->type, "directory") == 0)
        {
            dir *subfind = find->cont_head;
            while(subfind != NULL)
            {
                if(strcmp(subfind->type, "directory") == 0)
                {
                    delete(subfind->name, "directory", find);
                    subfind = subfind->next;
                }
                else
                {
                    dir *tmp = subfind;
                    subfind = subfind->next;
                    free(tmp);
                }
            }
        }
		free(find);
        return 0;
    }
}

dir *traverse(dir *head)
{
    printf("\nCurrent Directory : %s", head->name);
    dir *seeker = head->cont_head;
    char name[30], choice[10];
	if(seeker == NULL)
    {
        printf("\nThere are no subdirectories in this directory!\n");
        return head;
    }
    else
    {
        printf("\nList of subdirectories :\n");
        while(seeker !=NULL)
        {
            if(strcmp(seeker->type, "directory") == 0)
            {
                printf("%s\n", seeker->name);
            }
            seeker = seeker->next;
        }
        printf("Enter subdirectory you wish to enter (Enter 'exit' to escape) : ");
        scanf("%s", &name);
        if(strcmp(name, "exit") == 0)
        {
            return head;
        }
        else
        {
            seeker = search(name, "directory", head);
            if(seeker == NULL)
            {
                printf("Subdirectory Not Found!\n");
            }
            else
            {
                printf("Current Directory : %s\n", seeker->name);
                printf("Do you wish to continue? (yes/no)");
                scanf("%s", &choice);
                if(strcmp(choice, "yes") == 0)
                {
                    seeker = traverse(seeker);
                }
                else
                {
                    return seeker;
                }
            }
        }
    }
}

void display()
{
    printf("\nCurrent Directory: %s\n", current->name);
	dir *seeker = current->cont_head;
    int counter = 1;
	while(seeker != NULL)
	{
		printf("%d. %s : %s\n", counter++, seeker->name, seeker->type);
		seeker = seeker->next;
	}
}

void main()
{
	int choice, res;
    char name[30];
	root = (dir *)malloc(sizeof(dir));
    strcpy(root->name, "ROOT");
    strcpy(root->type, "directory");
    root->cont_head = NULL;
    root->next = NULL;
    current = root; 
    dir *searchres;  
	do
	{
		printf("\n\n~MENU~\n");
		printf("1. Traverse\n2. Create Directory\n3. Delete Directory\n4. Create File\n5. Delete File\n6. Search Directory\n7. Display\n8. Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: 
                if(root->cont_head == NULL)
                {
                    printf("No Directory exists!");
                }
                else
                {
                    current = traverse(root);
                }
                break;
            case 2:
                create("directory");
                break;
            case 3:
                printf("\nEnter name : ");
                scanf("%s", name);
                res = delete(name, "directory", current);
                if(res == 0)
                {
                    printf("\n%s Deleted!", name);
                }
                break;
            case 4:
                create("file");
                break;
            case 5:
                printf("\nEnter name : ");
                scanf("%s", name);
                res = delete(name, "file", current);
                if(res == 0)
                {
                    printf("\n%s Deleted!", name);
                }
                break;
            case 6:
                printf("\nEnter name : ");
                scanf("%s", name);
                searchres = search(name, "directory", current);
                if(searchres == NULL)
                {
                    searchres = search(name, "file", current);
                    if(searchres == NULL)
                    {
                        printf("%s Not Found!\n", name);
                    }
                    else
                    {
                        printf("%s File Found In Directory!\n", name);
                    }
                }
                else
                {
                    printf("%s Sub-Directory Found In Directory!\n", name);
                    searchres = search(name, "file", current);
                    if(searchres != NULL)
                    {
                        printf("%s File Found In Directory!\n", name);
                    }
                }
                break;
            case 7:
                display();
                break;
			case 8: break;

			default: printf("\nInvalid Choice!");			
		}
	}while(choice != 8);	
}