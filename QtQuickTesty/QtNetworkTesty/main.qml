import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 1920 * 0.5
    height: 1080 * 0.5
    visible: true
    title: qsTr("Prototype")
    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        Layout.alignment: Qt.AlignHCenter
        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "black"
            Flickable {
                id: flickable
                anchors.fill: parent

                TextArea.flickable: TextArea {
                    text: qmlAdapter.labelText
                    color: "white"
                    wrapMode: TextArea.Wrap
                    background: Rectangle {
                            color: "black"
                        }
                }

                ScrollBar.vertical: ScrollBar { }
            }
        }
        Rectangle {
            Layout.preferredHeight: 100
            Layout.preferredWidth: 200
            Layout.alignment: Qt.AlignHCenter
            color: Qt.rgba(0,0,0,0)
            RowLayout{
                anchors.fill: parent
                Layout.alignment: Qt.AlignHCenter
                spacing: 0
                Button{
                    id: buttonhost
                    text: "Host";
                    onClicked: {
                        qmlAdapter.startHost();
                    }
                }
                Button{
                    id: buttonjoin
                    text: "Join"
                    onClicked: {
                        qmlAdapter.joinHost();
                    }
                }
                Button{
                    id: buttonsend
                    text: "Send Data"
                    onClicked: {
                        qmlAdapter.sendData();
                    }
                }
            }
        }

    }
}
