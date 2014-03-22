/*!
	\file stack_template.c
	\brief Stack template implementation.
*/

#include <stdio.h>
#include <stdlib.h>

#include "stack_template.h"

struct stack_top *stack_create( void ) {

	struct stack_top *stack_ret = malloc( sizeof( struct stack_top ) );
	stack_ret->elems_count = 0;
	stack_ret->stack_ptr = NULL;
	return stack_ret;

}

void stack_push( struct stack_top *top, void *elem ) {

	if( top == NULL ) return;

	struct stack_elem *new_el = malloc( sizeof( struct stack_elem ) );
	new_el->el = elem;

	new_el->prev = top->stack_ptr;

	top->stack_ptr = new_el;
	++(top->elems_count);

}

void *stack_pop( struct stack_top *top ) {

	if( top == NULL || top->stack_ptr == NULL ) return NULL;

	struct stack_elem *tmp = top->stack_ptr;
	top->stack_ptr = tmp->prev;
	--(top->elems_count);

	void *ret_el = tmp->el;
	free( tmp );
	tmp = NULL;
	
	return ret_el;

}

void stack_delete( struct stack_top **top_ptr ) {

	if( top_ptr == NULL ) return;

	if( (*top_ptr)->stack_ptr == NULL ) goto FREE_TOPSTACKPTR;

	struct stack_top *top = *top_ptr;

	int elems = top->elems_count;

	struct stack_elem *stack_del = top->stack_ptr;
	struct stack_elem *stack_del_prev = NULL;

	while( elems-- > 0 ) {
		stack_del_prev = stack_del->prev;
		
		free( stack_del->el ); stack_del->el = NULL;
		free( stack_del ); stack_del = NULL;
		
		stack_del = stack_del_prev;
	}
		
	top->stack_ptr = NULL;
	top->elems_count = 0;

	FREE_TOPSTACKPTR:		// free stack holder
		free( *top_ptr );
		*top_ptr = NULL;
	
}


