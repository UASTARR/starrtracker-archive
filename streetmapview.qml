import QtQuick 2.7
import QtQuick.Window 2.2
import QtLocation 5.8
import QtPositioning 5.8

Window {
    id: win
    objectName: "window"
    visible: true
    width: 512
    height: 512

    Plugin {
        id: osm
        name: "osm"

        PluginParameter {
            name: "osm.useragent"
            value: "UAStarr"
        }

        PluginParameter {
            name: "osm.mapping.offline.directory"
            value: "qrc:/tiles/15/9124/"
        }

        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: true
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: osm
        activeMapType: map.supportedMapTypes[1]
        center: QtPositioning.coordinate(53.5461, -113.4937, 13) // Edmonton
        zoomLevel: 5
    }
}
