#ifndef __LTEMPLATE__
#define __LTEMPLATE__

/*
*	Linked list element; el is a pointer to user's stuff ( structure, int, whatever )
*/
struct lltemp {
	void *el;
	struct lltemp *next;
};

struct lltemp *ll_append( struct lltemp *ll_ptr, void *new_el );
struct lltemp *ll_prepend( struct lltemp *ll_ptr, void *new_el);
void ll_insert(struct lltemp *ll_elem_ptr, void *new_el);
struct lltemp *ll_search( struct lltemp *ll_ptr, void *needle, int (*comparefunction)(void *, void *) );
struct lltemp *ll_delete_elem( struct lltemp *ll_ptr, struct lltemp *delete, void (*freefunction)(void *) );
struct lltemp *ll_swap(struct lltemp *ll_ptr, struct lltemp *el1, struct lltemp *el2);
void ll_print( struct lltemp *ll_ptr, void (*printfunction)(void *) );
void ll_free( struct lltemp *ll_ptr, void (*freefunction)(void *) );

#endif
