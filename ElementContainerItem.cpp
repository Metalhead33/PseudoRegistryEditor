#include "ElementContainerItem.hpp"

ElementContainerItem::ElementContainerItem()
    : QAbstractItemModel()
{
    root_dir = Structure::ROOT_DIRECTORY;
}
bool ElementContainerItem::removeRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid()) {
        Structure::Element* parent_elem = (Structure::Element*)parent.internalPointer();
        if(!parent_elem) return false;
        if(!parent_elem->IsDirectory()) return false;
        Structure::Directory* parent_dir = (Structure::Directory*)parent_elem;
        if(rowCount(parent) < row+count) return false;
        beginRemoveRows(parent,row,row+count);
        for(int i = 0;i < count;++i) delete parent_dir->GetPElementByRow(row);
        endRemoveRows();
        return true;
    }
    else return false;
}

QVariant ElementContainerItem::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= rowCount(index.parent())) return QVariant();
    //if(role != Qt::DisplayRole) return QVariant();
    //return QString::fromStdString(((Structure::Element*)index.internalPointer())->GetName());
    switch(role)
    {
    case Qt::DisplayRole :
        return QString::fromStdString(((Structure::Element*)index.internalPointer())->GetName());
    default:
        return QVariant();
    }
}
int ElementContainerItem::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        Structure::Element* elem = (Structure::Element*)parent.internalPointer();
        if(elem->IsDirectory()) return ((Structure::Directory*)elem)->GetNumChildren();
        else return 0;
        //return ((Structure::Directory*)parent.internalPointer())->GetNumChildren();
    }
    else return root_dir->GetNumChildren();
}
int ElementContainerItem::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QModelIndex ElementContainerItem::index(int row, int column, const QModelIndex &parent) const
{
    /*if(!parent.isValid())
      return createIndex(row, column, 0);

    Structure::Element* parentP = (Structure::Element*)parent.internalPointer();

    Structure::Directory* true_parent = parentP->GetParent();

    return createIndex(row, column, true_parent);*/
    if(!parent.isValid())
      return createIndex(row, column, root_dir->GetPElementByRow(row));

    Structure::Directory* parent_2 = (Structure::Directory*)parent.internalPointer();

    return createIndex(row, column, parent_2->GetPElementByRow(row));
}
QModelIndex ElementContainerItem::parent(const QModelIndex &child) const
{
    if(!child.isValid()) return QModelIndex();
    Structure::Element* element = (Structure::Element*)child.internalPointer();

    Q_ASSERT(element);
    Structure::Directory* parent = element->GetParent();
    if(!parent) return QModelIndex();
    if(parent == root_dir) return QModelIndex();

    int row = 0;
    Structure::Directory* higher_parent = parent->GetParent();

    if(higher_parent)
    {
        Structure::ElementContainer* children = higher_parent->GetContainer();
        Structure::ElementIterator it;
      if(!children->empty()) for(it = children->begin(), row = 0;it != children->end() && (*it) != parent;++row,++it);
    }

    return createIndex(row, 0, parent);
}
