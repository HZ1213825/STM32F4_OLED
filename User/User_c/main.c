#include "stm32f4xx.h" // ע���������ļ���#define STM32F401xxΪ�Լ���оƬ�ͺ�
#include "Delay.h"
#include "OLED.h"

int main()
{
	OLED_Init();
	OLED_LineSegment(10, 30, 93, 63, 2);
	OLED_LineSegment(10, 30, 116, 30, 2);
	OLED_LineSegment(33, 63, 116, 30, 2);
	OLED_LineSegment(33, 63, 63, 0, 2);
	OLED_LineSegment(93, 63, 63, 0, 2);
	while (1)
	{
	}
}
