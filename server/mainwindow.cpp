#include "mainwindow.h"
#include "ui_mainwindow.h"

/****************************************************
* Copyright (C)	: Sh33p
* @file			: mainwindow.cpp
* @author		: Sh33p
* @email		: sh33p2007@163.com
* @date			: 2025/11/20
****************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new QTcpServer;
    connect(server,&QTcpServer::newConnection,this,&MainWindow::on_newConnection);
}

MainWindow::~MainWindow()
{
    foreach (QTcpSocket* socket, mSockets) {
        socket->disconnectFromHost();
        socket->deleteLater();
    }
    mSockets.clear();
    if(server){
        server->close();
        server->deleteLater();
    }
    delete ui;
}

void MainWindow::on_pushButton_close_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_start_clicked()
{
    if(ui->lineEdit_port->text().isEmpty()){
        QMessageBox::information(this,"提示","请输入服务器端口");
        return;
    }
    port = ui->lineEdit_port->text();
    if(server->listen(QHostAddress::AnyIPv4,port.toUShort())){
        ui->textEdit_log->append("监听成功,端口:"+port);
    }else{
        ui->textEdit_log->append("监听失败,端口:"+port);
    }
}

void MainWindow::on_newConnection()
{
    QTcpSocket* socket = server->nextPendingConnection();
    if(!socket){return;}
    mSockets.append(socket);
    ui->textEdit_log->append(QString("新连接-%1:%2 | 当前在线人数:%3").arg(socket->peerAddress().toString())
                                 .arg(socket->peerPort())
                                 .arg(mSockets.size()));
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::on_disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::on_readyRead);
}

void MainWindow::on_readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QByteArray buf = socket->readAll();
    buf = aesDecrypt(buf);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(buf);
    QJsonValue type = jsonDoc["type"];
    if(type == "Login"){
        QJsonObject jsonObj;
        jsonObj["userName"] = jsonDoc["userName"];
        jsonObj["type"] = "Login";
        jsonDoc.setObject(jsonObj);
        QByteArray data = jsonDoc.toJson(QJsonDocument::Compact);
        foreach (QTcpSocket* client, mSockets) {
            if(client->state() == QTcpSocket::ConnectedState){
                data = aesEncrypt(data);
                client->write(data);
                client->flush();
            }
        }
    }
    else if(type == "Message"){
        QJsonObject jsonObj;
        jsonObj["userName"] = jsonDoc["userName"];
        jsonObj["type"] = "Message";
        jsonObj["message"] = jsonDoc["message"];
        jsonDoc.setObject(jsonObj);
        QByteArray data = jsonDoc.toJson(QJsonDocument::Compact);
        foreach (QTcpSocket* client, mSockets) {
            if(client->state() == QTcpSocket::ConnectedState){
                data = aesEncrypt(data);
                client->write(data);
                client->flush();
            }
        }
    }
}

void MainWindow::on_disconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;
    mSockets.removeOne(socket);
    ui->textEdit_log->append(QString("连接断开-%1:%2 | 当前在线人数:%3").arg(socket->peerAddress().toString())
                                 .arg(socket->peerPort())
                                 .arg(mSockets.size()));
    socket->deleteLater();
}

QByteArray MainWindow::aesEncrypt(const QByteArray val)
{
    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QByteArray enBA = encryption.encode(val, aesKey.toUtf8(),aesIv.toUtf8());
    return enBA;
}

QByteArray MainWindow::aesDecrypt(const QByteArray val)
{
    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QByteArray  enBA = QByteArray::fromBase64(val);
    QByteArray deBA = encryption.decode(enBA, aesKey.toUtf8(),aesIv.toUtf8());
    return QAESEncryption::RemovePadding(deBA, QAESEncryption::PKCS7);
}
