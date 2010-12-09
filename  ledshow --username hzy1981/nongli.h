/****************************************Copyright (c)**************************************************
**                              四川唐门高新技术开发有限公司
**                                     研    发    部
**                                独门暗器之孔雀翎研究室 
**
**                                http://www.蜀中唐门.com
**
**                                   维护健康 信守诚诺
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: nongli.c
**创   建   人: 赖皮 
**最后修改日期: 2007年02月8日
**描        述: 最强万年历   
**              支持所有的单片机、ARM、AVR、MSP430、PIC等(支持C开发)
**              可嵌入任何标准C编译器  BC++、VC、ADS、KEIL等
**
**★〓 仅以此献给我的宝贝女儿小涵，我的小狗狗要过第一个春节了 〓★
**★〓    任何人都可以发布和使用，希望保留本文件信息。谢谢    〓★
********************************************************************************************************
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 赖皮 
** 版  本: v1.0
** 日　期: 2007年02月6日
** 描　述: 
**          这是改写网友Campo的万年历C51。
**          原作使用了数组查表法，效率较高。
**          移植到ARM上，我改写了进入参数。返回采用指针传递
**          例如:    GetChinaCalendar(2007,02,06,(unsigned char *)p);p-> 2006/12/19 在BC++4.5上可仿真
**          增加了天干地支转换             ★〓个人原创〓★
**          输入公历日期得到农历字符串	
**          如:      GetChinaCalendarStr(2007,02,06,(char *)str) 返回str="丙戌年腊月十九"
**          非本人原创部分仅供研究与学习之用。如想商业使用，
**          请与原作者Campo联系——虽然我也不知道他的联系方式 ^o^
**			
**          2007年02月6日    LAI2005PI@126.com
**------------------------------------------------------------------------------------------------------
********************************************************************************************************
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 赖皮 
** 版  本: v2.0(情人节版)   我会在2月14日发布-->愿天下有情人终成眷属
**                                              愿和我一样已经进城的人幸福美满
** 日　期: 2007年02月8日
** 描　述:   
**          应网友的要求增加24节气的支持    ★〓个人原创〓★
**          为了节约空间我未采用复杂算法  而先把节气标志做了个表格(好累人哦)
**          一年的24个节气的日期只需要3个字节编码,每个bit对应一个节气 高->低
**          50年的节气表,只需要150个字节的存储空间 
**          如果本月的节气日期等于基本日期 bit=0  else  bit=1
**
**★〓   仅以此献给我亲爱的刘筒, 我一定会给你种柚子和樱桃的   〓★
**★〓    任何人都可以发布和使用，希望保留本文件信息。谢谢    〓★
**         
**------------------------------------------------------------------------------------------------------
********************************************************************************************************
**--------------当前版本修订------------------------------------------------------------------------------
** 修改人: 
** 版  本: 
** 日　期: 
** 描　述:  
**         
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

/*********************************************************************************************************
** 函数名称:GetChinaCalendar
** 功能描述:公农历转换(只允许1901-2099年)
** 输　入:  year        公历年
**          month       公历月
**          day         公历日
**          p           储存农历日期地址
** 输　出:  1           成功
**          0           失败
** 作　者:  Campo
** 修  改:  赖皮
** 日　期:  2007年02月06日
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern unsigned char GetChinaCalendar(
								unsigned int  year,	
								unsigned char month,
								unsigned char day,
								unsigned char *p);
/*********************************************************************************************************
** 函数名称:GetWeek
** 功能描述:输入公历日期得到星期(只允许1901-2099年)
** 输　入:  year        公历年
**          month       公历月
**          day	        公历日
**          p           储存星期地址
** 输　出:  无
** 作　者:  Campo
** 修  改:  赖皮
** 日　期:  2007年02月06日
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void GetWeek(
			unsigned int year,
			unsigned char month,
			unsigned char day,
			unsigned char *p);
/*********************************************************************************************************
** 函数名称:GetChinaCalendarStr
** 功能描述:输入公历日期得到农历字符串	
**          如:GetChinaCalendarStr(2007,02,06,str) 返回str="丙戌年腊月十九"
** 输　入:  year        公历年
**          month       公历月
**          day         公历日
**          str         储存农历日期字符串地址   15Byte
** 输　出:  无
** 作　者:  赖皮        ★〓个人原创〓★
** 日　期:  2007年02月06日
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void GetChinaCalendarStr(
								unsigned int  year,	
								unsigned char month,
								unsigned char day,
								         char *str);

/*********************************************************************************************************
** 函数名称:GetJieQi
** 功能描述:输入公历日期得到本月24节气日期 day<15返回上半月节气,反之返回下半月	
**          如:GetJieQiStr(2007,02,08,str) 返回str[0]=4
** 输　入:  year        公历年
**          month       公历月
**          day         公历日
**          str         储存对应本月节气日期地址   1Byte
** 输　出:  1           成功
**          0           失败
** 作　者:  赖皮        ★〓个人原创〓★
** 日　期:  2007年02月08日
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern unsigned char GetJieQi(
			unsigned  int year,
			unsigned char month,
			unsigned char day,
			unsigned char *JQdate);
/*********************************************************************************************************
** 函数名称:GetJieQiStr
** 功能描述:输入公历日期得到24节气字符串	
**          如:GetJieQiStr(2007,02,08,str) 返回str="离雨水还有11天"
** 输　入:  year        公历年
**          month       公历月
**          day         公历日
**          str         储存24节气字符串地址   15Byte
** 输　出:  1           成功
**          0           失败
** 作　者:  赖皮        ★〓个人原创〓★
** 日　期:  2007年02月08日
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern unsigned char GetJieQiStr(
			unsigned int year,
			unsigned char month,
			unsigned char day,
			         char *str);