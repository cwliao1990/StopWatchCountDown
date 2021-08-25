import QtQuick 2.0

Rectangle {
    id: _self

    property string handColor: "black"
    property int handLength: 50
    property int handWidth: 4
    property real centerX : width/2
    property real centerY : height/2
    property int initAngle: 0
    property alias rotationAngle: _dragHand.rotation

    signal positionChanged()

    function rotateClockHand(degree) {
        _dragHand.rotation = degree;
    }

    anchors.centerIn: parent
    color: "transparent"
    width: 2*handLength
    height: 2*handLength
    radius: handLength

    Rectangle {
        id: _dragHand
        color: handColor
        width: handWidth
        height: handLength
        radius: width/2
        anchors.bottom: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        transformOrigin: Item.Bottom
        antialiasing: true
        rotation: 0
        MouseArea{
            anchors.fill: parent
            anchors.leftMargin: -5
            anchors.rightMargin: -5
            onPositionChanged:  {
                var point =  mapToItem (_self, mouse.x, mouse.y);
                console.log(mouse.x, mouse.y, point.x, point.y);
                var diffX = point.x - _self.centerX;
                var diffY = _self.centerY - point.y;
                var rad = Math.atan2(diffX, diffY);
                var deg = rad * 180 / Math.PI;
                deg = (deg < 0) ? deg += 360 : deg;
                console.log(diffX, diffY, rad, deg);
                _dragHand.rotation = deg;
                _self.positionChanged();
            }
        }

    }
}
