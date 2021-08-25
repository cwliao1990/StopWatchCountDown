import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: _root
    property string windowColor: "#E5E5E5"
    width: 600
    height: 550
    visible: true
    color: "#E5E5E5"
    title: "Stop Watch and Count Down"
    Item {
        width: _root.width
        height: _root.height
        anchors.fill: parent
        Loader{
            id: _viewLoader
            width: _root.width
            height: _root.height
            anchors.fill: parent
            source: "StopWatchView.qml"
        }
    }


}
