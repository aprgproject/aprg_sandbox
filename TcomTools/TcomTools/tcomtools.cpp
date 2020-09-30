#include "tcomtools.h"
#include "ui_tcomtools.h"

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
