#ifndef _VRE_APP_WIZARDTEMPLATE_
#define	_VRE_APP_WIZARDTEMPLATE_


#include "vmsys.h"
#include "vmio.h"
#include "vmgraph.h"
#include "vmchset.h"
#include "vmstdlib.h"
#include "vmlog.h"
#include "vmsm.h"
#include "stdio.h"
#include "string.h"


#define MRE_STR_SIZE_MAX      (100)
#define MRE_SET_MARGIN        (0)
#define MRE_MAX_SIZE_STRING	  (50)
#define MRE_STRING_PRINT_X	  (10)
#define MRE_STRING_PRINT_Y	  (10)
#define VM_SCREEN_START_X	  (0)
#define VM_SCREEN_START_Y     (0)
#define MRE_MARGIN_BET_LINE   (20)
#define MRE_SINGLE_LAYER	  (1)
#define MRE_STR_LEN			  (14) 

enum 
{
    mre_id_get_hello_string = 1
};

void handle_sysevt(VMINT message, VMINT param);
void handle_keyevt(VMINT event, VMINT keycode);
static void mre_draw_menu(void);
void mre_load_sm(void);
void mre_show_text (VMSTR text);
void mre_get_fn_id(void);

#endif

