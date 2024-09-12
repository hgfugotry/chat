#include<QtCore/QCoreApplication>
#include"MainObj.hpp"

int main(int argc,char* argv[])
{
	QCoreApplication app(argc,argv);
	MainObj o;
	return app.exec();
}