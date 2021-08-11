/****************************************************************************
 *�ļ���key.c
 *�汾��v0.0
 *���ߣ�lixianren
 *���ڣ�2021/8/10
 *������������IO�ڸߵ͵�ƽ��Key��⣬����ģʽ�У��̰���������
 *      �̰�ģʽ������Ҫ����Ϊ�������̰�1�Σ�2�Σ�3�Σ����MULT_CLIK�궨�弴�ɣ�
 *      ��Ҫ��ӻ���ٰ���ʱ����
 *      1���������Key1Statue��������������⺯��
 *      2���������KeyParaStructType���ͱ�������ʼ��
 *      3����KeyParaStructType�ṹ���ַ��ӽ�KeyStrPoint��ʼ����
 *      4����KeyStatueHandle������������Ӷ�Ӧ�İ�������������
 ***************************************************************************/
#include"key.h"

/*�궨��*/
/*<=======================================================================>*/
#define KEY_FIT_TIME 2          /*<�˲�ʱ�䣬��λ��10ms>*/
#define KEY_ON_TIME 150         /*<����ʱ�䣬��λ��10ms>*/
#define KEY_CHANGE_TIME 30      /*<�������ʱ��������λ��10ms>*/
#define MULT_CLIK               /*<�����Ƿ���Ҫ����ģʽ>*/

/*�ֲ���������*/
/*<=======================================================================>*/
uint8_t Key1Statue(void);
uint8_t Key2Statue(void);

/*���������ʼ��*/
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
  @�������ƣ�uint8_t Key1Statue(void)
  @�������ܣ���ȡ��������״̬
  @��������������ֵ 1������������0����֮
  @����˵������
**************************************************************************/
uint8_t Key1Statue(void)
{
    uint8_t re = 0;

    /*��Ӷ�ȡIO�����߼����ߵ�ƽor�͵�ƽ��*/
    if(xxxx)
    {
        re = 1;
    }
    
    return re;
}

uint8_t Key2Statue(void)
{
    uint8_t re = 0;

    /*��Ӷ�ȡIO�����߼����ߵ�ƽor�͵�ƽ��*/
    if(xxxx)
    {
        re = 1;
    }
    
    return re;

}

/**************************************************************************
  @�������ƣ�void KeyCheck(KeyParaStructType *KeyPara)
  @�������ܣ�ɨ���жϵ�����������
  @����������KeyParaStructType���͵�ָ��
  @����˵������KeyScan()�����е���
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
            if(KeyPara->KeyShortStep != 1)              //�̰�����
            {
                KeyPara->KeyShortStep = 1;
                KeyPara->KeyCnt++;
            }

            if(KeyPara->KeyOnTime >= KEY_ON_TIME)       //����
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
    /*�����ͷ�*/
    else
    {
        
        KeyPara->KeyOnTime = 0;
        KeyPara->KeyLongStep = 0;
        
#ifdef MULT_CLIK //�����Ƿ���Ҫ����ģʽ

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
  @�������ƣ�void KeyScan(void)
  @�������ܣ�����ɨ��
  @������������
  @����˵����������10ms��ѯ�е���
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
  @�������ƣ�void KeyStatueHandle(void)
  @�������ܣ������������߼�����
  @������������
  @����˵������ʵʱ�е���
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
