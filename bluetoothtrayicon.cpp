#include "bluetoothtrayicon.h"


BluetoothTrayIcon::BluetoothTrayIcon(): QSystemTrayIcon(QIcon::fromTheme("bluetooth"))
  ,powered("powered", this)
{
         trayMenu = new QMenu;
         trayMenu->addAction(&powered);
         setContextMenu(trayMenu);

}

BluetoothTrayIcon::~BluetoothTrayIcon()
{

}

