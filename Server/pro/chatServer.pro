QT			+=		core
QT			+=		network

TEMPLATE	=		app
TARGET		=       server

CONFIG		+=		rtti

#输入
SOURCES		+=		../src/main.cpp
HEADERS		+=		../src/MainObj.hpp
SOURCES		+=		../src/MainObj.cpp

#输出
DESTDIR		=		../out/exe		#可执行文件
MOC_DIR		=		../out/moc		#MOC中间文件
OBJECTS_DIR	=		../out/obj		#obj文件
