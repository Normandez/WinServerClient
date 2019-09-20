// QClient.cpp

#include "QClient.h"
#include "ui_MainWidget.h"

QClient::QClient( QWidget* parent /*= nullptr*/ )
	: QWidget(parent),
	  m_ui( new Ui::QClient )
{
	m_ui->setupUi(this);
}

QClient::~QClient()
{

}
