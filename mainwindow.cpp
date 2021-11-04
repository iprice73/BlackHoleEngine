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
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
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



void MainWindow::on_checkBoxBlackHole_stateChanged(int state)
{
    rda_->setInsertBlackHole(static_cast<bool>(state));
    if (ui->checkBoxBody->isChecked()) {
        ui->checkBoxBody->setChecked(!state);
    }
}


void MainWindow::on_checkBoxBody_stateChanged(int state)
{
    rda_->setInsertBody(static_cast<bool>(state));
    if (ui->checkBoxBlackHole->isChecked()) {
        ui->checkBoxBlackHole->setChecked(!state);
    }
}


void MainWindow::on_pushButton_eraseParticles_clicked()
{
    rda_->getSystem().eraseAll();
}

