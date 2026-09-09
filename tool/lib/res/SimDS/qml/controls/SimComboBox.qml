import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

Item {

    property alias title: title
    property alias combo: combo

    width: combo.width; height: column.height + SimControl.Spacing._08px

    Column {

        id: column

        anchors { left: parent.left; right: parent.right }

        spacing: SimControl.Spacing._08px

        SimLabel {

            id: title

            color: SimPalette.colors.grey[0]
        }

        SimCombo {

            id: combo
        }
    }
}
