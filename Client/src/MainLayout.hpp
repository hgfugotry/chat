#ifndef MAINLAYOUT_HPP_
#define MAINLAYOUT_HPP_

#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QHBoxLayout>
#include<QtWidgets/QTextBrowser>
#include<QtWidgets/QPlainTextEdit>
#include<QtWidgets/QLabel>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QLineEdit>
#include<QtWidgets/QSpinBox>

class MainLayout:public QVBoxLayout
{
    Q_OBJECT
public:
    MainLayout(QWidget* parent=nullptr);
    ~MainLayout();
private:
    QTextBrowser msgBrowser;
    QHBoxLayout msgHL;
        QLineEdit msgEdit;
        QPushButton btnSend;
    QHBoxLayout IPAddressHL;
        QLabel labIPAddress;
        QLineEdit IPAddressEdit;
        QLabel labPort;
        QSpinBox spinBoxPort;
        QPushButton btnConnect;
        QPushButton btnDisconnect;
    QLabel labStatus;
    void initUi();
    void initText();
private slots:
    void btnSend_clicked();
    void btnConnect_clicked();
public:
    void appendText(const QString& text);
    void setLabText(const QString& text);
    void setBtnConnectEnabled(bool enabled);
signals:
    void btnConnectClicked(QString IPStr,int port);
    void btnDisconnectClicked();
    void btnSendClicked(QString msgStr);
};

inline MainLayout::MainLayout(QWidget* parent):QVBoxLayout(parent)
{
    initUi();
    spinBoxPort.setMinimum(0);
    spinBoxPort.setMaximum(65535);
    connect(&btnConnect,SIGNAL(clicked()),this,SLOT(btnConnect_clicked()));
    connect(&btnDisconnect,SIGNAL(clicked()),this,SIGNAL(btnDisconnectClicked()));
    connect(&btnSend,SIGNAL(clicked()),this,SLOT(btnSend_clicked()));
}
inline MainLayout::~MainLayout(){}

inline void MainLayout::btnSend_clicked(){emit btnSendClicked(msgEdit.text());}
inline void MainLayout::btnConnect_clicked(){emit btnConnectClicked(IPAddressEdit.text(),spinBoxPort.value());}

inline void MainLayout::initUi()
{
    this->addWidget(&msgBrowser,7);

    msgHL.addWidget(&msgEdit);
    msgHL.addWidget(&btnSend);
    this->addLayout(&msgHL);

    IPAddressHL.addWidget(&labIPAddress);
    IPAddressHL.addWidget(&IPAddressEdit);
    IPAddressHL.addWidget(&labPort);
    IPAddressHL.addWidget(&spinBoxPort);
    IPAddressHL.addWidget(&btnConnect);
    IPAddressHL.addWidget(&btnDisconnect);
    this->addLayout(&IPAddressHL);
    
    this->addWidget(&labStatus);

    initText();
}
inline void MainLayout::initText()
{
    labIPAddress.setText("IP 地 址 :");
    labPort.setText("端 口 :");
    btnConnect.setText("连 接 (&C)");
    btnDisconnect.setText("断 开 (&D)");
    btnSend.setText("发 送 (&A)");
}

inline void MainLayout::appendText(const QString &text) {msgBrowser.append(text);}
inline void MainLayout::setLabText(const QString &text){labStatus.setText(text);}

#endif