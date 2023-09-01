#include "accounts.h"
#include <stdio.h>
#include <stdlib.h>
#include "defaults.h"
#include "btree_lib.h"
#include "strings.h"
#include "split_lib.h"
#include "file_lib.h"

void menu_start()
{
    printf("\t \t \t \t \t \t         UTKala\n");
    printf("\t \t \t \t  \t \t      full version  \n");
    printf("pls type your commands with space and if you want to exit the program, type -exit-:\n");
    printf("command: ");
}
void menu_core()
{
	int role_num = 0, f = 0;//f is duumy for now
	client_tree* current=NULL;
	client_tree* buyer_tree, *seller_tree;
	product_tree* goodss_tree, *goodsp_tree;
	

	//erase_from_client_tree(seller_tree, seller_tree->stats);

	while (f == 0)
	{
		//reading data from files
		seller_tree = read_file_client(sellers);
		buyer_tree = read_file_client(buyers);
		goodss_tree = read_file_good(goods_store);
		goodsp_tree = read_file_good(goods_purchased);

		//showing first page
		menu_start();

		//getting orders
		char s[256];
		scanf("%s", &s);
		printf("\n");
		char space = ',';
		list *com = spliter(s,space);
		int ord = command(com);

		//linking the order to the appopriate fuction

		if ((ord == signup_num) || (ord == login_num))
		{
			char* role;
			if (current == NULL)
			{
				role = com->next->next->next->word;
				if (role != NULL)
				{
					if (strcmp(role, "seller") == 0)
					{
						if (ord == signup_num) sign_up(seller_tree, com);
						else if (ord == login_num) current = login(seller_tree, com);
						role_num = seller_role;
					}
					else if (strcmp(role, "buyer") == 0)
					{
						if (ord == signup_num) sign_up(buyer_tree, com);
						else if (ord == login_num) current = login(buyer_tree, com);
						role_num = buyer_role;
					}
					else printf("wrong role. operation unsuccessful \n");
				}
				else printf("wrong command struct. operation unsuccessful \n");
			}
			else printf("error: first logout then try again \n");
		}

		else if (ord == logout_num)
		{
			if (current != NULL)
			{
				current = NULL;
				role_num = 0;
				printf("user logged out \n");
			}
			
			else printf("error: first login then try again \n");
		}

		else if (ord == deposit_num)
		{
			if ((current != NULL) && (role_num == buyer_role))  raise_credit(buyer_tree,current,com);
			
			else if (current == NULL) printf("error: first login then try again \n");
			else if (role_num == seller_role) printf("error: a seller can't deposit \n");
		}

		else if (ord == show_goods_num)
		{
			if (current!=NULL) show_goods(goodss_tree);
			//else ...
			else printf("error: first login then try again \n");
		}

		else if (ord == add_goods_num)
		{
			if ((current != NULL) && (role_num == seller_role)) add_goods(goodss_tree,com,current);
			//else ...
			else if (current == NULL) printf("error: first login then try again \n");
			else if (role_num == buyer_role) printf("error: a buyer can't add a good to the market \n");
		}

		else if (ord == remove_goods_num)
		{
			if ((current != NULL) && (role_num == seller_role)) remove_good(goodss_tree, com, current);
			//else ...
			else if (current == NULL) printf("error: first login then try again \n");
			else if (role_num == buyer_role) printf("error: a buyer can't remove a good \n");
		}

		else if (ord == change_goods_num)
		{
			if ((current != NULL) && (role_num == seller_role)) change_good(goodss_tree, com, current);
			//else ...
			else if (current == NULL) printf("error: first login then try again \n");
			else if (role_num == buyer_role) printf("error: a buyer can't remove a good \n");
		}

		else if (ord == view_num)
		{
			if (current != NULL)
			{
				if (role_num == buyer_role) view(current, goodsp_tree, role_num);
				if (role_num == seller_role) view(current, goodss_tree, role_num);
			}
			//else ...
			else printf("error: first login then try again \n");
		}
		
		else if (ord == buy_num)
		{
			if ((current != NULL) && (role_num == buyer_role))  buy(buyer_tree,seller_tree,current,goodss_tree,goodsp_tree, com);

			else if (current == NULL) printf("error: first login then try again \n");
			else if (role_num == seller_role) printf("error: a seller can't buy \n");
		}

		else if (ord == rate_goods_num)
		{
			if ((current != NULL) && (role_num == buyer_role))  rate(buyer_tree, current, goodss_tree, goodsp_tree, com);

			else if (current == NULL) printf("error: first login then try again \n");
			else if (role_num == seller_role) printf("error: a seller can't rate \n");
		}

		else if (ord == search_num)
		{
			if (current != NULL) search(goodss_tree,com);
			//else ...
			else printf("error: first login then try again \n");
		}

		//exiting
		else if (ord == exit_num) f = 1;
		else printf("error: command not defined \n");
		
		//writing data to the files
		write_file_client(seller_tree, sellers);
		write_file_client(buyer_tree, buyers);
		write_file_product(goodss_tree, goods_store);
		write_file_product(goodsp_tree, goods_purchased);

		//freeing  memory
		if (f == 1) {
			
			free_c(buyer_tree);
			free_c(seller_tree);
			free_p(goodss_tree);
			free_p(goodsp_tree);
		}
		//getting ready for the next command...
		else {
			//press any key to continue...
			printf("press any key to continue...\n");
			if (role_num == buyer_role) current = search_client(buyer_tree, current->stats.username);
			if (role_num == seller_role) current = search_client(seller_tree, current->stats.username);
			getch();
		}
	}

	
}