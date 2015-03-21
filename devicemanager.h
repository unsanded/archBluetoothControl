#ifndef BLUETOOTH_DEVICEMANAGER_H
#define BLUETOOTH_DEVICEMANAGER_H
#include "device.h"

#include <QMap>
#include <QObject>
#include <QQmlListProperty>


//namespace bluetooth {

class DeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Device> devices READ devices NOTIFY devicesChanged );
    Q_PROPERTY(bool powered READ powered WRITE setPowered NOTIFY poweredChanged)
    /**
    */

    Q_PROPERTY(QString basePath READ basePath WRITE setBasePath NOTIFY basePathChanged)



    QList< Device*> m_devices;
    QMap< QString , Device*> deviceLookup;

    QString m_basePath;

    bool m_powered;

public:
    explicit DeviceManager(QObject *parent = 0);
    ~DeviceManager();

 QQmlListProperty<Device> devices();

QString basePath() const
{
    return m_basePath;
}

bool powered() const
{
    return m_powered;
}

signals:

void devicesChanged(QQmlListProperty<Device> devices);

void basePathChanged(QString arg);

void poweredChanged(bool arg);

public slots:
    void update();
    void startScanning();

    void setBasePath(QString arg);

    void setPowered(bool arg)
    {
        if (m_powered == arg)
            return;
        m_powered = arg;

        emit poweredChanged(arg);
    }

protected:
    QVariant getProperty(QString name);
};

//} // namespace bluetooth

#endif // BLUETOOTH_DEVICEMANAGER_H
