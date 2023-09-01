#ifndef SPLIT_LIB_H
#define SPLIT_LIB_H

#include "defaults.h"
#include <stdio.h>
#include <stdlib.h>

//gets a line and splits it into the words
list* spliter(char string[],char split)
{
	list *head=(list*)malloc(sizeof(list));
	head->next = NULL;
	char s, i = 0,size,w=0;
	list *current = head,*pre;
	while (string[i] != '\0')
	{
		size = 1;
		if (current != NULL)
		{
			pre = current;
			current = (list*)malloc(sizeof(list));
			current->next = NULL;
			current->word= (char *)malloc(sizeof(char));
			pre->next = current;
		}
		while ((string[i] != split)&&(string[i] != '\0'))
		{
			size++;
			current->word = (char *)realloc(current->word,size*sizeof(char));
			current->word[size - 2] = string[i];
			i++;
		}
		current->word[size - 1] = '\0';
		if (w == 0) head = current;
		w++;
		if (string[i] == split) i++;
	}
	return head;
}
//freeing lists
void free_l(list* l)
{
	if (l->next == NULL)
	{
		free(l->word);;
		free(l);
	}
	else free_l(l->next);
}
#endif //  SPLIT_LIB_H