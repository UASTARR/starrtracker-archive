#include "streetmapview.h"

StreetMapView::StreetMapView(QWidget *parent) : QQuickWidget(parent)
{
    this->setSource(QUrl("qrc:/streetmapview.qml"));
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);
}
