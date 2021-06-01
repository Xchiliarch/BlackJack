#BlackJack
This is a Blackjack game based on C++ without GUI！
##features
- Full rules of Blackjack!
- No GUI(if it is a feature)
- An easter egg!(rather easy to find,reviewing codes isn't the best solution)
##references
Game rules are based on the entry at [wikipedia](https://en.wikipedia.org/wiki/Blackjack).
##others
A typical screenshot of the program running：![running](https://github.com/Xchiliarch/BlackJack/blob/main/running.png)


###rules

>本游戏使用一副牌进行，游戏结束即重新洗牌开局
>
>玩家独自与庄家进行游戏，初始筹码为200，筹码用完游戏结束
>游戏开局时，庄家给玩家发2张牌，庄家自己发一张明牌（玩家可看见），一张
>暗牌（玩家无法看见）
>***
>>获胜条件：结算时，玩家的点数比庄家更接近21点且未爆牌，或庄家爆牌
>
>>黑杰克：玩家手中的牌为一张10点一张A，此时玩家直接赢下游戏，获得1.5倍赌注
>
>>庄家将在17点停牌，并使用软17原则（指初始两张牌点数之和大于17且有一张为A）
>***
>>发牌结束后，玩家根据局势可选择要牌（hit），分牌（split）,停牌（stand），倍注（double），保险(insurance)与投降(Surrender)
>
>>要牌：庄家再发一张牌给玩家。
>
>>分牌：当玩家初始发的两张牌点数相同时可以分牌，再下一份相同的赌注，两副牌各再发一张补齐，玩家先后对两副牌进行操作，计算胜负（此时无黑杰克，仅看做普通21点）
>
>>停牌：玩家停止要牌，进入庄家操作阶段。
>
>>倍注：当玩家手中不是黑杰克时，该操作将会翻倍赌注，然后抽一张牌后停牌
>
>>保险：当庄家明牌为A时，可花赌注的>一半购买保险，若庄家黑杰克，玩家获得保险的两倍，即赌注。若不是，则继续游戏，保险不退。
>***
>玩家根据局势可持续要牌或停牌直到
>1. 爆牌（指玩家手中牌点数之和大于21）
>2. 等于21（玩家直接停牌）
>3. 拿到5张牌时仍未爆牌，判定玩家胜利，结束游戏
>***
>牌点数说明：
> 2~10 为牌面点数，JQK为10点，A为1点或11点（取决于手牌，以不爆牌的点数>作为其点数。例如：一张5一张A为16，两张8一张A为17
> 