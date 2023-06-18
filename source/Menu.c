/*
 * Menu.c
 *
 *  Created on: 2021��10��15��
 *      Author: awellfrog
 */

#include "Menu.h"

int8 aaa[20];
uint32 key;
uint32 Times;

_MOUSE *Mouse_pos = NULL;

uint32 selectItem_current, selectItem_hidden, selectItem;

/** �˵�Ŀ¼ */
_MENU MainMenu[MainMenu_NUM] = {
        {MainMenu_NUM, (int8 *)"nothing", {NULL, NULL, 0, 0}, NULL, NULL, MainMenu_F},
        {MainMenu_NUM, (int8 *)"happy", {NULL, NULL, 0, 0}, NULL, NULL, MainMenu_F},
        {MainMenu_NUM, (int8 *)"parameter", {NULL, NULL, 0, 0}, NULL, NULL, MainMenu_F},
        {MainMenu_NUM, (int8 *)"Gear", {NULL, NULL, 0, 0}, NULL, NULL, MainMenu_F},
        {MainMenu_NUM, (int8 *)"sub5", {NULL, NULL, 0, 0}, NULL, NULL, MainMenu_F},
        {MainMenu_NUM, (int8 *)"sub6", {NULL, NULL, 0, 0}, NULL, NULL, MainMenu_F},
        {MainMenu_NUM, (int8 *)"sub7", {NULL, NULL, 0, 0}, NULL, NULL, MainMenu_F},
        {MainMenu_NUM, (int8 *)"sub8", {NULL, NULL, 0, 0}, NULL, NULL, MainMenu_F},
        {MainMenu_NUM, (int8 *)"save", {NULL, NULL, 0, 0}, Save_para, NULL, MainMenu_F}
};

_MENU *MenuPoint = MainMenu;

_MENU Setmenu1[Setmenu1_NUM] = {
        {Setmenu1_NUM, (int8 *)"<back>", {NULL, NULL, 0, 0}, NULL, NULL, Setmenu1_F},
        {Setmenu1_NUM, (int8 *)"show_male", {NULL, NULL, 0, 0}, show_male, NULL, Setmenu1_F},
        {Setmenu1_NUM, (int8 *)"show_female", {NULL, NULL, 0, 0}, show_female, NULL, Setmenu1_F}
};

_MENU Setmenu2[Setmenu2_NUM] = {
        {Setmenu2_NUM, (int8 *)"<back>", {NULL, NULL, 0, 0}, NULL, NULL, Setmenu2_F},
        {Setmenu2_NUM, (int8 *)"init_num", {NULL, NULL, 0, 0}, NULL, NULL, Setmenu2_F},
        {Setmenu2_NUM, (int8 *)"show_tot", {NULL, NULL, 0, 0}, NULL, NULL, Setmenu2_F},
        {Setmenu2_NUM, (int8 *)"chg_len1", {"length1:%6.3f", &len1, float_T, 0}, trial, NULL, Setmenu2_F},
        {Setmenu2_NUM, (int8 *)"chg_len2", {"length2:%05d", &len2, uint32_T, 1}, tiral_uint32, NULL, Setmenu2_F},
        {Setmenu2_NUM, (int8 *)"chg_angle", {" angle :%6.3f", &angle, float_T, 2}, trial, NULL, Setmenu2_F}
};

_MENU Setmenu3[Setmenu3_NUM] = {
        {Setmenu3_NUM, (int8 *)"<back>", {NULL, NULL, 0, 0}, NULL, NULL, Setmenu3_F},
        {Setmenu3_NUM, (int8 *)"Gear_1", {NULL, NULL, gear_T, 0}, Gear_1_Para, NULL, Setmenu3_F},
        {Setmenu3_NUM, (int8 *)"Gear_2", {NULL, NULL, gear_T, 0}, Gear_2_Para, NULL, Setmenu3_F},
        {Setmenu3_NUM, (int8 *)"Gear_3", {NULL, NULL, gear_T, 0}, Gear_3_Para, NULL, Setmenu3_F},
};

_MENU Setmenu11[Setmenu11_NUM] = {
        {Setmenu11_NUM, (int8 *)"<back>", {NULL, NULL, 0, 0}, NULL, NULL, Setmenu11_F},
        {Setmenu11_NUM, (int8 *)"sonson2", {NULL, NULL, 0, 0}, fun1, NULL, Setmenu11_F}
};

/** �˵���ʼ���������ļ��м��ι�ϵ */
void Menu_Init() {
    /** ���ι�ϵ���� */
    MainMenu[1].Child_Menus = Setmenu1;
    MainMenu[2].Child_Menus = Setmenu2;
    MainMenu[3].Child_Menus = Setmenu3;
    Setmenu1[1].Child_Menus = Setmenu11;

    /** ������������ */
    selectItem_current = 1;
    selectItem_hidden = 0;
    selectItem = selectItem_current + selectItem_hidden;

}

void Run_Menus(uint32 key) {
    switch(key) {
        case BT_UP: { // ��
            if(selectItem_current > 1) selectItem_current--; // ����
            else if(selectItem_current == 1 && selectItem_hidden > 0) selectItem_hidden--; // ���Ϸ�ҳ
            else if(selectItem == 1) { // ��ת�����һ��
                if(MenuPoint->MenuCount >= SHOW_LINE) { // ��Ҫ��ҳ��Ŀ¼�ࣩ
                    selectItem_current = SHOW_LINE;
                    selectItem_hidden = (int32)(MenuPoint->MenuCount - SHOW_LINE);
                }
                else {
                    selectItem_current = MenuPoint->MenuCount % SHOW_LINE;
                }
            }
            selectItem = selectItem_current + selectItem_hidden;
        } break;
        case BT_OK: { // ok
            // ����п�ִ�к�������ִ��
            if(MenuPoint[selectItem - 1].Subs != NULL) {
                if(MenuPoint[selectItem - 1].Para_information.Parameter != NULL) {
                    if(MenuPoint[selectItem - 1].Para_information.Parameter_Type == float_T) {
                        MenuPoint[selectItem - 1].Subs(*(float *)MenuPoint[selectItem - 1].Para_information.Parameter, MenuPoint[selectItem - 1].Para_information.Para_Name_Output, MenuPoint[selectItem - 1].Para_information.Parameter); /*******���޸�*******/
                    }
                    else if(MenuPoint[selectItem - 1].Para_information.Parameter_Type == uint32_T){
                        MenuPoint[selectItem - 1].Subs(*(uint32 *)MenuPoint[selectItem - 1].Para_information.Parameter, MenuPoint[selectItem - 1].Para_information.Para_Name_Output, MenuPoint[selectItem - 1].Para_information.Parameter); /*******���޸�*******/
                    }
                }
                else MenuPoint[selectItem - 1].Subs();
            }
        } break;
        case BT_RIGHT: { // ��

            if(MenuPoint[selectItem-1].Para_information.Parameter != NULL) { // ���ٵ���
                if(MenuPoint[selectItem-1].Para_information.Parameter_Type == float_T)*(float *)MenuPoint[selectItem-1].Para_information.Parameter -= 0.1;
                else if(MenuPoint[selectItem-1].Para_information.Parameter_Type == uint32_T)*(uint32 *)MenuPoint[selectItem-1].Para_information.Parameter -= 1;
            }
            else if(MenuPoint[selectItem - 1].Child_Menus != NULL) {// ����Ӳ˵����յĻ�������
                // ����������һ�����λ��
                _MOUSE *new_node = (_MOUSE *) malloc (sizeof(_MOUSE));
                new_node->Cur_Select = selectItem_current;
                new_node->Hid_Select = selectItem_hidden;
                new_node->pre = Mouse_pos;
                Mouse_pos = new_node;

                // ����˵��µ���ʾλ��
                MenuPoint = MenuPoint[selectItem - 1].Child_Menus;
                selectItem_current = 1;
                selectItem_hidden = 0;
            }
            selectItem = selectItem_current + selectItem_hidden;
            if(MenuPoint == Setmenu3) SmartCar_OLED_P6x8Str(60, Current_Gear+1, " * ");
        } break;
        case BT_DOWN: { // ��
            if(selectItem_current < Get_Min(SHOW_LINE, MenuPoint->MenuCount)) selectItem_current++; // ����
            else if(selectItem_current == SHOW_LINE && selectItem < MenuPoint->MenuCount) selectItem_hidden++; // ��ҳ
            else if(selectItem == MenuPoint->MenuCount) { // ��Ŀ¼�����ת����һ��
                selectItem_current = 1;
                selectItem_hidden = 0;
            }
            selectItem = selectItem_current + selectItem_hidden;
        } break;
        case BT_LEFT: { // �� (back)
            if(MenuPoint[selectItem-1].Para_information.Parameter != NULL) { // ���ٵ���
                if(MenuPoint[selectItem-1].Para_information.Parameter_Type == float_T)*(float *)MenuPoint[selectItem-1].Para_information.Parameter += 0.1;
                else if(MenuPoint[selectItem-1].Para_information.Parameter_Type == uint32_T)*(uint32 *)MenuPoint[selectItem-1].Para_information.Parameter += 1;
            }
            else if(MenuPoint[selectItem - 1].Parent_Menus != NULL) {
                MenuPoint = MenuPoint[selectItem - 1].Parent_Menus;
                selectItem_current = Mouse_pos->Cur_Select;
                selectItem_hidden = Mouse_pos->Hid_Select;

                Mouse_pos = Mouse_pos->pre;
            }
            selectItem = selectItem_current + selectItem_hidden;
        } break;
    }
}



void Display(struct MenuItem * MenuPoint, uint32 selectItem_current, uint32 selectItem_hidden, uint32 selectItem) {
    uint32 j;
    uint8 x = 15;
    uint8 y = 1;
    SmartCar_OLED_Fill(0);
    SmartCar_OLED_Printf6x8(55, 0, "%d/%d", selectItem, MenuPoint->MenuCount);
    SmartCar_OLED_Printf6x8(90, 0, "[%d]", Times);
    for(j = selectItem_hidden; j < MenuPoint->MenuCount; j++) {
        if(selectItem > MenuPoint->MenuCount) break;
        if(j == selectItem - 1) SmartCar_OLED_P6x8Str(0, y, " > ");
        SmartCar_OLED_P6x8Str(x, y, MenuPoint[j].DisplayString);
        if(MenuPoint[j].Para_information.Parameter != NULL) {
            if(MenuPoint[j].Para_information.Parameter_Type == float_T){
                snprintf((int8 *) aaa, 8, "%6.3f", *(float *)MenuPoint[j].Para_information.Parameter);
                SmartCar_OLED_P6x8Str(80, y, (int8 *) aaa);
            }
            else if(MenuPoint[j].Para_information.Parameter_Type == uint32_T) {
                snprintf((int8 *) aaa, 8, " %05d", *(uint32 *)MenuPoint[j].Para_information.Parameter);
                SmartCar_OLED_P6x8Str(80, y, (int8 *) aaa);
            }
        }
        if(MenuPoint[j].Para_information.Parameter_Type == gear_T) SmartCar_OLED_P6x8Str(60, Current_Gear+1, "*");
        y += 1;
    }
}

void Save_para() {
    FIVEMENU_writeFlash();
}



