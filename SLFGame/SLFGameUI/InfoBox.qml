import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3


Rectangle{
    property alias descriptionText : desc.text
    property alias outputText : output.text
    property string adapterProperty
    ColumnLayout{
        spacing: 0
        anchors.fill: parent
        Rectangle
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            opacity: 0
        }
        TextBox{
            id: desc
            text: "Buchstabe"
            Layout.preferredHeight: parent.height * 0.2
            Layout.preferredWidth: parent.width * 0.8
            Layout.rightMargin: parent.width * 0.1
            Layout.leftMargin: parent.width * 0.1
        }
        TextBox{
            id: output
            text: qmlAdapter[adapterProperty]
            Layout.preferredHeight: parent.height * 0.2
            Layout.preferredWidth: parent.width * 0.8
            Layout.rightMargin: parent.width * 0.1
            Layout.leftMargin: parent.width * 0.1
        }
        Rectangle
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            opacity: 0
        }
    }
}
