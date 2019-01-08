# Othello

## Version 1 (2019.1.4)
1. 開局: 前兩步使用棋譜
    * 用Hash Function
2. 中局: Negamax, Alpha-Beta, Heuristic
      * 審局函數: 棋盤加權與行動力(幾個位置可下)的線性組合
3. 終局: 最後幾步用Negamax, Alpha-Beta做perfect search(算出實際的黑棋、白棋數量)  

* 可調參數: 審局函數(棋盤權重、行動力)、perfect search 深度
* 程式開始時可選擇搜尋深度(終局深度是固定的、不能選)，還有選擇誰先下棋(玩家或電腦)

##### Comment
1. 把WZebra當對手(3~6層)
2. 我的程式大致上與WZebra走的路差不多，但幾次的誤差，累積幾來就差蠻多的了
3. 觀察發現WZebra應該也是把行動力看蠻重要的

#### 可改進地方
1. 比如bit count可以加快速度: [c语言:统计整数二进制表示中1的个数(汉明重量)](https://blog.csdn.net/hitwhylz/article/details/10122617)
2. 程式整體架構有點亂，因為當初寫得有點急
3. 參數調整: 把開局中局及終局之間的參數可以分得更細，比如每10步換一個參數
4. 中局應該用MCTS
5. 棋譜(book)可以增加

## 一些技巧(雖然沒有全用在程式裡)
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

## Reference:
1. [玩黑白棋有什么技巧？](https://www.zhihu.com/question/25271618)
2. [Wikipedia: 黑白棋](https://zh.wikipedia.org/wiki/%E9%BB%91%E7%99%BD%E6%A3%8B)
2. [weight reference](https://my.vanderbilt.edu/cs260/files/2012/08/Othello.c1.txt)
4. [A World-Championship-Level Othello Program](https://apps.dtic.mil/dtic/tr/fulltext/u2/a106560.pdf)
5. [電腦對局導論:第六章](https://www.govbooks.com.tw/books/113537)
