import QtQuick.Controls 2.15
import QtQuick 2.7

import SimDS 1.0

Label {

    property bool accent: false

    color: accent ? SimPalette.colors.blue[500] : SimPalette.colors.grey[0]

    font.pixelSize: SimControl.Font._17px

    background: Item {

    }
}
