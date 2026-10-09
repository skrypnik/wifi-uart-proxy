import Qt.labs.qmlmodels 1.0

import QtQuick 2.7

import SimDS 1.0

SimPanel {

    title: "Параметры сети"

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
                        "title": "Сетевой адрес",
                        "value": engine.device.address
                    },

                    {
                        "title": "Сетевая маска",
                        "value": engine.device.netmask
                    },

                    {
                        "title": "Сетевой порт",
                        "value": engine.device.netport
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

                    id: address

                    title.text: "Сетевой адрес"

                    input.text: engine.device.address
                }

                SimInputBox {

                    id: netmask

                    title.text: "Сетевая маска"

                    input.text: engine.device.netmask
                }
            }

            Row {

                spacing: SimControl.Spacing._14px

                SimInputBox {

                    id: netport

                    title.text: "Сетевой порт"

                    input.text: engine.device.netport
                }

                SimButton {

                    anchors { bottom: netport.bottom }

                    scheme: SimControl.Scheme.Secondary

                    text: "Отмена"

                    onClicked: {

                        table.visible = true
                    }
                }

                SimButton {

                    anchors { bottom: netport.bottom }

                    text: "Применить"

                    onClicked: {

                        engine.device.changeELANConfig(address.input.text, netmask.input.text, netport.input.text)

                        table.visible = true
                    }
                }
            }
        }
    }

    onEdit: table.visible = false
}