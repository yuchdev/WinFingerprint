import QtQuick 2.0
import QtTest 1.2

import "../antios-gui/qml"

Item {
    Windows_ids {
        id: ids
    }

    TestCase {
        name: "[WindowsIDS]ComboboxStatesOnStarted"
        function test_system_name_combobox_enabled() {
            compare(ids.combobox_system_name.enabled, true)
        }

        function test_product_type_combobox_enabled() {
            compare(ids.combobox_product_type.enabled, true)
        }

        function test_updates_combobox_ebabled() {
            compare(ids.combobox_edition.enabled, false)
        }

        function test_build_combobox_enabled() {
            compare(ids.combobox_prodict_number.enabled, false)
        }
    }

    TestCase {
        name: "[WindowsIDS]LineEditsStatesOnStarted"
        function test_product_id_line_enabled() {
            compare(ids.first_id_text.enabled, false)
            compare(ids.second_id_text.enabled, false)
            compare(ids.third_id_text.enabled, false)
            compare(ids.four_id_text.enabled, false)
        }

        function test_install_date_line_enabled() {
            compare(ids.install_date_text.enabled, false)
        }

        function test_build_guid_line_enabled() {
            compare(ids.build_guid_text.enabled, true)
        }
    }
}
