import QtQuick 2.0
import QtPosition 5.5
import QtLocation 6.6

Rectangle {
    anchors.fill: parent

    Plugin {
        id: osmPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.providersrepository.disable"
            value: "true"
        }

        PluginParameter {
            name: "osm.mapping.providersrepository.address"
            value: "https://maps-redirect.qt.io/osm/5.6/"
        }

        // PluginParameter { // will contain tile server
        //     name: "osm.mapping.custom.host"
        //     value: ""
        // }
    }
}
