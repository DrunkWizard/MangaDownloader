import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 1000
    height: 480
    title: qsTr("Manga Downloader")
    property bool fileViewerStatus: false
    Loader{
        id: pageLoader
        anchors.fill: parent;
        source: (fileViewerStatus === false)
                ? "qrc:/mainWindow.qml"
                : "qrc:/fileViewer.qml"
    }
    Item {
        id: switchWindowButtons
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: parent.height * 0.2
        anchors.rightMargin: parent.width * 0.2
        Button{
            id: fileViewerButton
            text: "Library"
            onClicked: {
                fileViewerStatus = true;
                mainWidnowButton.visible = true;
                visible = false;
            }
        }
        Button{
            visible: false
            id: mainWidnowButton
            text: "Back to main"
            onClicked: {
                fileViewerStatus = false;
                fileViewerButton.visible = true;
                visible = false;
            }
        }
    }
}
