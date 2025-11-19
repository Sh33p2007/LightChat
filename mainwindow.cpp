#include "mainwindow.h"
#include "ui_mainwindow.h"

/****************************************************
* Copyright (C)	: Sh33p
* @file			: mainwindow.cpp
* @author		: Sh33p
* @email		: sh33p2007@163.com
* @date			: 2025/11/15
****************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg = new LoginDialog();
    setCentralWidget(_login_dlg);

    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(_login_dlg,&LoginDialog::login_success,this,&MainWindow::slot_login_success);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_login_success()
{
    _login_dlg->hide();
}
