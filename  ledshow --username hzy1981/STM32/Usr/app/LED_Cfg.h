#ifndef LED_CFG_H
#define LED_CFG_H

//各种卡预定义
#define CARDA0	 0x10 //A0型卡不支持时钟，最简单的卡，其他的卡都一样。
#define CARDA1	 0x11
#define CARDA2	 0x12

#define CARDB1   0x21
//#define CARDB0	 0x21
//#define CARDB1	 0x22
//#define CARDB2	 0x23
#define CARDCU1	 0x31
#define CARDCU2   0x32

#define CARDCW1  0x33 //短信卡
#define CARDCW2  0x34 //GRPS卡
//#define CARDC1	 0x31
//#define CARDC2	 0x32
#define CARDD    0x40
#define CARDDU	 0x41
#define CARDDE   0x42
#define CARDDM	 0x43

#define SCAN_HARD_MODE   0x00//硬件扫描模式
#define SCAN_SOFT_MODE0	 0x01//软件扫描模式0 --在扫描中断中进行数据转换
#define SCAN_SOFT_MODE1	 0x02//软件扫描模式1 --在特效中断中进行数据转换

//节目特征字
#define BORDER_SHOW_BIT 0x00
#define PIC_SHOW_BIT    0x01
#define CLOCK_BIT       0x02
#define CLOCK_SHOW_BIT  0x03
#define TIME_SHOW_BIT   0x04
#define TIMER_SHOW_BIT  0x05
#define LUN_SHOW_BIT    0x06
#define TEMP_SHOW_BIT   0x07
#define HUMIDITY_SHOW_BIT 0x08
#define NOISE_SHOW_BIT  0x09
#define TXT_SHOW_BIT    0x0A


#define CS_BYTES 1
#define ROM_CS_BYTES 2
#define DATA_CHK_EN 1

#define MAX_LIGHTNESS_LEVEL 16 //最大亮度等级
#define MAX_OPEN_CLOSE_TIME 4 //最大开关机时段
#define MAX_LIGHTNESS_TIME 4 //最大亮度控制时段

#if defined(__CC_ARM) || defined(__ICCARM__)
#define QT_EN 0//在QT环境下编译使用QT
#define QT_SIM_EN 0//使用QT仿真STM32情况。不同于预览
#define RMDK_SIM_EN	0
#else
#define QT_EN 1//在QT环境下编译使用QT
#define QT_SIM_EN 0//使用QT仿真STM32情况。不同于预览
#define RMDK_SIM_EN 0
#endif

//#define CARD_TYPE CARD_AX //A系列板卡针对小条屏，其他针对中大屏
//QT_EN=1,QT_SIM_EN=1表示预览功能，完全模仿QT_SIM_EN=0表示正常预览

#define WDG_EN 1 //看门狗使能，仿真调试时关闭
//#define GMODULE_DBG_EN 1//GPRS模块测试使能

#define OE_PWM_FREQ 1000 //1KPWM频率
#define COMPANY_NAME "AL"

//#define APP_NAME "大屏LED播放系统"
#define BLOCK_DATA_LEN 459 //每块数据的大小, BLOCK_DATA_LEN - 9应该可整除法2和3
#define MAX_BORDER_POINTS (40*8) //边框数据大小
//#endif


#if QT_EN
#define ASSERT_EN 1
#define FAC_VERSION_EN 0 //工厂版本

#define MAX_PROG_NUM 16 //最大节目数
#define MAX_AREA_NUM 8  //每个节目下最大分区数
#define MAX_FILE_NUM 50 //每个节目下最大文件数

#include "QT_SIM.h"

#if FAC_VERSION_EN
#define APP_NAME "LED设计师2013 内部生产使用版"
#else
#define APP_NAME "LED设计师2013"
#endif

#define APP_VERSION "V2.0"

#define SCAN_SCREEN_PERIOD 200//扫屏周期,单位us
//显示效果配置
#define MOVE_STEP_PERIOD 10 //移动步进时间,单位为ms
//#define MIN_STAY_TIME  10//每屏最小停留时间,单位为ms
#define MOVE_STEP 1 //每个调度单位移动的数据百分比 单位%
 

#define IN_SPEC_EFFECT_NUM 86 //进入特效个数
#define OUT_SPEC_EFFECT_NUM 48 //退出特效个数
#define FONT_NUM 2 //内嵌字体个数

//----根据不同的屏幕和硬件配置下列项目
#define MAX_POINTS (4096*256L) //最大点数--此处是三色屏的最大点数！单色屏的点数在此基础上*3

#define DATA_PREP_EN 0
#define MAX_STORA_BLOCK_NUM  4000
#define DATA_FLASH_SIZE 2000000
#define MAX_SCAN_BLOCK_NUM 10
#define SCAN_DATA_MODE SCAN_SOFT_MODE0

#define MAX_SMS_NUM 400
#define SMS_EN 0

#define CLOCK_EN       1 //时钟使能

#define BORDER_SHOW_EN 1 //边框显示使能
#define PIC_SHOW_EN    1 //图文显示使能
#define CLOCK_SHOW_EN  1 //表盘显示使能
#define LUN_SHOW_EN    1 //农历显示使能
#define TEMP_SHOW_EN   1 //温度显示使能
#define TIME_SHOW_EN   1 //时间显示使能
#define TIMER_SHOW_EN  1 //定时显示使能
#define HUMIDITY_SHOW_EN 1 //湿度湿度
#define NOISE_SHOW_EN  1 //噪音
#define TXT_SHOW_EN    1 //内码文字

#define CARD_NAME "A0"  //卡名称
//-----------------以下为了兼容STM32程序--------------
#else
/*
#if defined(CARD_A0)
#define CARD_NAME "A0"  //卡名称
#elif defined(CARD_A1)
#define CARD_NAME "A1"  //卡名称
#else
#error "card AX name error"
#endif

#define UDIS_EN  1//u盘使能
#define NET_EN	 1//网络使能
#define GPRS_EN  1//GPRS使能
#else //没有使能QT仿真 ---STM32的环境下
#define ASSERT_EN 0
*/
#if defined(CARD_A)
#define ASSERT_EN 0
#else
#define ASSERT_EN 1
#endif

#include "STM32.h"

#if defined(CARD_A)
#define CARD_TYPE CARDA1
#include "LED_ABX_Cfg.h"
#include "LED_ABX_Drv.h"
#elif defined(CARD_B)
#define CARD_TYPE CARDB1
#include "LED_ABX_Cfg.h"
#include "LED_ABX_Drv.h"
#elif defined(CARD_C)
#define CARD_TYPE CARDCU1
#include "LED_CX_Cfg.h"
#include "LED_CX_Drv.h"
#elif defined(CARD_CW)
#define CARD_TYPE CARDCW1
#include "LED_CWX_Cfg.h"
#include "LED_CWX_Drv.h"
#elif defined(CARD_D)
#define CARD_TYPE CARDD
#include "LED_DX_Cfg.h"
#include "LED_DX_Drv.h"
#elif defined(CARD_E)
#define CARD_TYPE CARDE0
#include "LED_EX_Cfg.h"
#include "LED_EX_Drv.h"
#else
#error "Card type error"
#endif

#if CARD_TYPE == CARDCW1 || CARD_TYPE == CARDCW2
#define APP_ADDRESS_OFF 0x8000 //应用程序地址偏移
#else
#define APP_ADDRESS_OFF 0x1000 //应用程序地址偏移
#endif

#endif

#define ENV_VAR_EN (TEMP_SHOW_EN | HUMIDITY_SHOW_EN | NOISE_SHOW_EN) //外部环境变量的支持,温度因为有内部温度传感器支持，所以不判断
//节目特征字
#define FILE_EN_WORD ((BORDER_SHOW_EN<<BORDER_SHOW_BIT) |\
                       (PIC_SHOW_EN << PIC_SHOW_BIT) |\
					   (CLOCK_EN<<CLOCK_BIT) |\
                       (CLOCK_SHOW_EN<<CLOCK_SHOW_BIT) |\
                       (TIME_SHOW_EN << TIME_SHOW_BIT) |\
                       (TIMER_SHOW_EN << TIMER_SHOW_BIT) |\
                       (LUN_SHOW_EN << LUN_SHOW_BIT) |\
                       (TEMP_SHOW_EN << TEMP_SHOW_BIT) |\
                       (HUMIDITY_SHOW_EN << HUMIDITY_SHOW_BIT) |\
                       (NOISE_SHOW_EN << NOISE_SHOW_BIT) |\
                       (TXT_SHOW_EN << TXT_SHOW_BIT))L

#endif



