import QtQuick 2.0
import QtQuick.Controls 2.5
import FileModel 1.0;

Item{
    anchors.fill: parent
    FileModel{
        id: fileModel
    }
    GridView{
        id: fileViewer
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 40
        height: parent.height - 40
        model: fileModel
        delegate: Rectangle{
            width: 95
            height: 95
            border.width: 1
            MouseArea{
                id: modelMouseArea
                anchors.fill: parent
                onClicked: {
                    fileModel.openDir(fileName.text);
                }
            }

            Text {
                id: fileName
                text: model.fileName
                anchors.centerIn: parent;
            }

            Text {
                id: fyleSize
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                text: model.fileSize
            }
        }
    }
}
