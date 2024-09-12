#include"MainWidget.hpp"
#include<QtNetwork/QHostInfo>

namespace
{
    //根据协议类型返回协议名称字符串
    /*QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
    {
        QString name;
        switch(protocol)
        {
        case QAbstractSocket::IPv4Protocol:
            name="IPv4";break;
        case QAbstractSocket::IPv6Protocol:
            name="IPv6";break;
        case QAbstractSocket::AnyIPProtocol:
            name="AnyInternetProtocol";break;
        default:
            name="Unknown";
        }
        return name;
    }*/
}

MainWidget::MainWidget(QWidget* parent):QWidget(parent)
{
    //ui
    this->setLayout(&mainLayout);
    connect(&mainLayout,SIGNAL(btnConnectClicked(QString,int)),this,SLOT(btnConnect_clicked(QString,int)));
    connect(&mainLayout,SIGNAL(btnSendClicked(QString)),this,SLOT(btnSend_clicked(QString)));
    connect(&mainLayout,SIGNAL(btnDisconnectClicked()),this,SLOT(btnDisconnect_clicked()));

    //tcpSocket
    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(tcpSocket_connected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(tcpSocket_disconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(tcpSocket_readyRead()));
}
MainWidget::~MainWidget(){}

void MainWidget::btnConnect_clicked(QString IPStr,int port)
{
    if(tcpSocket->state()!=QAbstractSocket::ConnectedState)
    {
        mainLayout.setLabText("正在连接...");
        QHostAddress address(IPStr);
        tcpSocket->connectToHost(address,port);
    }
    else
        mainLayout.appendText("原连接未断开,请先断开");
}
void MainWidget::btnDisconnect_clicked()
{
    if(tcpSocket->state()==QAbstractSocket::ConnectedState)
        tcpSocket->disconnectFromHost();
    else
        mainLayout.appendText("没有连接,无法断开");
}
void MainWidget::btnSend_clicked(QString msg)
{
    mainLayout.appendText("<< "+msg);
    QByteArray str=(msg+"\n").toUtf8();
    tcpSocket->write(str);
}
void MainWidget::tcpSocket_connected()
{
    mainLayout.setLabText("已连接");
}
void MainWidget::tcpSocket_disconnected()
{
    mainLayout.setLabText("已断开");
}
void MainWidget::tcpSocket_readyRead()
{
    while(tcpSocket->canReadLine())
        mainLayout.appendText(">> "+tcpSocket->readLine());
}