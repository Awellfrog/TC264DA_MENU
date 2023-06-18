/*
 * Function.c
 *
 *  Created on: 2021��10��15��
 *      Author: awellfrog
 */


#include "Function.h"

uint32 Get_Operation() {
    uint32 key;

    if (!GPIO_Read(P13, 2) || !GPIO_Read(P11, 6) || !GPIO_Read(P13,3) || !GPIO_Read(P11, 2) || !GPIO_Read(P11, 3) ) {
                if(!GPIO_Read(P13, 2))      key = 1; // ��
                else if(!GPIO_Read(P11, 6)) key = 2; // ok
                else if(!GPIO_Read(P13,3))  key = 3; // ��
                else if(!GPIO_Read(P11, 2)) key = 5; // ��
                else if(!GPIO_Read(P11, 3)) key = 4; // ��
    }
    else key = 0; // û����ť
    Delay_ms(STM0, 100);
    return key;
}

uint32 Get_Min(uint32 a, uint32 b) {
    return a>b?b:a;
}

void fun1() {
    SmartCar_OLED_P6x8Str(50, 5, "func3");
    Delay_ms(STM0, 1000);
}

/** ��λѡ�� */
void Gear_1_Para() {
    FIVEMENU_readFlash();
    Current_Gear = 1;
    Save_Gear();
}

void Gear_2_Para() {
    FIVEMENU_readFlash();
    Current_Gear = 2;
    Save_Gear();
}

void Gear_3_Para() {
    FIVEMENU_readFlash();
    Current_Gear = 3;
    Save_Gear();
}

void show_male() {
    SmartCar_OLED_P6x8Str(5, 0, "................");
    SmartCar_OLED_P6x8Str(5, 1, "...***....***...");
    SmartCar_OLED_P6x8Str(5, 2, "..*...*..*...*..");
    SmartCar_OLED_P6x8Str(5, 3, "................");
    SmartCar_OLED_P6x8Str(5, 4, "..*..........*..");
    SmartCar_OLED_P6x8Str(5, 5, "..*..........*..");
    SmartCar_OLED_P6x8Str(5, 6, "..**.*.*.*.*.*..");
    SmartCar_OLED_P6x8Str(5, 7, "................");
    Delay_ms(STM0, 1000);
}

void show_female() {
    SmartCar_OLED_P6x8Str(0, 0, "................");
    SmartCar_OLED_P6x8Str(0, 1, "................");
    SmartCar_OLED_P6x8Str(0, 2, "................");
    SmartCar_OLED_P6x8Str(0, 3, "................");
    SmartCar_OLED_P6x8Str(0, 4, "................");
    SmartCar_OLED_P6x8Str(0, 5, "................");
    SmartCar_OLED_P6x8Str(0, 6, "................");
    SmartCar_OLED_P6x8Str(0, 7, "................");
    Delay_ms(STM0, 1000);
}


/** �޸Ĳ���
 * ��Ҫ����һЩ�޸����ƵĲ���
 * �����ӡ��ʽ
 * */
void trial(float num, int8 output_format[], float *P) {
//    float num = reMyData.length1;               // ������Ҫ�޸ĵĲ���
    uint32 len_size = 5;                        // �ܵĿ��޸���λ
    uint32 len_after_point = 3;                 // С������м�λ
//    int8 output_format[] = "length1:%6.3f";      // ������ӡ��ʽ
    *P = Resize_Number_Float(num, len_size, len_after_point, output_format);
}

/** float���͵��޸� */
float Resize_Number_Float(float num, uint32 len_size, uint32 len_after_point, int8 output_format[]) {                            // �޸Ĳ��� len1
    snprintf((int8 *) aaa, 20, output_format, (float)num);
    SmartCar_OLED_Fill(0);
    SmartCar_OLED_P6x8Str(20, 2, (int8 *)aaa);
    uint32 len[len_size], pos = 0;                 // len[0] ��λ�� len[1] С�����һλ,�� len[2] С�����2λ
    uint32 wei = 1;                                // ת��Ϊ����
    float rewei = 1.0;                             // ת����С�������ڴ洢��
    uint32 current_num;
    uint32 time = 0;
    /** ȡ����λ���� */
    for(int i = 0; i < len_after_point; i++) wei *= 10, rewei *= 0.1;
    current_num = num * wei;
    for(int i = 0; i < len_size; i++) {
        len[i] = current_num % 10;
        current_num /= 10;
    }

    while(1) {

        key = Get_Operation();
        Delay_ms(STM0, 50);
        if(key != 0) {
            if(key == BT_UP) {
                if(len[pos] < 9) len[pos]++;
                else if(len[pos] == 9) {
                    len[pos] = 0;
                    if(pos != len_size-1) len[pos+1]++;
                }
            }
            else if(key == BT_DOWN) {
                if(len[pos] > 0) len[pos]--;
                else if(len[pos] == 0) {
                    len[pos] = 9;
                    if(pos != len_size-1)len[pos+1]--;
                }
                else if(pos == len_size-1) len[pos] = 0;
            }
            else if(key == BT_LEFT) {
                if(pos < len_size - 1) pos++;
            }
            else if(key == BT_RIGHT) {
                if(pos > 0) pos--;
            }
            else if(key == BT_OK) {
                float ans = (float)(current_num*rewei);
                return ans;
            }
        }
        /** ��дһ�� dispaly */
        time++;
        current_num = 0;
        for(int i = len_size - 1; i >= 0; i--) {
            current_num*= 10;
            current_num += len[i];
        }
        if(current_num > 99999) current_num = 0;
        float temp_num = (float)current_num;
        temp_num *= rewei; // ת��ΪС��
        snprintf((int8 *) aaa, 20, output_format, temp_num);
        SmartCar_OLED_P6x8Str(20, 4, (int8 *)aaa);
        SmartCar_OLED_P6x8Str(0, 6, "                        ");
        if(time < 3) {
            if(pos < 3) SmartCar_OLED_P6x8Str(56+12+(len_size-1-pos)*6, 6, " ^ ");
            else SmartCar_OLED_P6x8Str(56+6+(len_size-1-pos)*6, 6, " ^ ");
        }
        else if(time < 6) {

        }
        else time = 0;

    }
}

void tiral_uint32(uint32 num, int8 output_format[], uint32 *P) {
//    uint32 num = reMyData.length2;// ��Ҫ�޸ĵĲ���
    uint32 len_size = 5;// �ܵĿ��޸���λ
//    int8 output_format[] = "length2:%05d"; // ������ӡ��ʽ, ע�ⳤ�Ȼ�Ӱ���ӡ���
    *P = Resize_Number_Uint32(num, len_size, output_format);
}

/** uint32���͵��޸� */
uint32 Resize_Number_Uint32(uint32 num, uint32 len_size, int8 output_format[]) {                            // �޸Ĳ��� len1
    snprintf((int8 *) aaa, 20, output_format, (uint32)num);
    SmartCar_OLED_Fill(0);
    SmartCar_OLED_P6x8Str(20, 2, (int8 *)aaa);
    uint32 len[len_size], pos = 0;             // len[0]���λ��һ�εݽ�
    uint32 current_num = num;
    uint32 time = 0;
    /** ȡ����λ���� */
    for(int i = 0; i < len_size; i++) {
        len[i] = current_num % 10;
        current_num /= 10;
    }

    while(1) {
        key = Get_Operation();
        Delay_ms(STM0, 50);
        if(key != 0) {
            if(key == BT_UP) {
                if(len[pos] < 9) len[pos]++;
                else if(len[pos] == 9) {
                    len[pos] = 0;
                    if(pos != len_size-1) len[pos+1]++;
                }
            }
            else if(key == BT_DOWN) {
                if(len[pos] > 0) len[pos]--;
                else if(len[pos] == 0) {
                    len[pos] = 9;
                    if(pos != len_size-1)len[pos+1]--;
                }
                else if(pos == len_size-1) len[pos] = 0;
            }
            else if(key == BT_LEFT) {
                if(pos < len_size - 1) pos++;
            }
            else if(key == BT_RIGHT) {
                if(pos > 0) pos--;
            }
            else if(key == BT_OK) {
                uint32 ans = current_num;
                return ans;
            }
        }
        /** ��дһ�� dispaly */
        time++;
        current_num = 0;
        for(int i = len_size - 1; i >= 0; i--) {
            current_num*= 10;
            current_num += len[i];
        }
        if(current_num > 99999) current_num = 0;
        snprintf((int8 *) aaa, 20, output_format, current_num);
        SmartCar_OLED_P6x8Str(0, 6, "                        ");
        SmartCar_OLED_P6x8Str(20, 4, (int8 *)aaa);
        if(time < 3) {
            SmartCar_OLED_P6x8Str(56+6+(len_size-1-pos)*6, 6, " ^ ");
        }
        else if(time < 6) {

        }
        else time = 0;
    }
}

/***********Flash**********************************************************/

/** Flash��ȡ */
void FIVEMENU_readFlash(void) {
    uint32 cnt = 0;
    _MENU *SavePoint = MainMenu;
    for(int i = 0; i < MainMenu_NUM; i++) {
        if(SavePoint[i].Child_Menus != NULL) {
            _MENU *Save_Num_Point = SavePoint[i].Child_Menus;
            uint32 tot = Save_Num_Point->MenuCount;
            for(int j = 0; j < tot; j++) {
                if(Save_Num_Point[j].Para_information.Parameter != NULL) {
                    if(Save_Num_Point[j].Para_information.Parameter_Type == float_T) {
                        /** Flash���������� */
                        *(float *)Save_Num_Point[j].Para_information.Parameter = Page_Read(Current_Gear, cnt+Save_Num_Point[j].Para_information.Save_order, float);
                    }
                    else if(Save_Num_Point[j].Para_information.Parameter_Type == uint32_T){
                        *(uint32 *)Save_Num_Point[j].Para_information.Parameter = Page_Read(Current_Gear, cnt+Save_Num_Point[j].Para_information.Save_order, uint32);
                    }
                }
            }
            cnt = i * 100;
        }
    }
}

/** Flashд�� */
void FIVEMENU_writeFlash(void)
{
    uint32 buff[1024] = { 0 };
    uint32 cnt = 0;
    _MENU *SavePoint = MainMenu;
    for(int i = 0; i < MainMenu_NUM; i++) {
        if(SavePoint[i].Child_Menus != NULL) {
            _MENU *Save_Num_Point = SavePoint[i].Child_Menus;
            uint32 tot = Save_Num_Point->MenuCount;
            for(int j = 0; j < tot; j++) {
                if(Save_Num_Point[j].Para_information.Parameter != NULL) {
                    if(Save_Num_Point[j].Para_information.Parameter_Type == float_T) {
                        memcpy(buff+cnt+Save_Num_Point[j].Para_information.Save_order, Save_Num_Point[j].Para_information.Parameter, sizeof(float));
                    }
                    else if(Save_Num_Point[j].Para_information.Parameter_Type == uint32_T){
                        memcpy(buff+cnt+Save_Num_Point[j].Para_information.Save_order, Save_Num_Point[j].Para_information.Parameter, sizeof(uint32));
                    }
                }
            }
            cnt = i * 100; // ÿ�������� 100 ��ҳ�д洢(��Ҫ��ÿһ����Ŀ¼�µĲ������ܳ���100��)
        }
    }
    Sector_Erase(Current_Gear);            //�Ȳ���
    Sector_Program(Current_Gear, buff);   //��buff�е����ݴ���1��������ע��buffΪָ��
}

/** Flash ��¼Gear */
void Save_Gear(void) {
    uint32 buff_Gear[1024] = {Current_Gear, 0}; // 0����0ҳ�洢ģʽ״̬
    Sector_Erase(0);
    Page_Program(0, 0, buff_Gear);
}
/*-----------------------------------------------------------*/

