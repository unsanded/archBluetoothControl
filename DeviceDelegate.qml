import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import bluetooth 1.0


RowLayout {
    SystemPalette{
        id:palette
    }
    BusyIndicator{
        visible: busy
    }

    Switch{
        id: connectSwitch
        checked: connected
        enabled: !busy
        onClicked: {
            if(checked)
                connect()
            else
                disconnect()
        }
    }



    Text {
        color: connected?"green":palette.text
        id: nameText
        text: name
        font.bold: true;
    }
    Button{
        id: connectButton
        text: connected? "disconnect" : "connect"
        onClicked: {
            if(connected)
                disconnect();
            else
                connect();
        }

    }
    Text{
        id: statusText
        text: status
        color: palette.text
    }
}



