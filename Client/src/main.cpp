#include<QtWidgets/QApplication>
#include"MainWidget.hpp"

int main(int argc,char* argv[])
{
	QApplication app(argc,argv);
	MainWidget o;
	o.show();
	return app.exec();
}