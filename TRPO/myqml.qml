import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.6
import QtPositioning 5.6

Item {
    //width: 512
    //height: 512
    //visible: true

    signal widgetSignal;

    signal tour_changed;

    signal go_to_city;


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

    onGo_to_city: {
        //function readValues(anArray) {
            //map.center = QtPositioning.coordinate(anArray[0], anArray[1])

                //for (var i=0; i<anArray.length; i++)
                   // console.log("Array item:", anArray[i])
       // }

        //map.center = QtPositioning.coordinate(40.91, 20.75); //working
    }



    RouteModel {
        id: routeModel
        plugin: mapPlugin


       query: RouteQuery {}
        Component.onCompleted: {

            //for (var i = 0; i<5; i++)
            //{
            //routeModel.query.addWaypoint(QtPositioning.coordinate(59.91 + i, 10.75 + i))
            //    routeModel.update();
           // }



            //(QVariant(QString, "50.4507"), QVariant(QString, "30.5214"))
            //(QVariant(QString, "52.5130"), QVariant(QString, "13.3813"))
            //(QVariant(QString, "46.9484"), QVariant(QString, "7.4503"))

            //query.addWaypoint(QtPositioning.coordinate(50.4507, 30.5214));
            //routeModel.update();
            //query.addWaypoint(QtPositioning.coordinate(52.5130, 13.3813));
            //routeModel.update();
            //query.addWaypoint(QtPositioning.coordinate(46.9484, 7.4503));
            //routeModel.update();

            //query.addWaypoint(QtPositioning.coordinate(26.288128, 50.188725));
            //routeModel.update();
        }



       // onStatusChanged: console.debug("current route model status", status, count, errorString)
    }


    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo 55.0179,82.9344
        zoomLevel: 14

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

