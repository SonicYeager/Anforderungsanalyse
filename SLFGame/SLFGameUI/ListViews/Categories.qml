import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Modules"

ListView {
    id: category_list
    property alias count: list_model.count
    property alias listModel: list_model
    property var spacingSum : spacing * 2
    spacing: 5
    interactive: false

    delegate: Category{
        id: cat
        categoryName: model.categoryName
        categoryEntry: model.categoryEntry
        width : category_list.width
        height: 50
        onCategoryEntryChanged: {
            model.categoryEntry = categoryEntry
        }
    }
    model: ListModel{
         id:list_model
    }
}
