import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

GroupBox {

    id: control

    signal edit()

    enum Controls {

        None = 0x00,
        Edit = 0x01
    }

    property int controls: SimPanel.Controls.None

    leftPadding: SimControl.Padding._14px; topPadding: SimControl.Padding._14px + label.height; rightPadding: SimControl.Padding._14px; bottomPadding: SimControl.Padding._14px

    background: Rectangle {

        width: parent.contentWidth + parent.leftPadding + parent.rightPadding; height: parent.contentHeight + parent.topPadding + parent.bottomPadding

        color: SimPalette.colors.grey[1400]

        border.color: SimPalette.colors.grey[1300]
    }

    label: Rectangle {

        width: parent.contentWidth + parent.leftPadding + parent.rightPadding; height: SimControl.Size._32px

        color: SimPalette.colors.grey[1600]

        border.color: SimPalette.colors.grey[1300]

        Text {

            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: SimControl.Margin._08px }

            font { pixelSize: SimControl.Font._17px; weight: Font.DemiBold }

            color: SimPalette.colors.grey[0]

            text: control.title
        }

        Row {

            spacing: SimControl.Spacing._08px

            anchors { verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: SimControl.Margin._08px }

            SimMiniature {

                width: SimControl.Size._20px; height: SimControl.Size._20px

                visible: control.controls & SimPanel.Controls.Edit

                icon: "qrc:/SimDS/svg/controls/Edit.svg"

                onClicked: edit()
            }
        }
    }
}
