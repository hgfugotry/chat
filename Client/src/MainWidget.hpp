#ifndef MAINWIDGET_HPP_
#define MAINWIDGET_HPP_

#include<QtCore/QTimer>
#include<QtCore/QString>
#include<QtWidgets/QWidget>
#include<QtWidgets/QTextBrowser>
#include<QtWidgets/QPlainTextEdit>
#include<QtWidgets/QPushButton>
#include<QtNetwork/QTcpServer>
#include<QtNetwork/QTcpSocket>
#include"MainLayout.hpp"

class MainWidget:public QWidget
{
	Q_OBJECT
	Q_CLASSINFO("AUTHOR","hgfugotry");
public:
	MainWidget(QWidget* parent=nullptr);
	~MainWidget();
private:
	MainLayout mainLayout;
	QTcpSocket* tcpSocket;
private slots:
	void btnConnect_clicked(QString IPStr,int port);
	void btnDisconnect_clicked();
	void btnSend_clicked(QString msg);
	void tcpSocket_connected();
	void tcpSocket_disconnected();
	void tcpSocket_readyRead();
};

#endif