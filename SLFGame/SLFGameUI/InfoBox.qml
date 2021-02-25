import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3


Rectangle{
    property alias descriptionText : desc.text
    property alias outputText : output.text
    property alias outputTextColor : output.textColor
    property string adapterProperty
    property alias desc : desc.state
    RowLayout {
        spacing: 0
        anchors.fill: parent
        Rectangle
        {
            Layout.preferredHeight: parent.hight
            Layout.fillWidth: true
            opacity: 0
        }
        Rectangle{
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: parent.width * 0.15
            color: Qt.rgba(0,0,0,0)
            ColumnLayout{
                spacing: 0
                anchors.fill: parent
                Rectangle
                {
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.width
                    opacity: 0
                }
                TextBox{
                    id: desc
                    text: "Buchstabe"
                    state: "desc"
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 150
                    //Layout.rightMargin: parent.width * 0.1
                    //Layout.leftMargin: parent.width * 0.1
                }
                TextBox{
                    id: output
                    text: qmlAdapter[adapterProperty]
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 150
                    //Layout.rightMargin: parent.width * 0.1
                    //Layout.leftMargin: parent.width * 0.1
                }
                Rectangle
                {
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.width
                    opacity: 0
                }
            }
        }
        Rectangle
        {
            Layout.preferredHeight: parent.hight
            Layout.fillWidth: true
            opacity: 0
        }
    }
}
