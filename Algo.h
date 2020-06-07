#include <iostream>
#include "Input.h"
using namespace::std;


class Algo
{

private:
int ROWCnt[9]={0};//每行、列、宫里非空的数
int COLCnt[9]={0};
int PALCnt[9]={0};
int PALnum;
int WinCnt=0;

        int PalaceNum(int& _row,int& _col);


public:
        bool Logic(Input* & input);//新增遍历判断函数，一是弥补代码的严谨性随机性，二是防止bug玩法的出现

        void Check(Input* & input,Scene& effect);


};
