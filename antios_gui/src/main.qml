import QtQuick 2.1
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as OldControl


ApplicationWindow {
    id: main_window
    title: qsTr("AntiOS")

    visible: true

    width: 1100//1250
    height: 520

    minimumWidth  : width
    maximumWidth  : width
    minimumHeight : height
    maximumHeight : height

    property int    menu_bar_hegth:                 25
    property int    menu_item_width:                160
    property int    menu_item_heigth:               25
    property int    ident_from_menu:                10
    property int    tabs_width:                     81
    property int    tabbar_heigth:                  20
    property int    groupbox_border_width:          0
    property int    table_column_width:             200
    property int    button_width:                   90
    property int    button_height:                  30
    property color  bg_grupbox_color:               "#555F71"
    property color  groupbox_border_color:          "#000000"
    property color  bg_tabbutton_active_color:      "#404457"
    property color  bg_tabbutton_not_active_color:  "#8E929D"
    property color  bs_tabbutton_disabled:          "#555F71"
    property int    symmetrical_buttons_marging     : 100

    color: bg_grupbox_color

    menuBar: MenuBar {
        id: menu_bar
        width: main_window.width
        Menu {
            id: config_menu
            title: qsTr("Configuration")
            width: menu_item_width

            Menu {
                id: randomconfiguration_submenu; title: qsTr("Randomize configuration"); width: menu_item_width

                Action { id: all_menu_btn;          text: qsTr("All");          }
                Action { id: windows_ids_menu_btn;  text: qsTr("Windows IDs");  }
                Action { id: webrtc_menu_btn;       text: qsTr("WebRTC");       }
                Action { id: telemetry_menu_btn;    text: qsTr("Telemetry");  enabled: MainWindow.telemetry_active;  }
                Action { id: browser_menu_btn;      text: qsTr("Browser");      }
                Action { id: hardware_menu_btn;     text: qsTr("Hardware");     }

                delegate: MenuItem {
                    id: random_menu_item
                    implicitWidth: menu_item_width
                    implicitHeight: menu_item_heigth

                    arrow: Canvas {
                        x: parent.width - width
                        implicitWidth: 40
                        implicitHeight: 40
                        visible: random_menu_item.subMenu
                        onPaint: {
                            var ctx = getContext("2d")
                            ctx.fillStyle = random_menu_item.highlighted ? "#ffffff" : bg_grupbox_color
                            ctx.moveTo(15, 15)
                            ctx.lineTo(width - 15, height / 2)
                            ctx.lineTo(15, height - 15)
                            ctx.closePath()
                            ctx.fill()
                        }
                    }

                    indicator: Item {
                        implicitWidth: 40
                        implicitHeight: 40
                        Rectangle {
                            width: 26
                            height: 26
                            anchors.centerIn: parent
                            visible: random_menu_item.checkable
                            border.color: bg_grupbox_color
                            radius: 3
                            Rectangle {
                                width: 14
                                height: 14
                                anchors.centerIn: parent
                                visible: random_menu_item.checked
                                color: "black"
                                radius: 2
                            }
                        }
                    }

                    contentItem: Text {
                        text: random_menu_item.text
                        font: random_menu_item.font
                        opacity: enabled ? 1.0 : 0.3
                        color: random_menu_item.highlighted ? "#ffffff" : bg_grupbox_color
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        implicitWidth: 200
                        implicitHeight: 40
                        opacity: enabled ? 1 : 0.3
                        color: random_menu_item.highlighted ? "#999fa9" : "transparent"
                    }
                }
            }

            Action { id: export_menu_btn_btn; text: qsTr("Export configuration");             }
            Action { id: import_menu_btn_btn; text: qsTr("Import configuration");             }
            Action { id: rollback_menu_btn;   text: qsTr("Back to initial configuration");    }
            Action { id: quit_menu_btn;       text: qsTr("Quit");                             }

            delegate: MenuItem {
                id: menuItem
                implicitWidth: menu_item_width
                implicitHeight: menu_item_heigth

                arrow: Image {
                    id: arrow_image

                    width: 16
                    height: 10

                    x: menuItem.width - width - 2
                    y: 8

                    smooth: true
                    antialiasing: true
                    source: "qrc:/res/next.png"
                    visible: menuItem.subMenu
                }

                indicator: Item {
                    implicitWidth: 40
                    implicitHeight: 40
                    Rectangle {
                        width: 20
                        height: 20
                        anchors.centerIn: parent
                        visible: menuItem.checkable
                        border.color: bg_grupbox_color
                        radius: 3
                        Rectangle {
                            width: 14
                            height: 14
                            anchors.centerIn: parent
                            visible: menuItem.checked
                            color: "black"
                            radius: 2
                        }
                    }
                }

                contentItem: Text {
                    text: menuItem.text
                    font: menuItem.font
                    opacity: enabled ? 1.0 : 0.3
                    color: menuItem.highlighted ? "#ffffff" : bg_grupbox_color
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    anchors.leftMargin: 10
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 40
                    opacity: enabled ? 1 : 0.3
                    color: menuItem.highlighted ? "#999fa9" : "transparent"
                }
            }
        }

        Menu {
            id: option_menu;  title: qsTr("Options")
            width: menu_item_width

            Action { id: app_settings_menu_btn;    text: qsTr("Application settings"); onTriggered: { MainWindow.showSettings() } }
            Action { id: import_settings_menu_btn; text: qsTr("Import settings");      }
            Action { id: export_settings_menu_btn; text: qsTr("Export settings");      }

            delegate: MenuItem {
                id: menu_options_Item
                implicitWidth: menu_item_width
                implicitHeight: menu_item_heigth

                arrow: Canvas {
                    x: parent.width - width
                    implicitWidth: 40
                    implicitHeight: 40
                    visible: menu_options_Item.subMenu
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.fillStyle = menu_options_Item.highlighted ? "#ffffff" : bg_grupbox_color
                        ctx.moveTo(15, 15)
                        ctx.lineTo(width - 15, height / 2)
                        ctx.lineTo(15, height - 15)
                        ctx.closePath()
                        ctx.fill()
                    }
                }

                indicator: Item {
                    implicitWidth: 40
                    implicitHeight: 40
                    Rectangle {
                        width: 26
                        height: 26
                        anchors.centerIn: parent
                        visible: menu_options_Item.checkable
                        border.color: bg_grupbox_color
                        radius: 3
                        Rectangle {
                            width: 14
                            height: 14
                            anchors.centerIn: parent
                            visible: menu_options_Item.checked
                            color: "black"
                            radius: 2
                        }
                    }
                }

                contentItem: Text {
                    text: menu_options_Item.text
                    font: menu_options_Item.font
                    opacity: enabled ? 1.0 : 0.3
                    color: menu_options_Item.highlighted ? "#ffffff" : bg_grupbox_color
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 40
                    opacity: enabled ? 1 : 0.3
                    color: menu_options_Item.highlighted ? "#999fa9" : "transparent"
                }
            }
        }

        Menu {
            id: help_menu;  title: qsTr("Help")
            width: menu_item_width

            Action { id: tech_help_menu_btn;      text: qsTr("Technical help");    }
            Action { id: email_support_menu_btn;  text: qsTr("Email to support");  }
            Action { id: check_updates_menu_btn;  text: qsTr("Check for updates"); }
            Action { id: about_menu_btn;          text: qsTr("About");             }

            delegate: MenuItem {
                id: menu_help_item
                implicitWidth: menu_item_width
                implicitHeight: menu_item_heigth

                arrow: Canvas {
                    x: parent.width - width
                    implicitWidth: 40
                    implicitHeight: 40
                    visible: menu_help_item.subMenu
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.fillStyle = menu_help_item.highlighted ? "#ffffff" : bg_grupbox_color
                        ctx.moveTo(15, 15)
                        ctx.lineTo(width - 15, height / 2)
                        ctx.lineTo(15, height - 15)
                        ctx.closePath()
                        ctx.fill()
                    }
                }

                indicator: Item {
                    implicitWidth: 40
                    implicitHeight: 40
                    Rectangle {
                        width: 26
                        height: 26
                        anchors.centerIn: parent
                        visible: menu_help_item.checkable
                        border.color: bg_grupbox_color
                        radius: 3
                        Rectangle {
                            width: 14
                            height: 14
                            anchors.centerIn: parent
                            visible: menu_help_item.checked
                            color: "black"
                            radius: 2
                        }
                    }
                }

                contentItem: Text {
                    text: menu_help_item.text
                    font: menu_help_item.font
                    opacity: enabled ? 1.0 : 0.3
                    color: menu_help_item.highlighted ? "#ffffff" : bg_grupbox_color
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 40
                    opacity: enabled ? 1 : 0.3
                    color: menu_help_item.highlighted ? "#999fa9" : "transparent"
                }
            }
        }

        delegate: MenuBarItem {
            id: menu_bar_item_delegate

            width : 95
            height: 17

            contentItem: Text {
                text: menu_bar_item_delegate.text
                font: menu_bar_item_delegate.font
                color: menu_bar_item_delegate.highlighted ? "#000000" : "#FFFFF0"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitHeight: parent.height
                implicitWidth: parent.width
                color: menu_bar_item_delegate.highlighted ? "#DDDFE2" : "transparent"
            }
        }

        background: Rectangle {
            implicitHeight: menu_bar_hegth
            color: bg_grupbox_color
            Rectangle {
                color: bg_grupbox_color
                width: parent.width
                height: 1
                anchors.bottom: parent.bottom
            }
        }
    }

    GroupBox {
        id: tabs_group

        width:  parent.width / 2
        height: parent.height - tabbar_heigth - 40

        y: ident_from_menu

        background: Rectangle {
            width:          parent.width
            height:         parent.height
            border.color:   bs_tabbutton_disabled
            border.width:   1
            color:          bs_tabbutton_disabled
        }

        TabBar {
            id:     main_tab_bar
            width:  parent.width + 200
            height: tabbar_heigth

            background: { color: bg_grupbox_color }
            spacing: 1


            TabButton {
                id: windows_ids_btn
                text: qsTr("Current version")
                height: parent.height
                width: tabs_width

                contentItem: Text {
                    text: windows_ids_btn.text
                    font: windows_ids_btn.font
                    color: ((main_tab_bar.currentIndex == 0) ? bg_tabbutton_active_color : bg_tabbutton_not_active_color)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    border.color: "gray"
                    border.width: 1
                }
            }

            TabButton {
                id: web_rtc_btn
                text: qsTr("WebRTC")
                height: parent.height
                width: tabs_width

                contentItem: Text {
                    text: web_rtc_btn.text
                    font: web_rtc_btn.font
                    color: ((main_tab_bar.currentIndex == 1) ? bg_tabbutton_active_color : bg_tabbutton_not_active_color)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    border.color: "gray"
                    border.width: 1
                }
            }

            TabButton {
                id: telemetry_btn
                height: parent.height
                width: tabs_width
                text: qsTr("Telemetry")
                enabled: false /// NOTE: Inactive at that time

                contentItem: Text {
                    text: telemetry_btn.text
                    font: telemetry_btn.font
                    color: ((main_tab_bar.currentIndex == 2) ? bg_tabbutton_active_color : bg_tabbutton_not_active_color)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    border.color: bs_tabbutton_disabled
                    border.width: 1
                }
            }

            TabButton {
                id: browser_fingerprints_btn
                text: qsTr("Browser")
                height: parent.height
                width: tabs_width
                enabled: false /// NOTE: Inactive at that time

                contentItem: Text {
                    text: browser_fingerprints_btn.text
                    font: browser_fingerprints_btn.font
                    color: ((main_tab_bar.currentIndex == 3) ? bg_tabbutton_active_color : bg_tabbutton_not_active_color)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    border.color: bs_tabbutton_disabled
                    border.width: 1
                }
            }

            TabButton {
                id: hardware_tab
                text: qsTr("Hardware")
                height: parent.height
                width: tabs_width

                enabled: false /// NOTE: Inactive at that time

                contentItem: Text {
                    text: hardware_tab.text
                    font: hardware_tab.font
                    color: ((main_tab_bar.currentIndex == 4) ? bg_tabbutton_active_color : bg_tabbutton_not_active_color)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    border.color: bs_tabbutton_disabled
                    border.width: 1
                }
            }
        }

        StackLayout {
            width: parent.width
            currentIndex: main_tab_bar.currentIndex

            Item { id: windowsIDsTab; Windows_ids { }     }
            Item { id: webRTCTab;     WebRTC { }  }
            Item { id: telemetryTab;                      }
            Item { id: browserFingerprintsTab;            }
            Item { id: hardwareTab;                       }
        }
    }

    GroupBox {

        id: table_box

        x: parent.width / 2 - 100
        y: ident_from_menu

        width: parent.width / 2 + 85
        height: parent.height - tabbar_heigth - 40

        background: Rectangle {
            width:          parent.width
            height:         parent.height
            border.color:   bs_tabbutton_disabled
            border.width:   1
            color:          bs_tabbutton_disabled
        }

        OldControl.TableView {
            id: table_view_id
            anchors.fill: parent
            antialiasing: true
            ScrollBar.vertical: ScrollBar {}
            ScrollBar.horizontal: ScrollBar { visible: false }
            backgroundVisible: false

            OldControl.TableViewColumn {
                role: "title"
                title: "Identifier"
                width: table_column_width - 50
                movable: false
                resizable: false
            }

            OldControl.TableViewColumn {
                role: "before"
                title: "Before"
                width: table_column_width + 50
                movable: false
                resizable: false
            }

            OldControl.TableViewColumn {
                role: "after"
                title: qsTr("After")
                width: table_column_width + 8
                movable: false
                resizable: false
            }

            model: InfoTableModel

            style: TableViewStyle {
                itemDelegate: Rectangle {
                    width: table_column_width
                    color: "#000000"

                    Rectangle {
                        anchors.fill: parent
                        anchors.rightMargin: (styleData.column === 2) ? 0 : 1
                        color: "#BBBFC6"

                        Text {
                            id: text_item
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            anchors.leftMargin: 12
                            renderType: Text.NativeRendering
                            text: styleData.value
                            color: (styleData.column === 2) ? "red" : styleData.color
                        }
                    }
                }

                rowDelegate: Rectangle {
                    color: "#BBBFC6"
                    border.width: 0.3
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        color: bg_tabbutton_not_active_color
                    }
                }
            }
        }
    }

    RowLayout {
        id: status_row
        width: parent.width / 2
        height: 100

        x: 20
        y: main_window.height - height;

        spacing: 3

        Label {
            id: applying_changes_lbl
            text: qsTr("Applying changes: ");
        }

        ProgressBar {
            id: applying_changes_progress
            width: parent.width
            from: 0
            to: 100
            value: 75 /// for test
            x: 0
        }
    }

    Rectangle {
        id: status_rct
        color: bg_grupbox_color
        border.color:   groupbox_border_color
        border.width:   groupbox_border_width

        width: (parent.width / 2) - 24
        height: 40

        x: (main_window.width / 2 ) - 100
        y: main_window.height  - height - 41

        Label {
            id: status_lbl
            anchors.fill: parent
            text: qsTr("Configuration is not saved yet");
            color: "red"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            leftPadding: 12
        }

    }

    RowLayout {
        id: buttons_row
        width: button_width  * 2 + symmetrical_buttons_marging + 70;
        height: button_height

        y: main_window.height - 120
        x: symmetrical_buttons_marging - 20

        Button {
            id: randomize_btn
            text: qsTr("Randomize")

            implicitWidth: button_width
            implicitHeight: button_height

            enabled: MainWindow.buttons_active
            background: Rectangle {
                radius: 2
                implicitHeight: button_height
                implicitWidth: button_width
                anchors.fill: parent
                border.color: groupbox_border_color
                border.width: 1
                color: randomize_btn.pressed ? "#555F71" : "#BBBFC6"
                Text {
                    id: randomize_text
                    clip: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            onClicked: {
                console.log(randomize_btn.text, " clicked!");
                MainWindow.onRandomizeCLicked()
            }
        }

        Button {
            id: apply_btn
            text: qsTr("Apply")

            implicitWidth: button_width
            implicitHeight: button_height

            x: randomize_btn.width + symmetrical_buttons_marging + 10

            enabled: MainWindow.buttons_active
            background: Rectangle {
                radius: 2
                implicitHeight: button_height
                implicitWidth: button_width
                anchors.fill: parent
                border.color: groupbox_border_color
                border.width: 1
                color: apply_btn.pressed ? "#555F71" : "#BBBFC6"
                Text {
                    id: apply_text
                    clip: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            onClicked: {
                console.log(apply_btn.text, " clicked!");
                MainWindow.onApplyCLicked()
            }
        }
    }

    Rectangle {
        id: splitter_rct
        color: "#BBBFC6"
        width: 1
        height: main_window.height - 55
        y : ident_from_menu + 12
        x: main_window.width/2 - 110
    }
}
