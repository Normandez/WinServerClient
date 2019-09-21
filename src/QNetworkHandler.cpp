// QNetworkHandler.cpp

#include "QNetworkHandler.h"

QNetworkHandler::QNetworkHandler( QObject* parent /*= nullptr*/ )
	: QObject(parent)
{ }

QNetworkHandler::~QNetworkHandler()
{ }

void QNetworkHandler::onSendRequest( const QString& host_name, qint16 port, const QString& payload )
{
	QNetworkAccessManager netwokr_manager;
	QNetworkRequest request;
	int wait_timeout = 5000;	// 5 sec

	request.setUrl( host_name + ":" + QString(port) );
	request.setHeader( QNetworkRequest::ContentTypeHeader, "application/json" );

	QNetworkReply* reply = netwokr_manager.post( request, payload.toLocal8Bit() );
	if( !reply->waitForReadyRead(wait_timeout) )
	{
		emit error( reply->error(), reply->errorString() );
	}
	else
	{
		QString response_data = reply->readAll();
		emit newResponse(response_data);
	}

	reply->deleteLater();
}
