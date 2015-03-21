#ifndef BLUETOOTHTRAYICON_H
#define BLUETOOTHTRAYICON_H

#include <QAction>
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

class BluetoothTrayIcon : public QSystemTrayIcon
{
public:
    BluetoothTrayIcon();

    QMenu*  trayMenu;
    QAction powered;

    ~BluetoothTrayIcon();

protected:
    QCONTAINERFWD_H
};

#endif // BLUETOOTHTRAYICON_H
