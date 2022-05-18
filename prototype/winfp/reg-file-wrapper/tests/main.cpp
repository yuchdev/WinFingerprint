#include "../regfile.h"
#include "../regfile.cpp"
#include "../utils/utils.h"
#include "../utils/utils.cpp"
#include "../utils/win_registry_helper.h"
#include "../utils/win_registry_helper.cpp"
#include "../utils/win_errors.h"
#include "../utils/win_ptrs.h"
#include "../utils/win_system_information.h"
#include "../utils/win_system_information.cpp"

#include <exception>
#include <system_error>


#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/framework.hpp>

BOOST_AUTO_TEST_SUITE(RegFileTest)

std::string test_path("./test_backup_dir");

BOOST_AUTO_TEST_CASE (Construct) {
    BOOST_TEST_MESSAGE("Construct Test Begin...");

    RegFile f;
    f.set_path(test_path);

    BOOST_CHECK_EQUAL(f.get_path().empty(), false);
    BOOST_CHECK_EQUAL(File::directory_exists(f.get_path()), true);

    std::stringstream ss;
    ss << "Set Path and create directory: " << f.get_path() << " OK!";

    BOOST_TEST_MESSAGE(ss.str());
    BOOST_TEST_MESSAGE("Construct Test Passed");
}

BOOST_AUTO_TEST_CASE (writeTest) {
    BOOST_TEST_MESSAGE("Write Test Begin, for example get harware fingerprint keys 'MachineGuid' and binry 'SusClientIDValidation'");

    if (helpers::RegistryKey::is_key_exist(HwProfileGuid)) {
        helpers::RegistryKey key(HwProfileGuid);
        auto value = key.get_string_value("HwProfileGuid");
        BOOST_CHECK_EQUAL(value.second, true);

        if (value.second) {
            std::string val = value.first;

            BOOST_CHECK_EQUAL(val.empty(), false);

            RegItem reg(test_path, std::string("HwProfileGuid"), val, std::string("HwProfile.dat"), REG_SZ);
            RegFile reg_file(test_path, reg);

            BOOST_CHECK_EQUAL(reg_file.write(), true);
        }
    }
    else { BOOST_TEST_ERROR("Key '" + HwProfileGuid + "' does not exist!"); }

    if (helpers::RegistryKey::is_key_exist(WindowsUpdate)) {
        helpers::RegistryKey key(WindowsUpdate);
        auto value = key.get_binary_value("SusClientIDValidation");

        BOOST_CHECK_EQUAL(value.second, true);

        if (value.second) {
            std::vector<uint8_t> val = value.first;

            BOOST_CHECK_EQUAL(val.empty(), false);

            RegItem reg(test_path, std::string("WindowsUpdate"), "", std::string("SusClientIDValidation.dat"), REG_BINARY);
            reg.bin_value_ = val;

            RegFile reg_file(test_path, reg);

            BOOST_CHECK_EQUAL(reg_file.write(), true);
        }
    }
    else { BOOST_TEST_ERROR("Key '" + WindowsUpdate + "' does not exist!"); }

    BOOST_TEST_MESSAGE("Write Test Passed");
}

BOOST_AUTO_TEST_CASE (readTest) {
    BOOST_TEST_MESSAGE("Read Test Begin...");

    if (helpers::RegistryKey::is_key_exist(HwProfileGuid)) {
        helpers::RegistryKey key(HwProfileGuid);

        RegItem reg(test_path, std::string("HwProfileGuid"), "", std::string("HwProfile.dat"), REG_SZ);
        RegFile reg_file(test_path, reg);

        bool res = reg_file.read();

        BOOST_CHECK_EQUAL(res, true);

        if (res) {
            auto value = key.set_string_value(reg_file.get_reg_item().key_path_, reg_file.get_reg_item().value_);

            BOOST_CHECK_EQUAL(value, true);
        }
    }
    else { BOOST_TEST_ERROR("Key '" + HwProfileGuid + "' does not exist!"); }

    if (helpers::RegistryKey::is_key_exist(WindowsUpdate)) {
        helpers::RegistryKey key(WindowsUpdate);

        RegItem reg(test_path, std::string("WindowsUpdate"), "", std::string("WindowsUpdate.dat"), REG_SZ);
        RegFile reg_file(test_path, reg);

        bool res = reg_file.read();

        BOOST_CHECK_EQUAL(res, true);

        if (res) {
            auto value = key.set_binary_value(reg_file.get_reg_item().key_path_, reg_file.get_reg_item().bin_value_);

            BOOST_CHECK_EQUAL(value, true);
        }

    }
    else { BOOST_TEST_ERROR("Key '" + WindowsUpdate + "' does not exist!"); }


    BOOST_TEST_MESSAGE("Read Test Passed");
}

BOOST_AUTO_TEST_SUITE_END()
