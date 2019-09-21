// QNetworkHandler.h

#ifndef QNETWORKHANDLER_H
#define QNETWORKHANDLER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class QNetworkHandler
	: public QObject
{
	Q_OBJECT

public:
	QNetworkHandler( QObject* parent = nullptr );
	virtual ~QNetworkHandler();

signals:
	void newResponse( const QString& response );
	void error( int request_err, const QString& err_msg );

public slots:
	void onSendRequest( const QString& host_name, qint16 port, const QString& payload );

};

#endif // QNETWORKHANDLER_H
