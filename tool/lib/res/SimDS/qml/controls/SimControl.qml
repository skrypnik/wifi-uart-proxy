pragma Singleton

import QtQuick 2.7

Item {

    enum Font {

        _16px = 16.0,
        _17px = 17.0,
        _19px = 19.0,
        _24px = 24.0,
        _28px = 28.0
    }

    enum Size {

        _04px = 4.0,
        _08px = 8.0,
        _20px = 20.0,
        _24px = 24.0,
        _28px = 28.0,
        _32px = 32.0,
        _40px = 40.0,
        _48px = 48.0
    }

    enum Padding {

        _00px = 0.0,
        _01px = 1.0,
        _04px = 4.0,
        _12px = 12.0,
        _14px = 14.0,
        _16px = 16.0,
        _20px = 20.0,
        _40px = 40.0,
        _48px = 48.0
    }

    enum Spacing {

        _01px = 1.0,
        _04px = 4.0,
        _06px = 6.0,
        _08px = 8.0,
        _14px = 14.0,
        _16px = 16.0,
        _40px = 40.0
    }

    enum Margin {

        _02px = 2.0,
        _04px = 4.0,
        _08px = 8.0,
        _12px = 12.0,
        _14px = 14.0
    }

    enum Scheme {

        Primary   = 0x00,
        Secondary = 0x01,
        Outline   = 0x02
    }

    enum HorizontalOrientation {

        Left  = 0x00,
        Right = 0x01
    }

    enum VerticalOrientation {

        Top    = 0x00,
        Bottom = 0x01
    }
}
