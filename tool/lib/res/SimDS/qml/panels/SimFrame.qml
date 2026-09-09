import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

Frame {

    id: frame

    padding: SimControl.Padding._14px

    background: Rectangle {

        color: SimPalette.colors.grey[1400]

        border.color: SimPalette.colors.grey[1300]
    }

    Component.onCompleted: {

        frame.width = contentItem.childrenRect.width + SimControl.Padding._14px * 2.0
        frame.height = contentItem.childrenRect.height + SimControl.Padding._14px * 2.0
    }
}
