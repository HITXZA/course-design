// 课设.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<Windows.h>
using namespace std;
#define begin_x  0
#define begin_y  1

#define offset_x 5
#define offset_y 5
int now_x=0;
int now_y=1;
int len=0;
struct info {
	int car_num;
	int position;
	int time;
	int flag;
};
void goto_xy(short x, short y)//定位光标位置到指定坐标
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}
void printf_position(short x, short y) {
	int i = 0; 
	now_x = x;
	now_y = y;
	for ( i=0; i < 5; i++) {
		goto_xy(now_x +i,now_y );
		printf("*");
	}
	now_x = now_x + i;
	now_y = now_y;
	for ( i = 0; i < 5; i++) {
		goto_xy(now_x , now_y+i);
		printf("*");
	}
	now_x = now_x ;
	now_y = now_y+i;
	for (i = 0; i < 5; i++) {
		goto_xy(now_x-i, now_y );
		printf("*");
	}
	now_x = now_x - i;
	now_y = now_y;
	for (i = 0; i < 5; i++) {
		goto_xy(now_x, now_y - i);
		printf("*");
	}
	now_x = now_x;
	now_y = now_y-i;
}
void refresh(struct info* store) {
	for (int i = 0; i < len; i++)
	{
		goto_xy(begin_x+store[i].position * 7 + 2, begin_y +2);
		printf("C");
		printf("%d", store[i].car_num);
	}
}
int get_position(int *p) {//第一个可以停的车位
	int i = 0;
	while (1) {
		if (p[i] == 0) {
			p[i] = 1;
			break;
		}
		i++;
	}
	return i;
}
void leave_car(struct info* store,int car_num )
{
	int res=-1;
	for (int  i = 0; i < len; i++)
	{
		if (store[i].car_num == car_num)
		{
			res = i;
			break;
		}

	}
	if (res == -1)
		printf("不存在的编号！");
	else {
		goto_xy(begin_x + store[res].position * 7 + 2, begin_y + 2);//抹去图形
		printf("  ");
	}

}
int main()
{
	int num_stop=3;
	printf("停车场数量 输完回车\n");
	//cin >> num_stop;
	//system("cls");
	//scanf("%d", &num_stop);
	/*for (int i = 0; i < num_stop; i++) {
		printf("***\n");
		goto_xy(10, 10);
	}*/
	goto_xy(begin_x, begin_y);
	printf_position(begin_x, begin_y);//原始打印一个
	for (int i = 0; i < num_stop-1; i++) {
		printf_position(now_x +7, now_y );//后续位移打印一个
	}

	int *p = (int*)malloc(sizeof(int) * num_stop);
	for (int i = 0; i < num_stop; i++)
	{
		p[i] = 0;
	}
	struct info* store;
	store = (struct info*)malloc(sizeof(struct info)*num_stop);//按照车位多少建立一个结构体数组
	int x1;
	int x2;
	char c;
	while (1) {
		goto_xy(10, 10);
		printf("请依次输入 车号 时间 操作字符");
		scanf_s("%d,%d,%c",&x1,&x2,&c );
		fflush(stdin);
		//&store[len].car_num, &store[len].position, &store[len].char_info
		if (c == 'c'&&len != num_stop)//come 车辆到来 且还有空位
		{
			store[len].car_num = x1;
			store[len].time = x2;
			store[len].position=get_position(p);
			len++;
			refresh(store);
		}
		else if (c == 'c'&&len == num_stop) {
			printf("没有空位了熬");
		}
		else if (c == 'L')
		{
			cout << "test" << endl;
			leave_car(store, 2);
		}

	}
	goto_xy(10, 10);//不要破坏图像
	return 0;
}

