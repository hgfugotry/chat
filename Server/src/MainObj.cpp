#include "MainObj.hpp"

MainObj::MainObj(QObject *parent):QObject(parent)
{
    tSr=new QTcpServer(this);
    connect(tSr,SIGNAL(newConnection()),this,SLOT(tSr_newConnection()));
    QHostAddress adr("240e:874:14a:ed2c:3dfb:7ffc:cc29:c6a4");
    tSr->listen(adr,8000);
    std::cout<<"开始监听..."<<std::endl;
    std::cout<<"服务器地址:"<<tSr->serverAddress().toString().toStdString()<<std::endl;
    std::cout<<"服务器端口:"<<tSr->serverPort()<<std::endl;
}

MainObj::~MainObj()
{
    if(tSt)
        if(tSt->state()==QAbstractSocket::ConnectedState)
            tSt->disconnectFromHost();
    tSr->close();
}

void MainObj::tSr_newConnection()
{
    tSt=tSr->nextPendingConnection();
    connect(tSt,SIGNAL(connected()),this,SLOT(tSt_connected()));
    connect(tSt,SIGNAL(disconnected()),this,SLOT(tSt_disconnected()));
    connect(tSt,SIGNAL(readyRead()),this,SLOT(tSt_readyRead()));
    tSt_connected();
}
void MainObj::tSt_connected()
{
    std::cout<<"客户机Socket已连接."<<std::endl;
    std::cout<<"IP地址:"<<tSt->peerAddress().toString().toStdString()<<std::endl;
    std::cout<<"端口:"<<tSt->peerPort()<<std::endl;
}
void MainObj::tSt_disconnected()
{
    std::cout<<"客户机Socket已断开."<<std::endl;
    tSt->deleteLater();
}
void MainObj::tSt_readyRead()
{
    while(tSt->canReadLine())
        std::cout<<(">> "+tSt->readLine()).toStdString();
}