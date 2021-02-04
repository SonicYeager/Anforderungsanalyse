import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

ListView {
    id: category_list
    property alias count: list_model.count
    property alias listModel: list_model
    interactive: false

    delegate: Category{
        categoryName: model.categoryName
        categoryEntry: model.categoryEntry
        width : category_list.width
        height: 50
    }
    model: ListModel{
         id:list_model
    }
}
