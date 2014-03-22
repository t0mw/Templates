#include "../fsm_template.h"
#include <stdio.h>

#define FSM_FETCH_DATA( fsm ) ( (struct this_fsm_data *)( FSM_DATA( fsm ) ) )

enum this_states { S_PREAMBLE, S_FUNCTION, S_DATA_NO, S_DATA, S_CHECKSUM };

struct this_fsm_data {
	char function_code;
	int data_no;
	char data[20];
	char checksum;
};

void preamble( struct fsm *fsm, void *params ) {
	printf( "Reading preamble\n" );
	static int preamble_count = 0;
	if( *(unsigned char *)params == 0xFF ) {
		++preamble_count;
	} else {
		preamble_count = 0;
	}
	
	if( preamble_count == 5 ) {
		FSM_SWITCH( fsm, S_FUNCTION );
	}
}

void function( struct fsm *fsm, void *params ) {
	printf( "Reading function\n" );
	FSM_FETCH_DATA(fsm)->function_code = *(char *)params;
	FSM_SWITCH( fsm, S_DATA_NO );
}

void data_no( struct fsm *fsm, void *params ) {
	printf( "Reading data no\n" );
	FSM_FETCH_DATA(fsm)->data_no = *(char *)params;
	FSM_SWITCH( fsm, S_DATA );
}

void data_read( struct fsm *fsm, void *params ) {
	printf( "Reading data\n" );
	static int data_no = 0;
	if( data_no < FSM_FETCH_DATA(fsm)->data_no ) {
		FSM_FETCH_DATA(fsm)->data[data_no++] = *(char *)params;
	}
	
	if( data_no == FSM_FETCH_DATA(fsm)->data_no ) {
		FSM_SWITCH( fsm, S_CHECKSUM );
	}

}

void checksum_read( struct fsm *fsm, void *params ) {
	printf( "Read checskum\n" );
	FSM_FETCH_DATA(fsm)->checksum = *(char *)params;
	FSM_SWITCH( fsm, S_PREAMBLE );
}

/*
	Quick & dirty example.
*/
int main( void ) {

	struct fsm fsm;
	
	fsm_init( &fsm, S_PREAMBLE, preamble );
	struct this_fsm_data fd;
	FSM_DATA( &fsm ) = &fd;
	
	fsm_register_state( &fsm, S_PREAMBLE, preamble );
	fsm_register_state( &fsm, S_FUNCTION, function );
	fsm_register_state( &fsm, S_DATA_NO, data_no );
	fsm_register_state( &fsm, S_DATA, data_read );
	fsm_register_state( &fsm, S_CHECKSUM, checksum_read );

	unsigned char prot_frame[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 'f', 4, 'd', 'a', 't', 'a', 'c' };
	
	unsigned int i = 0;
	for( i = 0; i < sizeof(prot_frame)/sizeof(*prot_frame); ++i ) {
		fsm_run( &fsm, (void *)&(prot_frame[i]) );
	}
	
	printf( "FSM data: function: %c, data_no: %d\ndata: ",
			FSM_FETCH_DATA( &fsm )->function_code,
			FSM_FETCH_DATA( &fsm )->data_no	);
	for( i = 0; i < (unsigned int)FSM_FETCH_DATA( &fsm )->data_no; ++i ) {
		printf( "%c ", FSM_FETCH_DATA( &fsm )->data[i] );
	}
	printf( "\nchecksum: %c\n", FSM_FETCH_DATA( &fsm )->checksum );

	return 0;

}
