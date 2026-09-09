import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

GroupBox {

    id: window

    signal close()

    leftPadding: SimControl.Padding._14px; topPadding: SimControl.Padding._14px + label.height; rightPadding: SimControl.Padding._14px; bottomPadding: SimControl.Padding._14px

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 10.0
    Drag.hotSpot.y: 10.0

    background: Rectangle {

        color: SimPalette.colors.grey[1400]

        border.color: SimPalette.colors.grey[1300]
    }

    label: Rectangle {

        id: label

        width: parent.width; height: SimControl.Size._40px

        color: SimPalette.colors.grey[1600]

        border.color: SimPalette.colors.grey[1300]

        MouseArea {

            id: dragArea

            anchors.fill: parent

            drag.target: window
        }

        Text {

            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: SimControl.Margin._12px }

            font { pixelSize: SimControl.Font._19px; weight: Font.DemiBold }

            color: SimPalette.colors.grey[0]

            text: window.title
        }

        SimMiniature {

            width: SimControl.Size._20px; height: SimControl.Size._20px

            anchors { verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: SimControl.Margin._12px }

            icon: "qrc:/SimDS/svg/controls/Close.svg"

            onClicked: close()
        }
    }

    Component.onCompleted: {

        window.width = contentItem.childrenRect.width + SimControl.Padding._14px * 2.0
        window.height = label.height + contentItem.childrenRect.height + SimControl.Padding._14px * 2.0
    }
}
