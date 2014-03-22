#include <stdio.h>
#include <stdlib.h>

#include "hashtab_template.h"

/*!
	\brief Shitty default hashing function.
	\param elem New element's id.
	\param coll Collision number.
	\param max Max size of hash table.
	\return tab index < max
*/
static long long int hashing_function( long long int elem, int coll, long long int max ) {

	if( max == 0 ) { printf("#ERR: hashing_function: max == 0\n"); exit(1); }
		
	return ( (13*elem) + coll ) % max;
	
}

struct hashtab_holder *hashtab_create( long long int (*HX)(long long int, int, long long int) ) {

	struct hashtab_holder *new_htab = malloc( sizeof(struct hashtab_holder) );
	new_htab->elems_count = 0;
	new_htab->max_size = 0;
	new_htab->htable = NULL;
	if( HX != NULL ) new_htab->_HX = HX; else new_htab->_HX = hashing_function;

	return new_htab;

}

static void hashtab_expand( struct hashtab_holder *htab ) {

	if( htab == NULL ) return;
	
	htab->htable = realloc( htab->htable, (htab->max_size * 2 * sizeof(struct hashtab_elem)) );
		
	struct hashtab_elem *tmp = malloc( htab->max_size * sizeof(struct hashtab_elem) );
	
	long long int i = 0;
	for( i = 0; i < htab->max_size; i++ ) { tmp[i] = htab->htable[i]; }	// save old hashtable items
	
	for( i = 0; i < 2*(htab->max_size); i++ ) { htab->htable[i].value = NULL; htab->htable[i].key = 0; }	// reset new hashtable

	htab->elems_count = 0;
	
	for( i = 0; i < htab->max_size; i++ ) {
		int new_elem_index = htab->_HX( tmp[i].key, 0, (htab->max_size)*2 );
		int collision_num = 0;
		while( htab->htable[ new_elem_index ].value != NULL && htab->htable[ new_elem_index ].value != _HTAB_ELEM_DELETED ) {
			new_elem_index = htab->_HX( tmp[i].key, ++collision_num, (htab->max_size)*2 );
		}
				
		htab->htable[ new_elem_index ] = tmp[i];
		++htab->elems_count;
	}
	
	htab->max_size *= 2;
	
	free(tmp);

}

void hashtab_add( struct hashtab_holder *htab, void *new, int key ) {

	if( htab == NULL ) return;

	if( htab->elems_count == 0 ) { // Hash table is empty
		htab->max_size = 2;
		htab->htable = malloc( 2 * sizeof(struct hashtab_elem) );
		htab->htable[0].key = 0; htab->htable[1].key = 0;
		htab->htable[0].value = NULL; htab->htable[1].value = NULL;
	}

	if( htab->elems_count >= 0.8*(htab->max_size) ) hashtab_expand( htab );

	long long int new_elem_index = htab->_HX( key, 0, htab->max_size );
	int collision_num = 0;
	while( htab->htable[ new_elem_index ].value != NULL && htab->htable[ new_elem_index ].value != _HTAB_ELEM_DELETED ) {
		new_elem_index = htab->_HX( key, ++collision_num, htab->max_size );
	}
		
	htab->htable[ new_elem_index ].key = key;
	htab->htable[ new_elem_index ].value = new;
	++htab->elems_count;
	
}

void *hashtab_find( struct hashtab_holder *htab, int key ) {
	
	if( htab == NULL ) return NULL;
	
	void *ret = NULL;
	int index = htab->_HX( key, 0, htab->max_size );
		
	if( htab->htable[ index ].value == NULL ) return NULL;
	
	int collision_num = 0;
	while( htab->htable[ index ].value != NULL ) {
		if( htab->htable[ index ].key == key ) return htab->htable[index].value;
		index = htab->_HX( key, ++collision_num, htab->max_size );
	}
		
	return ret;

}

void hashtab_delete_elem( struct hashtab_holder *htab, int key, void (*free_deleted_elem)(void *) ) {

	if( htab == NULL ) return;
	
	int index = htab->_HX( key, 0, htab->max_size );
	if( htab->htable[ index ].value == NULL ) return;
	
	int collision_num = 0;
	while( htab->htable[ index ].value != NULL ) {
		if( htab->htable[ index ].key == key ) break;
		index = htab->_HX( key, ++collision_num, htab->max_size );
	}
	
	if( htab->htable[index].value != NULL ) {
		if( free_deleted_elem != NULL && htab->htable[index].value != _HTAB_ELEM_DELETED ) free_deleted_elem( htab->htable[index].value );
		htab->htable[ index ].key = 0;
		htab->htable[ index ].value = _HTAB_ELEM_DELETED;
	}
	
}

void hashtab_free( struct hashtab_holder **htab, void (*free_deleted_elem)(void *) ) {

	int i = 0;
	if( free_deleted_elem != NULL )	{
		for( i = 0; i < (*htab)->max_size; i++ ) {
			if( (*htab)->htable[i].value != NULL && (*htab)->htable[i].value != _HTAB_ELEM_DELETED ) free_deleted_elem( (*htab)->htable[i].value );
		}
	}
	
	free((*htab)->htable); (*htab)->htable = NULL;
	free((*htab)); (*htab) = NULL;

}



