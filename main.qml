import QtQuick 2.15
import QtQuick.Window 2.2
import QtLocation 5.8
import QtPositioning 5.6

Rectangle {
    property list<MapQuickItem> markers;

    id: mapview
    visible: true
    width: 512
    height: 512

    Map {
        id: map
        anchors.fill: parent
        zoomLevel: 13
        center: QtPositioning.coordinate(32.939817922584034, -106.92178417135429);
        plugin: offlinePlugin
        Plugin {
            id: offlinePlugin
            name: 'osm';
            PluginParameter {
                name: 'osm.mapping.offline.directory'
                value: ':/offline_tiles/'
            }
        }

        MapPolyline{
            id: mapline;
            line.width: 3
            line.color: "blue"
            path: []
        }
    }

    function setLocationMarker_1(lati, loni) {
        addMarker(lati, loni, locmarker)
        if (!mapline.containsCoordinate(QtPositioning.coordinate(lati, loni)))
            mapline.addCoordinate(QtPositioning.coordinate(lati, loni))
    }

    function setLocationMarker_2(lati, loni) {
        clearMarkers(1);
        addMarker(lati, loni, locmarker)
        if (!mapline.containsCoordinate(QtPositioning.coordinate(lati, loni)))
            mapline.addCoordinate(QtPositioning.coordinate(lati, loni))
    }

    function addMarker(lat, lon, component) {
        var item = component.createObject(map, {
            coordinate: QtPositioning.coordinate(lat, lon)
        })
        map.addMapItem(item)
        markers.push(item)
    }

    function clearMarkers(tokeep) {
        for (var i = tokeep; i < markers.length; i++) {
            map.removeMapItem(markers[i])
        }
        if (!markers.length === 0){
            var item = component.createObject(map, {
                coordinate: QtPositioning.coordinate(markers[0], marker[0])
            })
            markers = []
            if (tokeep === 1){
                map.addMapItem(item)
                markers.push(item)
            }
        }
    }

    function clearLine(){
        map.removeMapItem(mapline);
    }

    Component{
        id: locmarker
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
