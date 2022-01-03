#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include "charttool.h"

namespace Ui {
class ChartDialog;
}

class ChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChartDialog(QWidget *parent = nullptr);
    ~ChartDialog();

private:
    Ui::ChartDialog *ui;
};

#endif // CHARTDIALOG_H
