/*
 *                               POK header
 * 
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2009 POK team 
 *
 * Created by julien on Thu Jan 15 23:34:13 2009 
 */

#include "config.h"

#ifdef POK_NEEDS_ARINC653_EVENT

#ifndef APEX_EVENT
#define APEX_EVENT


#ifndef POK_NEEDS_ARINC653_PROCESS
#define POK_NEEDS_ARINC653_PROCESS 1
#endif

#include <arinc653/process.h>

// must be at least MAX_NAME_LENGTH of ARINC653
#define POK_EVENT_MAX_NAME_LENGTH 30

typedef struct
{
   pok_event_id_t    core_id;
   pok_bool_t        ready;
   pok_bool_t        is_up;
   char              name[POK_EVENT_MAX_NAME_LENGTH];
} pok_arinc653_event_layer_t;

extern pok_arinc653_event_layer_t pok_arinc653_events_layers[];


/*----------------------------------------------------------------------*/
/* */
/* EVENT constant definitions */
/* */
/*----------------------------------------------------------------------*/
/* implementation dependent */
/* these values are given as example */
/*------------------------------*/
/* max nb of events */
/*------------------------------*/
#define MAX_NUMBER_OF_EVENTS 63
/*----------------------------------------------------------------------*/
/* */
/* EVENT type definitions */
/* */
/*----------------------------------------------------------------------*/
/*------------------------------*/
/* event ident type */
/*------------------------------*/
typedef APEX_INTEGER EVENT_ID_TYPE;
/*------------------------------*/
/* event state type */
/*------------------------------*/
enum EVENT_STATE_VALUE_TYPE { UP, DOWN };

typedef enum EVENT_STATE_VALUE_TYPE EVENT_STATE_TYPE;

/*------------------------------*/
/* event name type */
/*------------------------------*/
typedef NAME_TYPE EVENT_NAME_TYPE;
/*------------------------------*/
/* event status type            */
/*------------------------------*/
typedef struct {
   EVENT_STATE_TYPE     EVENT_STATE;
   WAITING_RANGE_TYPE   WAITING_PROCESSES;
} EVENT_STATUS_TYPE;

/*----------------------------------------------------------------------*/
/* */
/* event management services */
/* */
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
extern void CREATE_EVENT (
      /*IN */ EVENT_NAME_TYPE EVENT_NAME,
      /*OUT*/ EVENT_ID_TYPE *EVENT_ID,
      /*OUT*/ RETURN_CODE_TYPE *RETURN_CODE );
/*----------------------------------------------------------------------*/
extern void SET_EVENT (
      /*IN */ EVENT_ID_TYPE EVENT_ID,
      /*OUT*/ RETURN_CODE_TYPE *RETURN_CODE );
/*----------------------------------------------------------------------*/
extern void RESET_EVENT (
      /*IN */ EVENT_ID_TYPE EVENT_ID,
      /*OUT*/ RETURN_CODE_TYPE *RETURN_CODE );
/*----------------------------------------------------------------------*/
extern void WAIT_EVENT (
      /*IN */ EVENT_ID_TYPE EVENT_ID,
      /*IN */ SYSTEM_TIME_TYPE TIME_OUT,
      /*OUT*/ RETURN_CODE_TYPE *RETURN_CODE );
/*----------------------------------------------------------------------*/
extern void GET_EVENT_ID (
      /*IN */ EVENT_NAME_TYPE EVENT_NAME,
      /*OUT*/ EVENT_ID_TYPE *EVENT_ID,
      /*OUT*/ RETURN_CODE_TYPE *RETURN_CODE );
/*----------------------------------------------------------------------*/
extern void GET_EVENT_STATUS (
      /*IN */ EVENT_ID_TYPE EVENT_ID,
      /*OUT*/ EVENT_STATUS_TYPE *EVENT_STATUS ,
      /*OUT*/ RETURN_CODE_TYPE *RETURN_CODE );
/*----------------------------------------------------------------------*/
#endif
#endif
