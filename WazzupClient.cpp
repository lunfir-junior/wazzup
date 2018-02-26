#include "WazzupClient.h"

#define DEFAULT_PORT 1234
#define DEFAULT_HOST "127.0.0.1"

WazzupClient::WazzupClient(QObject *parent) : QObject(parent)
{
  m_socket = new QTcpSocket(this);
  m_socket->connectToHost(QHostAddress(DEFAULT_HOST), DEFAULT_PORT, QTcpSocket::ReadWrite);

  connect(m_socket, &QTcpSocket::connected, this, &WazzupClient::sendData);
  connect(m_socket, &QTcpSocket::disconnected, this, &WazzupClient::closed);

  m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(m_notifier, &QSocketNotifier::activated, this, &WazzupClient::processConsoleData);
}

WazzupClient::WazzupClient(QHostAddress host, quint16 port, QObject *parent) : QObject(parent)
{
  m_socket = new QTcpSocket(this);
  m_socket->connectToHost(host, port, QTcpSocket::ReadWrite);

  connect(m_socket, &QTcpSocket::connected, this, &WazzupClient::sendData);
  connect(m_socket, &QTcpSocket::disconnected, this, &WazzupClient::closed);
}

WazzupClient::~WazzupClient()
{
  m_socket->close();
  delete m_socket;
  delete m_notifier;
}

void WazzupClient::sendData()
{
  connect(m_socket, &QTcpSocket::readyRead, this, &WazzupClient::processServerData);
  m_socket->write("Wazzup!");
}

void WazzupClient::closed()
{
  qDebug() << " in close slot";
  m_socket->close();
  m_socket->deleteLater();
  emit signalQuit();
}

void WazzupClient::processServerData()
{
  QByteArray serverData = m_socket->readAll();
  qDebug() << "in process data slot:";
  qDebug().noquote() << serverData;
}

void WazzupClient::processConsoleData()
{
  qDebug() << " in from console slot";
  std::string line;
      std::getline(std::cin, line);
      if (std::cin.eof() || line == "quit") {
          std::cout << "Good bye!" << std::endl;
      } else {
          std::cout << "Echo: " << line << std::endl;
          std::cout << "> " << std::flush;
          QString str = QString::fromStdString(line);
          QByteArray arr;

          arr.append(str);
          arr.append("\r\n");
          m_socket->write(arr);
      }
}
