// QClient.h

#ifndef QCLIENT_H
#define QCLIENT_H

#include <QWidget>

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
	~QClient();

private:
	Ui::QClient* m_ui;

};

#endif // QCLIENT_H
