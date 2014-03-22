#include <stdio.h>
#include <stdlib.h>
#include <check.h>

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
