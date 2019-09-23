// QClient.cpp

#include "QClient.h"
#include "ui_MainWidget.h"

QClient::QClient( QApplication* app, QWidget* parent /*= nullptr*/ )
	: QWidget(parent),
	  m_ui( new Ui::QClient )
{
	// Init GUI
	QMessageBox error_msg;
	error_msg.setWindowTitle("Connection Error");
	error_msg.setIcon( QMessageBox::Critical );
	m_ui->setupUi(this);
	this->setWindowTitle("WinServerClient");

	QNetworkHandler* network_handler = new QNetworkHandler();

	// Connections region
	{
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
		connection_chk = connect( m_ui->button_quit, &QPushButton::clicked, app, &QApplication::quit );
		if(!connection_chk)
		{
			error_msg.setText("Connection 'ButtonQuit::clicked() <---> QApplication::quit()' failed");
			error_msg.exec();
		}
		connection_chk = connect( m_ui->button_send, &QPushButton::clicked, this, &QClient::onBtnSendClicked );
		if(!connection_chk)
		{
			error_msg.setText("Connection 'ButtonSend::clicked() <---> Client::onBtnSendClicked()' failed");
			error_msg.exec();
		}
	}

	// Starts network handling
	network_handler->moveToThread(&m_network_thrd);
	m_network_thrd.start();
}

QClient::~QClient()
{
	m_network_thrd.quit();
	if( !m_network_thrd.wait(5000) )	// 5 sec
	{
		m_network_thrd.terminate();
	}
}

QString QClient::GeneratePayload( const QString& data_value ) const
{
	return QString( "{\"data\":\"" + data_value + "\"}" );
}

void QClient::onBtnSendClicked()
{
	QString host_name = m_ui->line_edit_server_name->text().trimmed();
	QString port = m_ui->line_edit_server_port->text().trimmed();
	QString payload = GeneratePayload( m_ui->text_edit_request->toPlainText().trimmed() );

	emit sendRequest( host_name, port, payload );
}

void QClient::onResponseReady( const QString& response )
{
	QJsonDocument json_doc = QJsonDocument::fromJson( response.toLocal8Bit() );
	QJsonObject root_obj = json_doc.object();
	if( json_doc.isEmpty() || root_obj.isEmpty() )
	{
		m_ui->text_edit_response->appendPlainText("ERROR: Response JSON is empty\n");
		return;
	}
	
	if( root_obj.contains("data") )
	{
		QString response_data = root_obj.value("data").toString();
		m_ui->text_edit_response->appendPlainText( "VALUE: " + response_data + "\n" );
	}
	else if( root_obj.contains("error") )
	{
		QString response_error = root_obj.value("error").toString();
		m_ui->text_edit_response->appendPlainText( "ERROR: " + response_error + "\n" );
	}
	else
	{
		QJsonDocument transfer_doc(root_obj);
		QString unknown_response = transfer_doc.toJson(QJsonDocument::Compact);
		m_ui->text_edit_response->appendPlainText( "UNKNOWN_RESPONSE: " + unknown_response + "\n" );
	}
}

void QClient::onResponseError( int request_err, const QString& err_msg )
{
	QString error_line = "ERROR: Request failed with code = " + QString::number(request_err) + ", reason: " + err_msg;
	m_ui->text_edit_response->appendPlainText( error_line + "\n" );
}
