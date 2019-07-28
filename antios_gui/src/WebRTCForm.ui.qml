import QtQuick 2.4
import QtQuick.Controls 1.4 as OldControls
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles.Desktop 1.0

Item {
    id: webrtc_form
    width: main_window.width / 2 - 200
    height: main_window.height

    property int groupbox_margin: 10

    Rectangle {
        id: webrtc_rct
        x: 0
        y: 25
        width: parent.width
        height: parent.height
        color: bg_grupbox_color

        GroupBox {
            id: webrtc_groubbox
            x: 0
            y: 10
            width: 415
            height: 268
            contentWidth: 3
            title: qsTr("WebRTC")

            Label {
                id: algorithm_lbl
                x: 0
                y: 13
                width: 103
                height: 13
                text: qsTr("WebRTC Algorithm:")
            }

            OldControls.ComboBox {
                id: algorithm_box
                x: 120
                y: 6
                width: 271
                height: 20
            }

            Label {
                id: ip_address_lbl
                x: 0
                y: 32
                width: 103
                height: 18
                text: qsTr("Ip Address:")
            }

            OldControls.TextField {
                id: ip_address_text
                x: 120
                y: 32
                width: 271
                height: 18
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                maximumLength: 15
                enabled: true //WindowsIDS.product_id_active

//                text: ((SettingsCPP.dns1 === "") ? "" : SettingsCPP.dns1)
//                                placeholderText: text === "" ? "0.0.0.0" : ""

                placeholderText: "0.0.0.0"


                style: TextFieldStyle {
                    textColor: "black"
                    background: Rectangle {
                        radius: 2
                        implicitWidth: ip_address_text.width
                        implicitHeight: ip_address_text.height
                        border.color: "#333"
                        border.width: 1
                        color: "#EAEAEA"
                    }
                }

                validator: RegExpValidator {
                    regExp: /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                }
            }
        }
    }
}
