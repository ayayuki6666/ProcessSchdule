// PCBTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<cstring>
#include<algorithm>
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
      bool operator<(const PCB& b)
      {
          return this->priority > b.priority;                   //“<”运算符重载优先数算法使用
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

void RR(PCB T[])
{
    PCB temp,Tflag;
    const int Time = 2;
    int count = 0, flag = 0;
    Tflag = T[0];
    while (true) {
        if (T[0].rest - Time > 0)
        {   
            T[0].state = 'R';
            cout << "Name\tCPUtime\tNeedTime\tCount\tstate\tround" << endl;
            for (int i = 0; i < 5; i++)
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
            for (int i = 0; i < 5; i++)
            {
                T[i].RRinfoShow();
                cout << "2" << endl;
            }
            T[0].rest = 0;
            T[0].cputime = T[0].require;
            T[0].state = 'F';
            T[0].count++;
            count++;
            flag = 1;
        }
        if (flag == 1)
        {
            cout << "就绪队列:";
            for (int i = 0; i < 5; i++)
            {
                if (T[i].state == 'W')
                    cout << T[i].name << "\t";
            }
            cout << endl << "完成队列:";
            for (int i = 0; i < 5; i++)
            {
                if (T[i].state == 'F')
                    cout << T[i].name << "\t";
            }
            flag = 0;
            if (T[0].state == 'R')
                T[0].state = 'W';
            cout << endl << endl;
        }
        temp = T[0];
        for (int i = 0; i < 4; i++)
        {
            T[i] = T[i + 1];
        }
        T[4] = temp;
        if (count == 5 && strcmp(T[0].name,Tflag.name) == 0)
            break;
    }
    cout << "Name\tCPUtime\tNeedTime\tCount\tstate\tround" << endl;
    for (int i = 0; i < 5; i++)
    {
        T[i].RRinfoShow();
        cout << "2" << endl;
    }
    cout << "就绪队列:";
    for (int i = 0; i < 5; i++)
    {
        if (T[i].state == 'W')
            cout << T[i].name << "\t";
    }
    cout << endl << "完成队列:";
    for (int i = 0; i < 5; i++)
    {
        if (T[i].state == 'F')
            cout << T[i].name << "\t";
    }
    flag = 0;
    if (T[0].state == 'R')
        T[0].state = 'W';
}

int main()
{
    char a[5] = "a1", b[5] = "a2",c[5]="a3",d[5]="a4",e[5]="a5";
    PCB an(a,3),bn(b,2),cn(c,4), dn(d,2),en(e,1),T[5];
    T[0] = an,T[1]=bn,T[2]=cn,T[3]=dn,T[4]=en;
    //RR(T);
    cout << sizeof(T) / sizeof(T[0]);
}
