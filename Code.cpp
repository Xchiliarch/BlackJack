#include<iostream>
#include<stdlib.h>
#include<cstring>
#include"rules.h" 
#include<ctime>
#include<windows.h>
#include<conio.h>
using namespace std;
Player player;
Dealer dealer;
void start(){
	cout<<"______ _            _    _            _\n";   
	cout<<"| ___ \\ |          | |  (_)          | |\n";  
	cout<<"| |_/ / | __ _  ___| | ___  __ _  ___| | __\n";
	cout<<"| ___ \\ |/ _` |/ __| |/ / |/ _` |/ __| |/ /\n";
	cout<<"| |_/ / | (_| | (__|   <| | (_| | (__|   < \n";
	cout<<"\\____/|_|\\__,_|\\___|_|\\_\\ |\\__,_|\\___|_|\\_\\ \n";
	cout<<"                       _/ |                \n";
	cout<<"                      |__/                 \n";
}

void help(){
	
cout<<"            _\n";           
cout<<"           | | \n";         
cout<<" _ __ _   _| | ___  ___ \n";
cout<<"| '__| | | | |/ _ \\/ __|\n";
cout<<"| |  | |_| | |  __/\\__ \\ \n";
cout<<"|_|   \\__,_|_|\\___||___/\n";

	cout<<"\n本游戏使用一副牌进行，游戏结束即重新洗牌开局\n\n";Sleep(500);

	cout<<"玩家独自与庄家进行游戏，初始筹码为200，筹码用完游戏结束\n";
	cout<<"游戏开局时，庄家给玩家发2张牌，庄家自己发一张明牌（玩家可看见），一张暗牌（玩家无法看见）\n";
	cout<<"获胜条件：结算时，玩家的点数比庄家更接近21点且未爆牌，或庄家爆牌\n\n";Sleep(500);
	
	cout<<"黑杰克：玩家手中的牌为一张10点一张A，此时玩家直接赢下游戏，获得1.5倍赌注\n";
	cout<<"庄家将在17点停牌，并使用软17原则（指初始两张牌点数之和大于17且有一张为A）\n\n";Sleep(500);

	cout<<"发牌结束后，玩家根据局势可选择要牌（hit），分牌（split）,停牌（stand），倍注（double），保险(insurance)与投降(Surrender)\n" ;
	cout<<"要牌：庄家再发一张牌给玩家。\n";
	cout<<"分牌：当玩家初始发的两张牌点数相同时可以分牌，再下一份相同的赌注，两副牌各再发一张补齐，玩家先后对两副牌进行操作，计算胜负（此时无黑杰克，仅看做普通21点）\n";
	cout<<"停牌：玩家停止要牌，进入庄家操作阶段。";
	cout<<"倍注：当玩家手中不是黑杰克时，该操作将会翻倍赌注，然后抽一张牌后停牌";
	cout<<"保险：当庄家明牌为A时，可花赌注的一半购买保险，若庄家黑杰克，玩家获得保险的两倍，即赌注。若不是，则继续游戏，保险不退。\n\n";Sleep(500);

	cout<<"玩家根据局势可持续要牌或停牌直到\n";
	cout<<"1.爆牌（指玩家手中牌点数之和大于21）\n2.等于21（玩家直接停牌）\n3.拿到5张牌时仍未爆牌，判定玩家胜利，结束游戏\n\n";Sleep(500);

	cout<<"牌点数说明：\n 2~10 为牌面点数，JQK为10点，A为1点或11点（取决于手牌，以不爆牌的点数作为其点数。例如：一张5一张A为16，两张8一张A为17\n"; 
	cout<<"玩家操作说明：\n 输入p 分牌 ,h 要牌,s 停牌, 倍注，i 保险,sur 投降（区分大小写）\n";Sleep(500);
}

int input(){
	char a[7];
	char list[6][7]={"help","p","h","s","d","sur"};
	cin>> a;
	for(int i=0;i<=7;i++){
		if(i ==7){
			return -1;
			break;
		}
		if(strcmp(a,list[i]) ==0){
			return i;
			break;	
		}
	}
}
// 输入检测 (0)help-打开帮助 (1)p-停牌 (2)h-要牌 (3)s-分牌  (4)d -倍注  (5)sur-投降  (-1)- 无效指令

char draw(){
	int tar =rand()%52;
	for(;;){
		if(deck.status[tar] == 0)
			break;
		else
			tar =rand()%52;	
	}     
	return deck.face[tar];   //返回牌面 
	deck.status[tar]=1;		 //该牌抽取值更改 
}
//抽牌函数 

int sum(char hand[],int handnum){
	int sum=0,Anum=0;
	for(int i=1;i<=handnum;i++){
		if(hand[i]=='A')
			Anum++;
	}
	for(int i=1;i<=handnum;i++){
		if(hand[i]<=57){
			sum+=hand[i]-48;
		}
		else if(hand[i]>=74){
			sum+=10;
		}
		else{
			continue;
		}
	}
	if(Anum!=0){
		sum+=Anum;
		if(sum<=11){
			sum+=10;
		}
	}
	return sum;
}
//计算手牌和

bool chipcheck(Player player){
	if(player.chips-player.outchips1<0||player.outchips1<=0)
		return 1;
	else
		return 0;
} 
//赌注检测函数 0为非负 

void show(char card[],int num){
	cout<<"当前手牌：";
	for(int i=1;i<num;i++){
		if(card[i]=='T'){
			cout<<"10"<<",";
		}
		else	
			cout<<card[i]<<",";
	}
	if(card[num]=='T')
		cout<<"10";
	else
		cout<<card[num];
	cout<<" 牌面和"<<sum(card,num)<<endl;
}
//展示手牌

int value(char a){
	if(a<=57)
		return a-48;
	else
		return 10;
	
}
//牌面值检测

int judge(int Psum,int Dsum){
	if(Psum>21){
	cout<<"你输了\n";
	return 0;
	}
	if(Dsum>21&&Psum<=21){	
		cout<<"你赢了！\n";
		return 1;
	}
	if(Psum<=21&&Dsum<=21){
		if(Psum-Dsum>0){
		cout<<"你赢了！\n";
		return 1;
		}
		else if(Psum-Dsum==0){
			cout<<"打平了\n";
			return 2;
		}
		else{
			cout<<"你输了\n";
			return 0;
		}
	}
}
//胜负判断

int Konami(){
	int m=0;
	char a[10]={72,72,80,80,75,77,75,77,66,65};
	for(int i=0;i<10;i++){
		int ch;
		ch=getch();
		if(ch==0xE0){
			ch=getch();
			if(ch==a[i])
				m++;
			else{
				return 1;
				break;
			}
			
		}//方向键
		else{
			if(ch==a[i])
				m++;
			else if(ch!=49){
				return 1;
			}
			else
				return 0;
				
		}	
	}
	if(m==10)
		return 2;
	else
		return 1; 
}
//0 开始游戏  1 其他（退出） 2 konami秘籍 

int main(){ 
	player.chips = 200;//初始赌金 
	cout<<"输入1开始,输入其他键退出";
	switch(Konami()){
		case 0:break;
		case 1:exit(1);
		case 2:cout<<"\na29uYW1pJTIwY29kZSUyMGRldGVjZXRk\nExtra chips gained!\n";cout<<"  _____     \n /     \\    \n |() ()|   \n \\  ^  /    \n  |||||     \n  |||||     \n";player.chips=999999;
	}
	srand(time(NULL));//播种随机数，用于生成牌库顺序 
	cout<<"\n游戏开始\n";
	start();
	int status;//操作代码 0 输，1 赢，2 平,3 分牌游戏中,4 游戏中,5 投降输,6 五小龙 7玩家黑杰克 8 庄家黑杰克 9 双方黑杰克
	int playerdone =0;//玩家完成操作前为0，操作完成后变为1，庄家操作 
	Sleep(500);
	cout<<"输入help显示规则与操作，你可以在发完牌后输入help查看帮助\n" ;
	Sleep(200);

	while(player.chips>=0){
		int insurance=0;
		if(player.chips<=0){
			cout<<"没有足够资金！";
			break;
		}
		status =4;
		playerdone=0;
		cout<<"你的当前资金为";
		cout<<player.chips<<endl; //初始化游戏 
		cout<<"输入你的赌注";
		cin>>player.outchips1;
		while(chipcheck(player)){
			cout<<"赌注异常，请重新输入\n";
			cin.clear();cin.sync();
			cin>>player.outchips1;
		}
		cout<<"下注成功\n";
		player.chips-=player.outchips1;
		cout<<"发牌中";
		for(int i=0;i<3;i++){
			cout<<".";
			Sleep(100);
		}
		player.hand[++player.onhand]=draw();
		cout<<"\n你的第一张牌:";
		if(player.hand[player.onhand]=='T')
			cout<<"10"<<endl;
		else
			cout<<player.hand[player.onhand]<<endl;

		dealer.hand[++dealer.onhand]=draw();
		cout<<"庄家的第一张牌：***"<<endl;

		player.hand[++player.onhand]=draw();
		cout<<"你的第二张牌:";
		if(player.hand[player.onhand]=='T')
			cout<<"10"<<endl;
		else
			cout<<player.hand[player.onhand]<<endl;
		
		dealer.hand[++dealer.onhand]=draw();
		cout<<"庄家的第二张牌：";
		if(dealer.hand[dealer.onhand]=='T')
			cout<<"10"<<endl;
		else
			cout<<dealer.hand[dealer.onhand]<<endl;//发牌
		show(player.hand,player.onhand);
		cout<<endl;

		if(dealer.hand[dealer.onhand]=='A'){
			cout<<"庄家明牌为A，是否购买保险？输入Y购买，其他不购买(不区分大小写）（金额为";
			cout<<player.outchips1/2<<")\n";
			char a;
			cin>>a;
			if(a=='y'||a=='Y'){
				if(player.chips-player.outchips1/2>=0){
					insurance=player.outchips1/2;
					player.chips-=player.outchips1/2;
					cout<<"购买成功！";
				}
				else
					cout<<"玩家资金不足以购买！\n";
				
			}
			else
				cout<<"不购买保险，继续游戏\n";
		}

		if(sum(dealer.hand,dealer.onhand)==21&&sum(player.hand,player.onhand)!=21){
			playerdone=1;
			cout<<"庄家";
			show(dealer.hand,dealer.onhand);
			cout<<"庄家黑杰克！\n";
			status =8;
			if(insurance!=0){
				cout<<"玩家购买保险，双倍返还保险金！";
				player.chips+=2*insurance;
			}
		}
		if(sum(player.hand,player.onhand)==21&&sum(dealer.hand,dealer.onhand)!=21){
			playerdone=1;
			cout<<"玩家黑杰克！\n";
			status =7;
		}
		if(sum(player.hand,player.onhand)==21&&sum(dealer.hand,dealer.onhand)==21){
			playerdone=1;
			cout<<"双方均为黑杰克！\n";
			status =9;
		}
		while(playerdone!=1){
			if(sum(player.hand,player.onhand)>21){
				cout<<"已爆牌，你输了！\n";
				playerdone=1;
				break;
			}
			else if(sum(player.hand,player.onhand)==21){
				cout<<"玩家达到21点，停牌。\n";
				playerdone=1;
				break;
			}
			else if(player.onhand==5&&player.splithand==0){
				cout<<"5小龙！你赢了\n";
				playerdone =1;
				status=6;
				break;
			}
			cout<<"请选择你手牌的操作：p-停牌 ，h-拿牌，s-分牌（仅可用时），d-倍注,sur-投降（仅第一次操作时） help-打开帮助";
			switch(input()){
				case 0: help();break;
				case 1: playerdone =1;break;
				case 2: player.hand[++player.onhand]=draw();
						cout<<"你的第"<<player.onhand<<"张牌为"<<player.hand[player.onhand]<<endl;break;
				case 3: if(value(player.hand[1])==value(player.hand[2])&&status!=3){
									player.hand2[++player.splithand]=player.hand[2]  ; //将手上第二张牌分牌 
									player.hand[2]='0';			  	    //手上第二张牌设为0 
									player.onhand = player.splithand =1;//手牌数重设 
									player.hand[++player.onhand]=draw();			//手牌抽一张 ,手牌数+1 
									player.hand2[++player.splithand]=draw();		//分牌堆抽一张，分牌数+1 
									player.outchips2=player.outchips1;  //分牌赌注 
									player.chips -= player.outchips2;   //赌金修正
									status=3;
									break;	
								}
							else if(status==3){
								cout<<"不能多次分牌，请重试\n";
							break;
							}
							else{
								cout<<"不能分牌，请重试\n";
								break;
							}
				case 4: if(status==4&&player.onhand==2){
							player.hand[++player.onhand]=draw(); //抽1张牌 
							player.chips -= player.outchips1;//赌金修正 
							player.outchips1*=2; //倍注 
							playerdone=1;
							break;
						}
						else{
							cout<<"当前情况下无法倍注";
							break;
						}
						
				case 5: if(status==4&&player.onhand==2){
							playerdone=1;
							status=5;
							player.chips+=0.5*player.outchips1;
						}
						else
							cout<<"当前情况下无法投降\n";
						break;
				case -1:cout<<"无效命令，请重试\n";break;
			}
			show(player.hand,player.onhand);
		}//手牌堆操作
		int splitdone=0;
		while(status==3&&splitdone!=1){
			
			if(sum(player.hand2,player.splithand)>21){
				cout<<"已爆牌，你输了！\n";
				splitdone=1;
				break;
			}
			cout<<"分牌堆";
			show(player.hand2,player.splithand);
			cout<<"请选择你分牌堆的操作：p-停牌 ，h-拿牌，help-打开帮助";
			switch(input()){
				case 0: help();break;
				case 1: splitdone =1;break;
				case 2: player.hand2[++player.splithand]=draw();
						cout<<"你的第"<<player.splithand<<"张牌为"<<player.hand2[player.splithand]<<endl;break;
				case -1:cout<<"无效命令，请重试\n";break;
			}
		}//玩家操作环节
		
		if(playerdone==1){
			while(sum(dealer.hand,dealer.onhand)<17){
				cout<<"庄家";
				show(dealer.hand,dealer.onhand);
				cout<<endl;
				cout<<"抽取一张\n";
				dealer.hand[++dealer.onhand]=draw();
			}
			cout<<"庄家";
			show(dealer.hand,dealer.onhand);
			cout<<endl;
			int Psum=sum(player.hand,player.onhand);
			int Dsum=sum(dealer.hand,dealer.onhand);
			int Ssum=sum(player.hand2,player.splithand);
			if(status<5)
				status=judge(Psum,Dsum);
			
			switch(status){
				case 0:break;
				case 1:player.chips+=player.outchips1*2;player.outchips1=0;break;
				case 2:player.chips+=player.outchips1;player.outchips1=0;break;
				case 5:cout<<"玩家投降，返还一半赌注\n";break;
				case 6:player.chips+=player.outchips1*2;player.outchips1=0;break;
				case 7:player.chips+=player.outchips1*2.5;player.outchips1=0;break;
				case 8:break;
				case 9:player.chips+=player.outchips1;player.outchips1=0;break;
			}
			if(player.splithand!=0){
				status=judge(Ssum,Dsum);
				switch(status){
				case 0:break;
				case 1:player.chips+=player.outchips2*2;player.outchips2=0;break;
				case 2:player.chips+=player.outchips2;player.outchips2=0;break;
				}
			}
		}//庄家操作环节
		for(int i=1;i<=7;i++){
			player.hand[i]='0';
			player.hand2[i]='0';
			dealer.hand[i]='0';
		}//重置手牌
		player.onhand=0;
		player.splithand=0;
		dealer.onhand=0;
	}
	cout<<"游戏结束！";
	system("pause"); 
}