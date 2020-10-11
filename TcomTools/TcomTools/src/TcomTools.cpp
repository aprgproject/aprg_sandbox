#include <QFileDialog>
#include <QMessageBox>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include "ui_tcomtools.h"
#include "tcomtools.h"

using namespace std;

void TcomTools::printOutput()
{
   //ui->display
}

TcomTools::TcomTools(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcomTools)
    , m_configuration()
    , m_stepHandler(m_configuration)
    , m_process(this)
{
    ui->setupUi(this);
    updateGuiUsingConfiguration();
    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
}

TcomTools::~TcomTools(){
    m_configuration.saveConfigurationToFile();
    delete ui;
}

void TcomTools::updateGuiUsingConfiguration()
{
    ui->extractStep->setChecked(m_configuration.isExtractStepOn);
    ui->combineAndSortStep->setChecked(m_configuration.isCombineAndSortStepOn);
    ui->grepStep->setChecked(m_configuration.isGrepStepOn);
    ui->cropStep->setChecked(m_configuration.isCropStepOn);
    ui->tcom->setChecked(m_configuration.isGrepTcomEnabled);
    ui->err->setChecked(m_configuration.isGrepErrEnabled);
    ui->errWrnTcom->setChecked(m_configuration.isGrepErrWrnTcomEnabled);
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
    ui->ch->setChecked(m_configuration.isGrepChEnabled);
    ui->hsch->setChecked(m_configuration.isGrepHschEnabled);
    ui->dmgr->setChecked(m_configuration.isGrepDmgrEnabled);
    ui->inputFileAndFolder->setText(QString::fromStdString(m_configuration.inputFileOrDirectory));
    ui->extractCondition->setText(QString::fromStdString(m_configuration.extractGrepCondition));
    ui->acceptedFilesCondition->setText(QString::fromStdString(m_configuration.acceptedFilesGrepCondition));
    ui->other->setText(QString::fromStdString(m_configuration.otherGrepCondition));
    ui->prioritizedLogPrint->setText(QString::fromStdString(m_configuration.prioritizedLogPrint));
}

void TcomTools::on_execute_clicked()
{
    m_stepHandler.executeSteps();
}

void TcomTools::on_actionOpenFile_triggered()
{
    alba::AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(m_configuration.inputFileOrDirectory);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QString::fromStdString(pathHandler.getFullPath()), tr("All Files (*)"));
    pathHandler.inputPath(fileName.toStdString());
    if(!pathHandler.isEmpty())
    {
        m_configuration.inputFileOrDirectory = pathHandler.getFullPath();
        ui->inputFileAndFolder->setText(QString::fromStdString(pathHandler.getFullPath()));
    }
}

void TcomTools::on_actionOpenFolder_triggered()
{
    alba::AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(m_configuration.inputFileOrDirectory);
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open folder"), QString::fromStdString(pathHandler.getDirectory()), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    pathHandler.inputPath(directory.toStdString());
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

void TcomTools::on_ch_toggled(bool checked)
{
    m_configuration.isGrepChEnabled = checked;
}

void TcomTools::on_dmgr_toggled(bool checked)
{
    m_configuration.isGrepDmgrEnabled = checked;
}

void TcomTools::on_err_toggled(bool checked)
{
    m_configuration.isGrepErrEnabled = checked;
}

void TcomTools::on_errWrnTcom_toggled(bool checked)
{
    m_configuration.isGrepErrWrnTcomEnabled = checked;
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
