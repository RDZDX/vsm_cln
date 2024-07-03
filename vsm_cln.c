#include "vsm_cln.h"

VMINT		layer_hdl[1];
VMINT       mre_g_sm_hdl = -1;
VMBOOL first_step = VM_FALSE;

void vm_main(void)
{
	layer_hdl[0] = -1;	
	vm_reg_sysevt_callback(handle_sysevt);
	vm_reg_keyboard_callback(handle_keyevt);
}

void handle_sysevt(VMINT message, VMINT param) 
{
	switch (message)
	{
	case VM_MSG_CREATE:
		break;
	case VM_MSG_PAINT:
		layer_hdl[0] = vm_graphic_create_layer(0, 0, 
							vm_graphic_get_screen_width(),
							vm_graphic_get_screen_height(),
							-1);

		vm_graphic_set_clip(0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height());
		mre_draw_menu();
		break;
	case VM_MSG_HIDE:
	case VM_MSG_INACTIVE :
	case VM_MSG_QUIT:
		if( layer_hdl[0] != -1 )
		{
			vm_graphic_delete_layer(layer_hdl[0]);
			layer_hdl[0] = -1;
		}
		break;
	}
}

void handle_keyevt(VMINT event, VMINT keycode)
{
	if (event == VM_KEY_EVENT_UP)
	{
		switch (keycode)
		{
		case VM_KEY_NUM1:
                        first_step = VM_TRUE;
			mre_load_sm();   /* to load SM */
			break;
	    case VM_KEY_NUM2:
                        if (first_step != VM_TRUE){
                           mre_show_text("First step is nessesary !");
			   break;
                        }
			mre_get_fn_id(); /* to access one of SM function */
			break;
		case VM_KEY_RIGHT_SOFTKEY:
			if( layer_hdl[0] != -1 )
		    {
			vm_graphic_delete_layer(layer_hdl[0]);
			layer_hdl[0] = -1;
		    }
			vm_exit_app();
			break;
		default:
			break;
		}
	}
}


static void mre_draw_menu(void) 
{
	VMWCHAR display_menu_string[MRE_MAX_SIZE_STRING];
	VMUINT8 *buf;	
	int menu_string_pos_x, menu_string_pos_y;

	vm_log_debug("Entering %s","static void mre_draw_menu(void)");
	buf = vm_graphic_get_layer_buffer(layer_hdl[0]);			
	vm_graphic_fill_rect(buf, VM_SCREEN_START_X,
                         VM_SCREEN_START_X, vm_graphic_get_screen_width(), 
                         vm_graphic_get_screen_height(), VM_COLOR_WHITE,
                         VM_COLOR_BLACK);	
	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Menu :");
	menu_string_pos_x = MRE_STRING_PRINT_X; 
	menu_string_pos_y = MRE_STRING_PRINT_Y; 			
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);
	
	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Press-1 Load SM");
	menu_string_pos_x = MRE_STRING_PRINT_X; 
	menu_string_pos_y = MRE_STRING_PRINT_Y + MRE_MARGIN_BET_LINE; 			
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);
	
	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Press-2 Access SM");
	menu_string_pos_x = MRE_STRING_PRINT_X; 
	menu_string_pos_y = MRE_STRING_PRINT_Y + 2 * MRE_MARGIN_BET_LINE; 			
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);
	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Exit");
	menu_string_pos_x = vm_graphic_get_screen_width() - (3 * MRE_STRING_PRINT_X); 
	menu_string_pos_y = vm_graphic_get_screen_height() - (2 * MRE_STRING_PRINT_X); 			
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);
	vm_graphic_flush_layer(layer_hdl, MRE_SINGLE_LAYER);
}

void mre_show_text (VMSTR text)
{
	VMWCHAR str[MRE_STR_SIZE_MAX];
	VMUINT8 *buf;
	vm_gb2312_to_ucs2 (str, MRE_STR_SIZE_MAX, text);\
	buf = vm_graphic_get_layer_buffer (layer_hdl[0]);
	vm_graphic_fill_rect (buf, MRE_SET_MARGIN, vm_graphic_get_screen_height () / 2, vm_graphic_get_screen_width () -  (MRE_SET_MARGIN * 2),
        (vm_graphic_get_screen_height () / 2) - MRE_SET_MARGIN, VM_COLOR_WHITE, 0X0500);
  	vm_graphic_textout (buf, (MRE_SET_MARGIN * 2), vm_graphic_get_screen_height()/ 2+ MRE_SET_MARGIN, str, wstrlen (str), VM_COLOR_WHITE);
	vm_graphic_flush_layer (layer_hdl, 1);
}

void mre_load_sm(void) {

        VMCHAR fname[100];
        VMINT load_status = -2;

        create_app_new_path(fname, "vsm_srv.vsm");

	if ((load_status = vm_sm_load(fname)) < 0)
	{
		mre_show_text("unable to load SM");
	}
	else
	{
		mre_show_text("SM load successfully");
		mre_g_sm_hdl = load_status;
	}
}

void mre_get_fn_id(void)
{
	typedef void (*get_hello_string_t1)(VMSTR str, VMINT len);
	void (*get_hello_string_t)(VMSTR str, VMINT len);
	VMINT fn_en_addr = -1;
	VMSTR    str1 = NULL;

        get_hello_string_t = (get_hello_string_t1)vm_sm_get_func_entry(mre_g_sm_hdl, mre_id_get_hello_string);

	str1 = (VMSTR) vm_calloc((MRE_STR_LEN + 1) * sizeof(VMCHAR));
	(get_hello_string_t)(str1, MRE_STR_LEN);
	mre_show_text(str1);
	vm_sm_unload(mre_g_sm_hdl);
	if (str1)
	{
		vm_free(str1);
	}
}

void create_app_new_path(VMSTR text, VMSTR My_app) {

    VMWCHAR fullPath[100];
    VMWCHAR appName[100];
    VMCHAR fullPath1[100];

    vm_get_exec_filename(fullPath);
    vm_get_filename(fullPath, appName);
    vm_ucs2_to_ascii(fullPath1, wstrlen(fullPath) + 1, fullPath);
    strncpy(text, fullPath1, vm_wstrlen(fullPath) - wstrlen(appName));
    strcat(text, My_app);
}