#ifndef _VRE_APP_WIZARDTEMPLATE_
#define	_VRE_APP_WIZARDTEMPLATE_

#include "vmsys.h"
#include "vmio.h"
#include "vmgraph.h"
#include "vmchset.h"
#include "vmstdlib.h"
#include "ResID.h"
#include "vm4res.h"
#include "string.h"
#include "vmsm.h"
#include "vmmm.h"

#define		SUPPORT_BG		

VMINT		layer_hdl[1];	/* layer handle array. */

typedef void (*func_t)(VMSTR str, VMINT len);

void handle_sysevt(VMINT message, VMINT param);
void handle_keyevt(VMINT event, VMINT keycode);
static void draw_hello(void);
void test_sm(void);

#endif