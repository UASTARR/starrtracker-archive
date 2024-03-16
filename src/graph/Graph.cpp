#include "Graph.h"

Graph::Graph(QCustomPlot *customPlot, QObject *parent) : QObject(parent), m_customPlot(customPlot)
{
    // Constructor now initializes m_customPlot with the provided customPlot pointer
    // Any additional initialization code for your graph class can go here
}

Graph::~Graph()
{
    delete m_customPlot;
}

void Graph::setGraph(const int rangeX, const int rangeY)
{
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    m_customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    m_customPlot->xAxis->setLabel("Time");          // X label
    m_customPlot->xAxis->setRange(0, 1800);   // Range of x
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    m_customPlot->yAxis->setRange(rangeX, rangeY);
}

void Graph::addGraph(const QVector<double> &x, const QVector<double> &y)
{
    m_customPlot->graph()->setData(x, y);
    m_customPlot->rescaleAxes();
    m_customPlot->replot();
    m_customPlot->update();
}
