/*
 * Function.h
 *
 *  Created on: 2021��10��15��
 *      Author: awellfrog
 */

#ifndef SOURCE_FUNCTION_H_
#define SOURCE_FUNCTION_H_


#include "SmartCar_GPIO.h"
#include "Menu.h"
#include "stdio.h"

/** ��ȡ������Ĳ���
 * ���� key ������� ���ϡ� ���¡� ��ok�� ���� ���ҡ�
 * */
uint32 Get_Operation();

/** ���� a, b �е���Сֵ */
uint32 Get_Min(uint32 a, uint32 b);

/** ͼ����ʾ���� */
void show_male();
void show_female();
void fun1();

/** ��λѡ�� */
void Gear_1_Para();
void Gear_2_Para();
void Gear_3_Para();


/** �����޸� ******************************************************************************/
/** float���޸� */
void trial(float num, int8 output_format[], float *P);
/** uint32���޸� */
void tiral_uint32(uint32 num, int8 output_format[], uint32 *P);

/** float���͵��޸�
 * ��Ҫ�����������
 * ��Ҫ���������ʽ
 * */
float Resize_Number_Float(float num, uint32 len_size, uint32 len_after_point, int8 output_format[]);

/** Uint32���͵��޸�
 * ��Ҫ�����������
 * ��Ҫ���������ʽ
 * */
uint32 Resize_Number_Uint32(uint32 num, uint32 len_size, int8 output_format[]);
/* -------------------------------------------------------------------------------------*/



/****** Flash ****************************************************************************/
/** д��Flash */
void FIVEMENU_writeFlash(void);

/** ����Flash */
/** ������λ�Ĳ����ֱ����1 2 3������ */
void FIVEMENU_readFlash(void);

/** ���浵λ��Flash */
void Save_Gear(void);



#endif /* SOURCE_FUNCTION_H_ */
