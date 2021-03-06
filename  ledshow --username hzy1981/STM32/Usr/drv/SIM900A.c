#define SIM900A_C
#include "Includes.h"

#if GPRS_EN || SMS_EN

// 初始化GSM状态
INT8U GsmInit(void)
{
	//char ans[128];		// 应答串


	//UCS字符集
	if(ATSendResponse("AT+CSCS=\"UCS2\"\r", "OK", 2000) EQ 0)
	  return 0;
	// PDU模式
	if(ATSendResponse("AT+CMGF=0\r", "OK", 2000) EQ 0)
	  return 0;
    //ATSend("AT+CSCA?\r");
	return 1;
}

INT8U GprsInit(void) 
{   
    //uint8_t erro;
	unsigned int i;
	//unsigned char temp_c[64];
	//erro=0;
	
    //if(ATSendResponse("AT+GSV\r\n", "OK", 300) EQ 0)
	  //return 0; 	

 /*
    if(ATSendResponse("AT+CLIP=1\r\n", "OK", 200) EQ 0)  //指示来电号码
      return 0;//erro+=GetResponse("OK", 2);
*/
    
    //ATSend("AT+CSQ\r\n");
    //erro+=GetResponse("OK", 2); //信号强度
    
    
    //ATSend("AT+COPS?\r\n");
    //erro+= GetResponse("+COPS", 2);

	if(ATSendResponse("AT+CIPHEAD=1\r\n", "OK", 2000) EQ 0)
	  ;//return 0;

    for(i = 0; i < 20; i ++)
	{
        if(ATSendResponse("AT+CGATT=1\r\n", "OK", 2000))  //注册网络
		  break;          
    }

	if(i EQ 20)
	  return 0;

    return 1;
    //erro += GetResponse("OK", 2);
 /*
    ATSend("AT+CIPSTATUS\r\n");
    erro+=GetResponse("STATE:", 2);
    delayMs(0, 200);
    if(check_respond("IP INITIAL") == 0) 
	{
    
        
        ATSend("AT+CIPMUX=1\r\n");
        erro+= GetResponse("OK", 2);
        
        
	
        strcpy(temp_c,"\"AT+CSTT=\"");
		strcat(temp_c,APN);
		strcat(temp_c,"\",\"");
		strcat(temp_c,usear);
		strcat(temp_c,"\",\"");
		strcat(temp_c,password);
		strcat(temp_c,"\"\r\n");
		ATSend(temp_c);
        erro += GetResponse("OK",2);
        
        
        ATSend("AT+CIICR\r\n");
        erro += GetResponse("OK", 20);
        
       
        ATSend("AT+CIFSR\r\n");
        erro += GetResponse(".", 3);
        
    } 
	else if(check_respond("IP STATUS") == 0) 
	{
        
        ;//printf("之前已经启动");
        
    }
	
	 else if(check_respond("CONNECT OK") == 0  ||
              check_respond("CONNECTING") == 0  ||
              check_respond("LISTENING") == 0   ||
              check_respond("CLOSING")== 0      ||
              check_respond("CLOSED") == 0) 
	{
              
        ATSend("AT+CIPSHUT\r\n");
        erro +=GetResponse("SHUT OK\r\n", 20);
        
    } 
	else if	(check_respond("IP GPRSACT") == 0 ) 
	{
		
        ATSend("AT+CIFSR\r\n");
        erro += GetResponse(".", 20);
	}
	else 
	{    
        erro = 1;
		gprs_power_down();
    }

exit:	
    return erro;
*/
}

void Module_PWR_KEY(void)
{
	SET_GSM_ON(1);
	OS_TimeDly_Ms(10);
	SET_GSM_ON(0);
	OS_TimeDly_Ms(10);
	SET_GSM_ON(1);
	OS_TimeDly_Ms(1100);
	SET_GSM_ON(0);
}

void ModuleReset(void)
{
    //INT8U i;

	//启动GSM模块	
	if(CHK_MODULE_STATUS() EQ 0)
	{
	    debug("reset sim900A module");
		Module_PWR_KEY();
	}

}

int Chk_CSQ(char reStr[])
{
   //static int flag = 0x55aa;
  	INT16U Len;
	int CSQ = 0;
	char *p;
    char Temp[30];
		
			
	ATSend("AT+CSQ\r\n");
	Len = ReadComm(Temp, sizeof(Temp), 2000);
	if(Len > 0 && strstr(Temp, "OK") != 0)
	{
	  p = strstr(Temp, "CSQ");
	  if(p != '\0')
	  {
		sscanf(p + 5, "%d", &CSQ);	// 读取信号强度
	    strncpy(reStr, p, 9);
	  }
	}
	
	return CSQ;		
}

void ModuleInit(void) //模块初始化
{
	//char *p;

	//INT16U Len;

  Clr_Watch_Dog();
      
	OS_Core_Wait_Ms(CHK_MODULE_STATUS(),3000); //最多等待3000ms。

	//连续3个AT自适应波特率
	ATSend("AT\r");
	OS_TimeDly_Ms(50);
	ATSend("AT\r");
	OS_TimeDly_Ms(50);
	ATSend("AT\r");
	OS_TimeDly_Ms(50);

	// 测试GSM-MODEM的存在性
	if(CHK_MODULE_STATUS() EQ 0)
	  goto err0;
	
	if(ATSendResponse("AT\r", "OK", 2000) EQ 0)
	  goto err0;
/*
	// ECHO OFF
	if(ATSendResponse("AT+IPR=0\r\n", "OK", 2000) EQ 0)
	  goto err0;
*/
	if(ATSendResponse("ATE0&W\r\n", "OK", 2000) EQ 0)
	  goto err0;
		   
    if(ATSendResponse("AT+CFUN=1\r\n", "OK", 2000) EQ 0) //全功能
      goto err0;

    if(ATSendResponse("AT+CMEE=1\r\n", "OK", 2000) EQ 0)// EQ 0)
	  goto err0;

	//检测sim卡是否正常
    if(ATSendResponse("AT+CCID\r\n", "OK", 2000) EQ 0)
	  goto err1;
 /*  
    for(i = 0; i < 3; i ++)
	{
      if(ATSendResponse("AT+CREG?\r\n", "OK", 2000))  //注册网络
		break;          
    }
 */
	//读取信号强度
	//if(ATSendResponse("AT+CSQ\r\n", "OK", 2000) EQ 0)// EQ 0)
	  //goto err0;

	  
   	//ATSendResponse("AT+CMGDA=6\r\n", "OK", 2000);

	//if(i EQ 20)
	 // return 0;
#if SMS_EN
    if(GsmInit() EQ 0)
	  goto err0;
#endif

#if GPRS_EN
	if(GprsInit() EQ 0)
	  goto err0;
#endif

    goto ok;
err0:
	Set_RT_Show_Area(0, 0, 64, 16);
	RT_Play_Status_Enter(3);
	Clr_All_Show_Data();
	
	LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "ERR10"); //模块启动失败
    return; 
err1:
	Set_RT_Show_Area(0, 0, 64, 16);
	RT_Play_Status_Enter(3);
	Clr_All_Show_Data();
	
	LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "ERR11"); //无sim卡
    return;
ok:

 
  return;

}

#if 0//GPRS_EN
//进行TCP连接
INT8U TCPConnect(void)
{
  INT8U Re;

  Screen_Para.GPRS_Para.Serv_Domain[sizeof(Screen_Para.GPRS_Para.Serv_Domain) - 1] = 0;	//目标地址最后一个字节填0，避免复制字符串溢出
  
  while(1)
  {
	  snprintf(GPRS_Buf.Data, sizeof(GPRS_Buf.Data), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", \
	           Screen_Para.GPRS_Para.Serv_Domain,  Screen_Para.GPRS_Para.Serv_Port);
	
	  Re = ATSendResponse(GPRS_Buf.Data, "CONNECT OK", 2000);
	  if(Re)
	    return Re; 
	  
	  ATSend("AT+IPCLOSE=1\r\n");

	  if(Screen_Para.GPRS_Para.Heart_Period EQ 0)
	  {
	    Screen_Para.GPRS_Para.Heart_Period = 3;
	    SET_SUM(Screen_Para);
	  }

      OS_TimeDly_Sec(Screen_Para.GPRS_Para.Heart_Period * 60 - 25); 
      
  }
}

//使用TCP发送数据
void TcpSendData(INT8U Data[], INT16U DataLen)
{


}
#endif

//读取COM口数据
INT16U ReadComm(char *pDst, INT16U Len, INT16U ms)
{
  INT16U WRPosi, RDPosi;

  //100ms内没有收到数据则认为数据稳定了.
  //OS_TimeDly_Ms(100);
  if(CHK_MODULE_STATUS() EQ 0)
    return 0;

  WRPosi = SMS_GPRS_Rcv_Buf.WRPosi;

  Clr_Watch_Dog();

  OS_Core_Wait_Ms(WRPosi != SMS_GPRS_Rcv_Buf.WRPosi, ms); //最多等待500ms。等到有数据接收

  while(1)
  {
    WRPosi = SMS_GPRS_Rcv_Buf.WRPosi;
    
	OS_TimeDly_Ms(200);
	
	Clr_Watch_Dog();

	if(WRPosi EQ SMS_GPRS_Rcv_Buf.WRPosi)
	  break; 
  }

  WRPosi = SMS_GPRS_Rcv_Buf.WRPosi;
  RDPosi = SMS_GPRS_Rcv_Buf.RDPosi;

  if(RDPosi < WRPosi)
  {
    if(RDPosi + Len >= WRPosi)
	  Len = WRPosi - RDPosi;
  }
  else
    Len = 0;

  memcpy(pDst, SMS_GPRS_Rcv_Buf.Buf + RDPosi, Len);
  SMS_GPRS_Rcv_Buf.RDPosi += Len;

  return Len;
}

//写COM口数据
INT16U WriteComm(char *pDst, INT16U Len)
{
  INT16U i;

  for(i = 0; i < Len; i ++)
  {
    Com_Send_Byte(CH_GPRS, pDst[i]);
    Com_Send_Byte(CH_DBG, pDst[i]);
  }
  return Len;
} 

INT8U ATSend(char *p)
{
  ClrComm();
  return WriteComm(p, strlen(p));
}

INT8U ATSendResponse(char *pSrc, char *pRes, INT16U ms)
{
	ATSend(pSrc);
	return GetResponse(pRes, ms);
}

char TempRcvData[200];
//检测是否收到p字符串，最多等待ms
INT8U GetResponse(char *p, INT16U ms)
{
  INT16U Len;

  memset(TempRcvData, 0, sizeof(TempRcvData));
  Len = ReadComm(TempRcvData, sizeof(TempRcvData), ms);
  if(Len > 0 && strstr(TempRcvData, p) != 0)
    return 1; 
  else
    return 0;
}

void ClrComm(void)
{
  SMS_GPRS_Rcv_Buf.RDPosi = 0;
  SMS_GPRS_Rcv_Buf.WRPosi = 0;

  SMS_GPRS_Rcv_Buf.Buf[0] = 0;
  SMS_GPRS_Rcv_Buf.Buf[1] = 0;

}

void Chk_Module_Status(void)
{
	static S_Int32U Sec = {CHK_BYTE, 0x00, CHK_BYTE};
	static S_Int32U Sec_Counts = {CHK_BYTE, 0x00, CHK_BYTE};
	
  if(CHK_MODULE_STATUS() EQ 0)
  {
    OS_TimeDly_Ms(10);
		if(CHK_MODULE_STATUS() EQ 0)
		{
			ModuleInit();
		}
  }
	
	if(Pub_Timer.Sec != Sec.Var)
	{
		Sec.Var = Pub_Timer.Sec;
		Sec_Counts.Var ++;
		
		if(Sec_Counts.Var >= 60 * 1440 * 1) //每天测试一次OK指令是否正常
		{
			Sec_Counts.Var = 0;
			//连续2次AT指令失败，则重新启动模块
		  if(ATSendResponse("AT\r", "OK", 2000) EQ 0 &&\
				 ATSendResponse("AT\r", "OK", 2000) EQ 0)
			{
				Module_PWR_KEY();
				OS_TimeDly_Ms(1000);
				ModuleInit();
			}
		}
		
	}
}
#endif
