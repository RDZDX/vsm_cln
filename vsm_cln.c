#include "vsm_cln.h"

VMCHAR s[50];

void vm_main(void) {

	layer_hdl[0] = -1;	
	vm_reg_sysevt_callback(handle_sysevt);
	vm_reg_keyboard_callback(handle_keyevt);
}

void handle_sysevt(VMINT message, VMINT param) {
#ifdef		SUPPORT_BG	
	switch (message) {
	case VM_MSG_CREATE:
		break;
	case VM_MSG_PAINT:
		layer_hdl[0] = vm_graphic_create_layer(0, 0, 
			vm_graphic_get_screen_width(),
			vm_graphic_get_screen_height(),
			-1);
		vm_graphic_set_clip(0, 0, 
			vm_graphic_get_screen_width(), 
			vm_graphic_get_screen_height());
		
                test_sm();
                draw_hello();
		break;
	case VM_MSG_HIDE:	
		if( layer_hdl[0] != -1 )
		{
			vm_graphic_delete_layer(layer_hdl[0]);
			layer_hdl[0] = -1;
		}
		break;
	case VM_MSG_QUIT:
		if( layer_hdl[0] != -1 )
		{
			vm_graphic_delete_layer(layer_hdl[0]);
			layer_hdl[0] = -1;
		}
		break;
	}
#else
	switch (message) {
	case VM_MSG_CREATE:
	case VM_MSG_ACTIVE:
		layer_hdl[0] = vm_graphic_create_layer(0, 0, 
			vm_graphic_get_screen_width(),
			vm_graphic_get_screen_height(),
			-1);
		vm_graphic_set_clip(0, 0, 
			vm_graphic_get_screen_width(), 
			vm_graphic_get_screen_height());
		break;
		
	case VM_MSG_PAINT:
                test_sm();
                draw_hello();
		break;
		
	case VM_MSG_INACTIVE:
		if( layer_hdl[0] != -1 )
			vm_graphic_delete_layer(layer_hdl[0]);
		
		break;	
	case VM_MSG_QUIT:
		if( layer_hdl[0] != -1 )
			vm_graphic_delete_layer(layer_hdl[0]);
		break;	
	}
#endif
}

void handle_keyevt(VMINT event, VMINT keycode) {
    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_OK) {
       test_sm();
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT_SOFTKEY) {
       //vm_vibrator_once();
       draw_hello();
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM1) {
       strcpy(s, "Test");
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM2) {
       strcpy(s, "");
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT_SOFTKEY) {
        if (layer_hdl[0] != -1) {
            vm_graphic_delete_layer(layer_hdl[0]);
            layer_hdl[0] = -1;
        }
        vm_exit_app();
    }
}

static void draw_hello(void) {

        VMWCHAR s1[100];
	int x, y, wstr_len;
	vm_graphic_color color;

        vm_ascii_to_ucs2(s1, (strlen(s) + 1) * 2, s);
	wstr_len = vm_graphic_get_string_width(s1);
	x = (vm_graphic_get_screen_width() - wstr_len) / 2;
	y = (vm_graphic_get_screen_height() - vm_graphic_get_character_height()) / 2;
	color.vm_color_565 = VM_COLOR_WHITE;
	vm_graphic_setcolor(&color);
	vm_graphic_fill_rect_ex(layer_hdl[0], 0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height());
	color.vm_color_565 = VM_COLOR_BLUE;
	vm_graphic_setcolor(&color);
	vm_graphic_textout_to_layer(layer_hdl[0],x, y, s1, wstr_len);
	vm_graphic_flush_layer(layer_hdl, 1);
}

void test_sm(void) {

    VMINT sm_hdl = -1;
    func_t func_ptr = NULL;
    VMCHAR smx[50];
 
    strcpy(s, "");

    sm_hdl = vm_sm_load("vsm_srv");
 
    if(sm_hdl < VM_SM_SUCCESS)
    {
         //vm_log_error("sm load error");
         vm_vibrator_once();
         sprintf(s, "%d", sm_hdl);
         return;
    }

    func_ptr = (func_t)vm_sm_get_func_entry(sm_hdl, 1);

    if(func_ptr == NULL)
    {
        //vm_log_error("get symbol error");
        vm_vibrator_once();
        return;
    }
    //func_ptr(s, 50);
    vm_sm_unload(sm_hdl);
}