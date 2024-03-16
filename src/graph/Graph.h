#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include "src/graph/qcustomplot.h"

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QCustomPlot *customPlot, QObject *parent = nullptr);
    ~Graph();

    void setGraph(const int rangeX, const int rangeY);
    void addGraph(const QVector<double> &x, const QVector<double> &y);
private:
    QCustomPlot *m_customPlot;
    QVector<double> qt_time;
    QVector<double> qt_data;
};

#endif // GRAPH_H
