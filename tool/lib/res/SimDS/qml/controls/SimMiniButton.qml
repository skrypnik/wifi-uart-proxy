import QtQuick 2.7

import SimDS 1.0

Rectangle {

    id: button

    signal clicked()

    /**
     * Button hint text
     */
    property alias hint: hint.text

    /**
     * Miniature icon source alias
     */
    property alias icon: icon.source

    /**
     * Selected property for flat button
     */
    property bool selected: false

    /**
     * Horizontal hint orientation
     */
    property int horizontalHintOrientation: SimControl.HorizontalOrientation.Left

    /**
     * Vertical hint orientation
     */
    property int verticalHintOrientation: SimControl.VerticalOrientation.Top

    width:  SimControl.Size._40px; height: SimControl.Size._40px

    color: SimPalette.colors.grey[1400]

    border { color: selected ? SimPalette.colors.blue[500] : SimPalette.colors.grey[0] }

    Image {

        id: icon

        width:  SimControl.Size._24px; height:  SimControl.Size._24px

        anchors.centerIn: parent
    }

    SimLabel {

        id: hint

        anchors {

            readonly property real rightOrientationMargin: -hint.contentWidth + button.width
            readonly property real bottomOrientationMargin: -hint.contentHeight - button.height - SimControl.Margin._02px

            left: parent.left
            bottom: parent.top

            leftMargin: parent.horizontalHintOrientation === SimControl.HorizontalOrientation.Left ? 0.0 : rightOrientationMargin
            bottomMargin: parent.verticalHintOrientation === SimControl.VerticalOrientation.Top ? SimControl.Margin._02px : bottomOrientationMargin
        }

        visible: false
    }

    MouseArea {

        anchors.fill: parent

        hoverEnabled: true

        onClicked: {

            button.clicked()
        }

        onEntered: {

            hint.visible = true
        }

        onExited: {

            hint.visible = false
        }
    }
}