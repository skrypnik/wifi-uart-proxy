import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

Item {

    property alias title: title
    property alias input: input
    property alias about: about

    width: 200.0; height: column.height + about.height + SimControl.Spacing._08px

    Column {

        id: column

        anchors { left: parent.left; right: parent.right }

        spacing: SimControl.Spacing._08px

        SimLabel {

            id: title

            color: input.acceptableInput ? (parent.focus ? SimPalette.colors.blue[700] : SimPalette.colors.grey[0]) : SimPalette.colors.red[900]
        }

        SimInput {

            id: input
        }
    }

    SimLabel {

        id: about

        height: text.length ? font.pixelSize + SimControl.Margin._02px : 0.0

        anchors { left: column.left; top: column.bottom; topMargin: SimControl.Margin._02px }

        color: input.acceptableInput ? SimPalette.colors.grey[900] : SimPalette.colors.red[900]

        font.pixelSize: SimControl.Font._16px
    }
}
