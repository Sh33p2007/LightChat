#ifndef GLOBAL_H
#define GLOBAL_H
#include <QRegularExpression>
#include <QByteArray>
#include <QNetworkReply>

/****************************************************
* Copyright (C)	: Sh33p
* @file			: global.h
* @author		: Sh33p
* @email		: sh33p2007@163.com
* @date			: 2025/11/16
****************************************************/

enum RequireId{
    ID_GET_CAPTCHA = 1001,//获取验证码
    ID_REG_USER = 1002,//注册用户
};

enum Module{
    REGISTERMOD = 0,
};

enum ErrorCode{
    SUCCESS = 0,
    ERR_JSON = 1,//Json解析失败
    ERR_NETWORK = 2,//网络错误
};

#endif // GLOBAL_H
