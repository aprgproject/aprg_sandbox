#ifndef TCOMTOOLS_H
#define TCOMTOOLS_H

#include <QMainWindow>

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

private slots:
    void on_actionOpenFile_triggered();
    void on_actionOpenFolder_triggered();
    void on_actionAboutAprg_triggered();
    void on_actionQuit_triggered();
};

#endif // TCOMTOOLS_H
