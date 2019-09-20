// QNetworkHandler.h

#ifndef QNETWORKHANDLER_H
#define QNETWORKHANDLER_H

#include <QThread>

class QNetworkHandler
	: public QThread
{
	Q_OBJECT

public:
	QNetworkHandler( QThread* parent = nullptr );
	virtual ~QNetworkHandler();

protected:
	virtual void run() override;

};

#endif // QNETWORKHANDLER_H
