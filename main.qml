import QtQuick 2.7
import QtQuick.Window 2.2
import QtLocation 5.8
import QtPositioning 5.6

Rectangle {
    id: win
    objectName: "window"
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
    }
}
