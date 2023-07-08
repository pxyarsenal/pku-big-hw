# cheatPOJ
## 作者： 彭莘尧 牛晨雨 周俊廷
## 小组： cheatGPT(73)




## 游戏规则
- 游戏的目的是使用尽可能少的操作数操纵角色从起点到达终点。

- 角色设定
    - 剩余操作数：移动、改变地形、发动技能都会消耗操作数，因某些特殊事件可能增加、减少操作数  
    - 血量
        - 踩到地上的“书本”会扣除血量
        - 碰到抓你逃课的老师也会扣除相应的血量

- 地图设定
    - 地图会被划分成若干方格，每个方格有其属性
          - 书本：踩到后不会消失，并会扣除角色血量
          - 桌子：可移动，但当其前方有墙体、老师、书本、钥匙、门的时候则不可移动，如果角色再向前走会跌倒，并扣除步数。
          - 老师：踩到之后老师会消失，并扣除角色血量
          - 钥匙：踩到之后钥匙会消失，角色具有钥匙属性，可以打开门逃出教室
          - 门：只有拿到钥匙后走到门游戏胜利，否则游戏失败


***

## 可行操作
人物设定：
- 方向键
    - ↑←↓→：控制角色进行移动
- esc键：出现暂停界面，可以回到游戏｜｜重新开始｜｜回到主菜单



***

## 人员分工
地图事件：
- 刺儿：消耗两倍操作数
- 小墙体：不可穿越（一般情况下），可以推动改变位置
- 大墙体：不可穿越、不可推动，可以直接销毁
- 钥匙/门：捡起钥匙可以打开门，否则门不可通过，门可以直接销毁
- 隐藏地块：初始黑暗，打破某一墙体后可以进入

***

## 致谢
感谢 中央美术学院 许烟溪同学
