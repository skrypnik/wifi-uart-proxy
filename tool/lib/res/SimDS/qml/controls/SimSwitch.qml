import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

Control {

    id: control

    property bool checked: false

    width: 40.0; height: 20.0

    background: Rectangle {

        radius: 10.0

        color: control.checked ? (control.hovered ? SimPalette.colors.blue[500] : SimPalette.colors.blue[600]) : (control.hovered ? SimPalette.colors.grey[1000] : SimPalette.colors.grey[1100])

        border { color: SimPalette.colors.grey[900] }
    }

    Rectangle {

        x: control.checked ? 22.0 : 2.0

        width: 16.0; height: 16.0; radius: 8.0

        anchors { verticalCenter: control.verticalCenter }

        color: SimPalette.colors.grey[0]
    }

    MouseArea {

        anchors.fill: parent

        onClicked: control.checked = !control.checked
    }
}
