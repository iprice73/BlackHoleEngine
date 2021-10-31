#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "renderarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_checkBoxBlackHole_stateChanged(int arg1);
    void on_checkBoxBody_stateChanged(int arg1);

    void on_pushButton_eraseParticles_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;
    RenderArea* rda_;
};
#endif // MAINWINDOW_H
