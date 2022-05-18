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

    comboboxProductVersion.onStateChanged: {
        console.log("SystemNameCombo State changed!");
    }


    comboboxProductVersion.onCurrentIndexChanged: {
        console.log("Index Changed To: ", comboboxProductVersion.currentIndex, "Text: ", comboboxProductVersion.textAt(comboboxProductVersion.currentIndex));
		WindowsIDS.loadSubproducts(comboboxProductVersion.textAt(comboboxProductVersion.currentIndex))
		WindowsIDS.loadEditions(comboboxProductVersion.textAt(comboboxProductVersion.currentIndex))
		WindowsIDS.loadBuilds(comboboxSubproductVersion.textAt(comboboxSubproductVersion.currentIndex))
    }

    comboboxSubproductVersion.onCurrentIndexChanged: {
        console.log("Index Changed To: ", comboboxSubproductVersion.currentIndex, "Text: ", comboboxSubproductVersion.textAt(comboboxSubproductVersion.currentIndex));
		WindowsIDS.loadBuilds(comboboxSubproductVersion.textAt(comboboxSubproductVersion.currentIndex))
    }

    comboboxEdition.onCurrentIndexChanged: {
        console.log("Index Changed To: ", comboboxEdition.currentIndex, "Text: ", comboboxEdition.textAt(comboboxEdition.currentIndex));
    }

    comboboxProductType.onCurrentIndexChanged: {
        console.log("Index Changed To: ", comboboxProductType.currentIndex, "Text: ", comboboxProductType.textAt(comboboxProductType.currentIndex));
    }

    comboboxBuildNumber.onCurrentIndexChanged: {
        console.log("Index Changed To: ", comboboxBuildNumber.currentIndex, "Text: ", comboboxBuildNumber.textAt(comboboxBuildNumber.currentIndex));
    }
}
