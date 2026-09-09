import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

GroupBox {

    leftPadding: SimControl.Padding._00px; topPadding: SimControl.Padding._20px + label.height; rightPadding: SimControl.Padding._12px; bottomPadding: SimControl.Padding._12px

    background: Item {

    }

    label: Text {

        font { pixelSize: SimControl.Font._19px; weight: Font.Medium }

        color: SimPalette.colors.grey[0]

        text: parent.title
    }
}
