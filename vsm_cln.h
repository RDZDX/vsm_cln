#ifndef _VRE_APP_WIZARDTEMPLATE_
#define	_VRE_APP_WIZARDTEMPLATE_

#include "vmsys.h"
#include "vmio.h"
#include "vmgraph.h"
#include "vmchset.h"
#include "vmstdlib.h"
#include "vmsm.h"
#include "stdio.h"
#include "string.h"

#define MRE_STR_SIZE_MAX	(100)
#define MRE_SET_MARGIN		(0)
#define MRE_MAX_SIZE_STRING	(50)
#define MRE_STRING_PRINT_X	(10)
#define MRE_STRING_PRINT_Y	(10)
#define VM_SCREEN_START_X	(0)
#define VM_SCREEN_START_Y	(0)
#define MRE_MARGIN_BET_LINE	(20)
#define MRE_SINGLE_LAYER	(1)
#define MRE_STR_LEN		(21) //14

enum {
    id_get_hello_string = 1,
    id_get_hello_string2 = 2,
    id_get_hello_string3 = 3,
    id_get_hello_string4 = 4
};

void handle_sysevt(VMINT message, VMINT param);
void handle_keyevt(VMINT event, VMINT keycode);
static void mre_draw_menu(void);
void mre_load_sm(void);
void mre_load_sm1(void);
void mre_get_fn_id(VMINT myFunc);
void mre_get_fn_id1(VMINT myFunc);
void create_app_new_path(VMSTR text, VMSTR My_app);
void save_input(VMINT state, VMWSTR text);
void vertical_scrolling_text(VMSTR text_string);
void mre_draw_black_rectangle(void);

typedef void (*get_hello_string_t)(VMSTR str, VMINT len);
typedef void (*get_hello_string_t1)(VMSTR str, VMINT len, VMSTR input_data);

#endif

