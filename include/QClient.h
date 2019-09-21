// QClient.h

#ifndef QCLIENT_H
#define QCLIENT_H

#include <QWidget>
#include <QMessageBox>
#include <QThread>

#include <QJsonDocument>

#include "QNetworkHandler.h"

namespace Ui
{
    class QClient;
}

class QClient
	: public QWidget
{
	Q_OBJECT

public:
	QClient( QWidget* parent = nullptr );
	virtual ~QClient();

private:
	Ui::QClient* m_ui;
	QThread m_network_thrd;

	inline QString GeneratePayload( const QString& data_value ) const;

signals:
	void sendRequest( const QString& host_name, qint16 port, const QString& payload );

private slots:
	void onResponseReady( const QString& response );
	void onResponseError( int request_err, const QString& err_msg );

};

#endif // QCLIENT_H
