/*-----------------------------------------------
               DS18b20��������
------------------------------------------------*/
#ifndef __DS18B20_H
#define __DS18B20_H
typedef enum{FAILED = 0 ,PASSED = !FAILED} TestStatus ;
#define DQ_GPIO  SHT1X_SDA_PORT
#define DQ_GPIO_Pin SHT1X_SDA_PIN
//REGISTER COMMANDS
#define REGISTER_9_BITS  0x1F
#define REGISTER_10_BITS 0x3F
#define REGISTER_11_BITS 0x5F
#define REGISTER_12_BIT2 0x7F
//ROM COMMANDS
#define ROM_Search_Cmd   0xF0
#define ROM_Read_Cmd     0x33
#define ROM_Match_Cmd    0x55
#define ROM_Skip_Cmd     0xCC
#define ROM_AlarmSearch_Cmd 0xEC
//DS18b20 FUNCTION COMMANDS
#define Convert_T          0x44
#define Write_Scratchpad  0x4E
#define Read_Scratchpad   0xBE
#define Copy_Scratchpad   0x48
#define Recall_EEPROM     0x88
#define Read_PowerSupply  0x84
#define DQ_Write_1()     GPIO_SetBits(DQ_GPIO ,DQ_GPIO_Pin)  //д1
#define DQ_Write_0()     GPIO_ResetBits(DQ_GPIO ,DQ_GPIO_Pin)//д0
#define DQ_ReadBit()     GPIO_ReadInputDataBit(DQ_GPIO ,DQ_GPIO_Pin) //��DQ�ϵ�ֵ
extern void GPIO_DQ_Out_Mode(void) ; //DQ���ģʽ
extern void GPIO_DQ_Input_Mode(void) ;  //DQ����ģʽ
extern void Tx_ResetPulse(void) ;    //���͸�λ����
extern void Rx_PresencePulse(void) ; //����Ӧ���ź�
extern void Write_OneByte_ToDS18b20(unsigned char data) ; //дһ���ֽڵ�18b20
extern unsigned char Read_OneByte_FromDS18b20(void) ; //��18b20��һ���ֽ�
extern void Read_Temperature(unsigned char *sign ,unsigned char *interger ,
                      unsigned int *decimal) ; //���¶�
//д���ò���TH��TL�ͳ�ʼ�����üĴ���
extern void Write_EEPROM(unsigned char Th,unsigned char Tl,unsigned char Register_Con );
void DS18B20_Init(void) ; //��ʼ��
INT16S Get_DS18B20_Temp(void);
INT8U Chk_DS18B20_Sensor(void);
#endif /*DS18B20*/