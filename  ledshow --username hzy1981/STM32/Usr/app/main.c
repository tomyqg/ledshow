#include "Includes.h"
//extern void juzhen (u8 *yuan,u8 *mud,u8 gao);
 void test()
 {
        int i; 
        unsigned char t1[8]={0x24,0x21,0xf0,0x7f,0x80,0x37,0xff,0x1f}; 
        unsigned char t2[8];//0xEA,0xE8,0xE9,0xC8,0xEC,0x6F,0x4C,0x54 

	    transpose8(t1, t2/*, 1*/);
        transpose4(t1, t2/*, 1*/);  
		//juzhen(t1, t2, 0);
		for(i = 0; i < 8; i	++)
		  printf("%d = %x", i, t2[i]);

 }

int main(void)
{
  Ram_Init();
  Hardware_Init();

  //test();

  RST_Periph();

  Para_Init(); //������ʼ��

  Com_Init(); //��ʼ������

#if UDISK_EN  
  UDisk_Init(); //U�̳�ʼ��
#endif

#if NET_EN
  Net_Init(); //�����ʼ��
#endif

  DS1302_Init(); //������1s�ٳ�ʼ��DS1302���ֲ�Ҫ��

  //Fac_Status_Self_Test(); //�Լ����
  
  Para_Show(); //�ϵ������ʾ

  SET_STATUS_LED_ON(); //��LED״̬��

  while(1)
  {
    Screen_Test(); //��Ļ���

	Self_Test(); //Ӳ���Լ�

#if SHELL_EN
    Shell_Proc();
#endif

    Show_Main_Proc();

#if UDISK_EN
    UDisk_Proc(); //u�̴���
#endif
#if NET_EN
	Net_Proc();
#endif
  }
  
}