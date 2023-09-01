#ifndef SEARCH_LIB_H
#define SEARCH_LIB_H


#include <stdio.h>
#include <stdlib.h>
#include "defaults.h"
#include "strings.h"

//search a user
client_tree* search_client(client_tree* head, char* name)
{
	if (head == NULL)
	{
		return NULL;
	}
	if (strcmp(head->stats.username, name) == 0)
		return head;
	if (strcmp(head->stats.username, name) == 1)
		return search_client(head->left,name);
	if (strcmp(head->stats.username, name) == -1)
		return search_client(head->right, name);
}

// search a product by its name
product_tree* search_by_name(product_tree* head, char* name)
{
	if (head == NULL)
	{
		return NULL;
	}
	if (strcmp(head->stats.name, name) == 0)
		return head;
	if (strcmp(head->stats.name, name) == 1)
		return search_by_name(head->left, name);
	if (strcmp(head->stats.name, name) == -1)
		return search_by_name(head->right, name);
}
//search a product by its name and buyer name
product_tree* search_by_buyer(product_tree* head, char* name,char* buyer_name)
{
	if (head == NULL)
	{
		return NULL;
	}
	if (strcmp(head->stats.name, name) == 0)
	{
		if (strcmp(head->stats.seller_name, buyer_name)==0) return head;
		else return search_by_buyer(head->left, name,buyer_name);
	}
	if (strcmp(head->stats.name, name) == 1)
		return search_by_buyer(head->left, name, buyer_name);
	if (strcmp(head->stats.name, name) == -1)
		return search_by_buyer(head->right, name, buyer_name);
}


#endif //  SEARCH_LIB_H