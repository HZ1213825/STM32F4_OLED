#include "stm32f4xx.h" // 注意更改这个文件的#define STM32F401xx为自己的芯片型号
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
