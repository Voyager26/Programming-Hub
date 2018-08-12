# Hello World
## Day 5 study program
### 2018.8.12
Today i made a game（guess game weitten in C language.Here are the code.

    #include<stdio.h>
    #include<stdlib.h>
    #include<time.h>
    #include<unistd.h>
    int main()
    { 
    srand(time(NULL));
    int price = rand() % 1000;          //随机生成1000以下数字
    int guess;                          //猜测价格
    int num;                             //次数
    printf("猜价格小游戏\n");
    for(int i = 0;;i ++)
    {
        printf("请输入:");
        scanf("%d",&guess);             //输入猜测的价格
        if(guess == price)              //判断是否正确
        {
            printf("您用了%d次猜对。\n",++ i);
            num = i;
            break;
        }
        else if(guess < price)
            printf("您的价格低了\nNeed higher\n");
        else
            printf("您的价格高了\nNeed lower\n");
    }
    if(num < 5)
        printf("猜数小能手！Brilliant！");
    return 0;
    }

