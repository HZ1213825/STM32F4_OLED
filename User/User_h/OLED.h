#ifndef __OLED_H
#define __OLED_H
/*头文件导入区*/
#include "stm32f4xx.h"
#include "Delay.h"
#include "Fort.h"
#include "arm_math.h"
/*结构体定义区*/
typedef struct
{
	uc8 (*TDArray)[128];
} OLED_Animation_Array;

typedef struct
{
	uc8 (*TDArray)[8];
} OLED_Alphanumeric_Array;

typedef struct
{
	uc8 (*TDArray)[16];
} OLED_Chinese_Array;

/*宏定义区*/
#define GPIO_group GPIOA					// I2C的GPIO组号
#define OLED_SCL GPIO_Pin_0					// I2C时钟的GPIO端口号
#define OLED_SDA GPIO_Pin_1					// I2C时钟的GPIO端口号
#define RCC_AHB1Periph RCC_AHB1Periph_GPIOA //所用组号的时钟

/*变量定义区*/
extern const OLED_Alphanumeric_Array OLED_Num_HEX_Small[16];
extern const OLED_Alphanumeric_Array OLED_Num_HEX_Big[16];
extern const OLED_Alphanumeric_Array OLED_Letter_Small[26];
extern const OLED_Alphanumeric_Array OLED_Letter_Big[26];
extern u8 OLED_Buffer[8][128];

/*函数定义区*/

/*软件I2C与命令发送函数*/
#define OLED_Write_SCL(x) GPIO_WriteBit(GPIO_group, OLED_SCL, x)
#define OLED_Write_SDA(x) GPIO_WriteBit(GPIO_group, OLED_SDA, x)
__STATIC_INLINE void I2C_Start(void);
__STATIC_INLINE void I2C_End(void);
void I2C_SendByte(u8 dat);
void OLED_Write_Ctrl_Start(void);
void OLED_Write_Data_Start(void);

/*初始化函数*/

void OLED_GPIO_Init(void);
void OLED_Init(void);

/*辅助功能函数*/

void OLED_Clear(void);
void OLED_ClearBuffer(u8 Dat);
void OLED_Set_PageAddress(u8 x, u8 y);
int OLED_Max(int Data1, int Data2);
int OLED_Min(int Data1, int Data2);
int OLED_Abs(int Data);
void OLED_LimMax(int *Dat, int Lim);
void OLED_LimMin(int *Dat, int Lim);
void OLED_CandA_LimMaxMin(int *X_Left, int *X_Right, int *Y_Up, int *Y_Down);

/*字母数字汉字函数*/

void OLED_Alphanumeric(u8 x, u8 y, OLED_Alphanumeric_Array Data);
void OLED_Chinese(u8 y, u8 x, OLED_Chinese_Array Data);
void OLED_Error(void);

/*画点函数*/

void OLED_Spot(int x, int y, int Width);

/*画圆和圆弧函数*/

void OLED_Circular(int X, int Y, int R, int Width, FunctionalState Solid);
void OLED_Arc(int X, int Y, int R, int Angle_Start, int Angle_End, int Width);
void OLED_Arc_Achieve(int X, int Y, int R, int X_Left, int X_Right, int Y_Up, int Y_Down, int Width);

/*全屏动画函数*/
void OLED_Animation(int Time, int Num);
void OLED_Animation_Ation(OLED_Animation_Array Array);

/*全屏图片函数*/
void OLED_Full_Picture(uc8 (*a)[128]);

/*划线函数*/
void OLED_LineSegment(int x1, int y1, int x2, int y2, int Width);
void OLED_Slash(int x1, int y1, int x2, int y2, int Width);
void OLED_Vertical_Line(int x1, int y1, int x2, int y2, int Width);

#endif
