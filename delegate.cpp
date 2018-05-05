#include "delegate.h"
#include <QModelIndex>
Delegate::Delegate(QObject *parent) : QItemDelegate(parent)
{

}
QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor=new QSpinBox(parent);
    editor->setMinimum(1);
    editor->setMaximum(9);
    return editor;
}
void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //if((index.QModelIndex.data)==0)
    //{
        int value=index.model()->data(index,Qt::EditRole).toInt();
        QSpinBox *spinbox=static_cast<QSpinBox*>(editor);
        spinbox->setValue(value);
    //}
}
void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //if((index.QModelIndex.data)==0)
    //{
        QSpinBox *spinbox=static_cast<QSpinBox*>(editor);
        spinbox->interpretText();
        int value = spinbox->value();
        model->setData(index,value,Qt::EditRole);
    //}
}
void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //if((index.QModelIndex.data)==0)
    //{
        editor->setGeometry(option.rect);
    //}
}
