#ifndef KEYS_HPP
#define KEYS_HPP

#include <string>
#include <map>


/// Telemetry Fingerprint, used only on win 10. Keys: ( "MachineId")
static const std::string SQMClient { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\SQMClient" };
/// "ETagQueryParameters"
static const std::string SettingsRequests  { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Diagnostics\\DiagTrack\\SettingsRequests" };

/// Network Fingerprint
/// TCP Params. Keys ( "NV Hostname",  "Hostname" )
static const std::string TCPParameters { "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters" };

/// Names. Keys ( "ComputerName", "ActiveComputerName", "RegisteredOwner" )
static const std::string ComputerName  { "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName" };
static const std::string ActiveComputerName  { "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ActiveComputerName" };

/// Windows Fingerprint.
/// Keys: ( "BuildGUID", "BuildLab", "BuildLabEx", "CurrentBuild", "CurrentBuildNumber",
///         "CurrentVersion", "DigitalProductId", "DigitalProductId4",
///         "EditionID", "InstallDate", "ProductId", "ProductName", "RegisteredOwner" )
static const std::string CurrentVersion { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion" };

/// IE Fingerprint.
/// Keys: ( "svcKBNumber", "ProductId", "DigitalProductId", "DigitalProductId", "DigitalProductId4" )
static const std::string IEFingerprint { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Internet Explorer\\Registration" };

/// Key: "IE Installed Date"
static const std::string IEMigration { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Internet Explorer\\Migration" };

static const std::string IE { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Internet Explorer" };

/// HW Fingerprint.
/// Keys: "HwProfileGuid", "SusClientId", "SusClientIDValidation" )
static const std::string HwProfileGuid { "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0001" };

/// key: "MachineGuid"
static const std::string MachineGuid { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Cryptography" };

/// keys: ( "SusClientId", "SusClientIDValidation" )
static const std::string WindowsUpdate { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate" };

///
static const std::string Fonts          { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts" };

///
static const std::string FontsHidden    { "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\\Hidden" };

//// test
static const std::string VolumeID { "HKEY_LOCAL_MACHINE\\" }; /// TODO!

#endif // KEYS_HPP
