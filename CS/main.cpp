#include<iostream>
#include<stdlib.h>
#include<vector>
#include<stack>
#include <fstream>
#include <iostream>
#include <string.h>
#define MAX 1000
#define LENG 20
using namespace std;

//使用邻接表,分别是飞机的邻接表&逆邻接表，火车的邻接表&逆邻接表
struct shift				//班次信息
{
	char kind;					//0 is train,1 is flight
	int start;			//起点
	int terminal;		//终点
	char start_time[LENG];		//出发时间
	char arrival_time[LENG];	//到达时间
	int price;					//价格
	struct shift* next;			//指向同起点、同种交通工具的下一班次
};

struct city
{
	char city_name[LENG];	//记录城市名字
	int signal;				//如果signal是0，说明已经被删除了，signal是1说明是正常的城市
	struct shift* adj;		//指向该城市的第一条路径
};

city city_node_flight_in[MAX];	//记录飞机班次的逆邻接表
city city_node_flight_out[MAX];	//记录飞机班次的邻接表
city city_node_train_in[MAX];	//记录火车班次的逆邻接表
city city_node_train_out[MAX];	//记录火车班次的邻接表
int city_total_num;				//记录出现过的不重复城市总数（包括已删除城市）
int current_city_num;


int find_city(char name[])			//用于寻找城市在数组中对应的下标
									//if城市存在，输出对应的下标，否则输出-1
{
	int i;
	for (i = 0; i < city_total_num; i++)
	{
		if (!strcmp(name, city_node_flight_in[i].city_name))
			return i;
	}
	return -1;
}

int GetWeigh(int v,int u,int kind)
{
	int min_dist = 999;
	shift* p;
	if (kind == 0)//train
	{
		p = city_node_flight_out[v].adj;
		while (p != NULL)
		{
			if (p->terminal == u && p->price < min_dist)
			{
				min_dist = p->price;
			}
			p = p->next;
		}
	}
	else
	{
		p = city_node_train_out[v].adj;
		while (p != NULL)
		{
			if (p->terminal == u && p->price < min_dist)
			{
				min_dist = p->price;
			}
			p = p->next;
		}
	}
	return min_dist;
}

//已完成
void add_city()					//增加城市
{
	char name[20];
	cout << "enter a city:" << endl;
	cin.getline(name, 20);
	cout << "The city is:" << name << endl;
	int city_num = find_city(name);
	if (city_num != -1 && city_node_flight_in[city_num].signal == 1)	//若城市现已存在
	{
		cout << "failed to add!existed!!" << endl;
		return;
	}
	if (city_num != -1 && city_node_flight_in[city_num].signal == 0)	//若城市曾出现，但被删除
	{
		city_node_flight_in[city_num].signal = 1;
		city_node_flight_out[city_num].signal = 1;
		city_node_train_in[city_num].signal = 1;
		city_node_train_out[city_num].signal = 1;
		cout << "succeed to add! The number of city is" << city_total_num << endl;
		return;
	}
	if (city_num == -1 && city_total_num == MAX)						//空间已满
	{
		cout << "failed to add!! No enough space!" << endl;
		return;
	}
	else//正常添加城市
	{
		strcpy_s(city_node_flight_in[city_total_num].city_name, name);
		city_node_flight_in[city_total_num].signal = 1;
		city_node_flight_in[city_total_num].adj = NULL;
		strcpy_s(city_node_flight_out[city_total_num].city_name , name);
		city_node_flight_out[city_total_num].signal = 1;
		city_node_flight_out[city_total_num].adj = NULL;
		strcpy_s(city_node_train_in[city_total_num].city_name , name);
		city_node_train_in[city_total_num].signal = 1;
		city_node_train_in[city_total_num].adj = NULL;
		strcpy_s(city_node_train_out[city_total_num].city_name , name);
		city_node_train_out[city_total_num].signal = 1;
		city_node_train_out[city_total_num].adj = NULL;
		city_total_num++;
		current_city_num++;
		cout << "succeed to add "<<name<<"!!current city number is " << current_city_num << endl;
		return;
	}		
}

//已完成
void delete_city()
{
	cout << "please enter the name of city to delete:"<<endl;
	char name[LENG];
	cin.getline(name, LENG);
	int city_num = find_city(name);
	if (city_num == -1)//不存在
	{
		cout << "failed to delete!not exist!" << endl;
		return;
	}
	if (city_num != -1 && city_node_flight_in[city_num].signal == 0)//曾被删除
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
		cout << "succeed to delete the city:" << name << endl;
		current_city_num--;
		cout << "current city number is " << current_city_num << endl;
		return;
	}
	
}

//已完成
void add_city_info()
{
	shift* info;
	char start_name[LENG];
	char terminal_name[LENG];
	info = new shift();
	cout << "adding city information:" << endl;
	cout << "please enter the kind(0 is train,1 is flight):" << endl;
	cin.getline(&info->kind,2);
	cout << "please enter the start:" << endl;
	cin.getline(start_name, LENG);
	info->start = find_city(start_name);
	cout << "please enter the terminal:" << endl;
	cin.getline(terminal_name, LENG);
	info->terminal = find_city(terminal_name);
	cout << "please enter the start time:" << endl;
	cin.getline(info->start_time, LENG);
	cout << "please enter the arrival time:" << endl;
	cin.getline(info->arrival_time, LENG);
	cout << "please enter the price:" << endl;
	cin>>info->price;
	cin.ignore();
	info->next = NULL;
	//起点不存在
	if (info->start == -1 || (info->start != -1 && city_node_flight_in[info->start].signal == 0))
	{
		cout << "fail to add information!start not exist!" << endl;
		return;
	}
	//终点不存在
	if (info->terminal == -1 || (info->terminal != -1 && city_node_flight_in[info->terminal].signal == 0))
	{
		cout << "fail to add information!terminal not exist!" << endl;
		return;
	}
	shift* p;
	if (info->kind == '1')//flight
	{	//增加起点的出邻接表和终点的入邻接表
		p = city_node_flight_out[info->start].adj;
		if (p == NULL)
		{
			city_node_flight_out[info->start].adj = info;
		}
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = info;
		}
		p = city_node_flight_in[info->terminal].adj;
		if (p == NULL)
		{
			city_node_flight_in[info->terminal].adj = info;
		}
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = info;
		}
	}
	else //train
	{	//增加起点的出邻接表和终点的入邻接表
		p = city_node_train_out[info->start].adj;
		if (p == NULL)
		{
			city_node_train_out[info->start].adj = info;
		}
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = info;
		}
		p = city_node_train_in[info->terminal].adj;
		if (p == NULL)
		{
			city_node_train_in[info->terminal].adj = info;
		}
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = info;
		}
		cout << "succeed to add shift information" << endl;
	}
	
}

//已完成
void delete_city_info()
{
	shift* info;
	char start_name[LENG];
	char terminal_name[LENG];
	info = new shift();
	cout << "adding city information:" << endl;
	cout << "please enter the kind(0 is train,1 is flight):" << endl;
	cin.getline(&info->kind,2);
	cout << "please enter the start:" << endl;
	cin.getline(start_name, LENG);
	info->start = find_city(start_name);
	cout << "please enter the terminal:" << endl;
	cin.getline(terminal_name, LENG);
	info->terminal = find_city(terminal_name);
	cout << "please enter the start time:" << endl;
	cin.getline(info->start_time, LENG);
	cout << "please enter the arrival time:" << endl;
	cin.getline(info->arrival_time, LENG);
	cout << "please enter the price:" << endl;
	cin>>info->price;
	cin.ignore();
	info->next = NULL;
	if (info->start == -1 || (info->start != -1 && city_node_flight_in[info->start].signal == 0))//起点不存在
	{
		cout << "fail to delete information!start not exist!" << endl;
		return;
	}
	if (info->terminal == -1 || (info->terminal != -1 && city_node_flight_in[info->terminal].signal == 0))//终点不存在
	{
		cout << "fail to delete information!terminal not exist!" << endl;
		return;
	}
	shift* p; shift* current;
	if (info->kind == '1')//flight
	{
		p = city_node_flight_out[info->start].adj;
		if (p == NULL)
		{
			cout << "no shift to delete!" << endl;
			return;
		}
		else//adj不是空
		{
			if (p->terminal == info->terminal && !strcmp(p->start_time, info->start_time))
			{
				city_node_flight_out[info->start].adj = p->next;
				cout << "succeed to delete shift! " << endl;
			}
			else
			{
				current = p;
				p = p->next;
				while (p != NULL)
				{
					if (p->terminal == info->terminal && !strcmp(p->start_time, info->start_time))
					{
						current->next = p->next;
						cout << "succeed to delete shift! " << endl;
						break;
					}
				}
			}

		}
		p = city_node_flight_in[info->terminal].adj;
		if (p == NULL) return;
		else//adj不是空
		{
			if (p->start == info->start && !strcmp(p->start_time, info->start_time))
			{
				city_node_flight_in[info->terminal].adj = p->next;
			}
			else
			{
				current = p;
				p = p->next;
				while (p != NULL)
				{
					if (p->start == info->start && !strcmp(p->start_time, info->start_time))
					{
						current->next = p->next;
						break;
					}
				}
			}

		}
	}
	else
	{
		p = city_node_train_out[info->start].adj;
		if (p == NULL)
		{
			cout << "no shift to delete!" << endl;
			return;
		}
		else//adj不是空
		{
			if (p->terminal == info->terminal && !strcmp(p->start_time, info->start_time))
			{
				city_node_train_out[info->start].adj = p->next;
			}
			else
			{
				current = p;
				p = p->next;
				while (p != NULL)
				{
					if (p->terminal == info->terminal && !strcmp(p->start_time, info->start_time))
					{
						current->next = p->next;
						break;
					}
				}
			}

		}
		p = city_node_train_in[info->terminal].adj;
		if (p == NULL) return;
		else//adj不是空
		{
			if (p->start == info->start && !strcmp(p->start_time, info->start_time))
			{
				city_node_train_in[info->terminal].adj = p->next;
			}
			else
			{
				current = p;
				p = p->next;
				while (p != NULL)
				{
					if (p->start == info->start && !strcmp(p->start_time, info->start_time))
					{
						current->next = p->next;
						break;
					}
				}
			}

		}
	}

}

//已完成
void print_schedule()	//输入城市名称，打印由该城市出发的所有列车路线以及飞机航
									//班班次信息
{
	cout << "please enter the name of city to print schedule:"<<endl;
	char name[LENG];
	cin.getline(name, LENG);
	int city_num = find_city(name);
	//不存在
	if (city_num == -1)
	{
		cout << "failed to print!not exist!" << endl;
		return;
	}
	//曾被删除
	if (city_num != -1 && city_node_flight_out[city_num].signal == 0)
	{
		cout << "failed to print!not exist!" << endl;
		return;
	}
	shift* p=NULL;
	if (city_num != -1 && city_node_flight_out[city_num].signal == 1)
	{
		p = city_node_flight_out[city_num].adj;
		if (p == NULL)
		{
			cout << "no flight" << endl;
		}
		else 
		{
			cout << "flight information:" << endl;
			while (p != NULL)
			{
				cout << "start:" << city_node_flight_out[p->start].city_name << "\t"
					"terminal:" << city_node_flight_out[p->terminal].city_name << "\t"
					"start time:" << p->start_time << "\t"
					"arrival time" << p->arrival_time << "\t"
					"price:" << p->price << "\t" << endl;
				p = p->next;
			}
		}
		p = city_node_train_out[city_num].adj;
		if (p == NULL)
		{
			cout << "no train" << endl;
		}
		else
		{
			cout << "train information:" << endl;
			while (p != NULL)
			{
				cout << "start:" << city_node_train_out[p->start].city_name << "\t"
					"terminal:" << city_node_train_out[p->terminal].city_name << "\t"
					"start time:" << p->start_time << "\t"
					"arrival time" << p->arrival_time << "\t"
					"price:" << p->price << "\t" << endl;
				p = p->next;
			}
		}
	}
	return;
}

//输出途中的路径环节没写
void find_cheapest()
{
	int i, j;
	int min;

	int dist[MAX];
	int path[MAX];
	int S[MAX];
	char kind[10];
	char start_city[20];
	char terminal_city[20];
	stack<shift> s;		shift* node = NULL;
	shift* p;
	cout << "please enter the kind(0 is train,1 is flight):" << endl;
	cin.getline(kind, 10);
	cout << "please enter the start:" << endl;
	cin.getline(start_city, LENG);
	cout << "please enter the terminal:" << endl;
	cin.getline(terminal_city, LENG);
	int start_num; int terminal_num;
	start_num = find_city(start_city);
	terminal_num = find_city(terminal_city);
	int near=start_num;
	if (start_num == -1 || (start_num != -1 && city_node_flight_in[start_num].signal == 0))//起点不存在
	{
		cout << "fail to find cheapest path!start not exist!" << endl;
		return;
	}
	if (terminal_num == -1 || (terminal_num != -1 && city_node_flight_in[terminal_num].signal == 0))//终点不存在
	{
		cout << "fail to find cheapest path!terminal not exist!" << endl;
		return;
	}
	switch (*kind)
	{
	case '0'://train
		min = 999;
		S[start_num] = -1;
		dist[start_num] = 0;
		for (i = 0; i < city_total_num; i++)	//初始化数组
		{
			if (city_node_train_in[i].signal == 0)	//被删除城市
			{
				S[i] = -1;
				dist[i] = 999;
			}
			if (city_node_train_in[i].signal == 1)	
			{
				S[i] = 0;
				path[i] = start_num;
				dist[i] = GetWeigh(start_num,i,0);
			}
		}
		for (i = 0; i < current_city_num - 1; i++)	//加入current_city
		{
			for (j = 0; j < city_total_num && city_node_train_in[i].signal == 1; j++)
			{
				if (dist[j] < min)
				{
					min = dist[j];
					near = j;
				}
			}
			S[near] = -1;
			for (j = 0; j < city_total_num && city_node_train_in[i].signal == 1 && S[j] != -1; j++)
			{
				if (dist[near] + GetWeigh(near, j, 0) < dist[j])
				{
					dist[j] = dist[near] + GetWeigh(near, j, 0);
					path[j] = near;
				}
			}
		}
		//输出
		i = terminal_num;
		int min_price;
		while(i!=start_num)
		{
			min_price = 999;
			p = city_node_train_out[path[i]].adj;
			while (p != NULL)
			{
				if (p->terminal == i && p->price < min_price)
				{
					node = p;
					min_price = p->price;
				}
				p = p->next;
			}
			s.push(*node);
			i = path[i];
		}
		min_price = 999;
		p = city_node_train_out[start_num].adj;
		while (p != NULL)
		{
			if (p->terminal == i && p->price < min_price)
			{
				node = p;
				min_price = p->price;
			}
			p = p->next;
		}
		cout << "***   path    *********************************************************" << endl;
		cout << "start from: " << city_node_train_out[node->start].city_name << "\t"
			"to: " << city_node_train_out[node->terminal].city_name << "\t"
			"price is: " << node->price << endl;
		while (!s.empty())
		{
			p = &s.top();
			s.pop();
			cout << "start from: " << city_node_train_out[p->start].city_name << "\t"
				"to: " << city_node_train_out[p->terminal].city_name << "\t"
				"price is: " << p->price << endl;
		}
		break;
	case '1':
		min = 999;
		S[start_num] = -1;
		dist[start_num] = 0;
		for (i = 0; i < city_total_num; i++)	//初始化数组
		{
			if (city_node_flight_in[i].signal == 0)	//被删除城市
			{
				S[i] = -1;
				dist[i] = 999;
			}
			if (city_node_flight_in[i].signal == 1)
			{
				S[i] = 0;
				path[i] = start_num;
				dist[i] = GetWeigh(start_num, i, 0);
			}
		}
		for (i = 0; i < current_city_num - 1; i++)	//加入current_city
		{
			for (j = 0; j < city_total_num && city_node_flight_in[i].signal == 1; j++)
			{
				if (dist[j] < min)
				{
					min = dist[j];
					near = j;
				}
			}
			S[near] = -1;
			for (j = 0; j < city_total_num && city_node_flight_in[i].signal == 1 && S[j] != -1; j++)
			{
				if (dist[near] + GetWeigh(near, j, 0) < dist[j])
				{
					dist[j] = dist[near] + GetWeigh(near, j, 0);
					path[j] = near;
				}
			}
		}
		//输出
		i = terminal_num;
		while (i != start_num)
		{
			min_price = 999;
			p = city_node_flight_out[path[i]].adj;
			while (p != NULL)
			{
				if (p->terminal == i && p->price < min_price)
				{
					node = p;
					min_price = p->price;
				}
				p = p->next;
			}
			s.push(*node);
			i = path[i];
		}
		min_price = 999;
		p = city_node_flight_out[start_num].adj;
		while (p != NULL)
		{
			if (p->terminal == i && p->price < min_price)
			{
				node = p;
				min_price = p->price;
			}
			p = p->next;
		}
		cout << "***   path    *********************************************************" << endl;
		cout << "start from: " << city_node_flight_out[node->start].city_name << "\t"
			"to: " << city_node_flight_out[node->terminal].city_name << "\t"
			"price is: " << node->price << endl;
		while (!s.empty())
		{
			p = &s.top();
			s.pop();
			cout << "start from: " << city_node_flight_out[p->start].city_name << "\t"
				"to: " << city_node_flight_out[p->terminal].city_name << "\t"
				"price is: " << p->price << endl;
		}
		break;
	default:
		cout << "can't find!!" << endl;
		break;
	}
	return;
}

void find_fastest()
{

}

int main()
{

	char func[20];
	while (*func!='9')
	{
		cout << "******************************************************************************************" << endl;
		cout << "please choose the function:" << endl;
		cout << "1 -> add city\t\t\t 2 -> delete city\t 3 -> add city information\n"
			"4 -> delete city information\t 5 -> print schedule\t 6 -> find cheapest path\n"
			"7 -> find fastest path\t (enter 9 to stop the program)\n";
		cin.getline(func,20);
		switch (*func)
		{
		case '1':add_city();
			break;
		case '2':delete_city();
			break;
		case '3':add_city_info();
			break;
		case '4':delete_city_info();
			break;
		case '5':print_schedule();
			break;
		case '6':find_cheapest();
			break;
		case '7':find_fastest();
			break;
		case '9':cout << "exit!";
			return 0;
			break;
		default:cout << "wrong input";
			continue;
		}
	}
	return 0;

}
