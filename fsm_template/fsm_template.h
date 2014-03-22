#ifndef __FSM_TEMPLATE_H__
#define __FSM_TEMPLATE_H__

#define FSM_MAX_STATES 10

#define FSM_SWITCH( fsm_obj_ptr, int_new_state ) ( (fsm_obj_ptr)->state_id = int_new_state )
#define FSM_DATA( fsm_obj_ptr ) ( (fsm_obj_ptr)->fsm_data )

struct fsm;

typedef void (*state_handler_t)( struct fsm *fsm, void *params );

struct fsm {
	volatile int state_id;
	volatile void *fsm_data;
	state_handler_t states[FSM_MAX_STATES];
};

void fsm_init( struct fsm *fsm_obj, int state_id, state_handler_t init_state );

void fsm_register_state( struct fsm *fsm_obj, int state_id, state_handler_t handler );

void fsm_unregister_state( struct fsm *fsm_obj, int state_id );

void fsm_run( struct fsm *fsm_obj, void *params );

#endif
