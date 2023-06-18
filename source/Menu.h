/*
 * Menu.h
 *
 *  Created on: 2021��10��15��
 *      Author: awellfrog
 */

#ifndef SOURCE_MENU_H_
#define SOURCE_MENU_H_


#include "Param.h"
#include "Function.h"
#include "SmartCar_Oled.h"
#include "SmartCar_Systick.h"
#include <stdlib.h>
#include "SmartCar_Flash.h"
#include "SmartCar_GPIO.h"

/** Flash ��ȡ����"SmartCar_Flash.h"�ж����ˣ�������Ӳ��ϣ�������Ķ����ע�ͼ���  */
//#define Page_Read(sector_num,page_num,type) (*(type *)((uint32)((EEPROM_BASE_ADDR + (sector_num)*EEPROM_SECTOR_SIZE)+ ((page_num)*8))))

extern uint32 Current_Gear; // ��ǰģʽ

/** ��������� */
#define BT_UP       1
#define BT_OK       2
#define BT_RIGHT    3
#define BT_DOWN     4
#define BT_LEFT     5

#define SHOW_LINE   7                   // ��Ļ��ʾ��������ȥ����һ�㣩

extern int8 aaa[20];                    // ���ڽ���ͬ��������תΪ int8 ����ʾ
extern uint32 key;                      // ������ȡ
extern uint32 Times;

/** ������ʾ���λ�� */
extern uint32 selectItem_current, selectItem_hidden, selectItem;
      /* ��ǰ�ڵڼ���              ǰ�����ص�����    ����ڵ�ǰĿ¼��λ��*/

/******��������***************************************************************************/

/***��������******/
enum Parameter_Type {
    uint32_T = 1, float_T = 2, gear_T = 4
};


/** ������Ϣ���� */
typedef struct Para {
        int8 *Para_Name_Output; // ��������
        void *Parameter;        // ��ǰ����ֵ
        uint32 Parameter_Type;  // ��Ҫ�޸ĵĲ������� 0 -> int8  1->uint32  2->float
        uint32 Save_order;      // ɾ��һ��������Ȼ�����ȡ����
} _Para;

/** �˵�Ŀ¼ */
typedef struct MenuItem {
        uint32 MenuCount;               // ��ǰ�˵�������
        int8 *DisplayString;            // ��ǰ��ĿҪ��ʾ���ַ�
        _Para Para_information;
        void(*Subs) ();                 // ѡ��ĳһ�˵���ִ�еĹ��ܺ���
        struct MenuItem *Child_Menus;   // ��ǰ��Ŀ���Ӳ˵�
        struct MenuItem *Parent_Menus;  // ��ǰ��Ŀ�ĸ��˵�
} _MENU;

extern _MENU *MenuPoint;                // ��ǰ�˵��ĵ�ַ

/** ���˵�����
 * MainMenu_NUM                         ���˵���ѡ����
 * MainMenu_F                           ���˵�����һ��Ŀ¼
 * MainMenu[MainMenu_NUM]               ������˵�ѡ�������
 * */

// ���һ���Ӳ˵�����Ҫ�޸�һ��Ŀ¼����Para�ĵ��м�����������һ�в˵�

#define MainMenu_NUM 9                  // Ŀ¼������
#define MainMenu_F NULL                 // ָ����һ����ָ��
extern _MENU MainMenu[MainMenu_NUM];

#define Setmenu1_NUM 3
#define Setmenu1_F MainMenu
extern _MENU Setmenu1[Setmenu1_NUM];

#define Setmenu2_NUM 6
#define Setmenu2_F MainMenu
extern _MENU Setmenu2[Setmenu2_NUM];

#define Setmenu3_NUM 4
#define Setmenu3_F MainMenu
extern _MENU Setmenu3[Setmenu3_NUM];

#define Setmenu11_NUM 2
#define Setmenu11_F Setmenu1
extern _MENU Setmenu11[Setmenu11_NUM];


/** ���ڴ洢�����Ϣ */
typedef struct Mouse{
        struct Mouse *pre;
        uint32 Cur_Select;
        uint32 Hid_Select;
} _MOUSE;

extern _MOUSE *Mouse_pos;

/** �˵���ʼ���������ļ��м��ι�ϵ */
void Menu_Init();

/** ������������Ʋ˵�ѡ��ʵ���˹�����ҳ
 * key ����İ�������
 * */
void Run_Menus(uint32 key);

/** ��ʾ�˵��͹��λ��
 * MenuPoint                            ��ǰ�˵���ָ���ַ
 * selectItem_current                   ��ǰ�������Ļ�ĵڼ���
 * selectItem_hidden                    �˵��м��б���������Ļ�Ϸ�
 * selectItem                           Ŀǰ����ڵ�ǰ�˵��ĵڼ���
 * */
void Display(_MENU * MenuPoint, uint32 selectItem_current, uint32 selectItem_hidden, uint32 selectItem);

/** Flashд�루���棩 */
void Save_para();


#endif /* SOURCE_MENU_H_ */
