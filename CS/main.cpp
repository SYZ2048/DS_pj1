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

//ʹ���ڽӱ�,�ֱ��Ƿɻ����ڽӱ�&���ڽӱ��𳵵��ڽӱ�&���ڽӱ�

struct city
{
	char city_name[LENG];	
	int signal;				//���signal��0��˵���Ѿ���ɾ���ˣ�signal��1˵���������ĳ���
	shift* adj;
};

city city_node_flight_in[MAX];
city city_node_flight_out[MAX];
city city_node_train_in[MAX];
city city_node_train_in[MAX];
int city_total_num;				//��������

struct shift				//�����Ϣ
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
	//if ���ڣ������Ӧ���±꣬�������-1

}


void add_city(char name[])
{
	int city_num = find_city(name);
	if (city_num != -1 && city_node_flight_in[city_num].signal == 1)//�Ѵ���
	{
		cout << "failed to add!existed!!" << endl;
		return;
	}
	if (city_num != -1 && city_node_flight_in[city_num].signal == 0)//����ɾ��
	{
		city_node_flight_in[city_num].signal = 1;
		city_node_flight_out[city_num].signal = 1;
		city_node_train_in[city_num].signal = 1;
		city_node_train_out[city_num].signal = 1;
		cout << "succeed to add! The number of city is" << n << endl;
		return;
	}
	if (city_num == -1 && city_total_num == MAX)//�ռ�����
	{
		cout << "failed to add! No enough space!" << endl;
		return;
	}
	else
	{
		city_node_flight_in[city_total_num].city_name = name;
		city_node_flight_in[city_total_num].signal = 1;
		city_node_flight_in[city_total_num].adj = NULL;
		city_node_flight_out[city_total_num].city_name = name;
		city_node_flight_out[city_total_num].signal = 1;
		city_node_flight_out[city_total_num].adj = NULL;
		city_node_train_in[city_total_num].city_name = name;
		city_node_train_in[city_total_num].signal = 1;
		city_node_train_in[city_total_num].adj = NULL;
		city_node_train_out[city_total_num].city_name = name;
		city_node_train_out[city_total_num].signal = 1;
		city_node_train_out[city_total_num].adj = NULL;
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
	if (city_num != -1 && city_node_flight_in[city_num].signal == 0)
	{
		cout << "failed to delete!not exist!" << endl;
		return;
	}
	if (city_num != -1 && city_node_flight_in[city_num].signal == 1)
	{
		city_node_flight_in[city_num].signal = 0;
		city_node_flight_out[city_num].signal = 0;
		city_node_train_in[city_num].signal = 0;
		city_node_train_out[city_num].signal = 0;
		cout << "succeed to delete! " << n << endl;
		return;
	}
	
}

void add_city_info(shift info)
{
	int start_num; int terminal_num;
	start_num = find(info.start);
	terminal_num = find(info.terminal);
	if (start_num == -1 || (start_num != -1 && city_node_flight_in[start_num].signal == 0))
	{
		cout << "fail to add information!start not exist!" << endl;
		return;
	}
	if (terminal_num == -1 || (terminal_num != -1 && city_node_flight_in[terminal_num].signal == 0))
	{
		cout << "fail to add information!terminal not exist!" << endl;
		return;
	}
	shift* p;
	if (info.kind == 1)//flight
	{

	}
}

void delete_city_info()
{

}


void print_schedule(char name[])	//����������ƣ���ӡ�ɸó��г����������г�·���Լ��ɻ���
									//������Ϣ
{
	int city_num = find_city(name);
	if (city_num == -1)
	{
		cout << "failed to print!not exist!" << endl;
		return;
	}
	if (city_num != -1 && city_node_flight_out[city_num].signal == 0)
	{
		cout << "failed to print!not exist!" << endl;
		return;
	}
	shift* p;
	if (city_num != -1 && city_node_flight_out[city_num].signal == 1)
	{
		p = city_node_flight_in[city_num].adj;
		while (p != NULL)
		{

		}
		return;
	}
	
}

void find_optimal(��㣬�յ�)
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
