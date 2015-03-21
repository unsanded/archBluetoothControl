#include "devicemanager.h"
#include "bluetoothtrayicon.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSystemTrayIcon>
#include <QtQuick>



int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    BluetoothTrayIcon icon;
    icon.show();
    qmlRegisterType<Device>("bluetooth", 1, 0, "Device");
    qmlRegisterType<DeviceManager>("bluetooth", 1, 0, "DeviceManager");
    //qRegisterMetaType<Device>("Device");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

