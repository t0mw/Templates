#ifndef __QUEUE_TEMPLATE_H__
#define __QUEUE_TEMPLATE_H__

/*!
	\file queue_template.h
	\brief Queue template interface declarations.
*/

/*!
	\mainpage Queue template.
	Simple queue (FIFO, First In First Out) template with basic features.
*/

/*!
	\brief Element of the queue.
*/
struct queue_elem {
	void *el;	//!< Element stored in queue.
	struct queue_elem *prev;	//!< Pointer to previous elem in queue.
};

/*!
	\brief Queue "holder".
*/
struct queue_top {
	int elems_count;	//!< Number of elems in stack.
	struct queue_elem *elems; //!< Pointer to actual queue.
	struct queue_elem *last_elem;	//!< Last element in queue.
};

/*!
	\brief Creates new queue.
	\return Pointer to new queue holder (no elems, no queue).
*/
struct queue_top *queue_create( void );

/*!
	\brief Gets last element and removes it from queue.
	\param top Queue holder.
	\return Last element stored in queue.
*/
void *queue_pop( struct queue_top *top );

/*!
	\brief Inserts new element into the queue.
	\param top Queue holder.
	\param new_el Pointer to new element.
*/
void queue_push( struct queue_top *top, void *new_el );

/*!
	\brief Deletes queue (holder and stored elements).
	\param top_ptr Pointer to queue holder.
*/
void queue_delete( struct queue_top **top_ptr );


#endif 