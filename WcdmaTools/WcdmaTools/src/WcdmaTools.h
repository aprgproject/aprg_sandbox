#pragma once

#include <ProgressBarThread.hpp>
#include <StepHandlerThread.hpp>
#include <WcdmaToolsConfiguration.hpp>

#include <QMainWindow>
#include <QLineEdit>

namespace Ui
{
class WcdmaTools;
}

class WcdmaTools : public QMainWindow
{
    Q_OBJECT

public:
    explicit WcdmaTools(QWidget *parent = 0);
    ~WcdmaTools();
    void setInputFileOrDirectory(std::string const& inputFileOrDirectory);

private slots:
    void updateProgressBar();
    void updateFilterConditionTextBox(bool const isFilterSubStepOn);
    void setReadOnlyForLineEdit(QLineEdit* lineEdit, bool const isReadOnly);
    void updateGrepFinalCondition();
    void onExecutionIsFinished();
    void on_executeButton_clicked();
    void on_actionOpenFile_triggered();
    void on_actionOpenFolder_triggered();
    void on_actionReset_to_default_triggered();
    void on_actionAboutAprg_triggered();
    void on_actionQuit_triggered();
    void on_extractStepCheckBox_toggled(bool checked);
    void on_combineAndSortStepCheckBox_toggled(bool checked);
    void on_grepStepCheckBox_toggled(bool checked);
    void on_cropStepCheckBox_toggled(bool checked);
    void on_filterSubStepCheckBox_toggled(bool checked);
    void on_allocationCheckBox_toggled(bool checked);
    void on_btsStatusCheckBox_toggled(bool checked);
    void on_cchhCheckBox_toggled(bool checked);
    void on_bchsenderCheckBox_toggled(bool checked);
    void on_dmgrCheckBox_toggled(bool checked);
    void on_codecCheckBox_toggled(bool checked);
    void on_ltcomCheckBox_toggled(bool checked);
    void on_lomCheckBox_toggled(bool checked);
    void on_rakeCheckBox_toggled(bool checked);
    void on_picCheckBox_toggled(bool checked);
    void on_hsdpaCheckBox_toggled(bool checked);
    void on_hstupCheckBox_toggled(bool checked);
    void on_hsupal2CheckBox_toggled(bool checked);
    void on_errCheckBox_toggled(bool checked);
    void on_errWrnNoSpamCheckBox_toggled(bool checked);
    void on_faultCheckBox_toggled(bool checked);
    void on_grmCheckBox_toggled(bool checked);
    void on_hschCheckBox_toggled(bool checked);
    void on_lrmCheckBox_toggled(bool checked);
    void on_recoveryCheckBox_toggled(bool checked);
    void on_rlhCheckBox_toggled(bool checked);
    void on_tcomCheckBox_toggled(bool checked);
    void on_toamCheckBox_toggled(bool checked);
    void on_tupcCheckBox_toggled(bool checked);
    void on_inputFileAndFolderTextBox_editingFinished();
    void on_extractConditionTextBox_editingFinished();
    void on_acceptedFilesConditionTextBox_editingFinished();
    void on_filterConditionTextBox_editingFinished();
    void on_otherTextBox_editingFinished();
    void on_prioritizedLogConditionTextBox_editingFinished();
    void on_cropSizeTextBox_editingFinished();

private:
    void updateGuiUsingConfiguration();
    Ui::WcdmaTools *ui;
    wcdmaToolsGui::WcdmaToolsConfiguration m_configuration;
    wcdmaToolsGui::StepHandlerThread m_stepHandlerThread;
    wcdmaToolsGui::ProgressBarThread m_progressBarThread;
};
