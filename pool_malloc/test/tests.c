#include "../pool_malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>

START_TEST( test_pool_create_malloc_buf ) {

	struct pool mempool, buf_mempool;
	struct pool *pool_ptr = &mempool, *buf_pool_ptr = &buf_mempool;
		
	uint8_t buffer[64];
	
	pool_create( &pool_ptr, 5*sizeof(int) );
	pool_create_from_buf( &buf_pool_ptr, buffer, 5*sizeof(int) );
	
	ck_assert_ptr_ne( NULL, mempool.avail );
	ck_assert_ptr_ne( NULL, mempool.start );
	ck_assert_ptr_eq( mempool.avail, mempool.start );
	ck_assert_int_eq( 5*sizeof(int), mempool.free_left );

	ck_assert_ptr_ne( NULL, buf_mempool.avail );
	ck_assert_ptr_ne( NULL, buf_mempool.start );
	ck_assert_ptr_eq( buffer, buf_mempool.avail );
	ck_assert_ptr_eq( buffer, buf_mempool.start );
	ck_assert_int_eq( 5*sizeof(int), buf_mempool.free_left );
	
	pool_free( &pool_ptr, free );
	pool_free( &buf_pool_ptr, NULL );

} END_TEST

START_TEST( test_pool_malloc ) {

	struct pool mempool, buf_mempool;
	struct pool *pool_ptr = &mempool, *buf_pool_ptr = &buf_mempool;
	
	int valid_values[] = { 5, 6, 7, 8, 9 };
	
	uint8_t buffer[64];
	
	pool_create( &pool_ptr, 5*sizeof(int) );
	pool_create_from_buf( &buf_pool_ptr, buffer, 5*sizeof(int) );
	
	int *pool_tab_l = pool_malloc( pool_ptr, 3*sizeof(int) );
	ck_assert_ptr_eq( mempool.avail, pool_tab_l + 3 );
	
	int *pool_tab_h = pool_malloc( pool_ptr, 2*sizeof(int) );
	
	int *buf_pool_tab_l = pool_malloc( buf_pool_ptr, 3*sizeof(int) );
	ck_assert_ptr_eq( buf_mempool.avail, buf_pool_tab_l + 3 );
	
	int *buf_pool_tab_h = pool_malloc( buf_pool_ptr, 2*sizeof(int) );
	
	int i = 0;
	for( i = 0; i < 5; ++i ) {
	
		if( i < 3 ) {
			pool_tab_l[i] = valid_values[i];
			buf_pool_tab_l[i] = valid_values[i];
		
			ck_assert_int_eq( valid_values[i], pool_tab_l[i] );
			ck_assert_int_eq( valid_values[i], buf_pool_tab_l[i] );
		} else {
			pool_tab_h[i-3] = valid_values[i];
			buf_pool_tab_h[i-3] = valid_values[i];
			
			ck_assert_int_eq( valid_values[i], pool_tab_h[i-3] );
			ck_assert_int_eq( valid_values[i], buf_pool_tab_h[i-3] );
		}
		
	}
	
	pool_free( &pool_ptr, free );
	pool_free( &buf_pool_ptr, NULL );


} END_TEST

START_TEST( test_pool_mallocfail ) {

	struct pool mempool, buf_mempool;
	struct pool *pool_ptr = &mempool, *buf_pool_ptr = &buf_mempool;
		
	uint8_t buffer[64];
	
	pool_create( &pool_ptr, 5*sizeof(int) );
	pool_create_from_buf( &buf_pool_ptr, buffer, 5*sizeof(int) );
	
	int *ptr = pool_malloc( pool_ptr, 6*sizeof(int) );
	ck_assert_ptr_eq( NULL, ptr );
	
	int *buf_ptr = pool_malloc( buf_pool_ptr, 6*sizeof(int) );
	ck_assert_ptr_eq( NULL, buf_ptr );
	
	pool_free( &pool_ptr, free );
	pool_free( &buf_pool_ptr, NULL );

} END_TEST

Suite *pool_malloc_testsuite( void ) {

	Suite *s = suite_create( "pool_malloc" );
	
	TCase *tc_pm = tcase_create( "test_pool_malloc" );
	tcase_add_test( tc_pm, test_pool_create_malloc_buf );
	tcase_add_test( tc_pm, test_pool_malloc );
	tcase_add_test( tc_pm, test_pool_mallocfail );
	
	suite_add_tcase( s, tc_pm );
	
	return s;

}


int main( void ) {

	Suite *s = pool_malloc_testsuite();
	SRunner *sr = srunner_create( s );
	
	srunner_run_all( sr, CK_NORMAL );
			
	return 0;

}