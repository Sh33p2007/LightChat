#include "mainwindow.h"
#include <QApplication>

/****************************************************
* Copyright (C)	: Sh33p
* @file			: main.cpp
* @author		: Sh33p
* @email		: sh33p2007@163.com
* @date			: 2025/11/20
****************************************************/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
