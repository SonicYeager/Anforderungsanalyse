#include "QmlAdapter.h"

QmlAdapter::QmlAdapter(QObject *parent) :
    QObject(parent)
{

}

QString QmlAdapter::getLetter()
{
    return _letter;
}

Categories QmlAdapter::getCategories()
{
    return _categories;
}

int QmlAdapter::getCategoryCount()
{
    return _categoryCount;
}

void QmlAdapter::setLetter(QString letter)
{
    if (letter == _letter)
        return;
    _letter = letter;
    emit letterChanged();
}

void QmlAdapter::setCategories(Categories categories)
{
    if (categories == _categories)
        return;
    _categories = categories;
    emit categoriesChanged();
}

void QmlAdapter::setCategoryCount(int categoryCount)
{
    if (categoryCount == _categoryCount)
        return;
    _categoryCount = categoryCount;
    emit categoryCountChanged();
}

QString QmlAdapter::getCategoryName(int idx)
{
    return QString::fromUtf8(_categories[idx].c_str());
}
