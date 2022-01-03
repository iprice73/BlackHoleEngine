#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : QWidget{parent}
{
    this->show();
}
void* ChartWidget::createChart() const
{
    QLineSeries* series = new QLineSeries();
    int i = 0;
    series->append(i, i++);
    series->append(i, i++);
    series->append(i, i++);
    series->append(i, i++);
    series->append(i, i++);
    series->append(i, i++);
    series->append(i, i++);
    series->append(i, i++);
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView* view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->show();

}
