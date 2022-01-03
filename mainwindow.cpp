#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QProcess>
#include <charttool.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(915, 600);
    scene_ = new QGraphicsScene();
    rda_ = new RenderArea();
    rda_->setFixedSize(1000, 1000);
    rda_->setStyleSheet("background-color: black");
    scene_->addWidget(rda_);
    ui->graphicsView->setScene(scene_);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_checkBox_DrawTraces_stateChanged(int state)
{
    rda_->setDrawingTrace(static_cast<bool>(state));
}

void MainWindow::on_pushButton_eraseParticles_clicked()
{
    rda_->getSystem().eraseParticles();
}


void MainWindow::on_pushButton_eraseBlackHoles_clicked()
{
    rda_->getSystem().eraseBlackHoles();
}

void MainWindow::on_pushButton_clicked()
{
    auto* tool = new ChartTool();
    tool->createChart(rda_->getSystem().getParticles()[0]->getAccOverTime(), "Acceleration");
}


void MainWindow::on_pushButton_2_clicked()
{
    auto* tool = new ChartTool();
    tool->createChart(rda_->getSystem().getParticles()[0]->getVelOverTime(), "Velocity");
}


void MainWindow::on_checkBox_stateChanged(int state)
{
    rda_->setDrawingRays(static_cast<bool>(state));
}

