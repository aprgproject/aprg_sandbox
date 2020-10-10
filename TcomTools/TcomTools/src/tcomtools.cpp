#include <AprgFileExtractor.hpp>
#include <BtsLogSorter.hpp>
#include <iostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_tcomtools.h"#include "tcomtools.h"

using namespace std;
TcomTools::TcomTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcomTools)
{
    ui->setupUi(this);
    updateGuiUsingConfiguration();
}

TcomTools::~TcomTools()
{
    m_configuration.saveConfigurationToFile();
    delete ui;
}

void TcomTools::updateGuiUsingConfiguration()
{
    QString temp;
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
    ui->cchhAndBchsender->setChecked(m_configuration.isGrepCchhBchsenderEnabled);
    ui->hsch->setChecked(m_configuration.isGrepHschEnabled);
    ui->dmgr->setChecked(m_configuration.isGrepDmgrEnabled);
    ui->inputFileAndFolder->setText(QString::fromStdString(m_configuration.inputFileOrDirectory));
    ui->extractCondition->setText(QString::fromStdString(m_configuration.extractGrepCondition));
    ui->acceptedFilesCondition->setText(QString::fromStdString(m_configuration.acceptedFilesGrepCondition));
    ui->other->setText(QString::fromStdString(m_configuration.otherGrepCondition));
    ui->prioritizedLogPrint->setText(QString::fromStdString(m_configuration.prioritizedLogPrint));
}

void TcomTools::on_start_clicked()
{
    cout << "on_start_clicked" << endl;

    alba::AlbaWindowsPathHandler currentPathHandler;
    currentPathHandler.inputPath(m_configuration.inputFileOrDirectory);
    for(int step=1; step<4; step++)
    {
        currentPathHandler.reInputPath();
        if(!currentPathHandler.isFoundInLocalSystem())
        {
            cout << currentPathHandler.getFullPath() << " isNotFoundInLocalSystem" << endl;
            return;
        }
        cout<<"currentPathHandler: "<<currentPathHandler.getFullPath()<<endl;
        if(1 == step && m_configuration.isExtractStepOn)
        {
            cout<<"Step1: "<<currentPathHandler.getFullPath()<<endl;
            alba::AprgFileExtractor fileExtractor(m_configuration.extractGrepCondition);
            fileExtractor.extractAllRelevantFiles(currentPathHandler.getFullPath());
            currentPathHandler.inputPath(currentPathHandler.getDirectory() + R"(\)" + currentPathHandler.getFilenameOnly());
        }
        else if(2 == step && m_configuration.isCombineAndSortStepOn)
        {
            cout<<"Step2: "<<currentPathHandler.getFullPath()<<endl;
            tcomToolsBackend::BtsLogSorter btsLogSorter(
                        m_configuration.acceptedFilesGrepCondition,
                        m_configuration.sorterConfigurationWithPcTime,
                        m_configuration.sorterConfigurationWithoutPcTime,
                        m_configuration.pathOfLogsWithoutPcTime);
            btsLogSorter.processDirectory(currentPathHandler.getDirectory());
            currentPathHandler.inputPath(currentPathHandler.getDirectory() + R"(\sorted.log)");
            btsLogSorter.saveAllToOutputFile(currentPathHandler.getFullPath());
        }
        else if(3 == step)
        {
            if(m_configuration.isGrepStepOn)
            {

            }
            if(m_configuration.isCropStepOn)
            {

            }
        }

    }
}

void TcomTools::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), R"(C:\)", tr("All Files (*)"));
    m_configuration.inputFileOrDirectory = fileName.toStdString();
    ui->inputFileAndFolder->setText(fileName);
}
void TcomTools::on_actionOpenFolder_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open folder"), R"(C:\)", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    m_configuration.inputFileOrDirectory = directory.toStdString();
    ui->inputFileAndFolder->setText(directory);
}
void TcomTools::on_actionAboutAprg_triggered()
{
    QMessageBox::about(this, tr("About Menu"), tr("Insert sample text here"));}

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

void TcomTools::on_cchhAndBchsender_toggled(bool checked)
{
    m_configuration.isGrepCchhBchsenderEnabled = checked;
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