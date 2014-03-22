/*
*	Linked list template.
*
*	There are three functions to define to get this thing to work (pointers passed to ll_functions).
*	Function 1: for printing linked list element: void printfunctionname( yourtype *ptr );
*	Function 2: for freeing linked list element: void freefunctionname( yourtype *ptr );
*	Function 3: for comparing elements in linked list: int comparefunctionname( yourtype *ptr1, yourtype *ptr2 );
*				\- returns 1 if equal, 0 if not
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lltemplate.h"

/*
*	Appends element new_el to linked list ll_ptr.
*	new_el is not copied, you shouldn't free() it after ll_append(). ll_free() will deal with it later.
*	in: ll_ptr; new_el
*	out: new pointer to linked list
*/
struct lltemp *ll_append( struct lltemp *ll_ptr, void *new_el ) {
	struct lltemp *ptr = NULL;
	if(ll_ptr != NULL) {
		ptr = ll_ptr;
		while(ptr->next != NULL) ptr = ptr->next;
		ptr->next = malloc( sizeof(struct lltemp) );
		ptr = ptr->next;
	} else {
		ptr = malloc( sizeof(struct lltemp) );
		ll_ptr = ptr;
	}
	ptr->el = new_el;
	ptr->next = NULL;
	
	return ll_ptr;
}

/*
*	Inserts new_el as first element of linked list.
*	new_el is not copied, you shouldn't free() it after ll_prepend(). ll_free() will deal with it later.
*	in: ll_ptr; new_el
*	out: new pointer to linked list
*/
struct lltemp *ll_prepend( struct lltemp *ll_ptr, void *new_el) {
	struct lltemp *ptr = malloc( sizeof(struct lltemp) );
	ptr->el = new_el;
	ptr->next = ll_ptr;
	return ptr;
}

/*
*	Inserts new_el after ll_elem_ptr.
*	new_el is not copied, you shouldn't free() it after ll_insert(). ll_free() will deal with it later.
*	in: ll_elem_ptr - pointer to element after which new_el will be inserted; new_el
*	out: void
*/
void ll_insert(struct lltemp *ll_elem_ptr, void *new_el) {
	struct lltemp *tmp_ptr = ll_elem_ptr->next;
	ll_elem_ptr->next = malloc( sizeof(struct lltemp) );
	ll_elem_ptr->next->el = new_el;
	ll_elem_ptr->next->next = tmp_ptr;
}

/*
*	Looks for "needle" in linked list.
*	compare function: returns 1 if equal, 0 if not
*	in: ll_ptr; needle - elem to search for; comparefunction - pointer to function comparing elems in LL
*	out: new pointer to linked list
*/
struct lltemp *ll_search( struct lltemp *ll_ptr, void *needle, int (*comparefunction)(void *, void *) ) {
	while(ll_ptr != NULL) {
		if( (*comparefunction)(ll_ptr->el, needle) ) return ll_ptr;
		ll_ptr = ll_ptr->next;
	}
	return NULL;
}

/*
*	Deletes element from linked list.
*	in: ll_ptr; delete - element to delete (you don't say); freefunction - pointer to function freeing element
*	out: new pointer to linked list
*/
struct lltemp *ll_delete_elem( struct lltemp *ll_ptr, struct lltemp *delete, void (*freefunction)(void *) ) {
	/* Deleting first element of linked list */
	if(ll_ptr == delete) {
		struct lltemp *tmpptr = delete->next;
		(*freefunction)(delete->el);
		free(delete);
		delete = NULL;
		return tmpptr;
	}

	/* Elem further in linked list */
	struct lltemp *previous = ll_ptr;
	while(previous != NULL) {
		if(previous->next == delete) break;
		previous = previous->next;
	}
	if(previous == NULL) return ll_ptr; /* no "delete" in list, doin' nothing */
	
	previous->next = delete->next;
	(*freefunction)(delete->el);
	free(delete);
	delete = NULL;
	return ll_ptr;
}

/*
*	Swaps two elems in linked list.
*	int: ll_ptr; el1 - first elem in linked list; el2 - second elem
*	out: new pointer to linked list
*/
struct lltemp *ll_swap(struct lltemp *ll_ptr, struct lltemp *el1, struct lltemp *el2) {
	if(el1 == el2) return ll_ptr;	/* got equal elems, return */

	if(el1->next == el2) {	/* ... ->[el1]->[el2]-> ... */
		if(el1 == ll_ptr) {
			el1->next = el2->next;
			el2->next = el1;
			return el2;
		}

		struct lltemp *ptr = ll_ptr;
		while(ptr != NULL) {
			if(ptr->next == el1) break;
			ptr = ptr->next;
		}
		if(ptr == NULL) return ll_ptr;	/* not swappin anything, el1 not in list */

		ptr->next = el2;
		el1->next = el2->next;
		el2->next = el1;
		return ll_ptr;
	} else {	/* ... ->[el1]-> ... ->[el2]-> ... */
		/* finding elem before el2 */
		struct lltemp *el2_prev = ll_ptr;
		while(el2_prev != NULL) {
			if(el2_prev->next == el2) break;
			el2_prev = el2_prev->next;
		}
		if(el2_prev == NULL) return ll_ptr;	/* el2 not in list */

		if(el1 == ll_ptr) {
			struct lltemp *tmpptr = el1->next;
			el2_prev->next = el1;
			el1->next = el2->next;
			el2->next = tmpptr; /* el1->next; */
			return el2;
		}
		
		struct lltemp *el1_prev = ll_ptr;
		while(el1_prev != NULL) {
			if(el1_prev->next == el1) break;
			el1_prev = el1_prev->next;
		}
		if(el1_prev == NULL) return ll_ptr;	/* not swappin anything, el1 not in list */
		
		struct lltemp *tmpptr = el2->next;
		el1_prev->next = el2;	/* no comment */
		el2->next = el1->next;
		el2_prev->next = el1;
		el1->next = tmpptr;
		return ll_ptr;
	}
}

/*
*	Prints each element in linked list with printfunction.
*	in: ll_ptr; printfunction - pointer to function printing elem
*	out: void
*/
void ll_print( struct lltemp *ll_ptr, void (*printfunction)(void *) ) {
	while(ll_ptr != NULL) {
		(*printfunction)(ll_ptr->el);
		ll_ptr = ll_ptr->next;
	}
}

/*
*	Frees the list.
*	in: ll_ptr; freefunction - pointer to function freeing elem
*	out: void
*/
void ll_free( struct lltemp *ll_ptr, void (*freefunction)(void *) ) {
	struct lltemp *ptr = ll_ptr;
	while(ll_ptr != NULL) {
		ptr = ll_ptr;
		ll_ptr = ll_ptr->next;

		(*freefunction)(ptr->el);
		free(ptr);
		ptr = NULL;
	}
}

/*
*	Linked list template end.
*/
