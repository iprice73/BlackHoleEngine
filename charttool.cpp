#include "charttool.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

using namespace QtCharts;

ChartTool::ChartTool(QObject *parent)
    : QObject{parent}
{

}

void ChartTool::createChart(const QList<QPointF>& pts, const QString& name) const
{
    QLineSeries* series = new QLineSeries();
    int i = 0;
    series->append(pts);
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle(name);

    QChartView* view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->resize(1000, 500);
    view->show();
}
