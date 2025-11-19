#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    connect(ui->lineEdit_password,SIGNAL(returnPressed()),this,SLOT(on_pushButton_login_clicked()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    if(ui->lineEdit_user->text().isEmpty()){
        ui->label_tip->setText(tr("请输入用户名"));
        return;
    }
    if(ui->lineEdit_password->text().isEmpty()){
        ui->label_tip->setText(tr("请输入密码"));
        return;
    }
    if(ui->lineEdit_password->text().compare("123456") == 0){
        emit login_success();
    }
    else{
        ui->label_tip->setText(tr("密码错误"));
    }
}
