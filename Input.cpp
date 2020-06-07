#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "Input.h"
using namespace::std;


Input::Input(void)
{
	cursor.x=4;
	cursor.y=4;//光标居中
        InputIdx=false;//
        InsideCur=0;//0,1,2三位
}

char read(void){//读取一个字符
	char c;
	static struct termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	system("stty -echo");

	c=getchar();//读入一个字符，不显示在屏幕上

	system("stty echo");
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return c;//返回其ASCLL码
}



void Input::up(void){	//光标逻辑位置移动
	cursor.y=(cursor.y+8)%9;}
void Input::down(void){	//可以跨边界
	cursor.y=(cursor.y+1)%9;}
void Input::left(void){ //如从(0,5)按左会到(8,5)
	cursor.x=(cursor.x+8)%9;}
void Input::right(void){
	cursor.x=(cursor.x+1)%9;}

void Input::showcursor(void){//将光标逻辑位置转换为实际位置并移动光标
        //row和col已调整为数据成员
	row=cursor.y*2+2;
	switch(cursor.x){
		case 0:col=2;break;
		case 1:col=7;break;
		case 2:col=12;break;
		case 3:col=16;break;
		case 4:col=21;break;
		case 5:col=26;break;
		case 6:col=30;break;
		case 7:col=35;break;
		case 8:col=40;break;
	}
	//公式由棋盘的格式确定
	printf("\033[%d;%dH",row,col);
}


void Input::showcursor(const int& _y,const int& _x){//重载了这个函数
        int _row,_col;
	_row=_y*2+2;
	switch(_x){
		case 0:_col=2;break;
		case 1:_col=7;break;
		case 2:_col=12;break;
		case 3:_col=16;break;
		case 4:_col=21;break;
		case 5:_col=26;break;
		case 6:_col=30;break;
		case 7:_col=35;break;
		case 8:_col=40;break;
		case 9:_col=44;break;
		case 10:_col=48;break;
		case 11:_col=52;break;
	}
	//公式由棋盘的格式确定
	printf("\033[%d;%dH",_row,_col);
}




void Input::InsideMove(void){
        InputIdx=!InputIdx;
        char x;
        while(InputIdx){
                x=read();
		switch(x){			
			case'A':case'a':
			InsideCur=(InsideCur+2)%3;
			break;
			case'D':case'd':
			InsideCur=(InsideCur+1)%3;
			break;

                        case 32://空格键退出输入模式
                        InputIdx=!InputIdx;
                        InsideCur=0;//下次进入时，重新定位到第一位数
                        break;
                        case 'L':case'l'://L键删除输入过的一位
                        if(Numbers[cursor.y][cursor.x].canErased[InsideCur]==true){
                        std::cout<<"\033[92;1m"<<"_";//重新打印空格，并更改存储的信息
                        Numbers[cursor.y][cursor.x].bit[InsideCur]='_';
                        Numbers[cursor.y][cursor.x].canErased[InsideCur]=false;
                        }
                        break;

                        case'J':case'j'://J键选中当前位置，并填0
                        if(Numbers[cursor.y][cursor.x].bit[InsideCur]=='_'){//如果这个位置是空的可填入
                        std::cout<<"\033[37;1m"<<"0";
                        Numbers[cursor.y][cursor.x].bit[InsideCur]='0';//并把该位的内容改为0
                        Numbers[cursor.y][cursor.x].canErased[InsideCur]=true;//更改了内容后，就说明这一位可以被擦除了
                        InsideCur=(InsideCur+1)%3;
                        }
                        break; 
			case'K':case'k'://K键选中当前位置，并填1
                        if(Numbers[cursor.y][cursor.x].bit[InsideCur]=='_'){
                        std::cout<<"\033[37;1m"<<"1";
                        Numbers[cursor.y][cursor.x].bit[InsideCur]='1';
                        Numbers[cursor.y][cursor.x].canErased[InsideCur]=true;
                        InsideCur=(InsideCur+1)%3;
                        }
                        break;
			default : continue;
                       
                }
        printf("\033[%d;%dH",row,col+InsideCur);//接受输入后，显示光标位置
        }
//退出输入模式后，调用Init.cpp中的Logic函数 遍历判断
//此时无输入，所以逻辑坐标是静止的
}



void Input::Wrong(void){                   
          for(int k=0;k<3;++k){//进行一次重新打印，产生红色的错误提醒
             if(Numbers[cursor.y][cursor.x].canErased[k]==true)
                std::cout<<"\033[91;1m"<<Numbers[cursor.y][cursor.x].bit[k];//把该位标为红色
             else
                std::cout<<"\033[92;1m"<<Numbers[cursor.y][cursor.x].bit[k];//正常打印该位为绿色              
          }
          printf("\033[%d;%dH",row,col);

}
