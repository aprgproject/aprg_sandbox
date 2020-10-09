#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_tcomtools.h"
#include "tcomtools.h"
#include <tcomtoolsConfiguration.hpp>

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
