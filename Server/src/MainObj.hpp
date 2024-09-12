#ifndef MAINOBJ_HPP_
#define MAINOBJ_HPP_
#include<iostream>
#include<QtCore/QObject>
#include<QtNetwork/QTcpServer>
#include<QtNetwork/QTcpSocket>

class MainObj:public QObject
{
    Q_OBJECT
public:
    MainObj(QObject* parent=nullptr);
    ~MainObj();
private:
    QTcpServer* tSr;
    QTcpSocket* tSt=nullptr;
private slots:
    void tSr_newConnection();
    void tSt_connected();
    void tSt_disconnected();
    void tSt_readyRead();
};

#endif