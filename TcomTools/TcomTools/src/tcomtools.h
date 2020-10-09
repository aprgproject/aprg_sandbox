#ifndef TCOMTOOLS_H
#define TCOMTOOLS_H

#include <QMainWindow>
#include <tcomtoolsConfiguration.hpp>

namespace Ui {
class TcomTools;
}

class TcomTools : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcomTools(QWidget *parent = 0);
    ~TcomTools();

private:
    Ui::TcomTools *ui;
    TcomtoolsConfiguration m_configuration;

private slots:
    void on_actionOpenFile_triggered();
    void on_actionOpenFolder_triggered();
    void on_actionAboutAprg_triggered();
    void on_actionQuit_triggered();
    void on_extractStep_toggled(bool checked);
    void on_combineAndSortStep_toggled(bool checked);
    void on_grepStep_toggled(bool checked);
    void on_cropStep_toggled(bool checked);
    void on_start_clicked();
};

#endif // TCOMTOOLS_H
