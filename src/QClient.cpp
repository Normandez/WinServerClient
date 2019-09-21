// QClient.cpp

#include "QClient.h"
#include "ui_MainWidget.h"

QClient::QClient( QWidget* parent /*= nullptr*/ )
	: QWidget(parent),
	  m_ui( new Ui::QClient )
{
	QMessageBox error_msg;
	error_msg.setWindowTitle("Connection error");
	error_msg.setIcon( QMessageBox::Critical );

	m_ui->setupUi(this);

	QNetworkHandler* network_handler = new QNetworkHandler();

	bool connection_chk = connect( network_handler, &QNetworkHandler::newResponse, this, &QClient::onResponseReady );
	if(!connection_chk)
	{
		error_msg.setText("Connection 'NetworkHandler::newResponse() <---> Client::onResponseReady()' failed");
		error_msg.exec();
	}
	connection_chk = connect( network_handler, &QNetworkHandler::error, this, &QClient::onResponseError );
	if(!connection_chk)
	{
		error_msg.setText("Connection 'NetworkHandler::error() <---> Client::onResponseError' failed");
		error_msg.exec();
	}
	connection_chk = connect( this, &QClient::sendRequest, network_handler, &QNetworkHandler::onSendRequest );
	if(!connection_chk)
	{
		error_msg.setText("Connection 'Client::sendRequest() <---> NetworkHandler::onSendRequest()' failed");
		error_msg.exec();
	}
	connection_chk = connect( &m_network_thrd, &QThread::finished, network_handler, &QNetworkHandler::deleteLater );
	if(!connection_chk)
	{
		error_msg.setText("Connection 'NetworkHandlerThread::finished() <---> NetworkHandler::deleteLater()' failed");
		error_msg.exec();
	}

	network_handler->moveToThread(&m_network_thrd);
}

QClient::~QClient()
{
	m_network_thrd.quit();
	m_network_thrd.wait();
}

QString QClient::GeneratePayload( const QString& data_value ) const
{
	return QString( "{\"data\":\"" + data_value + "\"}" );
}


void QClient::onResponseReady( const QString& response )
{

}

void QClient::onResponseError( int request_err, const QString& err_msg )
{

}
