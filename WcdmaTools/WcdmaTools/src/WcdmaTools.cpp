#include "WcdmaTools.h"
#include "ui_wcdmatools.h"

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace alba{

namespace ProgressCounters
{extern int getOverAllProgress();
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
    ui->inputFileAndFolderTextBox->setText(QString::fromStdString(inputFileOrDirectory));
}

void WcdmaTools::updateGuiUsingConfiguration()
{
    ui->extractStepCheckBox->setChecked(m_configuration.isExtractStepOn);
    ui->combineAndSortStepCheckBox->setChecked(m_configuration.isCombineAndSortStepOn);
    ui->grepStepCheckBox->setChecked(m_configuration.isGrepStepOn);    ui->cropStepCheckBox->setChecked(m_configuration.isCropStepOn);
    ui->filterSubStepCheckBox->setChecked(m_configuration.isFilterSubStepOn);
    ui->tcomCheckBox->setChecked(m_configuration.isGrepTcomEnabled);
    ui->errCheckBox->setChecked(m_configuration.isGrepErrEnabled);    ui->errWrnNoSpamCheckBox->setChecked(m_configuration.isGrepErrWrnNoSpamEnabled);
    ui->btsStatusCheckBox->setChecked(m_configuration.isGrepBtsStatusEnabled);
    ui->recoveryCheckBox->setChecked(m_configuration.isGrepRecoveryEnabled);
    ui->allocationCheckBox->setChecked(m_configuration.isGrepAllocationEnabled);
    ui->faultCheckBox->setChecked(m_configuration.isGrepFaultEnabled);
    ui->lrmCheckBox->setChecked(m_configuration.isGrepLrmEnabled);
    ui->grmCheckBox->setChecked(m_configuration.isGrepGrmEnabled);
    ui->toamCheckBox->setChecked(m_configuration.isGrepToamEnabled);
    ui->tupcCheckBox->setChecked(m_configuration.isGrepTupcEnabled);
    ui->rlhCheckBox->setChecked(m_configuration.isGrepRlhEnabled);
    ui->cchhCheckBox->setChecked(m_configuration.isGrepCchhEnabled);
    ui->bchsenderCheckBox->setChecked(m_configuration.isGrepBchsenderEnabled);
    ui->hschCheckBox->setChecked(m_configuration.isGrepHschEnabled);
    ui->dmgrCheckBox->setChecked(m_configuration.isGrepDmgrEnabled);
    ui->codecCheckBox->setChecked(m_configuration.isGrepCodecEnabled);
    ui->ltcomCheckBox->setChecked(m_configuration.isGrepLtcomEnabled);
    ui->lomCheckBox->setChecked(m_configuration.isGrepLomEnabled);
    ui->rakeCheckBox->setChecked(m_configuration.isGrepRakeEnabled);
    ui->picCheckBox->setChecked(m_configuration.isGrepPicEnabled);
    ui->hsdpaCheckBox->setChecked(m_configuration.isGrepHsdpaEnabled);
    ui->hstupCheckBox->setChecked(m_configuration.isGrepHsTupEnabled);
    ui->hsupal2CheckBox->setChecked(m_configuration.isGrepHsupaL2Enabled);
    //ui->inputFileAndFolderTextBox->setText(QString::fromStdString(m_configuration.inputFileOrDirectory)); // this is not needed because main gives the location
    ui->extractConditionTextBox->setText(QString::fromStdString(m_configuration.extractGrepCondition));
    ui->acceptedFilesConditionTextBox->setText(QString::fromStdString(m_configuration.acceptedFilesGrepCondition));
    ui->filterConditionTextBox->setText(QString::fromStdString(m_configuration.filterGrepCondition));
    ui->otherTextBox->setText(QString::fromStdString(m_configuration.otherGrepCondition));
    ui->prioritizedLogConditionTextBox->setText(QString::fromStdString(m_configuration.prioritizedLogCondition));
    ui->cropSizeTextBox->setText(QString::fromStdString(convertToString(m_configuration.cropSize)));
    updateFilterConditionTextBox(m_configuration.isFilterSubStepOn);
    setReadOnlyForLineEdit(ui->grepFinalConditionTextBox, true);
    updateGrepFinalCondition();}

void WcdmaTools::updateProgressBar()
{    ui->progressBar->setValue(ProgressCounters::getOverAllProgress());
}

void WcdmaTools::updateFilterConditionTextBox(bool const isFilterSubStepOn)
{
    bool isReadOnly = !isFilterSubStepOn;
    ui->filterConditionTextBox->setReadOnly(isReadOnly);
    if(isReadOnly)
    {
        ui->filterConditionTextBox->setText(QString::fromStdString(""));
        m_configuration.filterGrepCondition.clear();
    }
    setReadOnlyForLineEdit(ui->filterConditionTextBox, isReadOnly);
}

void WcdmaTools::setReadOnlyForLineEdit(QLineEdit* lineEdit, bool const isReadOnly)
{
    if(isReadOnly)
    {
        QPalette palette;
        palette.setColor(QPalette::Base,Qt::lightGray);
        palette.setColor(QPalette::Text,Qt::black);
        lineEdit->setPalette(palette);
    }
    else
    {
        lineEdit->setPalette(QApplication::palette(this));
    }
}

void WcdmaTools::updateGrepFinalCondition()
{
    ui->grepFinalConditionTextBox->setText(QString::fromStdString(m_configuration.getGrepCondition()));
}

void WcdmaTools::onExecutionIsFinished()
{
    m_progressBarThread.stopUpdatingProgressBar();
    ui->progressBar->setValue(100);
    ui->executeButton->setEnabled(true);
}

void WcdmaTools::on_executeButton_clicked()
{
    ui->executeButton->setEnabled(false);
    m_configuration.saveToConfigurationFile();
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
        ui->inputFileAndFolderTextBox->setText(QString::fromStdString(pathHandler.getFullPath()));
    }
}

void WcdmaTools::on_actionOpenFolder_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open folder"), QString::fromStdString(AlbaLocalPathHandler(m_configuration.inputFileOrDirectory).getDirectory()), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    AlbaLocalPathHandler pathHandler(directory.toStdString());
    if(!pathHandler.isEmpty())
    {
        m_configuration.inputFileOrDirectory = pathHandler.getFullPath();
        ui->inputFileAndFolderTextBox->setText(QString::fromStdString(pathHandler.getFullPath()));
    }
}

void WcdmaTools::on_actionReset_to_default_triggered()
{
    m_configuration.loadDefaultConfigurationFile();
    updateGuiUsingConfiguration();
}

void WcdmaTools::on_actionAboutAprg_triggered()
{
    QMessageBox about;
    about.setWindowTitle("About APRG");
    //about.setInformativeText("APRG is created by Mark Earvin Alba");
    about.setIconPixmap(QPixmap(":/resources/resources/About.png"));
    //about.setStandardButtons(QMessageBox::Ok);
    //about.setDefaultButton(QMessageBox::Ok);
    about.show();
    about.exec();
}

void WcdmaTools::on_actionQuit_triggered()
{
    exit(0); //think of something else, I don't like "exit".
}

void WcdmaTools::on_extractStepCheckBox_toggled(bool checked)
{
    m_configuration.isExtractStepOn = checked;
}

void WcdmaTools::on_combineAndSortStepCheckBox_toggled(bool checked)
{
    m_configuration.isCombineAndSortStepOn = checked;
}

void WcdmaTools::on_grepStepCheckBox_toggled(bool checked)
{
    m_configuration.isGrepStepOn = checked;
}

void WcdmaTools::on_cropStepCheckBox_toggled(bool checked)
{
    m_configuration.isCropStepOn = checked;
}

void WcdmaTools::on_filterSubStepCheckBox_toggled(bool checked)
{
    m_configuration.isFilterSubStepOn = checked;
    updateFilterConditionTextBox(m_configuration.isFilterSubStepOn);
}

void WcdmaTools::on_allocationCheckBox_toggled(bool checked)
{
    m_configuration.isGrepAllocationEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_btsStatusCheckBox_toggled(bool checked)
{
    m_configuration.isGrepBtsStatusEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_cchhCheckBox_toggled(bool checked)
{
    m_configuration.isGrepCchhEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_bchsenderCheckBox_toggled(bool checked)
{
    m_configuration.isGrepBchsenderEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_dmgrCheckBox_toggled(bool checked)
{
    m_configuration.isGrepDmgrEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_codecCheckBox_toggled(bool checked)
{
    m_configuration.isGrepCodecEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_ltcomCheckBox_toggled(bool checked)
{
    m_configuration.isGrepLtcomEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_lomCheckBox_toggled(bool checked)
{
    m_configuration.isGrepLomEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_rakeCheckBox_toggled(bool checked)
{
    m_configuration.isGrepRakeEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_picCheckBox_toggled(bool checked)
{
    m_configuration.isGrepPicEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_hsdpaCheckBox_toggled(bool checked)
{
    m_configuration.isGrepHsdpaEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_hstupCheckBox_toggled(bool checked)
{
    m_configuration.isGrepHsTupEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_hsupal2CheckBox_toggled(bool checked)
{
    m_configuration.isGrepHsupaL2Enabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_errCheckBox_toggled(bool checked)
{
    m_configuration.isGrepErrEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_errWrnNoSpamCheckBox_toggled(bool checked)
{
    m_configuration.isGrepErrWrnNoSpamEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_faultCheckBox_toggled(bool checked)
{
    m_configuration.isGrepFaultEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_grmCheckBox_toggled(bool checked)
{
    m_configuration.isGrepGrmEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_hschCheckBox_toggled(bool checked)
{
    m_configuration.isGrepHschEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_lrmCheckBox_toggled(bool checked)
{
    m_configuration.isGrepLrmEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_recoveryCheckBox_toggled(bool checked)
{
    m_configuration.isGrepRecoveryEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_rlhCheckBox_toggled(bool checked)
{
    m_configuration.isGrepRlhEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_tcomCheckBox_toggled(bool checked)
{
    m_configuration.isGrepTcomEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_toamCheckBox_toggled(bool checked)
{
    m_configuration.isGrepToamEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_tupcCheckBox_toggled(bool checked)
{
    m_configuration.isGrepTupcEnabled = checked;
    updateGrepFinalCondition();
}

void WcdmaTools::on_inputFileAndFolderTextBox_editingFinished()
{
    m_configuration.inputFileOrDirectory = ui->inputFileAndFolderTextBox->text().toStdString();
}

void WcdmaTools::on_extractConditionTextBox_editingFinished()
{
    m_configuration.extractGrepCondition = ui->extractConditionTextBox->text().toStdString();
}

void WcdmaTools::on_acceptedFilesConditionTextBox_editingFinished()
{
    m_configuration.acceptedFilesGrepCondition = ui->acceptedFilesConditionTextBox->text().toStdString();
}

void WcdmaTools::on_filterConditionTextBox_editingFinished()
{
    m_configuration.filterGrepCondition = ui->filterConditionTextBox->text().toStdString();
}

void WcdmaTools::on_otherTextBox_editingFinished()
{
    m_configuration.otherGrepCondition = ui->otherTextBox->text().toStdString();
    updateGrepFinalCondition();
}

void WcdmaTools::on_prioritizedLogConditionTextBox_editingFinished()
{
    m_configuration.prioritizedLogCondition = ui->prioritizedLogConditionTextBox->text().toStdString();
}

void WcdmaTools::on_cropSizeTextBox_editingFinished()
{
    m_configuration.cropSize = convertStringToNumber<double>(ui->cropSizeTextBox->text().toStdString());
}