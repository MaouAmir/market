#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defaults.h"
#include "btree_lib.h"
#include "split_lib.h"
#include "file_lib.h"
#include "search_lib.h"

//log out in menu.h

void sign_up(client_tree* head,list* com)
{
	client_tree* p = search_client(head, com->next->word);
	if (p == NULL)
	{
		com->next->next->next->word = "0";
		add_to_client_tree(head, com->next);
		printf("user added \n");
	}
	else printf("this user already exists. sign up unsucessful \n ");
}

client_tree* login(client_tree* head, list* com)
{
	client_tree* p = search_client(head, com->next->word);

	if (p!=NULL)
	{
		if (strcmp(p->stats.password, com->next->next->word) == 0)
		{
			printf("user entered \n");
			return p;
		}
		printf("wrong password. login unsucessful \n ");
	}
	else printf("this user doesnt exist. login unsucessful \n ");
	return NULL;
}

void raise_credit(client_tree* head,client_tree* current,list *com)
{
	client_tree* p = search_client(head,current->stats.username);
	int cash = atoi(com->next->word);
	if (cash >= 0)
	{
		p->stats.credit += cash;
		printf("credit is now: %d \n", p->stats.credit);
		printf("deposit %d credits completed \n", cash);
	}
	else printf("num should be positive \n");
}

void print_good(product p)
{  
	printf("seller: %s \n",p.seller_name);
	printf("name: %s \n",p.name);
    printf("price/good: %d \n",p.price);
    printf("number: %d  \n",p.num);
	printf("rating: %.2f \n \n", (float)p.rating / p.num_of_reviewers);
}

void show_goods(product_tree* head)
{
	
	if (head != NULL)
	{
		show_goods(head->left);
		float rating = (float)head->stats.rating / head->stats.num_of_reviewers;
		if ((rating >= 2) || (head->stats.num_of_reviewers < 5))
			print_good(head->stats);
		show_goods(head->right);
	}
	
}

void add_goods(product_tree* head, list* newgood,client_tree* current)
{
	int price, num;
	price = atoi(newgood->next->next->word);
	num= atoi(newgood->next->next->next->word);
	if ((price > 0) && (num > 0))
	{
		product_tree* p = search_by_name(head, newgood->next->word);
		if (p == NULL) 
		{
			//add good process : changing sequences for saving
			free(newgood->word);
			newgood->word = newgood->next->word;
			newgood->next->word = newgood->next->next->next->word;
			newgood->next->next->next->word = newgood->next->next->word;
			newgood->next->next->word = "0";
			newgood->next->next->next->next = (list*)malloc(sizeof(list));
			newgood->next->next->next->next->word = current->stats.username;
			newgood->next->next->next->next->next = (list*)malloc(sizeof(list));
			newgood->next->next->next->next->next->word = (char*)malloc(sizeof(char));
			newgood->next->next->next->next->next->word = "0";
			add_to_product_tree(head, newgood);
			printf("product added successfully \n");
		}
		else printf("good already exist \n");
	}
	else printf("parameters should be positive \n");
}

void remove_good(product_tree* head, list* com,client_tree* current)
{
	product_tree* p = search_by_name(head, com->next->word);
	if (p != NULL)
	{
		if (strcmp(current->stats.username, p->stats.seller_name) == 0)
		{
			erase_from_product_tree(head, p->stats);
			printf("product removed successfully \n");
		}
		else printf("you are not the seller \n");
	}
	else printf("good doesnt exist \n");
}

void change_good(product_tree* head, list* com, client_tree* current)
{
	product_tree* p = search_by_name(head, com->next->word);
	if (p != NULL)
	{
		if (strcmp(current->stats.username, p->stats.seller_name) == 0)
		{
			int price = atoi(com->next->next->word);
			if (price > 0)
			{
				p->stats.price = price;
				printf("product changed successfully \n");
			}
			else printf("price should be positive");
		}
		else printf("you are not the seller \n");
	}
	else printf("good doesnt exist \n");
}

void show_seller(product_tree* head, char* name)
{
	if (head != NULL)
	{
		show_seller(head->left,name);
	
		if (strcmp(name, head->stats.seller_name) == 0)
		{
			print_good(head->stats);
		}
		show_seller(head->right,name);
	}
}

void view (client_tree* current,product_tree* head,int role_num)
{
    printf("reloading user data... \n");
    printf("username: %s \n",current->stats.username);
    if (role_num==seller_role) printf("role: seller \n");
	if (role_num == buyer_role) printf("role: buyer \n");
    printf("credit: %d \n \n",current->stats.credit);
    printf("goods:\n \n");
	show_seller(head, current->stats.username);
} 

void buy(client_tree* buyer_tree,client_tree* seller_tree,client_tree * current,product_tree *goodss, product_tree *goodsp,list* com)
{
	product_tree* p = search_by_name(goodss, com->next->word);
	if (p != NULL)
	{
		float rating = (float)p->stats.rating / p->stats.num_of_reviewers;
		if ((rating >= 2) || (p->stats.num_of_reviewers < 5))
		{
			if (strcmp(com->next->next->next->word, p->stats.seller_name) == 0)
			{
				int count = atoi(com->next->next->word);
				if (count > 0)
				{
					if (count <= p->stats.num)
					{
						if (current->stats.credit >= (count*(p->stats.price)))
						{
							client_tree* buyer = search_client(buyer_tree, current->stats.username);
							client_tree* seller = search_client(seller_tree, com->next->next->next->word);
							int money = (count*(p->stats.price));
							//transport money
							buyer->stats.credit -= money;
							seller->stats.credit += money;
							p->stats.num -= count;
							//add good process : changing sequences for saving
							free(com->word);
							com->word = com->next->word;
							com->next->word = com->next->next->word;
							com->next->next->next->next = (list*)malloc(sizeof(list));
							com->next->next->next->next->next = (list*)malloc(sizeof(list));
							com->next->next->next->word = com->next->next->word;
							com->next->next->word = "0";
							com->next->next->next->word = (char*)malloc(6 * (sizeof(char)));
							itoa(p->stats.price, com->next->next->next->word, 10);
							com->next->next->next->next->word = current->stats.username;
							com->next->next->next->next->next->word = (char*)malloc(sizeof(char));
							com->next->next->next->next->next->word = "0";
							add_to_product_tree(goodsp, com);
							printf("product bought successfully \n");
						}
						else printf("currency is not enough \n");
					}
					else printf("the product num is not enough \n");
				}
				else printf("count should be positive \n");
			}
			else printf("this is not the seller \n");
		}
		else printf("good is not afordable \n");
	}
	else printf("good doesnt exist \n");
}
	
void rate(client_tree* buyer_tree, client_tree * current, product_tree *goodss, product_tree *goodsp, list* com)
{
	product_tree* p = search_by_name(goodss, com->next->word);
	if (p != NULL)
	{
		if (strcmp(p->stats.seller_name, com->next->next->word) == 0)
		{
			product_tree* c = search_by_buyer(goodsp, com->next->word, current->stats.username);
			if (c != NULL)
			{
				if (c->stats.num_of_reviewers == 0)
				{
					int score = atoi(com->next->next->next->word);
					if ((score >= 1) && (score <= 5))
					{
						c->stats.rating = score;
						c->stats.num_of_reviewers = 1;
						p->stats.num_of_reviewers++;
						p->stats.rating += score;
						printf("rated successfully \n");
					}
					else printf("wrong score \n");
				}
				else printf("product rated before \n");
			}
			else printf("wrong buyer \n");
		}
		else  printf("wrong seller \n");
	}
	else printf("good doesnt exist \n");
}

void show_good_s(product_tree *head, int min, int max, char *name, char *seller_name)
{
	if (head != NULL)
	{
		show_good_s(head->left, min, max, name, seller_name);

		if ((head->stats.price>=min)&& (head->stats.price <= max))
			if ((name==NULL)||(strcmp(name,head->stats.name)==0))
				if ((seller_name == NULL) || (strcmp(seller_name, head->stats.seller_name) == 0))
				{
					float rating = (float)head->stats.rating / head->stats.num_of_reviewers;
					if ((rating >= 2) || (head->stats.num_of_reviewers < 5))
						print_good(head->stats);
				}
		show_good_s(head->right, min, max, name, seller_name);
	}
}

void search(product_tree* head,list* com)
{
	int min = 0, max = 10000;
	char *seller_name = NULL, *name = NULL;
	int num = atoi(com->next->word);
	for (int i = 0; i < num; i++)
	{
		char s[256];
		scanf("%s", &s);
		char space = ',';
		list *l = spliter(s, space);
		if (strcmp(l->word, "max_price") == 0) max = atoi(l->next->word);
		if (strcmp(l->word, "min_price") == 0) max = atoi(l->next->word);
		if (strcmp(l->word, "name") == 0) name = l->next->word;
		if (strcmp(l->word, "seller_username") == 0) seller_name = l->next->word;
	}
	show_good_s(head, min, max, name, seller_name);

}



#endif //  ACCOUNTS_H