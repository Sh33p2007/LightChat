#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

/****************************************************
* Copyright (C)	: Sh33p
* @file			: logindialog.h
* @author		: Sh33p
* @email		: sh33p2007@163.com
* @date			: 2025/11/23
****************************************************/

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_pushButton_login_clicked();

signals:
    void login_success(QString userName);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
