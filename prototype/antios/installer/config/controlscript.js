function Controller() {
    installer.setDefaultPageVisible(QInstaller.ComponentSelection, 1);
    installer.setDefaultPageVisible(QInstaller.LicenseCheck, 1);
    installer.setDefaultPageVisible(QInstaller.StartMenuSelection, 1);
    installer.setDefaultPageVisible(QInstaller.TargetDirectory, 1);


    installer.uninstallationStarted.connect(onUninstallationStarted);
    installer.installationFinished.connect(onInstallFinished);
    installer.updateFinished.connect(onUpdaterFinnished);

    installer.setValue("RemoveTargetDir", true);
}

Controller.prototype.IntroductionPageCallback  = function() {
    gui.clickButton(buttons.NextButton); /// auto click to next
}

Controller.prototype.TargetDirectoryPageCallback = function() {
    gui.clickButton(buttons.NextButton); // automatically click the Next button
}

onUninstallationStarted = function() { }

onInstallFinished = function() {  }

onUpdaterStarted = function() { }

onUpdaterFinnished = function() { }