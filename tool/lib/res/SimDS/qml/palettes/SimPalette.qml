pragma Singleton

import QtQuick 2.7

Item {

    readonly property QtObject colors: QtObject {

        property var red: {

            300: "#FE989B",
            500: "#D4655E",
            600: "#CF5148",
            700: "#C63228",
            900: "#AA1E22"
        }

        readonly property var grey: {

            0:    "#FCFCFD",
            100:  "#F4F5F5",
            200:  "#EBECEC",
            300:  "#DEDFE0",
            400:  "#D3D4D5",
            500:  "#C8CACC",
            600:  "#BDBFC1",
            700:  "#B3B5B7",
            800:  "#A7A9AC",
            900:  "#919599",
            1000: "#686D71",
            1100: "#45494D",
            1200: "#3A3D40",
            1300: "#303234",
            1400: "#282B2D",
            1500: "#212325",
            1600: "#1B1C1D"
        }

        readonly property var blue: {

            100: "#E9F2FB",
            200: "#CBD9F6",
            300: "#9FBAEF",
            400: "#7CA0E9",
            500: "#5081E2",
            600: "#3A71DE",
            700: "#1F54BC",
            800: "#1A469D",
            900: "#153167"
        }

        readonly property QtObject status: QtObject {

            property color green:  "#07994A"
            property color yellow: "#FACF00"
            property color red:    "#EA2A35"
            property color grey:   "#919599"
        }
    }
}
