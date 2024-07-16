#include "vsm_cln.h"

VMINT layer_hdl[1];
VMINT mre_g_sm_hdl = -1;
VMBOOL first_step = VM_FALSE;
VMWCHAR editor_title[36];
int filledDsplByLines = 165;
VMCHAR ascii_data[21];
VMUINT8 *buf;

void vm_main(void)
{
	layer_hdl[0] = -1;	
	vm_reg_sysevt_callback(handle_sysevt);
	vm_reg_keyboard_callback(handle_keyevt);
        vm_ascii_to_ucs2(editor_title, 36, "Input expression:");
        vm_input_set_editor_title(editor_title);
}

void handle_sysevt(VMINT message, VMINT param) 
{
	switch (message)
	{
	case VM_MSG_CREATE:
		break;
	case VM_MSG_PAINT:
                vm_switch_power_saving_mode(turn_off_mode);
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
                if (mre_g_sm_hdl > -1) {vm_sm_unload(mre_g_sm_hdl);}
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
                           vertical_scrolling_text("First step is nessesary !");
			   break;
                        }
                        mre_get_fn_id(id_get_hello_string);
			break;
		case VM_KEY_NUM3:
                        if (first_step != VM_TRUE){
                           vertical_scrolling_text("First step is nessesary !");
			   break;
                        }
                        mre_get_fn_id(id_get_hello_string2);
			break;
		case VM_KEY_NUM4:
                        if (first_step != VM_TRUE){
                           vertical_scrolling_text("First step is nessesary !");
			   break;
                        }
                        mre_get_fn_id(id_get_hello_string3);
			break;
		case VM_KEY_NUM5:
                        if (first_step != VM_TRUE){
                           vertical_scrolling_text("First step is nessesary !");
			   break;
                        }
                        vm_input_text3(NULL, 21, 4, save_input);
			break;
		case VM_KEY_RIGHT_SOFTKEY:
                        if (mre_g_sm_hdl > -1) {vm_sm_unload(mre_g_sm_hdl);}
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
	int menu_string_pos_x, menu_string_pos_y;

	buf = vm_graphic_get_layer_buffer(layer_hdl[0]);			
	vm_graphic_fill_rect(buf, VM_SCREEN_START_X, VM_SCREEN_START_X, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_COLOR_WHITE, VM_COLOR_BLACK);	
	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Menu :");
	menu_string_pos_x = MRE_STRING_PRINT_X - 5; 
	menu_string_pos_y = MRE_STRING_PRINT_Y;	
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);
	
	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Press-1 Load SM");
	menu_string_pos_y = MRE_STRING_PRINT_Y + MRE_MARGIN_BET_LINE;	
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);
	
	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Press-2 Run function 1");
	menu_string_pos_y = MRE_STRING_PRINT_Y + 2 * MRE_MARGIN_BET_LINE;
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);

	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Press-3 Run function 2");
	menu_string_pos_y = MRE_STRING_PRINT_Y + 3 * MRE_MARGIN_BET_LINE; 			
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);

	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Press-4 Run function 3");
	menu_string_pos_y = MRE_STRING_PRINT_Y + 4 * MRE_MARGIN_BET_LINE; 			
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);

	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Press-5 Input expression");
	menu_string_pos_y = MRE_STRING_PRINT_Y + 5 * MRE_MARGIN_BET_LINE; 			
	vm_graphic_textout(buf,	menu_string_pos_x, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);

	vm_gb2312_to_ucs2(display_menu_string, MRE_MAX_SIZE_STRING, "Exit");
	menu_string_pos_x = vm_graphic_get_screen_width() - (3 * MRE_STRING_PRINT_X); 
	menu_string_pos_y = vm_graphic_get_screen_height() - (2 * MRE_STRING_PRINT_X); 			
	vm_graphic_textout(buf,	menu_string_pos_x - 8, menu_string_pos_y, display_menu_string, wstrlen(display_menu_string), VM_COLOR_WHITE);
	vm_graphic_flush_layer(layer_hdl, MRE_SINGLE_LAYER);
}

void mre_load_sm(void) {

        VMCHAR fname[100];
        VMINT load_status = -2;

        //sm_hdl = vm_sm_load("vsm_srv"); //put "vsm_srv.vsm" to "Memory card\MRE\" = homedir

        if (mre_g_sm_hdl > -1) {vm_sm_unload(mre_g_sm_hdl);}

        create_app_new_path(fname, "vsm_srv.vsm");

	if ((load_status = vm_sm_load(fname)) < 0)
	{
                first_step = VM_FALSE;
		vertical_scrolling_text("Unable to load SM");
	}
	else
	{
		vertical_scrolling_text("SM load successfully");
		mre_g_sm_hdl = load_status;
	}
}

void mre_load_sm1(void) {

        VMCHAR fname[100];
        VMINT load_status = -2;

        //sm_hdl = vm_sm_load("vsm_srv"); //put "vsm_srv.vsm" to "Memory card\MRE\" = homedir

        if (mre_g_sm_hdl > -1) {vm_sm_unload(mre_g_sm_hdl);}

        create_app_new_path(fname, "vsm_srv.vsm");

	if ((load_status = vm_sm_load(fname)) < 0)
	{
                first_step = VM_FALSE;
		//vertical_scrolling_text("Unable to load SM");
	}
	else
	{
		//vertical_scrolling_text("SM load successfully");
		mre_g_sm_hdl = load_status;
	}
}

void mre_get_fn_id(VMINT myFunc) {

        get_hello_string_t func_ptr = NULL;
	VMSTR str1 = NULL;

        func_ptr = (get_hello_string_t)vm_sm_get_func_entry(mre_g_sm_hdl, myFunc);
	str1 = (VMSTR)vm_calloc((MRE_STR_LEN + 1) * sizeof(VMCHAR));
        func_ptr(str1, MRE_STR_LEN);
	vertical_scrolling_text(str1);
	if (str1){ vm_free(str1); }
}

void mre_get_fn_id1(VMINT myFunc) {

        get_hello_string_t1 func_ptr = NULL;
	VMSTR str1 = NULL;

        func_ptr = (get_hello_string_t1)vm_sm_get_func_entry(mre_g_sm_hdl, myFunc);
	str1 = (VMSTR)vm_calloc((MRE_STR_LEN + 1) * sizeof(VMCHAR));
        func_ptr(str1, MRE_STR_LEN, ascii_data);
	vertical_scrolling_text(str1);
	if (str1){ vm_free(str1); }
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

void save_input(VMINT state, VMWSTR text) {

    VMINT lenght;

    lenght = vm_wstrlen(text);
    mre_draw_black_rectangle();
    mre_load_sm1();

    if (state == VM_INPUT_OK && lenght > 0) {
       vm_ucs2_to_ascii(ascii_data, lenght + 1, text);
       mre_get_fn_id1(id_get_hello_string4);
    } else { vertical_scrolling_text("No expression data!"); }
}

void vertical_scrolling_text(VMSTR text_string) {
    int max_height;
    int font_height = 20;
    int font_baseline = 12;
    int abc = 0;
    VMWCHAR str[MRE_STR_SIZE_MAX];

    //font_height = vm_graphic_get_character_height();

    vm_gb2312_to_ucs2 (str, MRE_STR_SIZE_MAX, text_string);

    //font_baseline = vm_graphic_get_string_baseline(str);

    buf = vm_graphic_get_layer_buffer (layer_hdl[0]);

    max_height = vm_graphic_get_screen_height();

    if (filledDsplByLines > max_height || filledDsplByLines == 165) {
        abc = 1;
        mre_draw_black_rectangle();
    }

    vm_graphic_clear_layer_bg(layer_hdl[0]);

    vm_graphic_textout_by_baseline(buf, (MRE_SET_MARGIN * 2) + 3, filledDsplByLines + abc, str, vm_wstrlen(str), VM_COLOR_WHITE, font_baseline);
    vm_graphic_flush_layer(layer_hdl, 1);
    filledDsplByLines += font_height;
}

void mre_draw_black_rectangle(void){

    filledDsplByLines = 165;
    buf = vm_graphic_get_layer_buffer (layer_hdl[0]);
    vm_graphic_fill_rect (buf, MRE_SET_MARGIN, vm_graphic_get_screen_height () / 2, vm_graphic_get_screen_width () -  (MRE_SET_MARGIN * 2), (vm_graphic_get_screen_height () / 2) - MRE_SET_MARGIN, VM_COLOR_WHITE, 0X0500); //0X0500
    vm_graphic_flush_layer (layer_hdl, 1);
}