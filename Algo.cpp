#include "Algo.h"


bool Algo::Logic(Input* & input){
                   
  int FilledIdx=3;
  bool WrongFlag=false;
  int Cnt=0;//记录相同的位数
  int i,j,k;

  PALnum=PalaceNum(input->cursor.y,input->cursor.x);

  int Comp=ROWCnt[input->cursor.y];
  ROWCnt[input->cursor.y]=0;//此处有略复杂的逻辑问题
 

  for(j=0;j<9;++j){//对行进行遍历
     for(k=0;k<3;++k){//对于一个数，比较每三位
        Cnt=0;
        if(Numbers[input->cursor.y][j].bit[k]=='_')
        --FilledIdx;
        else if(Numbers[input->cursor.y][input->cursor.x].bit[k]=='_')//如果遍历到的这个数有一位是空的
        break;//那就不比较并计入重复
        else if(input->cursor.x==j)//遍历到这个数本身，则不进行比较.否则会记为重复
        break;  
        else if(Numbers[input->cursor.y][input->cursor.x].bit[k]==Numbers[input->cursor.y][j].bit[k])
        ++Cnt;//记录下和另一个数相同的位数
     }
     if(FilledIdx==3)
     ++ROWCnt[input->cursor.y];
     if(Cnt==3)
     WrongFlag=true;//有相同的数则失败.
  }

  if(ROWCnt[input->cursor.y]<Comp){//当重新统计这一行的个数时，若比原先值小1
                                   //则说明一个原本填满的数被擦除了
  --COLCnt[input->cursor.x];
  --PALCnt[PALnum];  
  }
  else if(ROWCnt[input->cursor.y]>Comp){//若比原先多1，则说明新填满了一个数
  ++COLCnt[input->cursor.x];            //那么对应地：
  ++PALCnt[PALnum]; 
  }  

  if(WrongFlag)
  return false;

  for(i=0;i<9;++i){//对列进行遍历
     for(k=0;k<3;++k){
        Cnt=0;
        if(Numbers[input->cursor.y][input->cursor.x].bit[k]=='_')
        break;
        else if(input->cursor.y==i)
        break;  
        else if(Numbers[input->cursor.y][input->cursor.x].bit[k]==Numbers[i][input->cursor.x].bit[k])
        ++Cnt;
     }
     if(Cnt==3)
     return false;
  }


  //对宫进行遍历
  int tempy,tempx;
  tempy=PALnum/3;
  tempx=PALnum%3;
  tempy*=3;
  tempx*=3;

  for(i=0;i<3;++i){
     for(j=0;j<3;++j){
        for(k=0;k<3;++k){
           Cnt=0;
           if(Numbers[input->cursor.y][input->cursor.x].bit[k]=='_')
           break;
           else if(tempy==tempy+i&&tempx==tempx+j)
           break;  
           else if(Numbers[tempy+i][tempx+j].bit[k]==Numbers[tempy][tempx].bit[k])
           ++Cnt;
        }
        if(Cnt==3)
        return false;
     }
  }

  
  return true;

}




void Algo::Check(Input* & input,Scene& effect){

int ROW=input->cursor.y;
int COL=input->cursor.x;
int PAL=PalaceNum(input->cursor.y,input->cursor.x);


input->showcursor(ROW,9);
if(ROWCnt[ROW]==9)
        cout<<"\033[1;92m";
else
        cout<<"\033[0;90m";
cout<<effect.ROWeffect[ROW];


for(int line=0;line<3;++line){
input->showcursor(9+line,COL);
if(COLCnt[COL]==9)
        cout<<"\033[1;92m";
else
        cout<<"\033[0;90m";
cout<<effect.COLeffect[line*2][COL];

}


int tempy,tempx;
tempy=PAL/3;
tempx=PAL%3;
input->showcursor(tempy+9,tempx+9);
tempy=tempy*2;
if(PALCnt[PAL]==9)
        cout<<"\033[1;92m";
else
        cout<<"\033[0;90m";
cout<<effect.PALeffect[tempy][tempx];

input->showcursor();


for(int i=0;i<9;++i){
   WinCnt=0;
   if(ROWCnt[i]==9)
   ++WinCnt;
}
if(WinCnt==9)
  effect.GameWin();

}



int Algo::PalaceNum(int& _row,int& _col){
     int a=_row/3+1;
     int b=_col/3+1;
     return (a-1)*3+b-1;//宫的标号为0~8
}
