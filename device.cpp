#include "device.h"
#include <QtDBus/QtDBus>

//namespace bluetooth {

Device::Device(QString dbusPath, QObject *parent) : QObject(parent), m_dbusPath(dbusPath)
{
    QDBusConnection::systemBus().connect(
                                        "org.bluez",  dbusPath, "org.freedesktop.DBus.Properties", "PropertyChanged",
                                        this, SLOT(onDbusStatusChanged(QString, QDBusVariant))
                                );
    m_busy=false;
}

Device::Device(){

    m_busy=false;
}

Device::Device(const Device &other):
    QObject(other.parent())
{
    m_name=other.name();
    m_dbusPath=other.dbusPath();
    m_address=other.address();

}

Device::~Device()
{

}

QString Device::name() const
{
    return m_name;
}

QString Device::address() const
{
    return m_address;
}

QString Device::dbusPath() const
{
    return m_dbusPath;
}

QString Device::status() const
{
    return m_status;
}

void Device::update()
{

    QString newName = getProperty("Alias").toString();
    if(newName!=m_name)
        emit nameChanged(m_name=newName);

    bool newConnected = getProperty("Connected").toBool();
    if(newConnected!= connected())
        emit connectedChanged(m_connected=newConnected);


}

void Device::connect()
{
    setBusy(true);
    QDBusInterface iface("org.bluez", dbusPath(), "org.bluez.Device1", QDBusConnection::systemBus() );

    QDBusMessage reply = iface.call("Connect");
    qDebug() << reply;
    setStatus(reply.errorMessage());

    setBusy(false);

}

void Device::disconnect()
{
    QDBusInterface iface("org.bluez", dbusPath(), "org.bluez.Device1", QDBusConnection::systemBus() );
    QDBusMessage reply = iface.call("Disconnect");
    qDebug() << reply;
    setStatus(reply.errorMessage());
    setConnected(false);
}

void Device::onDbusStatusChanged(QString name, QDBusVariant value)
{
    qDebug() << name ;
}














void Device::setName(QString arg)
{
    if (m_name == arg)
        return;

    m_name = arg;
    emit nameChanged(arg);
}

void Device::setAddress(QString arg)
{
    if (m_address == arg)
        return;

    m_address = arg;
    emit addressChanged(arg);
}

void Device::setDbusPath(QString arg)
{
    if (m_dbusPath == arg)
        return;

    m_dbusPath = arg;
    emit dbusPathChanged(arg);
}

void Device::setStatus(QString arg)
{
    if (m_status == arg)
        return;

    m_status = arg;
    emit statusChanged(arg);
}

void Device::setConnected(bool arg)
{
    if (m_connected == arg)
        return;

    m_connected = arg;
    emit connectedChanged(arg);
}

QVariant Device::getProperty(QString name)
{
    QDBusInterface iface("org.bluez", dbusPath(), "org.freedesktop.DBus.Properties", QDBusConnection::systemBus() );

    QDBusMessage reply = iface.call("Get", "org.bluez.Device1", name);
    auto arg = reply.arguments()[0].value<QDBusVariant>();

    return arg.variant();

}

//} // namespace bluetooth
