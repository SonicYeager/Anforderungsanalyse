import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

ListView {
    id: list
    property alias count: list_model.count
    property alias listModel: list_model
    spacing: 5
    interactive: false


    delegate: AnswerBlock {
        id: answerBlock
        playerName: qmlAdapter.getPlayer(index)
        width : 820
        height: 30
        answer: qmlAdapter.getAnswer(index, qmlAdapter.activeOverviewItem)
        answerIDX: index
    }
    model: ListModel{
         id:list_model
    }
}
