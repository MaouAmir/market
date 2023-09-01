#ifndef FILE_LIB_H
#define FILE_LIB_H


#include <stdio.h>
#include <stdlib.h>
#include "defaults.h"
#include "split_lib.h"
#include "btree_lib.h"

//reading user data from file
client_tree* read_file_client(int el)
{
	FILE *file;
	char line[256];
	list *data;
	client_tree* head;
	head = (client_tree*)malloc(sizeof(client_tree));
	head->stats.username = NULL;
	head->left = NULL;
	head->right = NULL;
	if (el == sellers) 
		file = fopen(seller_addr, "r");
	else
		file = fopen(buyer_addr, "r");

	if (file == NULL) return NULL;
	while (fgets(line, sizeof(line), file))
	{
		data = spliter(line, ',');
		head = add_to_client_tree(head, data);
		if (feof(file)) break;
	}
	fclose(file);
	return head;
}

//reading product data from file
product_tree* read_file_good(int el)
{
	FILE *file;
	char line[256];
	list *data;
	product_tree* head;
	head = (product_tree*)malloc(sizeof(product_tree));
	head->stats.name = NULL;
	head->left = NULL;
	head->right = NULL;

	if (el == goods_store)
		file = fopen(good_s_addr, "r");
	else 
		file = fopen(good_p_addr, "r");

	if (file == NULL) return NULL;
	while (fgets(line, sizeof(line), file))
	{
		data = spliter(line, ',');
		head = add_to_product_tree(head, data);
		if (feof(file)) break;
	}
	
	fclose(file);
	return head;
}

//writing user data to the file

void print_treec(client_tree* tree, FILE *file)
{
	if ((tree != NULL) && (tree->stats.username != NULL))
	{
		fputs(tree->stats.username, file);
		fputs(",", file);

		fputs(tree->stats.password, file);
		fputs(",", file);

		char credit[20];
		itoa(tree->stats.credit, credit, 10);
		fputs(credit, file);

		fputs("\n", file);

		print_treec(tree->left, file);
		print_treec(tree->right, file);
	}
}
void write_file_client(client_tree* head,int el)
{
	FILE *file;

	if (el == sellers)
		file = fopen(seller_addr, "w");
	else
		file = fopen(buyer_addr, "w");


	print_treec(head,file);

	fclose(file);
}

//writing product data to the file

void print_treep(product_tree* tree, FILE *file)
{
	if ((tree != NULL) && (tree->stats.name != NULL))
	{
		fputs(tree->stats.name, file);
		fputs(",", file);

		char num[20];
		itoa(tree->stats.num, num, 10);
		fputs(num, file);
		fputs(",", file);
		
		char numr[20];
		itoa(tree->stats.num_of_reviewers, numr, 10);
		fputs(numr, file);
		fputs(",", file);

		char price[20];
		itoa(tree->stats.price,price, 10);
		fputs(price, file);
		fputs(",", file);

		fputs(tree->stats.seller_name, file);
		fputs(",", file);

		char rating[20];
		itoa(tree->stats.rating, rating, 10);
		fputs(rating, file);
		


		fputs("\n", file);

		print_treep(tree->left, file);
		print_treep(tree->right, file);
	}
}
void write_file_product(product_tree* head, int el)
{
	FILE *file;

	if (el == goods_purchased)
		file = fopen(good_p_addr, "w");
	else
		file = fopen(good_s_addr, "w");


	print_treep(head, file);

	fclose(file);
}

#endif //  FILE_LIB_H