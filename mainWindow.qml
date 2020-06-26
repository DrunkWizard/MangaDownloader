import QtQuick 2.0
import QtQuick.Controls 2.5
import ScrapImage 1.0;
Item {
    anchors.fill: parent
    property bool allChaptersCheck;
    ScrapImage{
        id: scrapImage;
    }

    TextField{
        id: linkField
        placeholderText: qsTr("Enter link to manga")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.2
        width: parent.width - 300
    }
    Button{
        id: submitButton
        anchors.top: linkField.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height * 0.2
        text: "Submit"
        enabled: allChaptersCheck || (from.text != "" && to.text != "")
        onClicked: {
            scrapImage.parse(linkField.text, allChaptersCheck, from.text, to.text);
        }
    }
    BusyIndicator{
        id: downloadIndicator
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.2
        running: scrapImage.downloadInProgress
    }

    Column{
        anchors.left: linkField.left
        anchors.top: linkField.top
        anchors.topMargin: 60
        spacing: 10
        Text {
            id: allChaptersText
            text: qsTr("All Chapters")
        }
        CheckBox{
            id: allChapters
            onCheckStateChanged: {
                if(checked == true)
                    allChaptersCheck = true;
                else
                    allChaptersCheck = false;
            }
        }
        Text {
            id: fromText
            text: qsTr("From")
            visible: !allChaptersCheck
        }
        TextField{
            id: from
            visible: !allChaptersCheck
        }
        Text {
            id: toText
            text: qsTr("To")
            visible: !allChaptersCheck
        }
        TextField{
            id: to
            visible: !allChaptersCheck
        }
    }
}
