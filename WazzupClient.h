#ifndef WAZZUPCLIENT_H
#define WAZZUPCLIENT_H

#include <QObject>
#include <QIODevice>
#include <QSocketNotifier>
#include <QDataStream>
#include <QTcpSocket>
#include <QProcess>
#include <QHostAddress>
#include <iostream>

class WazzupClient : public QObject
{
    Q_OBJECT
  public:
    explicit WazzupClient(QObject *parent = nullptr);
    explicit WazzupClient(QHostAddress host, quint16 port, QObject *parent = nullptr);
    ~WazzupClient();

   private:
    QTcpSocket *m_socket;
    QSocketNotifier *m_notifier;


//    QDataStream data;
//    QByteArray temp;

  public slots:
    void sendData();
    void processData();
    void closed();

    void fromConsole();
};

#endif // WAZZUPCLIENT_H
