import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

SimFrame {

    /**
     * Title item property alias
     */
    property alias title: title

    /**
     * Value item property alias
     */
    property alias value: value

    /**
     * Scale item property alias
     */
    property alias scale: scale

    SimLabel {

        id: title

        anchors { left: parent.left; top: parent.top }

        color: SimPalette.colors.grey[0]

        font { pixelSize: SimControl.Font._24px; weight: Font.Medium }
    }

    SimLabel {

        id: value

        anchors { left: parent.left; top: title.bottom; topMargin: SimControl.Margin._14px * 2.0 }

        color: SimPalette.colors.blue[500]

        font { pixelSize: SimControl.Font._28px; weight: Font.DemiBold }
    }

    SimRowScaleView {

        id: scale

        anchors { left: parent.left; top: value.bottom; topMargin: SimControl.Margin._12px }
    }

    SimLabel {

        anchors { left: scale.left; top: scale.bottom }

        color: SimPalette.colors.grey[900]

        font { weight: Font.Medium }

        text: scale.min
    }

    SimLabel {

        anchors { right: scale.right; top: scale.bottom }

        color: SimPalette.colors.grey[900]

        font { weight: Font.Medium }

        text: scale.max
    }
}