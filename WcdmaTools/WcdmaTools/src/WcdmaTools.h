#pragma once

#include <ProgressBarThread.hpp>
#include <QMainWindow>
#include <StepHandlerThread.hpp>
#include <WcdmaToolsConfiguration.hpp>

namespace Ui {
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
    void onExecutionIsFinished();
    void on_execute_clicked();
    void on_actionOpenFile_triggered();
    void on_actionOpenFolder_triggered();
    void on_actionAboutAprg_triggered();
    void on_actionQuit_triggered();
    void on_extractStep_toggled(bool checked);
    void on_combineAndSortStep_toggled(bool checked);
    void on_grepStep_toggled(bool checked);
    void on_cropStep_toggled(bool checked);
    void on_allocation_toggled(bool checked);
    void on_btsStatus_toggled(bool checked);
    void on_cchh_toggled(bool checked);
    void on_cchhSdl_toggled(bool checked);
    void on_dmgr_toggled(bool checked);
    void on_err_toggled(bool checked);
    void on_errWrnNoSpam_toggled(bool checked);
    void on_fault_toggled(bool checked);
    void on_grm_toggled(bool checked);
    void on_hsch_toggled(bool checked);
    void on_lrm_toggled(bool checked);
    void on_recovery_toggled(bool checked);
    void on_rlh_toggled(bool checked);
    void on_tcom_toggled(bool checked);
    void on_toam_toggled(bool checked);
    void on_tupc_toggled(bool checked);
    void on_inputFileAndFolder_editingFinished();
    void on_extractCondition_editingFinished();
    void on_acceptedFilesCondition_editingFinished();
    void on_other_editingFinished();
    void on_prioritizedLogPrint_editingFinished();
    void on_cropSize_editingFinished();

private:
    void updateGuiUsingConfiguration();
    Ui::WcdmaTools *ui;
    wcdmaToolsGui::WcdmaToolsConfiguration m_configuration;
    wcdmaToolsGui::StepHandlerThread m_stepHandlerThread;
    wcdmaToolsGui::ProgressBarThread m_progressBarThread;
};
