import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../Components"

RowLayout {
    id:categoryRow
    property alias categoryName : category_name.text
    property alias categoryEntry : category_entry.text
    property alias entryBox : category_entry
    Rectangle{
        id: cat_placeholderTop
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width * 0.2
        opacity: 0
    }
    TextBox{
        id: category_name
        text: ""
        state: "desc"
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width * 0.2
    }
    EntryBox{
        id: category_entry
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width * 0.4
        text: ""
    }
    Rectangle{
        id: cat_placeholderBottom
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width * 0.2
        opacity: 0
    }
}
