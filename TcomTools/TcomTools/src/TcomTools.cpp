#include <AlbaStringHelper.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include "ui_tcomtools.h"
#include "TcomTools.h"

using namespace alba;
using namespace std;

TcomTools::TcomTools(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcomTools)
    , m_configuration()
{
    ui->setupUi(this);
    updateGuiUsingConfiguration();
    updateProgressBar(0);
    connect(&m_stepHandlerThread, SIGNAL(finished()), this, SLOT(onExecutionIsFinished()));
    m_stepHandlerThread.start();
}

TcomTools::~TcomTools()
{
    delete ui;
}

void TcomTools::setInputFileOrDirectory(string const& inputFileOrDirectory)
{
    m_configuration.inputFileOrDirectory = inputFileOrDirectory;
    ui->inputFileAndFolder->setText(QString::fromStdString(inputFileOrDirectory));
}

void TcomTools::updateGuiUsingConfiguration()
{
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
    ui->other->setText(QString::fromStdString(m_configuration.otherGrepCondition));
    ui->prioritizedLogPrint->setText(QString::fromStdString(m_configuration.prioritizedLogPrint));
    ui->cropSize->setText(QString::fromStdString(stringHelper::convertNumberToString(m_configuration.cropSize)));
}

void TcomTools::updateProgressBar(int percentage)
{
    ui->progressBar->setValue(percentage);
}

void TcomTools::onExecutionIsFinished()
{
    ui->execute->setEnabled(true);
}

void TcomTools::on_execute_clicked()
{
    ui->execute->setEnabled(false);
    m_stepHandlerThread.execute(m_configuration);
}

void TcomTools::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QString::fromStdString(AlbaWindowsPathHandler(m_configuration.inputFileOrDirectory).getFullPath()), tr("All Files (*)"));
    AlbaWindowsPathHandler pathHandler(fileName.toStdString());
    if(!pathHandler.isEmpty())
    {
        m_configuration.inputFileOrDirectory = pathHandler.getFullPath();
        ui->inputFileAndFolder->setText(QString::fromStdString(pathHandler.getFullPath()));
    }
}

void TcomTools::on_actionOpenFolder_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open folder"), QString::fromStdString(AlbaWindowsPathHandler(m_configuration.inputFileOrDirectory).getDirectory()), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    AlbaWindowsPathHandler pathHandler(directory.toStdString());
    if(!pathHandler.isEmpty())
    {
        m_configuration.inputFileOrDirectory = pathHandler.getFullPath();
        ui->inputFileAndFolder->setText(QString::fromStdString(pathHandler.getFullPath()));
    }
}

void TcomTools::on_actionAboutAprg_triggered()
{
    QMessageBox::about(this, tr("About Menu"), tr("Insert sample text here"));
}

void TcomTools::on_actionQuit_triggered()
{
    exit(0); //think of something else, I don't like "exit".
}

void TcomTools::on_extractStep_toggled(bool checked)
{
    m_configuration.isExtractStepOn = checked;
}

void TcomTools::on_combineAndSortStep_toggled(bool checked)
{
    m_configuration.isCombineAndSortStepOn = checked;
}

void TcomTools::on_grepStep_toggled(bool checked)
{
    m_configuration.isGrepStepOn = checked;
}

void TcomTools::on_cropStep_toggled(bool checked)
{
    m_configuration.isCropStepOn = checked;
}

void TcomTools::on_allocation_toggled(bool checked)
{
    m_configuration.isGrepAllocationEnabled = checked;
}

void TcomTools::on_btsStatus_toggled(bool checked)
{
    m_configuration.isGrepBtsStatusEnabled = checked;
}

void TcomTools::on_cchh_toggled(bool checked)
{
    m_configuration.isGrepCchhEnabled = checked;
}

void TcomTools::on_cchhSdl_toggled(bool checked)
{
    m_configuration.isGrepCchhSdlEnabled = checked;
}

void TcomTools::on_dmgr_toggled(bool checked)
{
    m_configuration.isGrepDmgrEnabled = checked;
}

void TcomTools::on_err_toggled(bool checked)
{
    m_configuration.isGrepErrEnabled = checked;
}

void TcomTools::on_errWrnNoSpam_toggled(bool checked)
{
    m_configuration.isGrepErrWrnNoSpamEnabled = checked;
}

void TcomTools::on_fault_toggled(bool checked)
{
    m_configuration.isGrepFaultEnabled = checked;
}

void TcomTools::on_grm_toggled(bool checked)
{
    m_configuration.isGrepGrmEnabled = checked;
}

void TcomTools::on_hsch_toggled(bool checked)
{
    m_configuration.isGrepHschEnabled = checked;
}

void TcomTools::on_lrm_toggled(bool checked)
{
    m_configuration.isGrepLrmEnabled = checked;
}

void TcomTools::on_recovery_toggled(bool checked)
{
    m_configuration.isGrepRecoveryEnabled = checked;
}

void TcomTools::on_rlh_toggled(bool checked)
{
    m_configuration.isGrepRlhEnabled = checked;
}

void TcomTools::on_tcom_toggled(bool checked)
{
    m_configuration.isGrepTcomEnabled = checked;
}

void TcomTools::on_toam_toggled(bool checked)
{
    m_configuration.isGrepToamEnabled = checked;
}

void TcomTools::on_tupc_toggled(bool checked)
{
    m_configuration.isGrepTupcEnabled = checked;
}

void TcomTools::on_inputFileAndFolder_editingFinished()
{
    m_configuration.inputFileOrDirectory = ui->inputFileAndFolder->text().toStdString();
}

void TcomTools::on_extractCondition_editingFinished()
{
    m_configuration.extractGrepCondition = ui->extractCondition->text().toStdString();
}

void TcomTools::on_acceptedFilesCondition_editingFinished()
{
    m_configuration.acceptedFilesGrepCondition = ui->acceptedFilesCondition->text().toStdString();
}

void TcomTools::on_other_editingFinished()
{
    m_configuration.otherGrepCondition = ui->other->text().toStdString();
}

void TcomTools::on_prioritizedLogPrint_editingFinished()
{
    m_configuration.prioritizedLogPrint = ui->prioritizedLogPrint->text().toStdString();
}

void TcomTools::on_cropSize_editingFinished()
{
    m_configuration.cropSize = stringHelper::convertStringToNumber<double>(ui->cropSize->text().toStdString());
}
