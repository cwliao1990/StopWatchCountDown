import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.settings 1.0
import "controls"

Item {
    id: _self
    property int fontSize: 80
    property bool isRun: false
    width: 600
    height: 550
    visible: true

    Settings {
        id: _setting
        property string savedTimeDisplay: "00:00:00.00"
        property var savedTimeRecordList: []
    }

    Text {
        id: _timeDisplay
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 20
        text: StopWatch.timeDisplay
        color: "black"
        font.pixelSize: fontSize
        font.bold: true
    }

    Row {
        id: _buttonRow
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _timeDisplay.bottom
        anchors.margins: 20
        spacing: 20

        Button {
            id: _buttonStartPause
            contentItem: Text {
                text: isRun ? "Pause":"Start"
                font.pixelSize: fontSize/3
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                implicitWidth: 180
                implicitHeight: 50
                radius: 25
                color: _buttonStartPause.down ? "#646464":"#C4C4C4"
            }
            onClicked: {
                isRun = !isRun;
                StopWatch.setStopWatchRun(isRun);
            }
        }

        Button {
            id: _buttonSpilt
            contentItem: Text {
                text: isRun ? "Spilt":"Reset"
                font.pixelSize: fontSize/3
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                implicitWidth: 180
                implicitHeight: 50
                radius: 25
                color: _buttonSpilt.down ? "#646464":"#C4C4C4"
            }
            onClicked: {
                    if(isRun) {
                        StopWatch.addNewTimeRecord();
                    }
                    else {
                        StopWatch.reset();
                    }

            }
        }
    }

    ListView {
        id: _timeRecordList
        anchors.top: _buttonRow.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 80
        height: 500
        spacing: 5
        headerPositioning: ListView.OverlayHeader

        header: Rectangle {
            color: _root.windowColor
            width: parent.width
            height: 30
            RectangleBorder {
                topBorderwidth: 2
                bottomBorderwidth: 2
            }
            Row {//cwl_是否可以設 id 然後給 timeDelegate 對齊
                id: _listHeaderRow
                spacing: 85
                Text {
                    text: "Spilt Number"
                    font.pixelSize: fontSize/3
                }
                Text {
                    text: "Lap Time"
                    font.pixelSize: fontSize/3
                }
                Text {
                    text: "Spilt Time"
                    font.pixelSize: fontSize/3
                }
            }
        }

        model: StopWatch.timeRecordList
        delegate: _timeDelegate

        Component {
            id: _timeDelegate
            Item { //cwl_? 一定要這層？
                //anchors.leftMargin: 50
                //anchors.topMargin: 50
                width: _timeRecordList.width
                height: 30
                Item {
                    width: parent.width/3
                    height: parent.height
                    anchors.left: parent.left
                    anchors.leftMargin: -20
                    Text {
                        text: modelData.lapIndex
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: fontSize/4
                        color: "black"
                    }
                }

                Item {
                    width: parent.width/3
                    height: parent.height
                    anchors.horizontalCenter: parent.horizontalCenter
                    //anchors.leftMargin: 20 //cwl_不能微調？
                    Text {
                        text: modelData.lapTime
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.rightMargin: 30
                        font.pixelSize: fontSize/4
                        color: "black"
                    }
                }

                Item {
                    width: parent.width/3
                    height: parent.height
                    anchors.right: parent.right
                    anchors.rightMargin: -30
                    Text {
                        text: modelData.spiltTime
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: fontSize/4
                        color: "black"
                    }
                }
            }
        }
    }

    Rectangle {
        width: 30
        height: 30
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        color: _root.windowColor
        Image {
            width: parent.width
            height: parent.height
            source: "qrc:/image/countDown.png"
            mipmap: true
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                _viewLoader.source = "CountDownView.qml"
            }
        }
    }
}

