#include <QCoreApplication>

#include "WazzupClient.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  WazzupClient client;

  return a.exec();
}
