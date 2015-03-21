#ifndef BLUETOOTH_DEVICE_H
#define BLUETOOTH_DEVICE_H

#include <QDBusMessage>
#include <QDBusVariant>
#include <QObject>

//namespace bluetooth {

class DeviceManager;

class Device : public QObject
{
    friend class DeviceManager;
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString dbusPath READ dbusPath WRITE setDbusPath NOTIFY dbusPathChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)

    QString m_status;

    bool m_connected;

    bool m_busy;

public:
    explicit Device(QString dbusPath, QObject *parent = 0);
    Device(const Device& other);
    Device();
    ~Device();

    bool operator==(const Device& other){
        return other.dbusPath()==dbusPath();
    }

    Device& operator=(const Device& other){
        m_name=other.m_name;
        m_address=other.m_address;
        m_dbusPath=other.dbusPath();
    }

QString name() const;

QString address() const;

QString dbusPath() const;

QString status() const;

bool connected() const
{
    return m_connected;
}

bool busy() const
{
    return m_busy;
}

signals:

void nameChanged(QString arg);

void addressChanged(QString arg);

void dbusPathChanged(QString arg);

void statusChanged(QString arg);

void connectedChanged(bool arg);

void busyChanged(bool arg);

public slots:


void update();
void connect();
void disconnect();

void onDbusStatusChanged(QString, QDBusVariant value);



void setName(QString arg);

void setAddress(QString arg);

void setDbusPath(QString arg);

void setStatus(QString arg);

void setConnected(bool arg);

void setBusy(bool arg)
{
    if (m_busy == arg)
        return;

    m_busy = arg;
    emit busyChanged(arg);
}

protected:
    QString m_address;
    QString m_name;
    DeviceManager* manager;
    QString m_dbusPath;

    QVariant getProperty(QString name);
};

//} // namespace bluetooth

#endif // BLUETOOTH_DEVICE_H
