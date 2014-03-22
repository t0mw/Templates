#include "fsm_template.h"
#include <stdlib.h>
#include <assert.h>

void fsm_init( struct fsm *fsm_obj, int state_id, state_handler_t init_state ) {

	fsm_obj->fsm_data = NULL;
	fsm_obj->state_id = state_id;
	fsm_register_state( fsm_obj, state_id, init_state );

}

void fsm_register_state( struct fsm *fsm_obj, int state_id, state_handler_t handler ) {

	assert( state_id < FSM_MAX_STATES );

	fsm_obj->states[state_id] = handler;

}

void fsm_unregister_state( struct fsm *fsm_obj, int state_id ) {

	assert( state_id < FSM_MAX_STATES );

	fsm_obj->states[state_id] = NULL;

}

void fsm_run( struct fsm *fsm_obj, void *params ) {

	(fsm_obj->states[fsm_obj->state_id])( fsm_obj, params );
	
}
