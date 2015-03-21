#include "devicemanager.h"
#include <QtDBus/QtDBus>
#include <QDomDocument>
#include <QDebug>
//namespace bluetooth {

DeviceManager::DeviceManager(QObject *parent) : QObject(parent)
{

}

DeviceManager::~DeviceManager()
{

}

QQmlListProperty<Device> DeviceManager::devices()
{
    return QQmlListProperty<Device>((QObject*) this, m_devices);
}

void DeviceManager::update()
{
    bool newPowered = getProperty("Powered").toBool();
    if(newPowered!= m_powered)
        emit poweredChanged(m_powered=newPowered);



    bool changed=false;

    QDBusInterface iface("org.bluez", basePath(), "org.freedesktop.DBus.Introspectable", QDBusConnection::systemBus() );
    QDBusMessage reply = iface.call("Introspect") ;
    QDomDocument doc("doc");
    doc.setContent(reply.arguments()[0].toString());
    auto nodes = doc.elementsByTagName("node");

    for(int i=0; i < nodes.count(); i++){
        QDomNode n = nodes.at(i);
        QDomElement node = nodes.at(i).toElement();
        QString name = node.attribute("name");
        qDebug() << name;
        if(name.startsWith("dev_")){

            QString path = basePath() + "/" + name;

            if(deviceLookup.contains(path))
            {
                qDebug() << "  device is known";
                deviceLookup[path]->update();
            }
            else
            {
                qDebug() << "  adding device";
                Device* newDevice =  new Device(path, this);

                deviceLookup[path]=newDevice;

                m_devices.append(newDevice);
                newDevice->update();
                changed=true;
            }
        }
    }
    if(changed) emit devicesChanged(devices());


}

void DeviceManager::startScanning()
{

    QDBusInterface iface("org.bluez", basePath(), "org.bluez.Adapter1", QDBusConnection::systemBus() );
    QDBusMessage reply = iface.call("StartDiscovery") ;

}

void DeviceManager::setBasePath(QString arg)
{
    if (m_basePath == arg)
        return;

    m_basePath = arg;
    emit basePathChanged(arg);
}

QVariant DeviceManager::getProperty(QString name)
{
    QDBusInterface iface("org.bluez", basePath(), "org.freedesktop.DBus.Properties", QDBusConnection::systemBus() );

    QDBusMessage reply = iface.call("Get", "org.bluez.Adapter1", name);
    auto arg = reply.arguments()[0].value<QDBusVariant>();

    return arg.variant();

}

//} // namespace bluetooth

