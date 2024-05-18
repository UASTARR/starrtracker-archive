import QtQuick 2.7
import QtQuick.Window 2.2
import QtLocation 5.8
import QtPositioning 5.6

Rectangle {
    property double lat_1;
    property double lon_1;

    property double lat_2;
    property double lon_2;

    property list<MapQuickItem> markers;

    property Component locationMarker_1: locmarker_1;
    property Component locationMarker_2: locmarker_2;

    id: mapview
    visible: true
    width: 512
    height: 512

    Map {
        id: map
        anchors.fill: parent
        // activeMapType: map.supportedMapTypes[1]
        zoomLevel: 13
        center: QtPositioning.coordinate(32.939817922584034, -106.92178417135429);
        plugin: Plugin {
            name: 'osm';
            PluginParameter {
                name: 'osm.mapping.offline.directory'
                value: ':/offline_tiles/'
            }
        }
        MapPolyline{
            line.width: 3
            line.color: "blue"
            path: [
                QtPositioning.coordinate(lat_1, lon_1),
                QtPositioning.coordinate(lat_2, lon_2)
            ]
        }
    }

    function setLocationMarker_1(lati, loni) {
        clearMarkers()
        lat_1 = lati
        lon_1 = loni
        addMarker(lati, loni, locmarker_1)
    }

    function setLocationMarker_2(lati, loni) {
        lat_2 = lati
        lon_2 = loni
        addMarker(lati, loni, locmarker_2)
    }

    function clearMarkers() {
        for (var i = 0; i < markers.length; i++) {
            map.removeMapItem(markers[i])
        }
        markers = []
    }

    function addMarker(lat, lon, component) {
        var item = component.createObject(map, {
            coordinate: QtPositioning.coordinate(lat, lon)
        })
        map.addMapItem(item)
        markers.push(item)
    }

    Component{
        id: locmarker_1
        MapQuickItem{
            id: markerImg
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position
            sourceItem: Image {
                id: image
                width: 15
                height: 20
                source: 'qrc:/marker.png'
            }
        }
    }

    Component{
        id: locmarker_2
        MapQuickItem{
            id: markerImg
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position
            sourceItem: Image {
                id: image
                width: 15
                height: 20
                source: 'qrc:/marker.png'
            }
        }
    }
}
