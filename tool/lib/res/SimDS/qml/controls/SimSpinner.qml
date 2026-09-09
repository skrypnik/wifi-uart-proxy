import QtQuick 2.7

import SimDS 1.0

ListView {

    id: view

    property color color: SimPalette.colors.blue[700]

    width: SimControl.Size._08px * 4.0 + SimControl.Spacing._04px * 3.0; height: SimControl.Size._08px

    spacing: SimControl.Spacing._04px

    orientation: ListView.Horizontal

    model: 0x04

    delegate: Item {

        width: SimControl.Size._08px; height: SimControl.Size._08px

        Rectangle {

            readonly property real size: index === currentIndex ? SimControl.Size._08px : SimControl.Size._04px

            width: size; height: size

            anchors.centerIn: parent

            color: view.color
        }
    }

    Timer {

        interval: 500; running: true; repeat: true

        onTriggered: {

            parent.currentIndex++

            if (parent.currentIndex === 0x04) parent.currentIndex = 0x00
        }
    }

    Component.onCompleted: {

        currentIndex = 0x00
    }
}