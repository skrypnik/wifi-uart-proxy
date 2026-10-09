import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

import QtQuick.Layouts 1.15

import AppUI 1.0
import SimDS 1.0

ApplicationWindow
{
    id: mainView

    minimumWidth: page.width; minimumHeight: engine.device.ready ? page.height : 300.0
    maximumWidth: page.width; maximumHeight: engine.device.ready ? page.height : 300.0

    title: "Конфигуратор"

    visible: true

    StackLayout {

        anchors { fill: parent }

        currentIndex: engine.device.ready ? 0x01 : 0x00

        SimPage {

            id: splash

            Column {

                id: search

                anchors { centerIn: parent }

                spacing: SimControl.Spacing._14px

                SimLabel {

                    anchors { horizontalCenter: search.horizontalCenter }

                    font { pixelSize: SimControl.Font._24px }

                    text: "Ожидание подключения"
                }

                SimLabel {

                    anchors { horizontalCenter: search.horizontalCenter }

                    text: "Переключите устройство в режим конфигурации"
                }

                SimSpinner {

                    anchors { horizontalCenter: search.horizontalCenter }

                    enabled: true
                }
            }
        }

        SimPage {

            id: page

            width: column.width + SimControl.Margin._14px * 2.0; height: column.height + commit.height + SimControl.Margin._14px * 4.0

            Column {

                id: column

                anchors { left: parent.left; top: parent.top; margins: SimControl.Margin._14px }

                spacing: SimControl.Spacing._14px

                WLANInfoView {
                }

                ELANInfoView {
                }

                UARTInfoView {
                }
            }

            SimButton {

                id: commit

                width: column.width

                anchors { left: column.left; top: column.bottom; topMargin: SimControl.Margin._14px * 2.0 }

                text: "Записать изменения"

                onClicked: {

                    engine.device.commitChanges()
                }
            }
        }
    }
}
