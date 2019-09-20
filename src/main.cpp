// main.cpp

#include <QApplication>

#include "QClient.h"

int main( int argc, char* argv[] )
{
	QApplication app( argc, argv );

	QClient client;
	client.show();

	return app.exec();
}
