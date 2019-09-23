// main.cpp

#include <QApplication>

#include "QClient.h"

int main( int argc, char* argv[] )
{
	QApplication app( argc, argv );

	QClient client(&app);
	client.show();

	return app.exec();
}
