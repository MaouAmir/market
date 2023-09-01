#ifndef STRINGS_H
#define STRINGS_H

#include "accounts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "defaults.h"

//figures out the main command

int command(list *head)
{
    if (strcmp(head->word,"signup")==0) return signup_num;
    if (strcmp(head->word,"exit")==0) return exit_num;
    if (strcmp(head->word,"login")==0) return login_num;
    if (strcmp(head->word,"logout")==0) return logout_num;
    if (strcmp(head->word,"view")==0) return view_num;
    if (strcmp(head->word,"deposit")==0) return deposit_num;
    if (strcmp(head->word,"add_goods")==0) return add_goods_num;
    if (strcmp(head->word,"buy")==0) return buy_num;
    if (strcmp(head->word,"show_goods")==0) return show_goods_num;
	if (strcmp(head->word, "remove_goods") == 0) return remove_goods_num;
	if (strcmp(head->word, "change_goods_price") == 0) return change_goods_num;
	if (strcmp(head->word, "rate_goods") == 0) return rate_goods_num;
	if (strcmp(head->word, "search") == 0) return search_num;
	return 0;
}

#endif //  STRINGS_H