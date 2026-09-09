import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

Button {

    readonly property real buttonPadding: size < SimControl.Size._40px ? SimControl.Padding._12px : SimControl.Padding._16px

    property int scheme: SimControl.Scheme.Primary

    property real size: SimControl.Size._32px

    height: size

    leftPadding: buttonPadding; rightPadding: buttonPadding

    font { pixelSize: SimControl.Font._17px; weight: Font.Medium }

    palette {

        button: scheme === SimControl.Scheme.Primary ? SimPalette.colors.blue[700] : SimPalette.colors.grey[1200]
        buttonText: SimPalette.colors.grey[0]

        highlight: scheme === SimControl.Scheme.Primary ? SimPalette.colors.blue[500] : SimPalette.colors.grey[1100]
        highlightedText: SimPalette.colors.grey[0]
    }

    contentItem: Text {

        text: parent.text
        font: parent.font

        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter

        color:  parent.down ? palette.buttonText : palette.buttonText
    }

    background: Rectangle {

        implicitWidth: 120.0; implicitHeight: SimControl.Size._32px

        border {

            width: 2.0; color: parent.hovered ? palette.highlight : palette.button
        }

        color: (parent.down || !parent.enabled ) ? palette.highlight : palette.button
    }
}
