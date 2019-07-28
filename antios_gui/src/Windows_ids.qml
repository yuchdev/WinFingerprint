import QtQuick 2.4

Windows_idsForm {



    first_guid_text.onTextChanged: {
        WindowsIDS.guid_1 = first_guid_text.text
    }

    second_guid_text.onTextChanged: {
        WindowsIDS.guid_2 = second_guid_text.text
    }

    third_guid_text.onTextChanged: {
        WindowsIDS.guid_3 = third_guid_text.text
    }

    four_guid_text.onTextChanged: {
        WindowsIDS.guid_4 = four_guid_text.text
    }

    five_guid_text.onTextChanged: {
        WindowsIDS.guid_5 = five_guid_text.text
    }

    install_date_text.onTextChanged: {
        WindowsIDS.setInstallDate(install_date_text.text);
    }



    first_id_text.onTextChanged: {
        WindowsIDS.product_id_1 = first_id_text.text
    }

    second_id_text.onTextChanged: {
        WindowsIDS.product_id_2 = second_id_text.text
    }

    third_id_text.onTextChanged: {
        WindowsIDS.product_id_3 = third_id_text.text
    }

    four_id_text.onTextChanged: {
        WindowsIDS.product_id_4 = four_id_text.text
    }

    combobox_system_name.onStateChanged: {
        console.log("SystemNameCombo State changed!");
    }


    combobox_system_name.onCurrentIndexChanged: {
        console.log("Index Changed To: ", combobox_system_name.currentIndex, "Text: ", combobox_system_name.textAt(combobox_system_name.currentIndex));
    }

    combobox_update.onCurrentIndexChanged: {
        console.log("Index Changed To: ", combobox_update.currentIndex, "Text: ", combobox_update.textAt(combobox_update.currentIndex));
    }

    combobox_edition.onCurrentIndexChanged: {
        console.log("Index Changed To: ", combobox_edition.currentIndex, "Text: ", combobox_edition.textAt(combobox_edition.currentIndex));
    }

    combobox_product_type.onCurrentIndexChanged: {
        console.log("Index Changed To: ", combobox_product_type.currentIndex, "Text: ", combobox_product_type.textAt(combobox_product_type.currentIndex));
    }

    combobox_prodict_number.onCurrentIndexChanged: {
        console.log("Index Changed To: ", combobox_prodict_number.currentIndex, "Text: ", combobox_prodict_number.textAt(combobox_prodict_number.currentIndex));
    }
}
