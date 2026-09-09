import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

GroupBox {

    id: dialog

    signal accept()
    signal reject()

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 10.0
    Drag.hotSpot.y: 10.0

    leftPadding: SimControl.Padding._14px; topPadding: SimControl.Padding._14px + label.height; rightPadding: SimControl.Padding._14px; bottomPadding: SimControl.Padding._14px

    background: Rectangle {

        color: SimPalette.colors.grey[1400]

        border.color: SimPalette.colors.grey[1300]
    }

    label: Rectangle {

        width: parent.width; height: SimControl.Size._40px

        color: SimPalette.colors.grey[1600]

        MouseArea {

            id: dragArea

            anchors.fill: parent

            drag.target: dialog
        }

        Text {

            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: SimControl.Margin._12px }

            font { pixelSize: SimControl.Font._19px; weight: Font.DemiBold }

            color: SimPalette.colors.grey[0]

            text: dialog.title
        }

        SimMiniature {

            width: SimControl.Size._20px; height: SimControl.Size._20px

            anchors { verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: SimControl.Margin._12px }

            icon: "qrc:/SimDS/svg/controls/Close.svg"

            onClicked: {

                dialog.visible = false

                dialog.reject()
            }
        }
    }

    contentItem: Rectangle {

        color: SimPalette.colors.grey[1400]

        Row {

            anchors { left: parent.left; bottom: parent.bottom }

            spacing: SimControl.Spacing._14px

            SimButton {

                id: reject

                scheme: SimControl.Scheme.Secondary

                text: "Отклонить"

                onClicked: {

                    dialog.visible = false

                    dialog.reject()
                }
            }

            SimButton {

                id: accept

                scheme: SimControl.Scheme.Primary

                text: "Принять"

                onClicked: {

                    dialog.visible = false

                    dialog.accept()
                }
            }
        }
    }

    Component.onCompleted: {

        dialog.width = contentItem.childrenRect.width + SimControl.Padding._14px * 2.0
        dialog.height = label.height + contentItem.childrenRect.height + SimControl.Size._32px + SimControl.Padding._14px * 3.0
    }
}