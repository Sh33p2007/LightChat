#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "global.h"

/****************************************************
* Copyright (C)	: Sh33p
* @file			: mainwindow.h
* @author		: Sh33p
* @email		: sh33p2007@163.com
* @date			: 2025/11/20
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
    void on_pushButton_close_clicked();
    void on_pushButton_start_clicked();
    void on_newConnection();
    void on_readyRead();
    void on_disconnected();

private:
    Ui::MainWindow *ui;
    QTcpServer* server;
    bool mIsServerRunning;
    QString port;
    QList<QTcpSocket*> mSockets;

    QString aesKey = "Sh33p20071234567";
    QString aesIv = "Sh33p20077654321";
    QByteArray aesEncrypt(const QByteArray val);
    QByteArray aesDecrypt(const QByteArray val);
};
#endif // MAINWINDOW_H
