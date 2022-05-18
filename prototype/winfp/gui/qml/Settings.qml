import QtQuick 2.4

SettingsForm {
    start_checkbox.onCheckedChanged: {
        console.log("StartCheckBox Checked: ", start_checkbox.checked)
    }

    display_ids_checkbox.onCheckedChanged: {
        console.log("DisplayIds Checked: ", display_ids_checkbox.checked)
    }

    auto_export_checkbox.onCheckedChanged: {
        console.log("AutoExport Checked: ", auto_export_checkbox.checked)
    }

    max_number_checkbox.onCheckedChanged: {
        console.log("MaxNumber Checked: ", max_number_checkbox.checked)
    }

    count_auto_export.onEditingFinished: {
        console.log("COUNT AUTOEXPORT: ", count_auto_export.text)
    }

    number_uniq_configs.onEditingFinished: {
        console.log("COUNT UNIQ: ", number_uniq_configs.text)
    }


    apply_settings_btn.onClicked: {
        console.log("OK clicked!")
        SettingsCPP.okButtonClicked();
    }
}
