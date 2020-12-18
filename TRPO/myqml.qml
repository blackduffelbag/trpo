import QtQuick 2.12
import QtLocation 5.6
import QtPositioning 5.6

Item {

    function to_city(anArray) {
        map.center = QtPositioning.coordinate(anArray[0], anArray[1])
        map.zoomLevel = 13
    }

    function add_road(anArray) {
        routeModel.query.clearWaypoints();
        for (var i=0; i<anArray.length;  i=i+2){
            routeModel.query.addWaypoint(QtPositioning.coordinate(anArray[i], anArray[i+1]));
            routeModel.update();
        }
    }


    RouteModel {
        id: routeModel
        plugin: mapPlugin


       query: RouteQuery {}
        Component.onCompleted: {

        }
    }


    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(50.4507, 30.5214)
        zoomLevel: 1

        MapItemView {
                model: routeModel
                delegate: MapRoute {
                    route: routeData
                    line.color: "red"
                    line.width: 5
                    smooth: true
                }
            }
    }
}

