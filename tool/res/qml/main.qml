import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

ApplicationWindow
{
    id: mainView

    width: 1920.0; height: 1080.0

    title: "УППУ Моно DC"

    visible: true

    Row {

        anchors { centerIn: parent }

        spacing: 20.0

        Button {

            text: qsTr("Установить соединение")

            onClicked: {

                engine.connectToHost()
            }
        }

        Button {

            text: qsTr("Разорвать соединение")

            onClicked: {

                engine.disconnectFromHost()
            }
        }
    }

    Component.onCompleted: {

    }
}
