import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import bluetooth 1.0

Item {
    width: 640
    height: 480

    property alias button3: button3
    property alias button2: button2
    property alias button1: button1

    DeviceManager{
        id: manager
        basePath: "/org/bluez/hci0"
        powered: powerSwitch.checked
    }

    Timer{
        repeat:true
        triggeredOnStart: true
        running: true
        onTriggered: manager.update()
        interval: 3000
    }


    RowLayout {
        anchors.fill: parent

        Column{
            Switch{
                id:powerSwitch
                checked: manager.powered
                //onClicked: manager.powered=checked
            }


            Button {
                id: button1
                text: qsTr("update")
                onClicked:  manager.update()
            }

            Button {
                id: button2
                text: qsTr("scan")
                onClicked: manager.startScanning()
            }

            Button {
                id: button3
                text: qsTr("Press Me 3")
            }
        }
        ColumnLayout{

            ListView{
                model: manager.devices
                anchors.fill: parent
                delegate:  DeviceDelegate {


                }
            }
        }
    }
}
