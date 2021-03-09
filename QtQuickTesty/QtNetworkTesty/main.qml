import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 200
    height: 200
    visible: true
    title: qsTr("Prototype")

    ColumnLayout{
        id: buttons
        anchors.fill: parent
        Layout.alignment: Qt.AlignHCenter
        Label{
            Layout.alignment: Qt.AlignHCenter
            text: qmlAdapter.labelText
        }
        RowLayout{
            Layout.alignment: Qt.AlignHCenter
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
        }
    }
}
