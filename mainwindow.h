#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"

/****************************************************
* Copyright (C)	: Sh33p
* @file			: mainwindow.h
* @author		: Sh33p
* @email		: sh33p2007@163.com
* @date			: 2025/11/15
****************************************************/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_login_success();

private:
    Ui::MainWindow *ui;
    LoginDialog* _login_dlg;
};
#endif // MAINWINDOW_H
