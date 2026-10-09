import Qt.labs.qmlmodels 1.0

import QtQuick 2.7

import SimDS 1.0

SimPanel {

    title: "Параметры UART"

    controls: SimPanel.Controls.Edit

    Column {

        SimPropertyView {

            id: table

            titleWidth: 310.0

            model: TableModel {

                TableModelColumn {

                    display: "title"
                }

                TableModelColumn {

                    display: "value"
                }

                rows: engine.device === null ? [] : [

                    {
                        "title": "Скорость UART",
                        "value": engine.device.speed
                    },

                    {
                        "title": "Количество бит UART",
                        "value": engine.device.bits
                    },

                    {
                        "title": "Количество стоп бит UART",
                        "value": engine.device.stop
                    }
                ]
            }
        }

        Column {

            width: table.width

            visible: !table.visible

            spacing: SimControl.Spacing._08px

            Row {

                spacing: SimControl.Spacing._14px

                SimInputBox {

                    id: speed

                    title.text: "Скорость UART"

                    input.text: engine.device.speed
                }

                SimInputBox {

                    id: bits

                    title.text: "Количество бит UART"

                    input.text: engine.device.bits
                }
            }

            Row {

                spacing: SimControl.Spacing._14px

                SimInputBox {

                    id: stop

                    title.text: "Количество стоп бит UART"

                    input.text: engine.device.stop
                }

                SimButton {

                    anchors { bottom: stop.bottom }

                    scheme: SimControl.Scheme.Secondary

                    text: "Отмена"

                    onClicked: {

                        table.visible = true
                    }
                }

                SimButton {

                    anchors { bottom: stop.bottom }

                    text: "Применить"

                    onClicked: {

                        engine.device.changeUARTConfig(speed.input.text, bits.input.text, stop.input.text)

                        table.visible = true
                    }
                }
            }
        }
    }

    onEdit: table.visible = false
}