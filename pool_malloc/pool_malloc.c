#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "pool_malloc.h"

void pool_create( struct pool **new_pool, uint32_t new_pool_size ) {

	assert( new_pool != NULL && (*new_pool) != NULL );
	assert( new_pool_size > 0 );
	
	if( ( (*new_pool)->avail = malloc( new_pool_size ) ) == NULL ) {
		*new_pool = NULL;
		return;
	}
	
	(*new_pool)->start = (*new_pool)->avail;
	(*new_pool)->free_left = new_pool_size;
		
}

void pool_create_from_buf( struct pool **new_pool, uint8_t *buffer, uint32_t new_pool_size ) {

	assert( new_pool != NULL && (*new_pool) != NULL && buffer != NULL );
	assert( new_pool_size > 0 );
	
	(*new_pool)->avail = buffer;
	
	(*new_pool)->start = (*new_pool)->avail;
	(*new_pool)->free_left = new_pool_size;
		
}

void *pool_malloc( struct pool *dst_pool, uint32_t size ) {

	assert( dst_pool != NULL );
	assert( size > 0 );

	if( dst_pool->free_left >= size ) {
		uint8_t *tmp = dst_pool->avail;
		dst_pool->avail += size;
		dst_pool->free_left -= size;
		return tmp;
	}
	
	return NULL;

}

void pool_free( struct pool **pool_ptr, void (*free_fun)( void *p ) ) {

	assert( pool_ptr != NULL);
	assert( *pool_ptr != NULL );

	if( free_fun != NULL ) {
		free_fun( (*pool_ptr)->start );
		(*pool_ptr)->start = NULL;
	}

	(*pool_ptr)->avail = NULL;
	(*pool_ptr)->free_left = 0;

}
