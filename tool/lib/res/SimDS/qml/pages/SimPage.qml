import QtQuick 2.7

import SimDS 1.0

Item {

    DropArea {

        id: dropArea

        anchors { fill: parent; margins: SimControl.Margin._12px }
    }

    Rectangle {

        anchors {

            fill: parent
        }

        color: dropArea.containsDrag ? SimPalette.colors.grey[1600] : SimPalette.colors.grey[1500]
    }
}