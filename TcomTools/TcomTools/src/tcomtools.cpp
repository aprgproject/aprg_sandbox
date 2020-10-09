#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_tcomtools.h"
#include "tcomtools.h"

using namespace std;

TcomTools::TcomTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcomTools)
{
    ui->setupUi(this);
}

TcomTools::~TcomTools()
{
    delete ui;
}

void TcomTools::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), R"(C:\)", tr("All Files (*)"));
    ui->inputFileAndFolder->setText(fileName);
}

void TcomTools::on_actionOpenFolder_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open folder"), R"(C:\)", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->inputFileAndFolder->setText(directory);
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

void TcomTools::on_start_clicked()
{
    cout << "on_start_clicked" << m_configuration.acceptedFilesGrepCondition << endl;
}
