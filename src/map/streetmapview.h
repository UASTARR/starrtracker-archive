#ifndef STREETMAPVIEW_H
#define STREETMAPVIEW_H

#include <QQuickWidget>

class StreetMapView : public QQuickWidget
{

public:
    explicit StreetMapView(QWidget *parent = nullptr);
    ~StreetMapView();
};

#endif // STREETMAPVIEW_H
