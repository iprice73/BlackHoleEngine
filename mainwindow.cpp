#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setStyleSheet("background-color: grey");
    scene_ = new QGraphicsScene();
    rda_ = new RenderArea();
    rda_->setFixedSize(ui->graphicsView->size());
    rda_->setStyleSheet("background-color: black");
    scene_->addWidget(rda_);
    ui->graphicsView->setScene(scene_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = "D:/source/Qt/BlackHolePhysicsEngine/a.exe";
    QProcess::startDetached(filename);
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{

}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{

}

