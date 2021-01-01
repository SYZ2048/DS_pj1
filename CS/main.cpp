#include<iostream>
#include<stdlib.h>
#include<stack>
#include<vector>
#include<queue>
#include <fstream>
#include <iostream>
#define MAX 1000
#define LENG 20
using namespace std;

//使用邻接表

struct city
{
	char city_name[LENG];	
	int signal;				//如果signal是0，说明已经被删除了，signal是1说明是正常的城市
	shift* adj;
};

city city_node[MAX];
int city_total_num;				//城市总数

struct shift				//班次信息
{
	int kind;				//0 is train,1 is flight
	char start[LENG];
	char terminal[LENG];
	char start_time[LENG];
	char arrival_time[LENG];
	int price;
	struct shift* next;		
};


int find_city(char name[])
{
	//if 存在，输出对应的下标，否则输出-1

}


void add_city(char name[])
{
	int city_num = find_city(name);
	if (city_num != -1 && city_node[city_num].signal == 1)//已存在
	{
		cout << "failed to add!existed!!" << endl;
		return;
	}
	if (city_num != -1 && city_node[city_num].signal == 0)//曾被删除
	{
		city_node[city_num].signal = 1;
		cout << "succeed to add! The number of city is" << n << endl;
		return;
	}
	if (city_num == -1 && city_total_num == MAX)//空间已满
	{
		cout << "failed to add! No enough space!" << endl;
		return;
	}
	else
	{
		city_node[city_total_num].city_name = name;
		city_node[city_total_num].signal = 1;
		city_node[city_total_num].adj = NULL;
		cout << "succeed to add! The number of city is" << city_total_num << endl;
		city_total_num++;
		return;
	}
	return;
		
}

void delete_city()
{
	int city_num = find_city(name);
	if (city_num == -1)
	{ 
		cout << "failed to delete!not exist!" << endl;
		return;
	}
	if (city_num != -1 && city_node[city_num].signal == 0)
	{
		cout << "failed to delete!not exist!" << endl;
		return;
	}
	if (city_num != -1 && city_node[city_num].signal == 1)
	{
		city_node[city_num].signal = 0;
		cout << "succeed to delete! " << n << endl;
		return;
	}
	
}

void add_city_info(int )
{

}

void delete_city_info()
{

}


void print_schedule(char name[])	//输入城市名称，打印由该城市出发的所有列车路线以及飞机航
									//班班次信息
{

	
}

void find_optimal(起点，终点)
{



}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int i;
	for (i = 0; i < n; i++)
	{

	}

}
