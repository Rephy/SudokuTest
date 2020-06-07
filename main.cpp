#include "Scene.cpp"
#include "Input.cpp"
#include "Algo.cpp"
#include<cstdlib>
#include<ctime>

int main(){
srand((int)time(0));
cout<<"\033c";//清屏
int random=rand()%6;
int table[9][9];
for(int i=0;i<=9;i++)
{
	for(int j=0;j<=9;j++)
	{
		table[i][j]=InitNumbers[random][i][j];
	}
}
		

Scene scene;
Algo exam;


Input* pinput=new Input;//创建对象指针

scene.GameBegin();
sleep (5);//等待输入游戏开始信号，可以调用read函数
	char c;//存储输入的指令
	int  d;//存储输入的难度
	cin>>d;//1=easy,2=normal,3=hard
	switch(d){
	case 1: d=30 ;break;
	case 2: d=40 ;break;
	case 3: d=60 ;break;
	}
        scene.Print(table,d);//待设置游戏开始和退出控制
	pinput->showcursor();//需先显示光标，才能初始化row和col的值，否则会有bug

             

	for(int i=0;i<200;++i){//测试用，只接收前50个指令，之后程序会结束
		c=read();//
		switch(c){
			//W,A,S,D控制光标上下左右			
			case'W':case'w':
			pinput->up();
			pinput->showcursor();
			continue;
			case'A':case'a':
			pinput->left();
			pinput->showcursor();
			continue;
			case'S':case's':
			pinput->down();
			pinput->showcursor();
			continue;
			case'D':case'd':
			pinput->right();
			pinput->showcursor();
			continue;

                        case 32://空格键进入输入模式
                        pinput->InsideMove();
                        if(!exam.Logic(pinput))
                        pinput->Wrong();
                        exam.Check(pinput,scene);
                        continue;
			case 27://ESC键退出游戏
			cout<<"\033c";//清屏
			exit(1);
			default:continue;

			
                }

        }
			

delete pinput;

return 0;
}

