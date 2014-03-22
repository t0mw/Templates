#include <stdio.h>
#include <stdlib.h>
#include "lltemplate.h"

/*
*	Serious overkill is serious (just testin' lltemplate)
*	quick and dirty linked list bubble sort
*/

void pel(int *el) {
	static int nr = 0;
	printf("#%d: %d\n", nr++ % 10, *el);
}

void fel(int *el) {
	free(el);
	el = NULL;
}

struct lltemp *bubblesort(struct lltemp *llhead) {
	struct lltemp *ptr = llhead;
	struct lltemp *ptr2 = NULL;
	while(ptr != NULL && ptr->next != NULL) {
		ptr2 = ptr->next;
		if( *((int*)ptr->el) > *((int*)ptr2->el) ) {
			llhead = ll_swap(llhead, ptr, ptr2);
			ptr = llhead;
			continue;
		}
		ptr = ptr->next;
	}
	return llhead;
}

int main(void) {

	struct lltemp *ll = NULL;
	int *el;
	int i;
	for(i = 10; i > 0; i--) {
		el = malloc(sizeof(int));
		*el = i;
		ll = ll_append(ll, el);
	}

	ll_print(ll, (void*)pel);
	ll = bubblesort(ll);

	ll_print(ll, (void*)pel);

	ll_free(ll, (void*)fel);
	
	return 0;
	
}