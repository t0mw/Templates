#ifndef __POOL_MALLOC_H__
#define __POOL_MALLOC_H__

#include <stdint.h>

struct pool {
	uint8_t *avail;		//!< First available memory byte.
	uint8_t *start;		//!< Start of pool.
	uint32_t free_left;	//!< Free memory bytes left.
};

/*!
	\brief Create pool - allocate new_pool_size bytes for pool.
	\param new_pool Address of pointer to struct pool. If allocation failed, new_pool will be set to NULL.
	\param new_pool_size New pool size.
*/
void pool_create( struct pool **new_pool, uint32_t new_pool_size );

/*!
	\brief Create pool from buffer.
	\param new_pool Address of pointer to struct pool.
	\param buffer Buffer for allocated data.
	\param new_pool_size New pool size (size of buffer).
*/
void pool_create_from_buf( struct pool **new_pool, uint8_t *buffer, uint32_t new_pool_size );

/*!
	\brief Allocates memory from specified pool.
	\param dst_pool Pointer to struct pool with available memory.
	\param size Requested size to allocate.
	\return Address of first available byte in memory, NULL if dst_pool is full.
*/
void *pool_malloc( struct pool *dst_pool, uint32_t size );

/*!
	\brief Free memory from specified pool.
	\param pool_ptr Address of pointer to struct pool.
	\param free_fun Function to free pool (NULL if pool created from buffer)
*/
void pool_free( struct pool **pool_ptr, void (*free_fun)( void *p ) );

#endif
