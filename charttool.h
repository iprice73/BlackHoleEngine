#ifndef CHARTTOOL_H
#define CHARTTOOL_H

#include <QObject>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

class ChartTool : public QObject
{
    Q_OBJECT
public:
    explicit ChartTool(QObject *parent = nullptr);
    void createChart(const QList<QPointF>& pts, const QString& name) const;

};

#endif // CHARTTOOL_H
