#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<ctime>

struct Player{
	char hand[7] ={'0'}; //拿牌第一张牌为hand[1]
	char hand2[7] ={'0'};//拿牌第一张牌为hand[1] 分牌牌堆
	int onhand = 0;		 //手牌数
	int splithand =0;    //手牌数 分牌牌堆
	int chips;			 //赌金 
	double outchips1;		 //赌注(手牌)
	double outchips2;		 //赌注(分牌) 
};//玩家
	
	struct Dealer{
	char hand[7] ={'0'};//拿牌第一张牌为hand[1]
	int onhand = 0;	    //手牌数
};//庄家

struct Deck{
		char face[52]={'A','2','3','4','5','6','7','8','9','T','J','Q','K',
					'A','2','3','4','5','6','7','8','9','T','J','Q','K',
					'A','2','3','4','5','6','7','8','9','T','J','Q','K',
					'A','2','3','4','5','6','7','8','9','T','J','Q','K'};//牌初始化，T为10 
	bool status[52]={0};//牌堆抽取状态，0为未抽到。 
}deck; //牌堆初始化


void start();//输出一个ascii的标题
void help();//玩家帮助
int input();// 输入检测 (0)help-打开帮助 (1)p-停牌 (2)h-要牌 (3)s-分牌  (4)d -倍注  -1 无效指令
char draw();//抽牌函数 
int sum(char hand[],int handnum);//计算手牌和
bool chipcheck(Player player);//赌注检测函数 0为非负 
void show(char card[],int num);//展示手牌
int value(char a);//牌面值检测
int judge(int Psum,int Dsum);//胜负判断
int Konami();