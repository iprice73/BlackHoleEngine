#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    QChartView* createChart() const;

};

#endif // CHARTWIDGET_H
