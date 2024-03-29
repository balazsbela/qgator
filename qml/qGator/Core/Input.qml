import QtQuick 2.0

FocusScope {
    id:container
    width: 220
    height: 28
    BorderImage { source: "../Components/images/lineedit.sci"; anchors.fill: parent }
    signal accepted
    property alias text: input.text
    property alias item:input
    TextInput{
        id: input
        width: parent.width - 12
        anchors.centerIn: parent
        maximumLength:21
        font.pixelSize: 16;
        font.bold: true
        color: "#151515"; selectionColor: "mediumseagreen"
        focus: true
        onAccepted:{container.accepted()}
        text: ""
        selectByMouse: true
    }
}
