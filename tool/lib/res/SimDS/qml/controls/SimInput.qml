import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

TextField {

    property real size: SimControl.Size._32px

    height: size

    color: SimPalette.colors.grey[0]

    font.pixelSize: SimControl.Font._17px

    placeholderTextColor: SimPalette.colors.grey[900]

    background: Rectangle {

        implicitWidth: 200.0; implicitHeight: SimControl.Size._32px

        border.color: acceptableInput ? (parent.focus ? SimPalette.colors.blue[700] : (parent.hovered ? SimPalette.colors.grey[900] : SimPalette.colors.grey[1100])) : SimPalette.colors.red[900]

        color: SimPalette.colors.grey[1500]

        Image {

            anchors { verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: SimControl.Margin._08px }

            source: "qrc:/SimDS/svg/controls/Error.svg"

            visible: !acceptableInput
        }
    }
}
