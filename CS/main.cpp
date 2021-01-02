#include<iostream>
#include<stdlib.h>
#include<vector>
#include<queue>
#include <fstream>
#include <iostream>
#include <string.h>
#define MAX 1000
#define LENG 20
using namespace std;

//ʹ���ڽӱ�,�ֱ��Ƿɻ����ڽӱ�&���ڽӱ��𳵵��ڽӱ�&���ڽӱ�
struct shift				//�����Ϣ
{
	char kind;				//0 is train,1 is flight
	char start[LENG];
	char terminal[LENG];
	char start_time[LENG];
	char arrival_time[LENG];
	int price;
	struct shift* next;		
};

struct city
{
	char city_name[LENG];	
	int signal;				//���signal��0��˵���Ѿ���ɾ���ˣ�signal��1˵���������ĳ���
	struct shift* adj;		
};

city city_node_flight_in[MAX];
city city_node_flight_out[MAX];
city city_node_train_in[MAX];
city city_node_train_out[MAX];
int city_total_num;				//��������


int find_city(char name[])	//if ���ڣ������Ӧ���±꣬�������-1
{
	int i;
	for (i = 0; i < city_total_num; i++)
	{
		if (!strcmp(name, city_node_flight_in[i].city_name))
			return i;
	}

	return -1;
}

//�����
void add_city()
{
	char name[20];
	cout << "enter a city:" << endl;
	cin.getline(name, 20);
	cout << "The city is:" << name << endl;
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
		cout << "succeed to add! The number of city is" << city_total_num << endl;
		return;
	}
	if (city_num == -1 && city_total_num == MAX)//�ռ�����
	{
		cout << "failed to add!! No enough space!" << endl;
		return;
	}
	else
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
		cout << "succeed to add!! The number of city is " << city_total_num << endl;
		cout << name << endl;
		
		return;
	}
	
		
}
//�����
void delete_city()
{
	cout << "please enter the name of city to delete:"<<endl;
	char name[LENG];
	cin.getline(name, LENG);
	int city_num = find_city(name);
	if (city_num == -1)//������
	{
		cout << "failed to delete!not exist!" << endl;
		return;
	}
	if (city_num != -1 && city_node_flight_in[city_num].signal == 0)//����ɾ��
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
		cout << "succeed to delete! " << city_total_num << endl;
		return;
	}
	
}

void add_city_info()
{
	shift* info;
	info = new shift();
	cout << "adding city information:" << endl;
	cout << "please enter the kind(0 is train,1 is flight):" << endl;
	cin.getline(&info->kind,2);
	cout << "please enter the start:" << endl;
	cin.getline(info->start, LENG);
	cout << "please enter the terminal:" << endl;
	cin.getline(info->terminal, LENG);
	cout << "please enter the start time:" << endl;
	cin.getline(info->start_time, LENG);
	cout << "please enter the arrival time:" << endl;
	cin.getline(info->arrival_time, LENG);
	cout << "please enter the price:" << endl;
	cin>>info->price;
	cin.ignore();
	info->next = NULL;
	int start_num; int terminal_num;
	start_num = find_city(info->start);
	terminal_num = find_city(info->terminal);
	if (start_num == -1 || (start_num != -1 && city_node_flight_in[start_num].signal == 0))//��㲻����
	{
		cout << "fail to add information!start not exist!" << endl;
		return;
	}
	if (terminal_num == -1 || (terminal_num != -1 && city_node_flight_in[terminal_num].signal == 0))//�յ㲻����
	{
		cout << "fail to add information!terminal not exist!" << endl;
		return;
	}
	shift* p;
	if (info->kind == '1')//flight
	{	//�������ĳ��ڽӱ���յ�����ڽӱ�
		p = city_node_flight_out[start_num].adj;
		if (p == NULL)
		{
			city_node_flight_out[start_num].adj = info;
		}
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = info;
		}
		p = city_node_flight_in[terminal_num].adj;
		if (p == NULL)
		{
			city_node_flight_in[terminal_num].adj = info;
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
	{	//�������ĳ��ڽӱ���յ�����ڽӱ�
		p = city_node_train_out[start_num].adj;
		if (p == NULL)
		{
			city_node_train_out[start_num].adj = info;
		}
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = info;
		}
		p = city_node_train_in[terminal_num].adj;
		if (p == NULL)
		{
			city_node_train_in[terminal_num].adj = info;
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

void delete_city_info()
{
	shift* info;
	info = new shift();
	cout << "adding city information:" << endl;
	cout << "please enter the kind(0 is train,1 is flight):" << endl;
	cin >> info->kind;
	cout << "please enter the start:" << endl;
	cin.getline(info->start, LENG);
	cout << "please enter the terminal" << endl;
	cin.getline(info->terminal, LENG);
	cout << "please enter the start time:" << endl;
	cin.getline(info->start_time, LENG);
	cout << "please enter the arrival time:" << endl;
	cin.getline(info->arrival_time, LENG);
	cout << "please enter the price:" << endl;
	cin >> info->price;
}

//�����
void print_schedule()	//����������ƣ���ӡ�ɸó��г����������г�·���Լ��ɻ���
									//������Ϣ
{
	cout << "please enter the name of city to print schedule:"<<endl;
	char name[LENG];
	cin.getline(name, LENG);
	int city_num = find_city(name);
	//������
	if (city_num == -1)
	{
		cout << "failed to print!not exist!" << endl;
		return;
	}
	//����ɾ��
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
				cout << "start:" << p->start << "\t" << "terminal:" << p->terminal << "\t" << "start time:" << p->start_time << "\t"
					<< "arrival time" << p->arrival_time << "\t" << "price:" << p->price << "\t" << endl;
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
				cout << "start:" << p->start << "\t" << "terminal:" << p->terminal << "\t" << "start time:" << p->start_time << "\t"
					<< "arrival time" << p->arrival_time << "\t" << "price:" << p->price << "\t" << endl;
				p = p->next;
			}
		}
	}
	return;
}

void find_cheapest()
{
	char kind;
	char start_city[20];
	char terminal_city[20];
	cout << "please enter the kind(0 is train,1 is flight):" << endl;
	cin.getline(&kind, 2);
	cout << "please enter the start:" << endl;
	cin.getline(start_city, LENG);
	cout << "please enter the terminal:" << endl;
	cin.getline(terminal_city, LENG);
	int start_num; int terminal_num;
	start_num = find_city(start_city);
	terminal_num = find_city(terminal_city);
	if (start_num == -1 || (start_num != -1 && city_node_flight_in[start_num].signal == 0))//��㲻����
	{
		cout << "fail to find cheapest path!start not exist!" << endl;
		return;
	}
	if (terminal_num == -1 || (terminal_num != -1 && city_node_flight_in[terminal_num].signal == 0))//�յ㲻����
	{
		cout << "fail to find cheapest path!terminal not exist!" << endl;
		return;
	}



}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	char func[20];
	while (*func!='9')
	{
		cout << "******************************************************************************************" << endl;
		cout << "please choose the function:" << endl;
		cout << "1 -> add city\t\t\t 2 -> delete city\t 3 -> add city information\n4 -> delete city information\t 5 -> print schedule\t 6 -> find_fastest\n7 -> find_cheapest\t (enter 9 to stop the program)\n";
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
		case '6':
		case '7':
		case '9':cout << "exit!";
			return 0;
			break;
		default:cout << "wrong input";
			continue;
		}
	}
	return 0;

}
