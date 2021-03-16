#include "WcdmaTools.h"
#include "ui_wcdmatools.h"

#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <QFileDialog>
#include <QMessageBox>

using namespace alba;
using namespace std;

namespace alba
{

namespace ProgressCounters
{
extern int getOverAllProgress();
extern void resetProgressCounters();
}

}

WcdmaTools::WcdmaTools(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WcdmaTools)
    , m_configuration()
    , m_stepHandlerThread(m_configuration)
{
    ui->setupUi(this);
    updateGuiUsingConfiguration();
    ProgressCounters::resetProgressCounters();
    updateProgressBar();
    connect(&m_stepHandlerThread, SIGNAL(executionDone()), this, SLOT(onExecutionIsFinished()));
    connect(&m_progressBarThread, SIGNAL(triggerUpdateProgressBar()), this, SLOT(updateProgressBar()));
    m_stepHandlerThread.start();
    m_progressBarThread.start();
}

WcdmaTools::~WcdmaTools()
{
    delete ui;
}

void WcdmaTools::setInputFileOrDirectory(string const& inputFileOrDirectory)
{
    m_configuration.inputFileOrDirectory = inputFileOrDirectory;
    ui->inputFileAndFolder->setText(QString::fromStdString(inputFileOrDirectory));
}

void WcdmaTools::updateGuiUsingConfiguration()
{
    stringHelper::NumberToStringConverter converter;
    ui->extractStep->setChecked(m_configuration.isExtractStepOn);
    ui->combineAndSortStep->setChecked(m_configuration.isCombineAndSortStepOn);
    ui->grepStep->setChecked(m_configuration.isGrepStepOn);
    ui->cropStep->setChecked(m_configuration.isCropStepOn);
    ui->tcom->setChecked(m_configuration.isGrepTcomEnabled);
    ui->err->setChecked(m_configuration.isGrepErrEnabled);
    ui->errWrnNoSpam->setChecked(m_configuration.isGrepErrWrnNoSpamEnabled);
    ui->btsStatus->setChecked(m_configuration.isGrepBtsStatusEnabled);
    ui->recovery->setChecked(m_configuration.isGrepRecoveryEnabled);
    ui->allocation->setChecked(m_configuration.isGrepAllocationEnabled);
    ui->fault->setChecked(m_configuration.isGrepFaultEnabled);
    ui->lrm->setChecked(m_configuration.isGrepLrmEnabled);
    ui->grm->setChecked(m_configuration.isGrepGrmEnabled);
    ui->toam->setChecked(m_configuration.isGrepToamEnabled);
    ui->tupc->setChecked(m_configuration.isGrepTupcEnabled);
    ui->rlh->setChecked(m_configuration.isGrepRlhEnabled);
    ui->cchh->setChecked(m_configuration.isGrepCchhEnabled);
    ui->cchhSdl->setChecked(m_configuration.isGrepCchhSdlEnabled);
    ui->hsch->setChecked(m_configuration.isGrepHschEnabled);
    ui->dmgr->setChecked(m_configuration.isGrepDmgrEnabled);
    ui->inputFileAndFolder->setText(QString::fromStdString(m_configuration.inputFileOrDirectory));
    ui->extractCondition->setText(QString::fromStdString(m_configuration.extractGrepCondition));
    ui->acceptedFilesCondition->setText(QString::fromStdString(m_configuration.acceptedFilesGrepCondition));
    ui->filterCondition->setText(QString::fromStdString(m_configuration.filterGrepCondition));
    ui->other->setText(QString::fromStdString(m_configuration.otherGrepCondition));
    ui->prioritizedLogPrint->setText(QString::fromStdString(m_configuration.prioritizedLogPrint));
    ui->cropSize->setText(QString::fromStdString(converter.convert(m_configuration.cropSize)));}

void WcdmaTools::updateProgressBar()
{
    ui->progressBar->setValue(ProgressCounters::getOverAllProgress());
}

void WcdmaTools::onExecutionIsFinished()
{
    m_progressBarThread.stopUpdatingProgressBar();
    ui->progressBar->setValue(100);
    ui->execute->setEnabled(true);
}

void WcdmaTools::on_execute_clicked()
{
    ui->execute->setEnabled(false);
    m_progressBarThread.startUpdatingProgressBar();
    m_stepHandlerThread.execute();
}

void WcdmaTools::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QString::fromStdString(AlbaLocalPathHandler(m_configuration.inputFileOrDirectory).getFullPath()), tr("All Files (*)"));
    AlbaLocalPathHandler pathHandler(fileName.toStdString());
    if(!pathHandler.isEmpty())
    {
        m_configuration.inputFileOrDirectory = pathHandler.getFullPath();
        ui->inputFileAndFolder->setText(QString::fromStdString(pathHandler.getFullPath()));
    }
}

void WcdmaTools::on_actionOpenFolder_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open folder"), QString::fromStdString(AlbaLocalPathHandler(m_configuration.inputFileOrDirectory).getDirectory()), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    AlbaLocalPathHandler pathHandler(directory.toStdString());
    if(!pathHandler.isEmpty())
    {
        m_configuration.inputFileOrDirectory = pathHandler.getFullPath();
        ui->inputFileAndFolder->setText(QString::fromStdString(pathHandler.getFullPath()));
    }
}

void WcdmaTools::on_actionAboutAprg_triggered()
{
    QMessageBox::about(this, tr("About Menu"), tr("Insert sample text here"));
}

void WcdmaTools::on_actionQuit_triggered()
{
    exit(0); //think of something else, I don't like "exit".
}

void WcdmaTools::on_extractStep_toggled(bool checked)
{
    m_configuration.isExtractStepOn = checked;
}

void WcdmaTools::on_combineAndSortStep_toggled(bool checked)
{
    m_configuration.isCombineAndSortStepOn = checked;
}

void WcdmaTools::on_grepStep_toggled(bool checked)
{
    m_configuration.isGrepStepOn = checked;
}

void WcdmaTools::on_cropStep_toggled(bool checked)
{
    m_configuration.isCropStepOn = checked;
}

void WcdmaTools::on_allocation_toggled(bool checked)
{
    m_configuration.isGrepAllocationEnabled = checked;
}

void WcdmaTools::on_btsStatus_toggled(bool checked)
{
    m_configuration.isGrepBtsStatusEnabled = checked;
}

void WcdmaTools::on_cchh_toggled(bool checked)
{
    m_configuration.isGrepCchhEnabled = checked;
}

void WcdmaTools::on_cchhSdl_toggled(bool checked)
{
    m_configuration.isGrepCchhSdlEnabled = checked;
}

void WcdmaTools::on_dmgr_toggled(bool checked)
{
    m_configuration.isGrepDmgrEnabled = checked;
}

void WcdmaTools::on_err_toggled(bool checked)
{
    m_configuration.isGrepErrEnabled = checked;
}

void WcdmaTools::on_errWrnNoSpam_toggled(bool checked)
{
    m_configuration.isGrepErrWrnNoSpamEnabled = checked;
}

void WcdmaTools::on_fault_toggled(bool checked)
{
    m_configuration.isGrepFaultEnabled = checked;
}

void WcdmaTools::on_grm_toggled(bool checked)
{
    m_configuration.isGrepGrmEnabled = checked;
}

void WcdmaTools::on_hsch_toggled(bool checked)
{
    m_configuration.isGrepHschEnabled = checked;
}

void WcdmaTools::on_lrm_toggled(bool checked)
{
    m_configuration.isGrepLrmEnabled = checked;
}

void WcdmaTools::on_recovery_toggled(bool checked)
{
    m_configuration.isGrepRecoveryEnabled = checked;
}

void WcdmaTools::on_rlh_toggled(bool checked)
{
    m_configuration.isGrepRlhEnabled = checked;
}

void WcdmaTools::on_tcom_toggled(bool checked)
{
    m_configuration.isGrepTcomEnabled = checked;
}

void WcdmaTools::on_toam_toggled(bool checked)
{
    m_configuration.isGrepToamEnabled = checked;
}

void WcdmaTools::on_tupc_toggled(bool checked)
{
    m_configuration.isGrepTupcEnabled = checked;
}

void WcdmaTools::on_inputFileAndFolder_editingFinished()
{
    m_configuration.inputFileOrDirectory = ui->inputFileAndFolder->text().toStdString();
}

void WcdmaTools::on_extractCondition_editingFinished()
{
    m_configuration.extractGrepCondition = ui->extractCondition->text().toStdString();
}

void WcdmaTools::on_acceptedFilesCondition_editingFinished()
{
    m_configuration.acceptedFilesGrepCondition = ui->acceptedFilesCondition->text().toStdString();
}

void WcdmaTools::on_filterCondition_editingFinished()
{
    m_configuration.filterGrepCondition = ui->filterCondition->text().toStdString();
}

void WcdmaTools::on_other_editingFinished()
{
    m_configuration.otherGrepCondition = ui->other->text().toStdString();}

void WcdmaTools::on_prioritizedLogPrint_editingFinished()
{
    m_configuration.prioritizedLogPrint = ui->prioritizedLogPrint->text().toStdString();
}

void WcdmaTools::on_cropSize_editingFinished()
{
    m_configuration.cropSize = stringHelper::convertStringToNumber<double>(ui->cropSize->text().toStdString());
}
