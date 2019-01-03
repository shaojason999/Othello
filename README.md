# Othello

### 程式能力
1. 開局(前兩步)使用棋譜
    * 用Hash Function
2. 之後用Negamax, Alpha-Beta
    * 深度在main.c設為全域變數(#define DEPTH xx)

### 一些技巧(雖然沒有全用在程式裡)
From Wikipedia  
1. 遊戲的後期是關鍵位置的爭奪，而前期的布局，就是為搶占關鍵位置作準備。比如，若不想讓對方占據棋盤邊緣的有利位置，那麼自己就應避免在靠近邊緣的那一排落子。
2. C位、星位(不要下)
3. 初期佔據中心(控制中心)
4. 角不可能被翻走，同時角也可以保護其他棋子
5. 不要有牆: 形成牆的後果可以是棋步耗盡而被強迫棄角
6. 想辦法讓對手棄角
7. 讓對方可下步少(行動力低)
8. 我方有內部子，可以翻四面八方的對手(沒有內部子在戰略上是很糟的)
9. 盡量要吃最多子通常是不好的棋步，會築起許多牆，失去行動力
10. 下子在奇數空位的區域通常是好的，這樣最後一步會是我方下，可以翻對方棋
11. 完全安靜步: 完全不增加對手的行動力，通常是最好的棋步
12. 一個邊若未達6子則為危險邊

Others  
1. 不比子數，比行動力
2. 對方行動力少->只能下星位，而你可以下角
3. 盡量讓自己被包圍->你行動力大

### Reference:
1. [玩黑白棋有什么技巧？](https://www.zhihu.com/question/25271618)
2. [Wikipedia: 黑白棋](https://zh.wikipedia.org/wiki/%E9%BB%91%E7%99%BD%E6%A3%8B)
2. [weight reference](https://my.vanderbilt.edu/cs260/files/2012/08/Othello.c1.txt)
4. [A World-Championship-Level Othello Program](https://apps.dtic.mil/dtic/tr/fulltext/u2/a106560.pdf)
5. [電腦對局導論:第六章](https://www.govbooks.com.tw/books/113537)
