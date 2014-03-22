#ifndef _HASHTAB_TEMPLATE_H_
#define _HASHTAB_TEMPLATE_H_

#define _HTAB_ELEM_DELETED (void *)0x01

/*!
	\brief Main hashtab structure.
*/
struct hashtab_holder {
	long long int elems_count;	//!< Elems in hashtable.
	long long int max_size;		//!< Max size of tab.
	struct hashtab_elem *htable;	//!< Hashtable.
	long long int (*_HX)( long long int, int, long long int );	//!< Hashing function pointer.
};

/*!
	\brief Hashtable element, holds unique key and ptr to users struct.
*/
struct hashtab_elem {
	long long int key;
	void *value;
};

/*!
	\brief Creates hashtab.
	\param HX pointer to hashing function (open addressing) HX( key, collision_number, max ). Returned value can't be bigger than actual size of hashtable.
	\return Pointer to hashtab holder.
*/
struct hashtab_holder *hashtab_create( long long int (*HX)(long long int, int, long long int) );

/*!
	\brief Adds new elem to hashtable.
	\param htab Hashtable pointer.
	\param new Pointer to elem to add.
	\param key Key of new elem.
*/
void hashtab_add( struct hashtab_holder *htab, void *new, int key );

/*!
	\brief Finds elem in hashtable by key.
	\param htab Hashtable pointer.
	\param key Key to search for.
	\return Pointer to found elem or NULL if not in hashtable.
*/
void *hashtab_find( struct hashtab_holder *htab, int key );

/*!
	\brief Deletes elem from hashtable.
	\brief htab Hashtable pointer.
	\brief key Hashtable elems key.
	\brief free_deleted_elem pointer to function free()-ing elem in htab (if necessary, NULL if not).
*/
void hashtab_delete_elem( struct hashtab_holder *htab, int key, void (*free_deleted_elem)(void *) );

/*!
	\brief Frees all elems and deletes hashtable.
	\param htab Pointer to hashtable pointer.
	\param free_deleted_elem pointer to function free()-ing elem in htab (if necessary, NULL if not).
*/
void hashtab_free( struct hashtab_holder **htab, void (*free_deleted_elem)(void *) );

#endif