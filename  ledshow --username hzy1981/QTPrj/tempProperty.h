#ifndef TEMPPROPERTY_H
#define TEMPPROPERTY_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include "simpleTextEdit.h"
#include "areaProperty.h"
#include "showArea.h"

class Ctemp:public QGroupBox
{
    Q_OBJECT
private:

  QComboBox *tempCombo;
  CcolorCombo *colorCombo;
  CsizeCombo *sizeCombo;

signals:
    void edited();

public:
    void screenCardParaChangeProc();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    Ctemp(QWidget *parent=0);
    ~Ctemp();
};

//节目属性窗
class CtempProperty:public QWidget
{
    Q_OBJECT
public slots:
    void edited();
private:

    QGroupBox *tempPropertyGroup; //属性


    QLabel *textLabel;  //文本
    CsimpleTextEdit *simpleTextEdit;
    Ctemp *tempStyle;
    CshowModeEdit *showModeEdit;
    //QTextEdit *textEdit; //显示文本
    //QPushButton *editButton; //编辑按钮
    CborderEdit *borderEdit;


public:
    CnameEdit *nameEdit;
    Carea *area;
    void connectSignal();
    void disconnectSignal();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CtempProperty(QWidget *parent=0);
    ~CtempProperty();
};

void getTempParaFromSettings(QString str, U_File_Para &para);
void updateTempShowArea(CshowArea *area);
void Get_Temp_Text_Point(INT8U Area_No, INT16U Width, INT16U Height, S_Point &P0);
#endif // TEMPPROPERTY_H
