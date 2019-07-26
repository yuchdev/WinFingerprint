import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles.Desktop 1.0

Item {

    property int edit_range: 5

    id: win_ids_tab
    width: main_window.width / 2
    height: main_window.height
    property alias five_guid_text: five_guid_text
    property alias four_guid_text: four_guid_text
    property alias third_guid_text: third_guid_text
    property alias second_guid_text: second_guid_text
    property alias first_guid_text: first_guid_text

    property alias install_date_text: install_date_text
    property alias four_id_text: four_id_text
    property alias third_id_text: third_id_text
    property alias second_id_text: second_id_text
    property alias first_id_text: first_id_text
    property alias combobox_prodict_number: combobox_prodict_number
    property alias combobox_product_type: combobox_product_type
    property alias combobox_edition: combobox_edition
    property alias combobox_update: combobox_update
    property alias combobox_system_name: combobox_system_name
    property alias combos_rct: combos_rct
    antialiasing: true

    Rectangle {
        id: winids_rectangle
        x: 8
        y: 43
        width: parent.width
        height: parent.height
        color: bg_grupbox_color

        Rectangle {
            id: lbls_rtc
            width: 123
            height: 255
            color: bg_grupbox_color

            Label {
                id: build_number_lbl
                x: 16
                y: 24
                width: 107
                height: 20
                text: qsTr("System Name")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Label {
                id: build_lab_lbl
                x: 15
                y: 49
                width: 107
                height: 20
                text: qsTr("Service Pack/Update")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Label {
                id: build_lab_ex_lbl
                x: 15
                y: 75
                width: 107
                height: 20
                text: qsTr("Edition")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Label {
                id: build_guid_lbl
                x: 15
                y: 101
                width: 107
                height: 20
                text: qsTr("Product type")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Label {
                id: crypto_machine_guid_lbl
                x: 15
                y: 127
                width: 107
                height: 20
                text: qsTr("Product ID")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Label {
                id: device_guid_lbl
                x: 15
                y: 153
                width: 107
                height: 20
                text: qsTr("Build number")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Label {
                id: ckcl_guid_lbl
                x: 15
                y: 179
                width: 107
                height: 20
                text: qsTr("Install date")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Label {
                id: harware_guid_lbl
                x: 15
                y: 205
                width: 107
                height: 20
                text: qsTr("Build GUID")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            GroupBox {
                id: current_version_groubbox
                x: 8
                y: 8
                width: 398
                height: 241
                title: qsTr("Current Version")
            }
        }

        Rectangle {
            id: combos_rct
            x: 121
            y: 0
            width: 290
            height: 255
            color: bg_grupbox_color

            ComboBox {
                id: combobox_system_name
                x: 8
                y: 25
                width: 266
                height: 20
                editable: false
                antialiasing: true
                textRole: "display"
                model: SystemNameModel
                enabled: WindowsIDS.system_name_acive
            }

            ComboBox {
                id: combobox_update
                x: 8
                y: 49
                width: 266
                height: 20
                editable: false
                antialiasing: true
                textRole: "display"
                model: ServiceUpdateModel
                enabled: WindowsIDS.service_update_active
            }

            ComboBox {
                id: combobox_edition
                x: 8
                y: 75
                width: 266
                height: 20
                editable: false
                antialiasing: true
                textRole: "display"
                model: EditionModel
                enabled: WindowsIDS.edition_active
            }

            ComboBox {
                id: combobox_product_type
                x: 8
                y: 101
                width: 266
                height: 20
                editable: false
                antialiasing: true
                textRole: "display"
                model: ProductTypeModel
                enabled: WindowsIDS.product_type_active
            }

            ComboBox {
                id: combobox_prodict_number
                x: 8
                y: 153
                width: 266
                height: 20
                editable: false
                antialiasing: true
                textRole: "display"
                model: BuildNumberModel
                enabled: WindowsIDS.build_number_active
            }

            RowLayout {
                id: product_id_input_rct
                x: 8
                y: 127
                width: 266
                height: 20

                TextField {
                    id: first_id_text
                    x: 0
                    width: 40
                    text: WindowsIDS.product_id_1
                    height: product_id_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 5
                    enabled: WindowsIDS.product_id_active

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: first_id_text.width
                            implicitHeight: first_id_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }

                    validator: RegExpValidator {
                        regExp: /(\d{5})?$/
                    }
                }

                TextField {
                    id: second_id_text
                    width: 24
                    text: WindowsIDS.product_id_2
                    height: product_id_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 3
                    enabled: WindowsIDS.product_id_active

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: second_id_text.width
                            implicitHeight: second_id_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }

                    validator: RegExpValidator {
                        regExp: /(\d{3})?$/
                    }
                }

                TextField {
                    id: third_id_text
                    width: 92
                    text: WindowsIDS.product_id_3
                    height: product_id_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 7
                    enabled: WindowsIDS.product_id_active

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: third_id_text.width
                            implicitHeight: third_id_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }

                    validator: RegExpValidator {
                        regExp: /(\d{7})?$/
                    }
                }

                TextField {
                    id: four_id_text
                    width: 92
                    text: WindowsIDS.product_id_4
                    height: product_id_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 5
                    enabled: WindowsIDS.product_id_active

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: four_id_text.width
                            implicitHeight: four_id_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }

                    validator: RegExpValidator {
                        regExp: /(\d{5})?$/
                    }
                }
            }

            TextField {
                id: install_date_text
                x: 8
                y: 179
                width: 266
                height: 20
                maximumLength: 10
                enabled: WindowsIDS.install_date_active

                style: TextFieldStyle {
                    textColor: "black"
                    background: Rectangle {
                        radius: 2
                        implicitWidth: install_date_text.width
                        implicitHeight: install_date_text.height
                        border.color: "#333"
                        border.width: 1
                        color: "#EAEAEA"
                    }
                }

                validator: RegExpValidator {
                    regExp: /(\d{1,2})([.,]\d{1,2})([.,]\d{4})?$/
                }
            }

            RowLayout {
                id: build_guid_input_rct
                x: 8
                y: 205
                width: 266
                height: 20

                TextField {
                    id: first_guid_text
                    width: 56
                    text: WindowsIDS.guid_1
                    height: build_guid_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 8
                    enabled: true

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: first_guid_text.width
                            implicitHeight: first_guid_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }
                }

                TextField {
                    id: second_guid_text
                    width: 32
                    text: WindowsIDS.guid_2
                    height: build_guid_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 4
                    enabled: true

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: second_guid_text.width
                            implicitHeight: second_guid_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }
                }

                TextField {
                    id: third_guid_text
                    width: 32
                    text: WindowsIDS.guid_3
                    height: build_guid_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 4
                    enabled: true

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: third_guid_text.width
                            implicitHeight: third_guid_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }
                }

                TextField {
                    id: four_guid_text
                    width: 32
                    text: WindowsIDS.guid_4
                    height: build_guid_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 4
                    enabled: true

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: four_guid_text.width
                            implicitHeight: four_guid_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }
                }

                TextField {
                    id: five_guid_text
                    width: 95
                    text: WindowsIDS.guid_5
                    height: build_guid_input_rct.height
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    maximumLength: 12
                    enabled: true

                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            radius: 2
                            implicitWidth: five_guid_text.width
                            implicitHeight: five_guid_text.height
                            border.color: "#333"
                            border.width: 1
                            color: "#EAEAEA"
                        }
                    }
                }
            }
        }
    }
}
