// QNetworkHandler.cpp

#include "QNetworkHandler.h"

QNetworkHandler::QNetworkHandler( QObject* parent /*= nullptr*/ )
	: QObject(parent)
{ }

QNetworkHandler::~QNetworkHandler()
{ }

void QNetworkHandler::onSendRequest( const QString& host_name, const QString& port, const QString& payload )
{
	QTcpSocket socket;
	int wait_timeout = 3000;	// 3 sec

	socket.connectToHost( host_name, port.toInt() );
	if( !socket.waitForConnected(wait_timeout) )
	{
		emit error( socket.error(), socket.errorString() );
		return;
	}

	QString request_headers = "";
	request_headers += "POST / HTTP/1.1\n";
	request_headers += "Host: WinServerClient\n";
	request_headers += "Content-Type: application/json\n";
	request_headers += "Content-Length: " + QString::number( payload.length() ) + "\n";
	QString completed_request = request_headers + "\n" + payload;

	socket.write( completed_request.toLocal8Bit() );
	if( !socket.waitForBytesWritten(wait_timeout) )
	{
		emit error( socket.error(), "Request send timeout" );
		return;
	}

	if( !socket.waitForReadyRead(wait_timeout) )
	{
		emit error( socket.error(), "Request receive timeout" );
		return;
	}

	QString completed_response = socket.readAll();
	emit newResponse( completed_response.split("\r\n").last() );
}
