//Author:绫雪 时间:2021/11/20 邮箱:2239301685@qq.com/yaolin6666@gmail.com 
//操作系统实验作业:进程调度
//RR轮转法 PR优先数法
#include <iostream>
#include<cstring>
#include<algorithm>
#include<windows.h>
using namespace std;
class PCB {
public:char name[5];
      int priority;
      int require;
      int cputime;
      int rest;
      int count;                                                 //计数 cpu分配次数
      char state;
      PCB(void);
      PCB(char a[5], int b);
      void RRinfoShow(void);
      void PRinfoShow(void);
      bool operator<(const PCB& b)
      {       
          if (this->priority == b.priority)
              return this->rest < b.rest;
          else
              return this->priority > b.priority;           
          //“<”运算符重载优先数算法使用
      }
};
PCB::PCB(void)
{
    strcpy_s(name, "NULL");
    priority = 50;
    rest = 0;
    cputime = 0;
    require = 0;
    count = 0;
    state = 'N';
}
PCB::PCB(char a[5], int b)
{
    strcpy_s(name, a);
    priority = 50-b;
    require = b;
    cputime = 0;
    rest = require;
    count = 0;
    state = 'W';
}

void PCB::RRinfoShow(void)
{
    cout << name << "\t" << cputime << "\t" << rest << "\t\t" << count << "\t" << state << "\t";
}

void PCB::PRinfoShow(void)
{
    cout << name << "\t" << cputime << "\t" << rest << "\t\t" << count << "\t" << state <<"\t" << priority << endl;
}

void RR(PCB T[],int size)
{
    PCB temp, Tflag;
    const int Time = 2;
    int count = 0, flag = 0;
    char F[10][5];
    Tflag = T[0];
    while (true) {
        if (T[0].rest - Time > 0)
        {
            T[0].state = 'R';
            cout << "Name\tCPUtime\tNeedTime\tCount\tstate\tround" << endl;
            for (int i = 0; i < size; i++)
            {
                T[i].RRinfoShow();
                cout << "2" << endl;
            }
            T[0].rest -= Time;
            T[0].cputime += Time;
            T[0].count++;
            flag = 1;
        }
        else if (T[0].state != 'F')
        {
            T[0].state = 'R';
            cout << "Name\tCPUtime\tNeedTime\tCount\tstate\tround" << endl;
            for (int i = 0; i < size; i++)
            {
                T[i].RRinfoShow();
                cout << "2" << endl;
            }
            T[0].rest = 0;
            T[0].cputime = T[0].require;
            
            flag = 1;
        }
        if (flag == 1)
        {
            cout << "就绪队列:";
            for (int i = 1; i < size; i++)
            {
                if (T[i].state == 'W')
                    cout << T[i].name << "\t";
            }
            cout << endl << "完成队列:";
            for (int i = 0; i < count; i++)
            {
                cout << F[i] << "\t";
            }
            flag = 0;
            if (T[0].state == 'R')
                T[0].state = 'W';
            if (T[0].rest == 0) {
                T[0].state = 'F';
                T[0].count++;
                strcpy_s(F[count], T[0].name);
                count++;
            }
            cout << endl << endl;
        }
        temp = T[0];
        for (int i = 0; i < size-1; i++)
        {
            T[i] = T[i + 1];
        }
        T[size-1] = temp;
        if (count == size && strcmp(T[0].name, Tflag.name) == 0)
            break;
    }
    cout << "Name\tCPUtime\tNeedTime\tCount\tstate\tround" << endl;
    for (int i = 0; i < size; i++)
    {
        T[i].RRinfoShow();
        cout << "2" << endl;
    }
    cout << "就绪队列:";
    for (int i = 0; i < size; i++)
    {
        if (T[i].state == 'W')
            cout << T[i].name << "\t";
    }
    cout << endl << "完成队列:";
    for (int i = 0; i < count; i++)
    {
        cout << F[i] << "\t";
    }
    flag = 0;
    if (T[0].state == 'R')
        T[0].state = 'W';

}


void PR(PCB T[], int size)
{
    int count = 0,cursors=size,flag=0;
    PCB temp;
    const int Time = 2;
    char F[10][5];        
    while (true) {
        sort(T, T +cursors );
        sort(T + cursors, T+size);
        if (T[0].rest - Time > 0)
        {
            T[0].state = 'R';
            cout << "Name\tCPUtime\tNeedTime\tCount\tstate\tpriority" << endl;
            for (int i = 0; i < size; i++)
            {
                T[i].PRinfoShow();
            }
            T[0].rest -= Time;
            T[0].cputime += Time;
            T[0].count++;
            T[0].priority -= 3;
            T[0].state = 'W';
        }
        else if (T[0].state != 'F')
        {
            cout << "Name\tCPUtime\tNeedTime\tCount\tstate\tpriority" << endl;
            T[0].state = 'R';
            for (int i = 0; i < size; i++)
            {
                T[i].PRinfoShow();
            }
            T[0].rest = 0;
            T[0].cputime = T[0].require;
        }
        cout << "就绪队列:";
        for (int i = 1; i < size; i++)
        {
            if (T[i].state == 'W')
                cout << T[i].name << "\t";
        }
        cout << endl << "完成队列:";
        for (int i = 0; i < count; i++)
        {
            cout << F[i] << "\t";
        }
        cout << endl<<endl<<endl;
        if (T[0].rest == 0) {
            T[0].state = 'F';
            T[0].count++;
            strcpy_s(F[count], T[0].name);
            count++;
            cursors--;
            flag = 1;
        }
        if (T[0].state == 'F')
        {
            temp = T[0];
            for (int i = 0; i < size-1; i++)
            {
                T[i] = T[i + 1];
            }
            T[size-1] = temp;
        }
        if (count==size)
            break;
    }
    sort(T, T + size);
    
    cout << "Name\tCPUtime\tNeedTime\tCount\tstate\tpriority" << endl;
    for (int i = 0; i < size; i++)
    {
        T[i].PRinfoShow();
    }
    cout << "就绪队列:";
    for (int i = 0; i < size; i++)
    {
        if (T[i].state == 'W')
            cout << T[i].name << "\t";
    }
    cout << endl << "完成队列:";
    for (int i = 0; i < count; i++)
    {
        cout << F[i] << "\t";
    }
    cout << endl;
}

int main()
{
    int size=0;
    char name[5];
    int need,i=0;
    PCB T[25],t;
    //cout << "input the number of Progress" << endl;
    //cin >> size;                                                                      //进程数量最大支持25
    //size = 5;
    cout << "input name and needtime"<<endl;
    while (cin >> name)
    {
        cin >> need;
        PCB t(name, need);
        T[i] = t;
        size++;
        i++;
        if (size > 10)
        {
            size = 10;
            break;
        }
    }

    /*char a[5] = "a1", b[5] = "a2", c[5] = "a3", d[5] = "a4", e[5] = "a5";
    PCB an(a,3),bn(b,2),cn(c,4), dn(d,2),en(e,1),T[5];
    //T[0] = an,T[1]=bn,T[2]=cn,T[3]=dn,T[4]=en;
    //size = sizeof(T) / sizeof(T[0]);*/                                                //测试用例



    //RR(T, size);                                                       //RR启动(时间片)
    PR(T, size);                                                      //PR启动(优先数算法)
    //Sleep(5000);
}
