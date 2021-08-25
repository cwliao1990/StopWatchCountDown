import QtQuick 2.0

Rectangle
{
    property string borderColor : "black"
    property int leftBorderwidth : 0
    property int rightBorderwidth : 0
    property int topBorderwidth : 0
    property int bottomBorderwidth : 0

    color: borderColor
    z : -1
    anchors {
        fill: parent
        topMargin: -topBorderwidth
        bottomMargin: -bottomBorderwidth
        leftMargin: -leftBorderwidth
        rightMargin: -rightBorderwidth
    }
}
