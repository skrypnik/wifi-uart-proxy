import Qt.labs.qmlmodels 1.0

import QtQuick 2.7

import SimDS 1.0

SimPanel {

    title: "Беспроводная сеть"

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
                        "title": "SSID беспроводной сети",
                        "value": engine.device.ssid
                    },

                    {
                        "title": "Пароль беспроводной сети",
                        "value": engine.device.password
                    },

                    {
                        "title": "Номер канала",
                        "value": engine.device.channel
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

                    id: ssid

                    title.text: "SSID беспроводной сети"

                    input.text: engine.device.ssid
                }

                SimInputBox {

                    id: password

                    title.text: "Пароль беспроводной сети"

                    input.text: engine.device.password
                }
            }

            Row {

                spacing: SimControl.Spacing._14px

                SimInputBox {

                    id: channel

                    title.text: "Номер канала"

                    input.text: engine.device.channel
                }

                SimButton {

                    anchors { bottom: channel.bottom }

                    scheme: SimControl.Scheme.Secondary

                    text: "Отмена"

                    onClicked: {

                        table.visible = true
                    }
                }

                SimButton {

                    anchors { bottom: channel.bottom }

                    text: "Применить"

                    onClicked: {

                        engine.device.changeWLANConfig(ssid.input.text, password.input.text, channel.input.text)

                        table.visible = true
                    }
                }
            }
        }
    }

    onEdit: table.visible = false
}
