# include "../../include/timeFunction.h"
# include"stdio.h"
/**************************************************/
/*名称：timeFunction
/*描述：时间相关的函数
/*作成日期：2019.9.2  
/*参数： buf size
/*返回值：
/*作者：zkx
/***************************************************/


void getCurrentDay(char buf[], int size)
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep);
	strftime(buf, size, "%Y-%m-%d", p);
}
	

void getCurrentTime(char buf[], int size)
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep);
	strftime(buf, size, "%Y-%m-%d %H:%M:%S", p);
}
