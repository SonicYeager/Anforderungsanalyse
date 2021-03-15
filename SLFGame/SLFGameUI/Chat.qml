import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle {
    Layout.preferredHeight: parent.height
    Layout.preferredWidth: parent.width
    color: Qt.rgba(0,0,0,0)
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Layout.alignment: Qt.AlignHCenter
        Rectangle {
            Layout.preferredHeight: parent.height * 0.9 - 10
            Layout.fillWidth: true - 20
            Layout.bottomMargin: 10
            color: Qt.rgba(0,0,0,0)
            Flickable {
                id: flickable
                anchors.fill: parent
                interactive: false

                TextArea.flickable: TextArea {
                    readOnly: true
                    selectByMouse: true
                    activeFocusOnPress: true
                    text: qmlAdapter.chatLog
                    font.pointSize: 14
                    color:"#9fcce0"
                    wrapMode: TextArea.Wrap
                    background: Rectangle {
                        color: "black"
                        border.width: 3
                        border.color: "#d4d6d5"
                    }
                }

                ScrollBar.vertical: ScrollBar { }
            }
        }
        Rectangle {
            Layout.preferredHeight: parent.height * 0.1
            Layout.fillWidth: true
            color: Qt.rgba(0,0,0,0)
            RowLayout {
                anchors.fill: parent
                spacing: 0
                EntryBox{
                    id: entryBox
                    Layout.preferredWidth: parent.width * 0.8
                    Layout.preferredHeight: parent.height - 10
                    Layout.alignment: Qt.AlignVCenter
                    Layout.rightMargin: parent.width * 0.02
                    horizontalAlignment: TextEdit.AlignLeft
                    state: "chatEntry"
                }
                GameButton {
                    text: "SEND"
                    textColor: "black"
                    Layout.preferredWidth: parent.width * 0.18
                    Layout.preferredHeight: parent.height - 10
                    state: "whiteButton"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (entryBox.text !== "")
                            {
                                qmlAdapter.sendChatMessage(entryBox.text);
                                entryBox.text = "";
                            }
                        }
                    }
                }
            }
        }
    }
}
