#include "../vector_template.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

START_TEST( test_vector_create ) {

	struct vector *v = vector_create();
	
	ck_assert_int_eq( 0, v->count );
	ck_assert_int_eq( 0, v->size );
	ck_assert_ptr_eq( v->elems, NULL );
	ck_assert_int_eq( -1, v->empty_index );
	
	vector_free( &v, NULL );
	
} END_TEST

START_TEST( test_vector_add_insert_get ) {

	struct vector *v = vector_create();
	
	vector_add( v, strdup("test_str") );
	
	int *intptr = malloc( sizeof(int) ); *intptr = 314;
	vector_add( v, intptr );
	
	ck_assert_str_eq( "test_str", (char *)v->elems[0] );
	ck_assert_int_eq( 314, *(int *)v->elems[1] );
	
	ck_assert_str_eq( "test_str", vector_get( v, 0 ) );
	ck_assert_int_eq( 314, *(int *)vector_get( v, 1 ) );
	
	vector_insert( v, strdup("test_str_no2"), 0 );
	ck_assert_str_eq( "test_str_no2", vector_get( v, 0 ) );
	
	vector_free( &v, free );

} END_TEST

START_TEST( test_vector_swap ) {

	struct vector *v = vector_create();
	
	vector_add( v, strdup("first_elem") );
	vector_add( v, strdup("second_elem") );
	
	vector_swap( v, 0, 1 );
	
	ck_assert_str_eq( "second_elem", vector_get( v, 0 ) );
	ck_assert_str_eq( "first_elem", vector_get( v, 1 ) );
	
	vector_free( &v, free );

} END_TEST

START_TEST( test_vector_delete_el ) {

	struct vector *v = vector_create();
	
	vector_add( v, strdup("elem_to_delete") );
	vector_delete_el( v, 0, free );
	
	ck_assert_ptr_eq( NULL, vector_get( v, 0 ) );
	
	vector_free( &v, NULL );

} END_TEST

START_TEST( test_vector_shrink_to_fit ) {

	struct vector *v = vector_create();
	
	vector_add( v, strdup("first") );
	vector_add( v, strdup("second") );
	vector_add( v, strdup("third") );
	
	int vector_old_size = v->size;
	vector_delete_el( v, 0, free );
	
	vector_shrink_to_fit( v );
	
	ck_assert_int_eq( vector_old_size - 1, v->size );
	ck_assert_int_eq( v->count, v->size );
	
	vector_free( &v, free );

} END_TEST

static void map_fun( void *vel ) {
	*(int *)vel += 10;
}

START_TEST( test_vector_map ) {

	struct vector *v = vector_create();
	
	int *a = NULL;
	vector_add( v, (a = malloc(sizeof(int)), *a = 5, a) );
	vector_add( v, (a = malloc(sizeof(int)), *a = 10, a) );
	vector_add( v, (a = malloc(sizeof(int)), *a = 15, a) );

	vector_map( v, map_fun );
	
	ck_assert_int_eq( 15, *(int *)vector_get( v, 0 ) );
	ck_assert_int_eq( 20, *(int *)vector_get( v, 1 ) );
	ck_assert_int_eq( 25, *(int *)vector_get( v, 2 ) );
	
	vector_free( &v, free );

} END_TEST

START_TEST( test_vector_add_at_deleted_index ) {

	struct vector *v = vector_create();
	
	vector_add( v, strdup("to_delete") );
	vector_add( v, strdup("teststr") );
	
	vector_delete_el( v, 0, free );
	vector_add( v, strdup("new_elem") );
	
	ck_assert_str_eq( "new_elem", vector_get( v, 0 ) );
	
	vector_free( &v, free );

} END_TEST

static int strcmp_v2( void *el1, void *el2 ) {

	return ( strcmp( (char *)el1, (char *)el2 ) == 0 ) ? 1 : 0;

}

START_TEST( test_vector_search ) {

	struct vector *v = vector_create();
	
	vector_add( v, strdup("testone") );
	vector_add( v, strdup("testtwo") );
	vector_add( v, strdup("should_found") );
	vector_add( v, strdup("testfour") );
		
	int index = vector_search( v, "should_found", strcmp_v2 );
	
	ck_assert_int_eq( 2, index );
	
	vector_free( &v, free );

} END_TEST

Suite *vector_testsuite( void ) {

	Suite *s = suite_create( "vector_template_test" );
	
	TCase *tc_vector = tcase_create( "test_vector" );
	
	tcase_add_test( tc_vector, test_vector_create );
	tcase_add_test( tc_vector, test_vector_add_insert_get );
	tcase_add_test( tc_vector, test_vector_swap );
	tcase_add_test( tc_vector, test_vector_delete_el );
	tcase_add_test( tc_vector, test_vector_shrink_to_fit );
	tcase_add_test( tc_vector, test_vector_map );
	tcase_add_test( tc_vector, test_vector_add_at_deleted_index );
	tcase_add_test( tc_vector, test_vector_search );
	
	suite_add_tcase( s, tc_vector );
	
	return s;

}

int main(void) {
	
	Suite *s = vector_testsuite();
	SRunner *sr = srunner_create( s );
	
	srunner_run_all( sr, CK_NORMAL );
	
	return 0;
	
}
