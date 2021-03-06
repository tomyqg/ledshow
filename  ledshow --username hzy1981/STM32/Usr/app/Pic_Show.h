#ifndef PIC_SHOW_H
#define PIC_SHOW_H

#include "Includes.h"

#if 1//PIC_SHOW_EN

#undef EXT
#ifdef PIC_SHOW_C
#define EXT
#else
#define EXT extern
#endif

#define FIX_MODE 0x00 //固定系数
#define H_MODE  0x01 //横向
#define V_MODE  0x02//纵向
#define HV_ADD_MODE 0x03 //+
#define HV_SQRT_MODE 0x04 //开方,对角
#define HV_MAX_MODE  0x05 //横向或纵向最大值
#define HHV_ADD_MODE 0x06 //
#define HVH_ADD_MODE 0x07
#define TVH_ADD_MODE 0x08
#define THV_ADD_MODE 0x09

#define WIDTH_FLAG 0x01
#define HEIGHT_FLAG 0x02

typedef struct
{
  void (*Func)(INT8U);
  INT8U Step_Mode; //步进模式,0-横向，1纵向，3纵横同步
  float Fac; //0,1表示1，其他表示
  INT8U Size_Flag; //WIDTH_FLAG表示适合宽屏，HEIGHT_FLAG表示适合高屏幕
#if QT_EN
  const char *name;
#endif  
}S_Mode_Func;

extern const S_Mode_Func In_Mode_Func[];
extern const S_Mode_Func Out_Mode_Func[];
EXT INT16U Calc_Move_Step(void);
EXT void Set_Area_Border_In(INT8U Area_No);
EXT void Set_Area_Border_Out(INT8U Area_No);
EXT void Calc_Screen_Color_Num(void);
EXT void Calc_Show_Mode_Step(INT8U Area_No);
EXT INT8U Chk_File_Play_Status(INT8U Area_No);
EXT void Update_Pic_Data(INT8U Area_No);
EXT INT8U Check_XXX_Data(INT8U Flag);
#endif
#endif

