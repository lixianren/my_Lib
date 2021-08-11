/****************************************************************************
 *�ļ���
 *�汾��
 *���ߣ�
 *���ڣ�
 *������
 ***************************************************************************/
#include"key.h"

/*�궨��*/
/*<=======================================================================>*/
#define KEY_FIT_TIME 2
#define KEY_ON_TIME 150
#define KEY_CHANGE_TIME 30
#define MULT_CLIK 

/*�ֲ���������*/
/*<=======================================================================>*/
uint8_t Key1Statue(void);
uint8_t Key2Statue(void);

/*��������*/
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

/*��������*/
/*<=======================================================================>*/
/**************************************************************************
  @�������ƣ�
  @�������ܣ�
  @����������
  @����˵����
**************************************************************************/
uint8_t Key1Statue(void)
{
    return 1;
}

/**************************************************************************
  @�������ƣ�
  @�������ܣ�
  @����������
  @����˵����
**************************************************************************/
uint8_t Key2Statue(void)
{
    return 1;
}

/**************************************************************************
  @�������ƣ�
  @�������ܣ�
  @����������
  @����˵����
**************************************************************************/
void KeyCheck(KeyParaStructType *KeyPara)
{
    /*��������*/
    if(KeyPara->KeySta())
    {
        KeyPara->KeyOffTime = 0;
        KeyPara->KeyOnTime++;
        if(KeyPara->KeyOnTime >= KEY_FIT_TIME)          //�˲����̰���
        {
            if(KeyPara->KeyShortStep != 1)
            {
                KeyPara->KeyShortStep = 1;
                KeyPara->KeyCnt++;
            }

            if(KeyPara->KeyOnTime >= KEY_ON_TIME)       //����
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
    /*�����ͷ�*/
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
            if(KeyPara->KeyOffTime >= KEY_CHANGE_TIME) //�������ΰ�������ʱ����
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
  @�������ƣ�
  @�������ܣ�
  @����������
  @����˵����
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
  @�������ƣ�
  @�������ܣ�
  @����������
  @����˵����
**************************************************************************/
void KeyStatueHandle(void)
{
    if(Key1Para.KeyMode != KEY_MODE_NOTHING)
    {
        /*����߼�����*/
        Key1Para.KeyMode = KEY_MODE_NOTHING;
    }

     if(Key2Para.KeyMode != KEY_MODE_NOTHING)
    {
        /*����߼�����*/
        Key2Para.KeyMode = KEY_MODE_NOTHING;
    }
}
