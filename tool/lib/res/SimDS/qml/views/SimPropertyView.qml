import Qt.labs.qmlmodels 1.0

import QtQuick 2.14

import SimDS 1.0

TableView {

    id: table

    property real titleWidth: 320.0
    property real valueWidth: 160.0

    width: 480.0 + SimControl.Spacing._01px; height: rows * SimControl.Size._32px + rows * rowSpacing

    columnSpacing: SimControl.Spacing._01px; rowSpacing: SimControl.Spacing._01px

    clip: true

    delegate: Rectangle {

        implicitWidth: column === 0x00 ? table.titleWidth : table.valueWidth; implicitHeight: SimControl.Size._32px

        color: column === 0x00 ? SimPalette.colors.grey[1500] : ( row % 0x02 ? SimPalette.colors.grey[1400] : SimPalette.colors.grey[1300] )

        border { color: SimPalette.colors.grey[1300] }

        SimLabel {

            id: label

            property bool hovered: false

            anchors { left: parent.left; leftMargin: SimControl.Margin._08px; verticalCenter: parent.verticalCenter }

            font { weight: column === 0x00 ? Font.DemiBold : (hovered ? Font.DemiBold : Font.Normal) }

            text: display
        }

        MouseArea {

            anchors.fill: parent

            hoverEnabled: true

            onEntered: label.hovered = true
            onExited: label.hovered = false
        }
    }
}
