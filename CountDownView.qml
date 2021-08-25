import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.settings 1.0
import CountDown 1.0
import "controls"

Item {
    id: _self

    property int fontSize: 80

    width: 600
    height: 550
    visible: true

    Component.onCompleted: {
        _countDown.setHMS(_setting.savedHr, _setting.savedMin, _setting.savedSec);
        _hrHand.rotateClockHand(_setting.savedHr * 30 + _setting.savedMin * 0.5);
        _minHand.rotateClockHand(_setting.savedMin * 6);
        _secHand.rotateClockHand(_setting.savedSec * 6);
    }

    Component.onDestruction: {
        _setting.savedHr = _countDown.getHour();
        _setting.savedMin = _countDown.getMin();
        _setting.savedSec = _countDown.getSec();
    }

    Settings {
        id: _setting
        property int savedHr: 0
        property int savedMin: 0
        property int savedSec: 0
    }

    CountDown {
        id: _countDown
        onTimeDisplayChanged: {
            if (_countDown.isRun) {
                var hr = _countDown.getHour();
                var min = _countDown.getMin();
                var sec = _countDown.getSec();
                _hrHand.rotateClockHand(hr*30+min*0.5);
                _minHand.rotateClockHand(min*6);
                _secHand.rotateClockHand(sec*6);
            }
        }
    }

    Text {
        id: _timeDisplay
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 20
        text: _countDown.timeDisplay
        color: "black"
        font.pixelSize: fontSize
        font.bold: true
    }

    Rectangle{
        id: _recClock;
        width: 300
        height: 300
        color: "white";
        radius: (width / 2);
        antialiasing: true;
        anchors.centerIn: parent;
        Image {
            width: parent.width
            height: parent.height
            source: "image/clock.png"
            mipmap: true
        }
        ClockDragHand {
            id: _hrHand
            handColor: "black"
            handLength: 60
            handWidth: 4
            z: 3
            onPositionChanged: {
                if (!_countDown.isRun) {
                    _countDown.setHMS((Math.floor(_hrHand.rotationAngle/30)%12),
                                      (Math.floor(_minHand.rotationAngle/6)%60),
                                      (Math.floor(_secHand.rotationAngle/6)%60));
                }
            }
        }
        ClockDragHand {
            id: _minHand
            handColor: "gray"
            handLength: 100
            handWidth: 3
            z: 2
            onPositionChanged: {
                if (!_countDown.isRun) {
                    _countDown.setHMS((Math.floor(_hrHand.rotationAngle/30)%12),
                                      (Math.floor(_minHand.rotationAngle/6)%60),
                                      (Math.floor(_secHand.rotationAngle/6)%60));
                }
            }
        }
        ClockDragHand {
            id: _secHand
            handColor: "red"
            handLength: 140
            handWidth: 2
            z: 1
            onPositionChanged: {
                if (!_countDown.isRun) {
                    _countDown.setHMS((Math.floor(_hrHand.rotationAngle/30)%12),
                                      (Math.floor(_minHand.rotationAngle/6)%60),
                                      (Math.floor(_secHand.rotationAngle/6)%60));
                }
            }
        }
    }

    Button {
        id: _buttonStartPause
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _recClock.bottom
        anchors.margins: 40
        contentItem: Text {
            text: _countDown.isRun? "Pause":"Start"
            font.pixelSize: fontSize/3
            color: "black"
            horizontalAlignment: Text.AlignHCenter //cwl_??
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            implicitWidth: 180 //cwl??
            implicitHeight: 50
            radius: 25
            color: _buttonStartPause.down ? "#646464":"#C4C4C4" //cwl_??
        }
        onClicked: {
            _countDown.setCountDownRun(!_countDown.isRun);
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
            source: "image/stopWatch.png"
            mipmap: true
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                _viewLoader.source = "StopWatchView.qml"
            }
        }
    }
}


