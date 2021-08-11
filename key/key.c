/****************************************************************************
 *文件：key.c
 *版本：v0.0
 *作者：lixianren
 *日期：2021/8/10
 *简述：适用与IO口高低电平的Key检测，按键模式有：短按、长按。
 *      短按模式根据需要可设为：连续短按1次，2次，3次（添加MULT_CLIK宏定义即可）
 *      需要添加或减少按键时，需
 *      1、添加形如Key1Statue（）按键动作检测函数
 *      2、添加形如KeyParaStructType类型变量并初始化
 *      3、将KeyParaStructType结构体地址添加进KeyStrPoint初始化中
 *      4、在KeyStatueHandle（）中自行添加对应的按键动作处理函数
 ***************************************************************************/
#include"key.h"

/*宏定义*/
/*<=======================================================================>*/
#define KEY_FIT_TIME 2          /*<滤波时间，单位：10ms>*/
#define KEY_ON_TIME 150         /*<长按时间，单位：10ms>*/
#define KEY_CHANGE_TIME 30      /*<连按最大时间间隔，单位：10ms>*/
#define MULT_CLIK               /*<设置是否需要连按模式>*/

/*局部函数声明*/
/*<=======================================================================>*/
uint8_t Key1Statue(void);
uint8_t Key2Statue(void);

/*变量定义初始化*/
/*<=======================================================================>*/
KeyParaStructType Key1Para =
{
    .KeySta = Key1Statue,
    .KeyMode = KEY_MODE_NOTHING,
    .KeyOnTime = 0,
    .KeyOffTime = 0,
    .KeyShortStep = 0,
    .KeyLongStep = 0,
};

KeyParaStructType Key2Para =
{
    .KeySta = Key2Statue,
    .KeyMode = KEY_MODE_NOTHING,
    .KeyOnTime = 0,
    .KeyOffTime = 0,
    .KeyShortStep = 0,
    .KeyLongStep = 0,
};

KeyPiontStuctType KeyStrPoint =
{
    .KeyPiont = {&Key1Para,&Key2Para},
    .KeyPiontNum = 2,
};

/*函数定义*/
/*<=======================================================================>*/
/**************************************************************************
  @函数名称：uint8_t Key1Statue(void)
  @函数功能：读取按键动作状态
  @函数参数：返回值 1：按键动作，0：反之
  @函数说明：无
**************************************************************************/
uint8_t Key1Statue(void)
{
    uint8_t re = 0;

    /*添加读取IO动作逻辑（高电平or低电平）*/
    if(xxxx)
    {
        re = 1;
    }
    
    return re;
}

uint8_t Key2Statue(void)
{
    uint8_t re = 0;

    /*添加读取IO动作逻辑（高电平or低电平）*/
    if(xxxx)
    {
        re = 1;
    }
    
    return re;

}

/**************************************************************************
  @函数名称：void KeyCheck(KeyParaStructType *KeyPara)
  @函数功能：扫描判断单个按键动作
  @函数参数：KeyParaStructType类型的指针
  @函数说明：在KeyScan()函数中调用
**************************************************************************/
void KeyCheck(KeyParaStructType *KeyPara)
{
    /*按键按下*/
    if(KeyPara->KeySta())
    {
        KeyPara->KeyOffTime = 0;
        KeyPara->KeyOnTime++;
        if(KeyPara->KeyOnTime >= KEY_FIT_TIME)          //滤波（短按）
        {
            if(KeyPara->KeyShortStep != 1)              //短按次数
            {
                KeyPara->KeyShortStep = 1;
                KeyPara->KeyCnt++;
            }

            if(KeyPara->KeyOnTime >= KEY_ON_TIME)       //长按
            {
                KeyPara->KeyOnTime = KEY_ON_TIME;
                if(KeyPara->KeyLongStep != 1)
                {
                    KeyPara->KeyLongStep = 1;
                    KeyPara->KeyMode = KEY_MODE_LONG;
                    KeyPara->KeyCnt = 0;
                }
            }
        }
    }
    /*按键释放*/
    else
    {
        
        KeyPara->KeyOnTime = 0;
        KeyPara->KeyLongStep = 0;
        
#ifdef MULT_CLIK //设置是否需要连按模式

        if(KeyPara->KeyShortStep == 1)
        {
            KeyPara->KeyShortStep = 2;
        }

        if(KeyPara->KeyShortStep == 2)
        {
            KeyPara->KeyOffTime++;
            if(KeyPara->KeyOffTime >= KEY_CHANGE_TIME) //连续两次按键按下时间间隔
            {
                KeyPara->KeyShortStep = 0;
                KeyPara->KeyOffTime = 0;
                switch(KeyPara->KeyCnt)
                {
                    case 0:
                    break;

                    case 1:
                    KeyPara->KeyMode = KEY_MODE_SHORT1;
                    break;

                    case 2:
                    KeyPara->KeyMode = KEY_MODE_SHORT2;
                    break;

                    case 3:
                    KeyPara->KeyMode = KEY_MODE_SHORT3;
                    break;

                    default:
                    break;
                }
                
                KeyPara->KeyCnt = 0;
                
            }
        }
#else
        KeyPara->KeyShortStep = 0;
        if(KeyPara->KeyCnt)
        {
            KeyPara->KeyMode = KEY_MODE_SHORT1;
            KeyPara->KeyCnt = 0;
        }
#endif

    }
}


/**************************************************************************
  @函数名称：void KeyScan(void)
  @函数功能：按键扫描
  @函数参数：无
  @函数说明：建议在10ms轮询中调用
**************************************************************************/
void KeyScan(void)
{
    uint8_t i;
    for(i = 0;i < KeyStrPoint.KeyPiontNum;i++)
    {
        KeyCheck(KeyStrPoint.KeyPiont[i]);
    }
}

/**************************************************************************
  @函数名称：void KeyStatueHandle(void)
  @函数功能：按键动作后逻辑代码
  @函数参数：无
  @函数说明：在实时中调用
**************************************************************************/
void KeyStatueHandle(void)
{
    if(Key1Para.KeyMode != KEY_MODE_NOTHING)
    {
        /*添加逻辑代码*/
        Key1Para.KeyMode = KEY_MODE_NOTHING;
    }

     if(Key2Para.KeyMode != KEY_MODE_NOTHING)
    {
        /*添加逻辑代码*/
        Key2Para.KeyMode = KEY_MODE_NOTHING;
    }
}
