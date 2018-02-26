#include <QCoreApplication>

#include "WazzupClient.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  WazzupClient client;

  QObject::connect(&client, &WazzupClient::signalQuit, &a, &QCoreApplication::quit);

  return a.exec();
}
