import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

ComboBox {

    id: control

    leftPadding: SimControl.Padding._14px

    font { pixelSize: SimControl.Font._17px; weight: Font.Medium }

    popup: Popup {

        width: control.width

        implicitHeight: contentItem.implicitHeight

        padding: SimControl.Padding._01px

        contentItem: ListView {

            implicitHeight: contentHeight + SimControl.Margin._02px

            currentIndex: control.highlightedIndex

            model: control.popup.visible ? control.delegateModel : null

            clip: true
        }
    }
    background: Rectangle {

        implicitWidth: 200.0; implicitHeight: SimControl.Size._32px

        color: SimPalette.colors.blue[700]

        border.color: SimPalette.colors.grey[1200]
    }

    indicator: Image {

        anchors { right: parent.right; verticalCenter: parent.verticalCenter; rightMargin: SimControl.Margin._12px }

        source: parent.popup.opened ? "qrc:/SimDS/svg/controls/Hide.svg" : "qrc:/SimDS/svg/controls/Show.svg"
    }

    contentItem: Text {

        horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter

        font: parent.font

        color: SimPalette.colors.grey[0]

        text: parent.currentText
    }

    delegate: ItemDelegate {

        id: item

        width: parent.width; height: SimControl.Size._32px

        contentItem: Text {

            horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter

            color: SimPalette.colors.grey[0]

            text: modelData
        }

        background: Rectangle {

            width: parent.width; height: parent.height

            color: item.hovered ? SimPalette.colors.blue[700] : SimPalette.colors.grey[1500]
        }
    }
}