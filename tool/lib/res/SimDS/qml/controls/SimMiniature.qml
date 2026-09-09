import QtGraphicalEffects 1.15
import QtQuick 2.7

import SimDS 1.0

Item {

    signal clicked()

    /**
     * Miniature icon source alias
     */
    property alias icon: icon.source

    /**
     * Hovered property
     */
    property bool hovered: false

    width: SimControl.Size._24px; height: SimControl.Size._24px

    Image {

        id: icon

        width: parent.width; height: parent.height

        anchors.centerIn: parent
    }

    ColorOverlay {

        id: overlay

        anchors { fill: icon }

        source: icon

        visible: false

        color: SimPalette.colors.grey[0]
    }

    MouseArea {

        anchors.fill: parent

        propagateComposedEvents: true

        hoverEnabled: true

        onClicked: parent.clicked()

        onEntered: {

            parent.hovered = true
            overlay.visible = true
        }

        onExited: {

            parent.hovered = false
            overlay.visible = false
        }
    }
}
