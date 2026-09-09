import QtQuick 2.7

import SimDS 1.0

Item {

    id: panel

    /**
     * Minimum scale value
     */
    property real min: 0.0

    /**
     * Maximum scale value
     */
    property real max: 0.0

    /**
     * Current value
     */
    property real value: 0.0

    /**
     * Current value index in scale repeater
     */
    readonly property int valueIndex: scale.count * (value - min) / (max - min)

    implicitWidth: 375.0; implicitHeight: SimControl.Size._32px

    Repeater {

        id: scale

        width: panel.implicitWidth; height: SimControl.Size._32px

        model: width / 4.0

        delegate: Rectangle {

            x: index * 4.0; y: 0.0

            width: 3.0; height: SimControl.Size._32px

            color: index <= panel.valueIndex ? SimPalette.colors.blue[600] : SimPalette.colors.grey[900]
        }
    }
}