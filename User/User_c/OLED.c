#include "OLED.h"
#include "arm_math.h"
u8 OLED_Buffer[8][128] = {0};

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

软件I2C与命令发送函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

// I2C起始信号
__STATIC_INLINE void I2C_Start(void)
{
	OLED_Write_SDA(Bit_SET);
	OLED_Write_SCL(Bit_SET); //确保SCL与SDA为高电平
	// Delay_us();//这里可以加延迟，保证信号稳定，是SDA高电平持续的延迟，编者的OLED模块不需要加
	OLED_Write_SDA(Bit_RESET); //在SCL为高电平时SDA产生下降沿
	// Delay_us();//这里可以加延迟，保证信号稳定，是SDA与SCL下降沿之间的延迟，编者的OLED模块不需要加
	OLED_Write_SCL(Bit_RESET); //将SCL拉低，准备接受数据
}
// I2C结束信号
__STATIC_INLINE void I2C_End(void)
{							   //从发送数据到结束部分，默认SCL为低电平
	OLED_Write_SDA(Bit_RESET); //将SDA拉低
	OLED_Write_SCL(Bit_SET);
	// Delay_us();//这里可以加延迟，保证信号稳定，是SDA和SCL上升沿之间的延迟，编者的OLED模块不需要加
	OLED_Write_SDA(Bit_SET);
	// Delay_us();//这里可以加延迟，保证信号稳定，是SDA高电平持续的延迟，编者的OLED模块不需要加
}
// I2C发送1Byte数据
void I2C_SendByte(u8 dat)
{
	u8 zj = dat;				 //不能更改dat
	for (int i = 7; i >= 0; i--) // 8次就行，怎么循环随意
	{							 //进入发送数据默认SCL为低电平
		if (zj & 0x80)			 //判断最高位
		{
			OLED_Write_SDA(Bit_SET);
		}
		else
		{
			OLED_Write_SDA(Bit_RESET);
		}
		OLED_Write_SCL(Bit_SET);   // SCL拉高，让外设读取数据
		OLED_Write_SCL(Bit_RESET); //准备读取下个数据
		zj <<= 1;				   //向左移位，让数据从高到低发送
	}
	OLED_Write_SCL(Bit_SET); //第九个周期，应答位
	//可以加验证的代码，一般不需要验证
	OLED_Write_SCL(Bit_RESET);
}
//写入控制命令的开始 写完数据后加结束命令
void OLED_Write_Ctrl_Start(void)
{
	I2C_Start();
	I2C_SendByte(0x78);
	I2C_SendByte(0x00);
}
//写入数据的开始 写完数据后加结束命令
void OLED_Write_Data_Start(void)
{
	I2C_Start();
	I2C_SendByte(0x78);
	I2C_SendByte(0x40);
}

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

初始化函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

//初始化GPIO
void OLED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;				//声明结构体
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph, ENABLE); //打开时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;		//输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;		//开漏输出
	GPIO_InitStruct.GPIO_Pin = OLED_SCL | OLED_SDA; // SDA和SCL线
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//快速模式
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIO_group, &GPIO_InitStruct);		//初始化
	GPIO_SetBits(GPIO_group, OLED_SCL | OLED_SDA);	//设置为默认为高电平
}
// OLED的初始化
void OLED_Init(void)
{
	for (int i = 0; i < 1000; i++) //上电延时
	{
		for (int j = 0; j < 1000; j++)
			;
	}

	OLED_GPIO_Init();		 //初始化GPIO
	OLED_Write_Ctrl_Start(); //开始写入初始化命令
	I2C_SendByte(0xAE);		 //关闭显示

	I2C_SendByte(0xD5); //设置显示时钟分频比/振荡器频率
	I2C_SendByte(0x80);

	I2C_SendByte(0xA8); //设置多路复用率
	I2C_SendByte(0x3F);

	I2C_SendByte(0xD3); //设置显示偏移
	I2C_SendByte(0x00);

	I2C_SendByte(0x40); //设置显示开始行

	I2C_SendByte(0xA1); //设置左右方向，0xA1正常 0xA0左右反置

	I2C_SendByte(0xC8); //设置上下方向，0xC8正常 0xC0上下反置

	I2C_SendByte(0xDA); //设置COM引脚硬件配置
	I2C_SendByte(0x12);

	I2C_SendByte(0x81); //设置对比度控制
	I2C_SendByte(0xCF);

	I2C_SendByte(0xD9); //设置预充电周期
	I2C_SendByte(0xF1);

	I2C_SendByte(0xDB); //设置VCOMH取消选择级别
	I2C_SendByte(0x30);

	I2C_SendByte(0xA4); //设置整个显示打开/关闭

	I2C_SendByte(0xA6); //设置正常/倒转显示

	I2C_SendByte(0x8D); //设置充电泵
	I2C_SendByte(0x14);
	I2C_SendByte(0x2E); //关闭滚动
	I2C_SendByte(0xAF); //开启显示

	I2C_End();
	OLED_Clear();
}

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

辅助功能函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

//清屏
void OLED_Clear(void)
{
	OLED_Write_Ctrl_Start();
	I2C_SendByte(0x20); //设置寻址模式 (0x00/0x01/0x02)
	I2C_SendByte(0x00); //水平寻址模式
	I2C_SendByte(0x21); //设置列地址
	I2C_SendByte(0x00);
	I2C_SendByte(0x7f);
	I2C_SendByte(0x22); //设置页地址
	I2C_SendByte(0x00);
	I2C_SendByte(0x07);
	I2C_End();
	OLED_Write_Data_Start();
	for (int i = 0; i < 8; i++)		  // 0-7页
		for (int j = 0; j < 128; j++) // 0-127列
			I2C_SendByte(0x00);
	I2C_End();
}

//清理缓冲区为同一数据
void OLED_ClearBuffer(u8 Dat)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 128; j++)
			OLED_Buffer[i][j] = Dat;
}

//设置页寻址模式的其实地址,x是列数，y是页数
void OLED_Set_PageAddress(u8 x, u8 y)
{
	// 0<=y<=7,0<=x<=127
	if ((y <= 7) && (x <= 127))
	{
		OLED_Write_Ctrl_Start();
		I2C_SendByte(0x20);						//设置寻址模式 (0x00水平/0x01垂直/0x02页)
		I2C_SendByte(0x10);						//页寻址模式
		I2C_SendByte(0xb0 | (y & 0x0f));		//设置页
		I2C_SendByte(((x & 0xf0) >> 4) | 0x10); //设置列的高位
		I2C_SendByte(x & 0x0f);					//设置页的低位
		I2C_End();
	}
}

//取最大值
int OLED_Max(int Data1, int Data2)
{
	if (Data1 > Data2)
		return Data1;
	else
		return Data2;
}

//取最小值
int OLED_Min(int Data1, int Data2)
{
	if (Data1 > Data2)
		return Data2;
	else
		return Data1;
}

//取绝对值
int OLED_Abs(int Data)
{
	if (Data > 0)
	{
		return Data;
	}
	else
	{
		return ((-1) * Data);
	}
}

//限制数到给定的最大值
void OLED_LimMax(int *Dat, int Lim)
{
	if ((*Dat) >= Lim)
		(*Dat) = Lim;
}

//限制数到给定的最小值
void OLED_LimMin(int *Dat, int Lim)
{
	if ((*Dat) <= Lim)
		(*Dat) = Lim;
}

//画圆和圆弧用 限制最大最小值
void OLED_CandA_LimMaxMin(int *X_Left, int *X_Right, int *Y_Up, int *Y_Down)
{
	OLED_LimMin(X_Left, 0);
	OLED_LimMin(Y_Up, 0);
	OLED_LimMax(X_Right, 127);
	OLED_LimMax(Y_Down, 63);
}

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

字母数字汉字函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

//指定位置写字母或数字 先输入选定的行数<4，再输入列数<16，再输入数据
void OLED_Alphanumeric(u8 y, u8 x, OLED_Alphanumeric_Array Data)
{
	if (y < 4 && x < 16) //验证，避免超范围
	{
		for (int i = 0; i < 2; i++) //扫描字模的两页
		{
			OLED_Set_PageAddress(x * 8, y * 2 + i); //每页都需要设置地址
			OLED_Write_Data_Start();
			for (int j = 0; j < 8; j++) //扫描列
			{
				I2C_SendByte(Data.TDArray[i][j]);
			}
			I2C_End();
		}
	}
	else
	{
		OLED_Error();
	}
}

//指定位置写汉字
void OLED_Chinese(u8 y, u8 x, OLED_Chinese_Array Data)
{
	if (y < 4 && x < 8)
	{
		for (int i = 0; i < 2; i++)
		{
			OLED_Set_PageAddress(x * 16, y * 2 + i);
			OLED_Write_Data_Start();
			for (int j = 0; j < 16; j++)
			{
				I2C_SendByte(Data.TDArray[i][j]);
			}
			I2C_End();
		}
	}
	else
	{
		OLED_Error();
	}
}

// OLED上提示错误函数
void OLED_Error(void)
{
	for (int i = 0; i < 4; i++)
	{
		OLED_Alphanumeric(i, 0, OLED_Letter_Big['E' - 'A']);
		OLED_Alphanumeric(i, 1, OLED_Letter_Big['R' - 'A']);
		OLED_Alphanumeric(i, 2, OLED_Letter_Big['R' - 'A']);
		OLED_Alphanumeric(i, 3, OLED_Letter_Big['O' - 'A']);
		OLED_Alphanumeric(i, 4, OLED_Letter_Big['R' - 'A']);
	}
}

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

画点函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

//指定位置画点,宽度最小为0（只亮一个OLED）
void OLED_Spot(int X, int Y, int Width)
{
	u8 Spot_Zj;
	OLED_LimMin(&X, 0);
	OLED_LimMax(&X, 127);
	OLED_LimMin(&Y, 0);
	OLED_LimMax(&Y, 63);
	if (Width)
	{
		for (int y = (Y - Width) / 8; y < (Y + Width) / 8; y++) //遍历页
		{
			for (int x = X - Width; x < X + Width; x++) //遍历页
			{
				Spot_Zj = 0;
				for (int z = 0; z < 8; z++) //遍历指定页，列的8个led
				{
					Spot_Zj >>= 1;
					if ((Y / 8 * 8 + z) >= (Y - Width) && (Y / 8 * 8 + z) <= (Y + Width))
					{
						Spot_Zj |= 0x80;
					}
				}
				OLED_Buffer[y][x] |= Spot_Zj;
			}
		}
		if ((Y + Width) % 8)
		{
			for (int x = X - Width; x < X + Width; x++) //扫描列
			{
				Spot_Zj = 0;
				for (int z = 0; z < 8; z++)
				{
					Spot_Zj >>= 1;
					if ((Y / 8 * 8 + z) >= (Y - Width) && (Y / 8 * 8 + z) <= (Y + Width))
					{
						if (z <= ((Y + Width) % 8)) //在指定范围内才写入
						{
							Spot_Zj |= 0x80;
						}
					}
				}
				OLED_Buffer[(Y + Width) / 8][x] |= Spot_Zj;
			}
		}
	}
	else
	{
		Spot_Zj = 1 << (Y % 8);
		OLED_Buffer[Y / 8][X] |= Spot_Zj;
	}
	OLED_Full_Picture(OLED_Buffer);
}

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

画圆和圆弧函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

//画圆 输入横纵坐标，半径和粗细
void OLED_Circular(int X, int Y, int R, int Width, FunctionalState Solid)
{
	int X_Left, X_Right, Y_Up, Y_Down;
	u8 Circular_Zj;
	X_Left = X - R - Width - 1;
	X_Right = X + R + Width + 1;
	Y_Up = (Y - R) / 8 - 1;
	Y_Down = (Y + R) / 8 + 1;
	OLED_CandA_LimMaxMin(&X_Left, &X_Right, &Y_Up, &Y_Down);
	for (int y = Y_Up; y < Y_Down; y++) //扫描页
	{
		for (int x = X_Left; x < X_Right; x++) //扫描列
		{
			Circular_Zj = 0;
			for (int z = 0; z < 8; z++) //页内的led
			{
				Circular_Zj >>= 1;
				if (Solid == DISABLE) //空心圆
				{
					if (OLED_Abs(powf(x - X, 2) + powf((y * 8 + z) - Y, 2) - powf(R, 2)) < powf(Width, 2))
					{
						Circular_Zj |= 0x80;
					}
				}
				else if (Solid == ENABLE) //实心圆
				{
					if ((powf(x - X, 2) + powf((y * 8 + z) - Y, 2)) < (powf(R, 2) + powf(Width, 2)))
					{
						Circular_Zj |= 0x80;
					}
				}
			}
			OLED_Buffer[y][x] |= Circular_Zj;
		}
	}
	OLED_Full_Picture(OLED_Buffer);
}

//画圆弧
void OLED_Arc(int X, int Y, int R, int Angle_Start, int Angle_End, int Width)
{
	float Radian_Start = (Angle_Start * PI) / 180; //算出弧度制起始角度
	float Radian_End = (Angle_End * PI) / 180;	   //算出弧度制终止角度
	int X_End, X_Start, Y_Up, Y_Down;
	X_End = X + arm_cos_f32(Radian_End) * R;	 //终止角度计算的边界
	X_Start = X + arm_cos_f32(Radian_Start) * R; //起始角度计算的边界
	Y_Up = Y - R;								 //上边界
	Y_Down = Y + R;								 //下边界
	if (Angle_Start >= 0 && Angle_Start <= 180)	 //起始点在1，2象限
	{
		if (Angle_Start < Angle_End)
		{
			if (Angle_End >= 0 && Angle_End <= 180) //终点在1，2象限
			{
				OLED_Arc_Achieve(X, Y, R, X_End, X_Start, Y_Up, Y, Width); // s-e部分
			}
			else if (Angle_End > 180 && Angle_End <= 360) //终点在3，4象限
			{
				OLED_Arc_Achieve(X, Y, R, X - R, X_Start, Y_Up, Y, Width); // s-180部分
				OLED_Arc_Achieve(X, Y, R, X - R, X_End, Y, Y_Down, Width); // 180-e部分
			}
		}
		else
		{
			OLED_Arc_Achieve(X, Y, R, X - R, X_Start, Y_Up, Y, Width);	   // s-180部分
			OLED_Arc_Achieve(X, Y, R, X - R, X + R + 1, Y, Y_Down, Width); // 180-360部分
			OLED_Arc_Achieve(X, Y, R, X_End, X + R + 1, Y_Up, Y, Width);   // 0-e部分
		}
	}
	else if (Angle_Start >= 180 && Angle_Start <= 360)
	{

		if (Angle_End >= 180 && Angle_End <= 360)
		{
			if (Angle_Start < Angle_End)
			{
				OLED_Arc_Achieve(X, Y, R, X_Start, X_End, Y, Y_Down, Width); // s-e部分
			}
			else
			{
				OLED_Arc_Achieve(X, Y, R, X_Start, X + R, Y, Y_Down, Width);   // s-360部分
				OLED_Arc_Achieve(X, Y, R, X - R, X + R, Y_Up, Y, Width);	   // 360(0)-180部分
				OLED_Arc_Achieve(X, Y, R, X - R, X - X_End, Y, Y_Down, Width); // 180-e部分
			}
		}
		else if (Angle_End > 0 && Angle_End < 180)
		{
			OLED_Arc_Achieve(X, Y, R, X_Start, X + R, Y, Y_Down, Width); // s-360部分
			OLED_Arc_Achieve(X, Y, R, X_End, X + R, Y_Up, Y, Width);	 // 360-e部分
		}
	}
	OLED_Full_Picture(OLED_Buffer);
}

// 画圆弧的实现函数
void OLED_Arc_Achieve(int X, int Y, int R, int X_Left, int X_Right, int Y_Up, int Y_Down, int Width)
{
	u8 Arc_Zj;
	OLED_CandA_LimMaxMin(&X_Left, &X_Right, &Y_Up, &Y_Down);
	for (int y = Y_Up / 8; y < Y_Down / 8; y++)
	{
		for (int x = X_Left; x < X_Right; x++)
		{
			Arc_Zj = 0;
			for (int z = 0; z < 8; z++)
			{
				Arc_Zj >>= 1;
				if (OLED_Abs(powf(x - X, 2) + powf((y * 8 + z) - Y, 2) - powf(R, 2)) < powf(Width, 2))
				{
					Arc_Zj |= 0x80;
				}
			}
			OLED_Buffer[y][x] |= Arc_Zj;
		}
	}
	if (Y_Down % 8)
	{
		for (int x = X_Left; x < X_Right; x++) //扫描列
		{
			Arc_Zj = 0;
			for (int z = 0; z < 8; z++)
			{
				Arc_Zj >>= 1;
				if (OLED_Abs(powf(x - X, 2) + powf((Y_Down / 8 * 8 + z) - Y, 2) - powf(R, 2)) < powf(Width, 2))
				{
					if (z <= (Y_Down % 8)) //在指定范围内才写入
					{
						Arc_Zj |= 0x80;
					}
				}
			}
			OLED_Buffer[Y_Down / 8][x] |= Arc_Zj;
		}
	}
}

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

全屏动画函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

//动画刷新函数（有需要修改的值） Time:间隔时间单位ms Num：帧的数量
void OLED_Animation(int Time, int Num)
{
	//这个需要修改，修改数组大小和内部值 将uc8 [128][8]的名字按顺序放入
	OLED_Animation_Array ac[50] = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50};
	OLED_Clear();
	for (int i = 1; i <= Num; i++)
	{
		OLED_Animation_Ation(ac[i - 1]);
		Delay_ms(Time);
	}
}

//动画实现函数 Array：含每帧数据的结构体
void OLED_Animation_Ation(OLED_Animation_Array Array)
{
	//使用水平寻址模式模式
	OLED_Write_Ctrl_Start();
	I2C_SendByte(0x20); //设置寻址模式 (0x00水平/0x01垂直/0x02页)
	I2C_SendByte(0x00); //水平寻址模式
	I2C_SendByte(0x21); //设置列地址
	I2C_SendByte(0x00);
	I2C_SendByte(0x7f);
	I2C_SendByte(0x22); //设置页地址
	I2C_SendByte(0x00);
	I2C_SendByte(0x07);
	I2C_End();

	OLED_Write_Data_Start();
	for (int i = 0; i < 8; i++) //扫描页
	{
		for (int j = 0; j < 128; j++) //扫描列
			I2C_SendByte(Array.TDArray[i][j]);
	}
	I2C_End();
}

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

全屏图片函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

//显示一张全屏图片
void OLED_Full_Picture(uc8 (*a)[128])
{
	OLED_Animation_Array Pic = {a};
	OLED_Animation_Ation(Pic);
}

/*
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

划线函数

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/

//画斜线
void OLED_Slash(int x1, int y1, int x2, int y2, int Width)
{
	unsigned char Line_Zj = 0;
	float a, b;
	a = ((float)(y2 - y1)) / ((float)(x2 - x1)); //斜率
	b = (float)y2 - a * (float)x2;				 // y轴截距
	//直接操作编码好的数据也就是[8][128]数组
	for (int y = OLED_Min(y1, y2) / 8; y < (OLED_Max(y1, y2) / 8); y++) //扫描页，从最小值所在页到最大值所在页的前一页
	{
		for (int x = OLED_Min(x1, x2); x < OLED_Max(x1, x2); x++) //扫描列
		//上面这两个循环是在两个点之间的矩形区域扫描
		{
			Line_Zj = 0;				//中间变量没列都需要重置
			for (int z = 0; z < 8; z++) //扫描一页中的数据
			{
				Line_Zj >>= 1;									 //从显示屏的上到下扫描，页的低位到高位
				if (OLED_Abs((a * x + b - (y * 8 + z))) < Width) //在宽度范围内的则将其值写1，重点是y坐标的计算
				{
					Line_Zj |= 0x80;
				}
			}
			OLED_Buffer[y][x] |= Line_Zj; //数据存到缓冲区中
		}
	}
	if ((OLED_Max(y1, y2) % 8) != 0) //生成最后一页的数据
	{
		for (int x = OLED_Min(x1, x2); x < OLED_Max(x1, x2); x++) //扫描列
		{
			Line_Zj = 0;
			for (int z = 0; z < 8; z++)
			{
				Line_Zj >>= 1;
				if (OLED_Abs(a * x + b - ((OLED_Max(y1, y2) / 8 * 8) + z)) < Width) //这里的y坐标是仅随z变化的,乘8除8是利用int精度丢失数据
				{
					if (z <= (OLED_Max(y1, y2) % 8)) //在指定范围内才写入
					{
						Line_Zj |= 0x80;
					}
				}
			}
			OLED_Buffer[OLED_Max(y1, y2) / 8][x] |= Line_Zj;
		}
	}
}

//画竖线
void OLED_Vertical_Line(int x1, int y1, int x2, int y2, int Width)
{
	int xl, xr;
	u8 Line_Zj;
	if (x1 == x2)
	{
		xl = x1 - Width + 1;
		xr = x1 + Width;
		if (xl <= 0)
			xl = 0;
		if (xr >= 127)
			xr = 127;
		for (int x = xl; x < xr; x++)
		{
			for (int y = OLED_Min(y1, y2) / 8; y < (OLED_Max(y1, y2) / 8) + 1; y++) //扫描页，从最小值所在页到最大值所在页
			{
				Line_Zj = 0;
				for (int z = 0; z < 8; z++)
				{
					Line_Zj >>= 1;
					if ((y * 8 + z) >= OLED_Min(y1, y2))
					{
						if ((y * 8 + z) <= OLED_Max(y1, y2))
						{
							Line_Zj |= 0x80;
						}
					}
				}
				OLED_Buffer[y][x] |= Line_Zj; //数据存到缓冲区中
			}
		}
	}
}

//划线，依次输入 点1横纵坐标 点2横纵坐标 宽度
void OLED_LineSegment(int x1, int y1, int x2, int y2, int Width)
{
	//限制范围
	OLED_LimMin(&x1, 0);
	OLED_LimMax(&x1, 126);
	OLED_LimMin(&x2, 0);
	OLED_LimMax(&x2, 126);
	OLED_LimMin(&y1, 0);
	OLED_LimMax(&y1, 63);
	OLED_LimMin(&y2, 0);
	OLED_LimMax(&y2, 63);

	if (x1 == x2 && y1 == y2) //两个点同坐标
	{
		OLED_ClearBuffer(0xff);
	}
	else if (x1 == x2) //竖线(斜率不存在)
	{
		OLED_Vertical_Line(x1, y1, x2, y2, Width);
	}
	else //斜线(斜率存在)
	{
		OLED_Slash(x1, y1, x2, y2, Width);
	}
	OLED_Full_Picture(OLED_Buffer);
}
