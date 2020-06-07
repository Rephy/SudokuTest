#ifndef _INPUT_H_
#define _INPUT_H_


char read(void);//输入函数

class Algo;

//输入判断类
class Input
{

friend class Algo;

public:
	Input(void);//构造函数

	void up(void);//光标位置控制
	void down(void);
	void left(void);
	void right(void);

	void showcursor(void);//输出光标位置
        void showcursor(const int& _y,const int& _x);

        void InsideMove(void);//内部输入模式
     
        void Wrong(void);

            
private:
	struct {int x;int y;} cursor;//光标逻辑位置

//代码调整部分：
	int row;//光标实际位置
	int col;//
        bool InputIdx;//是否为内部移动模式的标志
        int InsideCur;//新增：内部三位移动的光标

};
#endif


