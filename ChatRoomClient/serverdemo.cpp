#include "serverdemo.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QObjectList>
#include <QDebug>

ServerDemo::ServerDemo(QObject* parent) : QObject(parent), m_handler(nullptr)
{
    connect(&m_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void ServerDemo::onNewConnection()
{
    QTcpSocket* tcp = m_server.nextPendingConnection();
    TxtMsgAssembler* assembler = new TxtMsgAssembler();

    m_map.insert(tcp, assembler);

    connect(tcp, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(tcp, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(tcp, SIGNAL(readyRead()), this, SLOT(onDataReady()));
    connect(tcp, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
}

void ServerDemo::onConnected()
{

}

void ServerDemo::onDisconnected()
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());

    if( tcp != nullptr )
    {
        delete m_map.take(tcp);
    }
}

void ServerDemo::onDataReady()
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());
    char buf[256] =  {0};
    int len = 0;

    if( tcp != nullptr )
    {
        TxtMsgAssembler* assembler = m_map.value(tcp);

        while( (len = static_cast<int>(tcp->read(buf, sizeof(buf)))) > 0 )
        {
            QSharedPointer<TextMessage> ptm = (assembler != nullptr) ? assembler->assemble(buf, len) : nullptr;

            if( (ptm != nullptr) && (m_handler != nullptr) )
            {
                m_handler->handle(*tcp, *ptm);
            }
        }
    }
}

void ServerDemo::onBytesWritten(qint64 bytes)
{
    (void)bytes;
}

bool ServerDemo::start(int port)
{
    bool ret = true;

    if( !m_server.isListening() )
    {
        ret = m_server.listen(QHostAddress("127.0.0.1"), static_cast<quint16>(port));
    }

    return ret;
}

void ServerDemo::stop()
{
    if( m_server.isListening() )
    {
        m_server.close();
    }
}

ServerDemo::~ServerDemo()
{
    const QObjectList& list = m_server.children();

    for(int i=0; i<list.length(); i++)
    {
        QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(list[i]);

        if( tcp != nullptr )
        {
            tcp->close();
        }
    }

    const QList<TxtMsgAssembler*>& al = m_map.values();

    for(int i=0; i<al.length(); i++)
    {
        delete al.at(i);
    }
}

void ServerDemo::setHandler(TxtMsgHandler* handler)
{
    m_handler = handler;
}
