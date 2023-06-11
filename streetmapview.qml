import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    Plugin {
        id: osm
        name: "osm"
        // specify plugin parameters if necessary
        PluginParameter{name: "osm.useragent"; value: "UAStarr"}
        PluginParameter{name: "osm.mapping.custom.host"; value: "https://tile.openstreetmap.org"}
        PluginParameter{name: "osm.mapping.providersrepository.disabled"; value: true}
    }

    Map {
        anchors.fill: parent
        plugin: osm
        center: QtPositioning.coordinate(53.5461, -113.4937, 13) // Edmonton
        zoomLevel: 14
    }
}
