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
};

#endif // TCOMTOOLS_H
