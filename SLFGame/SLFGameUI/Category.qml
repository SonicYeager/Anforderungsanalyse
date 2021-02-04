import QtQuick 2.0
import QtQuick.Layouts 1.3

RowLayout {
    id:categoryRow
    property alias categoryName : category_name.text
    property alias categoryEntry : category_entry.text
    Rectangle{
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width * 0.1
        opacity: 0
    }

    TextBox{
        id: category_name
        text: ""
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width * 0.2
    }
    EntryBox{
        id: category_entry
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width * 0.6
        text: ""
    }
    Rectangle{
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width * 0.1
        opacity: 0
    }
}
