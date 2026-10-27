#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCalculator.h"
#include <iostream>
#include<QTime>

class QtCalculator : public QMainWindow
{
    Q_OBJECT

public:
    QtCalculator(QWidget *parent = nullptr);
    ~QtCalculator();
    void init();
    void Test();
    void sleep(unsigned int msec);//延时功能

private slots:
    void on_num_btn_clicked();                  //数字按键槽函数声明
    void on_flag_btn_clicked();                   //符号按键槽函数声明
    void on_action_btn_equal_clicked();     //等号按键槽函数声明
    void on_clear_btn_clicked();                 //清除按键槽函数声明

private:
    Ui::QtCalculatorClass ui;
};
