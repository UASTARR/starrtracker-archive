#include "streetmapview.h"

StreetMapView::StreetMapView(QWidget *parent) : QQuickWidget(parent)
{
    this->setSource(QUrl(QStringLiteral("qrc:/streetmapview.qml")));
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);
}
