/*
* P2
*
*  Created on: Jan 13, 2014
*      Author: Grant Toepfer
*		Class:	CSE 222
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <stdlib.h>

struct node
{
	int	data;
	struct	node *next;
};

int		SEARCH(struct node *, int num);		//check the list for num
void	INSERT(struct node *, int num);		//insert num into the list
void	DEL(struct node *, int num);		//delete num from the list
void	DLIST(struct node *);				//clears the list
void	TRAVERSE(struct node *);			//display the entire list
void	HELP(void);							//display the help message
void	ERROR(void);						//display the error message
int		CHECKSPACE(char *);					//detects extra chars in the buffer or lack of integers
int		CHECK(char *);						//detects extra chars in the buffer
int		CHECKINT(char *);					//detects extra chars in the buffer

int main(void)
{
	char buffer[40]; 							//temp storage
	int i;
	int returns;								//number of items scanned by sscanf
	int num;
	char c;
	struct node *list;
	int searc;
	list = malloc(sizeof(struct node));
	list->next = NULL;
	
	while (1)
	{
		printf("\n>");
		fgets(buffer, 40, stdin);				//input to temp storage

		for (i = 0; buffer[i] != '\n'; i++)		//check inputs to be valid
		{
			if (buffer[i] != 'c' && buffer[i] != 'd' && buffer[i] != 'p' && buffer[i] != 'q' && buffer[i] != 's' && buffer[i] != '?' && buffer[i] != ' ' && buffer[i] != '-' && (buffer[i] < '0' || '9' < buffer[i]))
			{
				ERROR();
				break;
			}
		}

		if (buffer[i] == '\n')
		{
			returns = sscanf(buffer, "%c %d", &c, &num);
			if ((c >= '0' && c <= '9') || c == '-')	//scan and insert number if only a new number was inserted
			{
				if (CHECKINT(buffer) == 1)
				{
					sscanf(buffer, "%d", &num);
					if (SEARCH(list, num) == 1)
						printf("\nThe number %i is already in the list.\n", num);
					else
						INSERT(list, num);
				}
				else
					ERROR();
			}

			if (c == 'c')
			{
				if (NULL != list->next)
				{
					if (CHECK(buffer) == 1)
						DLIST(list);
					else ERROR();
				}	
			}

			if (c == 'd')
			{
				if (CHECKSPACE(buffer) == 1)
					DEL(list, num);
				else ERROR();
			}

			if (c == 'p')
			{
				if (CHECK(buffer) == 1)
					TRAVERSE(list);
				else ERROR();
			}

			if (c == 'q')					//quit if q is entered
			{
				if (CHECK(buffer) == 1)
					break;
				else ERROR();
			}

			if (c == 's')
			{
				if (CHECKSPACE(buffer) == 1)
				{
					searc = SEARCH(list, num);
					if (searc == 1) printf("\nThe number %i IS in the list.\n", num);
					if (searc == 0) printf("\nThe number %i IS NOT in the list\n", num);
				}
				else ERROR();
			}

			if (c == '?')
			{
				if (CHECK(buffer) == 1)
					HELP();
				else ERROR();
			}
			if (c == ' ') ERROR();
		}
	}

	return 0;
}

void TRAVERSE(struct node *L)				//Prints the entire list
{
	L = L->next;							//move past header node
	printf("\n");
	while (NULL != L)
	{
		printf("%d ", L->data);
		L = L->next;				
	}
	printf("\n");
}

void INSERT(struct node *L, int num)		//insert num into the list
{
	struct node *new;
	new = malloc(sizeof(struct node));
	new->next = NULL;

	new->data = num;						//insert data into node

	new->next = L->next;					//make sure to set empty things first
	L->next = new;
}

int SEARCH(struct node *L, int num)			//returns 1 if found, 0 if not found
{
	L = L->next;							//move past header node
	if (NULL == L) return 0;
	while (1)
	{
		if (L->data == num)
		{
			return 1;
		}
		L = L->next;
		if (NULL == L)
		{
			return 0;
		}
	}
}

void DEL(struct node *L, int num)			//delete num from the list
{
	struct node *Lb4;						//Lb4 holds the address of the previous node
	Lb4 = L;
	L = L->next;
	while (1)
	{
		if (L->data == num)
		{
			Lb4->next = L->next;
			free(L);
			break;
		}

		L = L->next;
		Lb4 = Lb4->next;

		if (L == NULL) 
		{
			printf("\nThe number %i was not found in the list.\n", num);
			break;
		}
	}
}

void DLIST(struct node *L)					//clears the entire list
{
	struct node *Lb4;						//Lb4 holds the address of the previous node
	Lb4 = L;
	
	L = L->next;
	Lb4->next = L->next;

	while (1)
	{

		free(L);
		if (NULL == Lb4->next) break;
		L = Lb4->next;
		Lb4->next = L->next;
	}
}

void HELP(void)								//displays the help message
{
	printf("\nCOMMANDS:\n\n");
	printf("      <integer>:   Adds integer to the list if it's not already there\n");
	printf("              c:   Clears the list\n");
	printf("    d <integer>:   Deletes integer from the list\n");
	printf("              p:   Prints the list\n");
	printf("              q:   Exits program\n");
	printf("    s <integer>:   Searches the list for integer\n");
	printf("              ?:   Prints out this page\n\n");
	printf("End of help\n");

}

void ERROR(void)							//displays the error message
{
	printf("\nInvalid command. Enter '?' for help.\n");
}

int CHECKSPACE(char *c)
{
	int i;
	for (i = 2; c[i] != '\n'; i++)
	{
		if ((c[i] != '-' && (c[i] < '0' || c[i] > '9')) || ((c[i] == '-') && (i != 2)))
			return 0;
	}
	if (c[1] != ' ')
		return 0;
	if (c[2] == '\n')
		return 0;
	return 1;
}

int CHECK(char *c)
{
	if (c[1] != '\n')
		return 0;
	return 1;
}

int CHECKINT(char *c)
{
	int i;
	for (i = 0; c[i] != '\n'; i++)
	{
		if ((c[i] != '-' && (c[i] < '0' || c[i] > '9')) || ((c[i] == '-') && (i != 0)))
			return 0;
	}
	return 1;
}
