/****************************************************************************
 *文件：
 *版本：
 *作者：
 *日期：
 *简述：
 ***************************************************************************/
#include"key.h"

/*宏定义*/
/*<=======================================================================>*/
#define KEY_FIT_TIME 2
#define KEY_ON_TIME 150
#define KEY_CHANGE_TIME 30
#define MULT_CLIK 

/*局部函数声明*/
/*<=======================================================================>*/
uint8_t Key1Statue(void);
uint8_t Key2Statue(void);

/*变量定义*/
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
  @函数名称：
  @函数功能：
  @函数参数：
  @函数说明：
**************************************************************************/
uint8_t Key1Statue(void)
{
    return 1;
}

/**************************************************************************
  @函数名称：
  @函数功能：
  @函数参数：
  @函数说明：
**************************************************************************/
uint8_t Key2Statue(void)
{
    return 1;
}

/**************************************************************************
  @函数名称：
  @函数功能：
  @函数参数：
  @函数说明：
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
            if(KeyPara->KeyShortStep != 1)
            {
                KeyPara->KeyShortStep = 1;
                KeyPara->KeyCnt++;
            }

            if(KeyPara->KeyOnTime >= KEY_ON_TIME)       //长按
            {
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
        
#ifdef MULT_CLIK

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
  @函数名称：
  @函数功能：
  @函数参数：
  @函数说明：
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
  @函数名称：
  @函数功能：
  @函数参数：
  @函数说明：
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
