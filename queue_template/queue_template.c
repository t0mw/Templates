/*!
	\file queue_template.c
	\brief Queue template implementation.
*/

#include <stdio.h>
#include <stdlib.h>

#include "queue_template.h"

struct queue_top *queue_create( void ) {
	struct queue_top *new_queue = malloc( sizeof( struct queue_top ) );
	
	new_queue->elems_count = 0;
	new_queue->elems = NULL;
	new_queue->last_elem = NULL;

	return new_queue;
}

void *queue_pop( struct queue_top *top ) {

	if( top == NULL || top->elems == NULL ) return NULL;
		
	struct queue_elem *tmp = top->elems;
	
	void *ret = tmp->el;
	
	top->elems = tmp->prev;
	free( tmp ); tmp = NULL;

	--(top->elems_count);
	
	return ret;
}

void queue_push( struct queue_top *top, void *new_el ) {
	
	if( top == NULL ) return;
	
	struct queue_elem *new_q_elem = malloc( sizeof( struct queue_elem ) );
	new_q_elem->el = new_el;
	new_q_elem->prev = NULL;
	
	if( top->last_elem == NULL ) {
		top->last_elem = new_q_elem;
		top->elems = new_q_elem;
	} else {
		top->last_elem->prev = new_q_elem;
		top->last_elem = new_q_elem;
	}
	
	++(top->elems_count);

}

void queue_delete( struct queue_top **top_ptr ) {

	if( top_ptr == NULL ) return;
	
	if( (*top_ptr)->elems == NULL ) goto FREE_TOPQUEUEPTR;
	
	struct queue_top *top = *top_ptr;

	int elems_counter = top->elems_count;
	
	struct queue_elem *to_del = top->elems;
	
	while( elems_counter-- > 0 ) {
		
		top->elems = to_del->prev;
		
		free( to_del->el ); to_del->el = NULL;
		free( to_del ); to_del = NULL;
		
		to_del = top->elems;
		
	}
	
	top->elems_count = 0;
	top->last_elem = NULL;
	
	FREE_TOPQUEUEPTR:		// free queue holder
		free( *top_ptr );
		*top_ptr = NULL;

}








