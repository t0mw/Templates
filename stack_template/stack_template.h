#ifndef __STACK_TEMPLATE_H__
#define __STACK_TEMPLATE_H__

/*!
	\file stack_template.h
	\brief Stack template interface declarations.
*/

/*!
	\mainpage Stack template.
	Simple stack (FILO, First In Last Out) template with basic features.
*/

/*!
	\brief Element of the stack.
*/
struct stack_elem {
	void *el;	//!< Element stored in stack.
	struct stack_elem *prev; //!< Pointer to previous stack elem.
};

/*!
	\brief Stack "holder".
*/
struct stack_top {
	int elems_count;	//!< Number of elems that are actually in stack.
	struct stack_elem *stack_ptr;	//!< Pointer to the stack.
};

/*!
	\brief Creates new stack.
	\return New stack holder, with zeroed elems counter and no stack.
*/
struct stack_top *stack_create( void );

/*!
	\brief Push new elem to stack.
	\param top Stack holder.
	\param elem Pointer to new element pushed on stack.
*/
void stack_push( struct stack_top *top, void *elem );

/*!
	\brief Gets first element and removes it from stack.
	\param top Stack holder.
	\return Pointer to first element that have been stored in stack, or NULL if "top" param was NULL.
*/
void *stack_pop( struct stack_top *top );

/*!
	\brief Deletes stack holder and whole stack.
	\param top_ptr Pointer to stack holder.
*/
void stack_delete( struct stack_top **top_ptr );


#endif