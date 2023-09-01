#ifndef DEFAULTS_H
#define DEFAULTS_H


//roles
#define seller_role -1
#define buyer_role 1

//files_stored
#define buyers 1
#define sellers 2
#define goods_store 3
#define goods_purchased 4

//files_stroed adds
#define good_s_addr "txts/goods_s.txt"
#define good_p_addr "txts/goods_p.txt"
#define seller_addr "txts/seller.txt"
#define buyer_addr "txts/buyer.txt"

//command nums
#define signup_num 1
#define login_num 2
#define logout_num -2
#define view_num 4
#define deposit_num 3
#define add_goods_num 5
#define buy_num -5
#define show_goods_num 6
#define remove_goods_num -6
#define change_goods_num 7
#define rate_goods_num 8
#define search_num 9
#define exit_num -99

//structs
typedef struct good product;
struct good {
	char *name;
	int num;
	int price;
	int rating;
	int num_of_reviewers;
	char *seller_name;
};

typedef struct person client;
struct person {
	char* username;
	int credit;
	char* password;
};


typedef struct Tnode_client client_tree;
struct Tnode_client
{
	struct person stats;
	client_tree* left;
	client_tree* right;
};


typedef struct Tnode_product  product_tree;
struct Tnode_product
{
	struct good stats;
	product_tree* left;
	product_tree* right;
};

 

typedef struct node list;
struct node
{
	char* word;
	list *next;
};


#endif //  DEFAULTS_H