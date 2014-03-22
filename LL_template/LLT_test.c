#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lltemplate.h"

struct ll_data {
	int a;
	int b;
	char *str;
};

void print_elem( struct ll_data *ptr ) {
	printf("a: %d; b: %d; str: %s\n", ptr->a, ptr->b, ptr->str);
}

void free_elem( struct ll_data *ptr ) {
	if(ptr->str != NULL) {
		free(ptr->str);
		ptr->str = NULL;
	}
}

int compare_strcts(struct ll_data *el1, struct ll_data *el2) {
	if(el1->a == el2->a) return 1;
	return 0;
}

int main(void) {

	struct lltemp *llist = NULL;
	
	char *one = "str1", *two = "stringnr2", *three = "stringnr3", *four = "insertedone"; 
	
	struct ll_data *tmpptr = malloc(sizeof(struct ll_data));
	tmpptr->a = 1; tmpptr->b = 2;
	tmpptr->str = malloc(strlen(one)+1);
	strcpy(tmpptr->str, one);
	llist = ll_append(llist, tmpptr);

	tmpptr = malloc(sizeof(struct ll_data));
	tmpptr->a = 3; tmpptr->b = 4;
	tmpptr->str = malloc(strlen(two)+1);
	strcpy(tmpptr->str, two);
	llist = ll_append(llist, tmpptr);

	tmpptr = malloc(sizeof(struct ll_data));
	tmpptr->a = 5; tmpptr->b = 6;
	tmpptr->str = malloc(strlen(three)+1);
	strcpy(tmpptr->str, three);
	llist = ll_append(llist, tmpptr);

	llist = ll_prepend(llist, tmpptr);
	
	tmpptr = malloc(sizeof(struct ll_data));
	tmpptr->a = 666; tmpptr->b = 777;
	tmpptr->str = malloc(strlen(four)+1);
	strcpy(tmpptr->str, four);

	ll_insert(llist, tmpptr);

	ll_print(llist, (void*)print_elem);

	struct lltemp *found = NULL;
	struct ll_data *f = NULL;
	tmpptr = malloc(sizeof(struct ll_data));
	tmpptr->a = 3; tmpptr->b = 777; tmpptr->str = NULL;
	found = ll_search(llist, tmpptr, (void*)compare_strcts);
	
	if(found == NULL) {
		printf("Element not found.\n");
	} else {
		f = found->el;
		printf("\nSearchin: <<%d>> %d %s; Found: <<%d>> %d %s\n", tmpptr->a, tmpptr->b, tmpptr->str, f->a, f->b, f->str);
	}

	// llist = ll_delete_elem(llist, found, (void*)free_elem);

	tmpptr = malloc(sizeof(struct ll_data)); tmpptr->a = 666;
	struct lltemp *fod2 = ll_search(llist, tmpptr, (void*)compare_strcts);
	f = fod2->el;
	printf("Found 2: <<%d>> %d %s\nSwapping\n\n", f->a, f->b, f->str);
	llist = ll_swap(llist, fod2, found);
	
	ll_print(llist, (void*)print_elem);

	ll_free(llist, (void*)free_elem);

	return 0;
}