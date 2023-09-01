#ifndef BTREE_LIB_H
#define BTREE_LIB_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defaults.h"

client_tree* add_to_client_tree(client_tree* head, list* newcli)
{
	if (head == NULL)
	{
		head = (client_tree*)malloc(sizeof(client_tree));
		head->stats.username = NULL;
		head->left = NULL;
		head->right = NULL;
	}
	if (head->stats.username == NULL)
	{
		head->stats.username = newcli->word;
		head->stats.password = newcli->next->word;
		head->stats.credit = atoi(newcli->next->next->word);
	}
	else
	{
		if (strcmp(head->stats.username, newcli->word) == 1)
			head->left = add_to_client_tree(head->left, newcli);
		if (strcmp(head->stats.username, newcli->word) == -1)
			head->right = add_to_client_tree(head->right, newcli);
	}
	return head;
}
product_tree* add_to_product_tree(product_tree* head, list* newcli)
{
	if (head == NULL)
	{
		head = (product_tree*)malloc(sizeof(product_tree));
		head->stats.name = NULL;
		head->left = NULL;
		head->right = NULL;
	}
	if (head->stats.name == NULL)
	{
		head->stats.name = newcli->word;
		head->stats.num = atoi(newcli->next->word);
		head->stats.num_of_reviewers = atoi(newcli->next->next->word);
		head->stats.price = atoi(newcli->next->next->next->word);
		head->stats.seller_name = newcli->next->next->next->next->word;
		head->stats.rating = atoi(newcli->next->next->next->next->next->word);
	}
	else
	{
		if (strcmp(head->stats.name, newcli->word) == 0)
			head->left = add_to_product_tree(head->left, newcli);
		if (strcmp(head->stats.name, newcli->word) == 1)
			head->left = add_to_product_tree(head->left, newcli);
		if (strcmp(head->stats.name, newcli->word) == -1)
			head->right = add_to_product_tree(head->right, newcli);
	}
	return head;
}


product minValueNode(product_tree* head)
{
	if (head->left==NULL) return head->stats;
	return minValueNode(head->left);
}

product_tree* erase_from_product_tree(product_tree* head, product current)
{
	if (head == NULL) return head;


	if (strcmp(head->stats.name, current.name) == 1)
		head->left = erase_from_product_tree(head->left, current);

	else if (strcmp(head->stats.name, current.name) == -1)
		head->right = erase_from_product_tree(head->right, current);

	else
	{
		product_tree *temp;
		
		if (head->left == NULL)
		{
			temp = head->right;
			free(head);
			return temp;
		}
		else if (head->right == NULL)
		{
			temp = head->left;
			free(head);
			return temp;
		}

		product s;
		s = minValueNode(head->right);

		// Copy the inorder successor's data to this node 
		head->stats.name = s.name;
		head->stats.seller_name = s.seller_name;
		head->stats.num = s.num;
		// Delete the inorder successor 
		head->right = erase_from_product_tree(head->right, s);
	
	}
	return head;
}
//freeing product data memories
void free_p(product_tree* head)
{
	if (head != NULL)
	{
		free_p(head->left);
		free_p(head->right);
		free(head->stats.name);
		free(head->stats.seller_name);
		free(head);
	}
}
//freeing user data memories
void free_c(client_tree* head)
{
	if (head != NULL)
	{
		free_c(head->left);
		free_c(head->right);
		free(head->stats.username);
		free(head->stats.password);
		free(head);
	}
}


#endif //  BTREE_LIB_H