import QtQuick 2.4
import QtQuick.Window 2.11
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as OldControl

Item {
    id: settings_form
    width: 400
    height: 300
    property alias number_uniq_configs: number_uniq_configs
    property alias count_auto_export: count_auto_export
    property alias max_number_checkbox: max_number_checkbox
    property alias auto_export_checkbox: auto_export_checkbox
    property alias display_ids_checkbox: display_ids_checkbox
    property alias start_checkbox: start_checkbox
    property alias apply_settings_btn: apply_settings_btn
    property color bg_grupbox_color: "#555F71"
    property color groupbox_border_color: "#000000"
    property color bg_tabbutton_active_color: "#404457"
    property color bg_tabbutton_not_active_color: "#8E929D"
    property int button_width: 90
    property int button_height: 30

    Rectangle {
        anchors.fill: parent
        color: bg_grupbox_color
    }

    Button {
        id: apply_settings_btn
        text: qsTr("OK")
        transformOrigin: Item.Center
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        width: button_width
        height: button_height
        x: parent.width / 2 - button_width / 2
        y: parent.height - 30
        background: Rectangle {
            radius: 2
            implicitHeight: parent.height
            implicitWidth: parent.width
            anchors.fill: parent
            border.color: "#000000"
            border.width: 1
            color: apply_settings_btn.pressed ? "#555F71" : "#BBBFC6"
            Text {
                id: apply_settings_text
                clip: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    GroupBox {
        id: settings_groupBox
        x: 8
        y: 8
        width: parent.width - 15
        height: parent.height - 50
        title: qsTr("")

        background: Rectangle {
            width: parent.width
            height: parent.height
            border.color: groupbox_border_color
            border.width: 1
            color: bg_grupbox_color
            radius: 2
        }

        OldControl.CheckBox {
            id: start_checkbox
            y: 0
            width: 177
            height: 20
            text: qsTr("   Start with the operation system")
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        OldControl.CheckBox {
            id: display_ids_checkbox
            x: 9
            y: 26
            width: 260
            height: 20
            text: qsTr("Display all identifiers, includeing GUIDs and IDs")
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        OldControl.CheckBox {
            id: auto_export_checkbox
            x: 0
            y: 52
            width: 260
            height: 20
            text: qsTr("Automatic export all generated configurations")
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        OldControl.CheckBox {
            id: max_number_checkbox
            x: -1
            y: 78
            width: 260
            height: 20
            text: qsTr("Maximum number of autosaved configurations")
            anchors.leftMargin: 0
            anchors.left: parent.left

            OldControl.TextField {
                id: count_auto_export
                enabled: max_number_checkbox.checked
                x: 294
                y: 0
                width: 40
                height: 20
                maximumLength: 3
            }
        }

        OldControl.Label {
            id: label
            x: 0
            y: 104
            width: 260
            height: 20
            text: qsTr("Number of consequent unique configurations ")

            OldControl.TextField {
                id: number_uniq_configs
                x: 294
                y: 0
                width: 40
                height: 20
                maximumLength: 3
            }
        }
    }
}




/*##^## Designer {
    D{i:7;anchors_height:31;anchors_width:360;anchors_x:0;anchors_y:0}D{i:8;anchors_height:31;anchors_width:360;anchors_x:0;anchors_y:0}
}
 ##^##*/
