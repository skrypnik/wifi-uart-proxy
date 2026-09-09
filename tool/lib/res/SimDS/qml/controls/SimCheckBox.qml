import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

CheckBox {

    id: control

    width: SimControl.Size._20px; height: SimControl.Size._20px

    indicator: Rectangle {

        implicitWidth: SimControl.Size._20px; implicitHeight: SimControl.Size._20px

        color: control.checkState === Qt.Unchecked ? SimPalette.colors.grey[1500] : SimPalette.colors.blue[700]

        border.color: control.checkState === Qt.Unchecked ? SimPalette.colors.grey[600] : SimPalette.colors.blue[700]

        Image {

            anchors.centerIn: parent

            source: "qrc:/SimDS/svg/controls/CheckBoxChecked.svg"

            visible: control.checkState === Qt.Checked
        }

        Image {

            anchors.centerIn: parent

            source: "qrc:/SimDS/svg/controls/CheckBoxPartiallyChecked.svg"

            visible: control.checkState === Qt.PartiallyChecked
        }
    }
}
