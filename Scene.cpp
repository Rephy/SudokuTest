#include "Scene.h"
#include<ctime>


int Scene::Print(int table[9][9],int d)
{

int value;
string temp;
char blank='_';


printf("\033[1;1H");

for(i=0;i<9;++i){

if(i%3==0)  //判断打印宫分隔线或行分隔线
cout<<"\033[92;1m"<<END2<<endl;
else
cout<<"\033[0;90m"<<END1<<endl; 



  for(j=0;j<9;++j){

     if(j%3==0)
        cout<<"\033[92;1m"<<"┊";//打印数字间的分隔符
     else
        cout<<"︲";

//先调用随机数生成函数，得到0~80里哪些数需要挖空
//而且，9不能挖空
//开局打印棋盘时，完成数字到二进制的转化
        value = table[i][j];
	temp = Binary[value-1];//temp是二进制的1位
//      if(blank(i,j))  blank函数名未定义，可更改。判断该数是否要挖空 
//如果这个数要挖空，再调用随机数生成函数，得到1~3位里哪几个位要挖空
//如010挖空为_1_,则 Numbers[i][j].bit1 = blank; bit3=blank;  blank为"_"
//且原本的010不需要存储，已设计遍历判断函数，后续根据一位是否为"_"来确定能否输入一个数


/*      else { // 不挖空则进行计数，每行、列非空的数加1
        ++ROWCnt[i-1];
        ++COLCnt[j-1];
        PALnum=PalaceNum(i,j);
        ++PALCnt[PALnum-1];
       }
*/
 
        for(k=0;k<3;++k){
	int r=rand()%100;
	if(r<=d && table[i][j]!=9)//25%概率挖空
	   {
	   Numbers[i][j].bit[k]=blank;
	   //Numbers[i][j].canErased[k]=true;
	   }
	else
           {
	   Numbers[i][j].bit[k]=temp[k];   
	   }
           cout<<"\033[92;1m"<<Numbers[i][j].bit[k];//屏幕上显示的是Numbers

           sleep (0.5);

        }


   }//第二层循环结束

cout<<"\033[92;1m"<<"┊";//打印右边界的分隔符



   cout<<"\033[0;90m"<<ROWeffect[i]<<endl;//打印灰色01串



}
//第一层循环结束，棋盘打印结束
//接着打印列特效和宫特效
cout<<"\033[92;1m"<<END2<<endl;


for(i=0;i<5;++i){

  for(j=0;j<9;++j){
  
       cout<<"\033[1;90m"<<COLeffect[i][j];

  }
  cout<<PALeffect[i][0]<<PALeffect[i][1]<<PALeffect[i][2]<<endl;

}//打印完成



return 0;
}




int Scene::Draw(){


int draw[7][54]={ 
{3,4,5,6,10,11,17,18,20,21,22,30,31,33,34,38,39,42,43,45,46,52,53},
{1,2,7,8,10,18,20,23,24,29,35,38,42,45,53},
{1,10,18,20,25,26,28,36,38,40,41,45,53},
{2,3,4,5,6,7,10,18,20,26,28,36,38,39,45,53},
{8,10,18,20,25,26,28,36,38,40,41,45,53},
{1,2,7,8,10,11,17,18,20,23,24,29,35,38,42,45,46,52,53},
{3,4,5,6,12,13,14,15,16,20,21,22,30,31,33,34,38,39,42,43,47,48,49,50,51}};


for(i=0;i<7;++i){
   for(j=0;j<54;++j){
       if(!draw[i][j])
       break;
       else
       temp=draw[i][j];
       UIscene[i+2][temp-1]='1';
   }
}

for(i=0;i<18;++i){
   for(j=0;j<54;++j){
       if(UIscene[i][j]=='1')
       cout<<"\033[1;92m"<<'1';
       else
       cout<<"\033[0;90m"<<'0';
   }
cout<<endl;
}


return 0;
}



void Scene::GameBegin(){

for(i=0;i<18;++i){
   for(j=0;j<54;++j){

       cout<<"\033[0;90m"<<'0';
       sleep (0.1);

   }

cout<<endl;
}

printf("\033[1;1H");

Draw();

string Help[3]={"0000000000000000000000W0A0S0D0000000000000000000000000",
                "00000000000000000000000Space00000000000000000000000000",
                "00000000000000000000000J0K0L00000000000000000000000000"};

string tempstr;
for(int i=0;i<3;i++){
    printf("\033[%d;1H",i+15);
    tempstr=Help[i];
    for(int j=0;j<54;j++){
         if(tempstr[j]=='0')
         cout<<"\033[0;90m";
         else
         cout<<"\033[1;92m";
         
         cout<<tempstr[j];
    }

}
printf("\033[1;1H");

}
            






void Scene::GameWin(){

for(i=0;i<16;++i){
   for(j=0;j<54;++j){

       cout<<"\033[1;92m"<<'0';
       sleep (0.1);

   }

cout<<endl;
}

printf("\033[1;1H");

Draw();

string Hint="00000000000000000000Y0O0U000W0O0N0!0000000000000000000";


printf("\033[15;1H");

    for(int i=0;i<54;++i){
         if(Hint[i]=='0')
         cout<<"\033[0;90m";
         else
         cout<<"\033[1;92m";
         
         cout<<Hint[i];
    }
printf("\033[1;1H");
}




