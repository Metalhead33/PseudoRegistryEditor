#ifndef ELEMENTCONTAINERITEM_H
#define ELEMENTCONTAINERITEM_H
#include <QAbstractItemModel>
#include <RegistryStructure/Seeker.hpp>
#include <RegistryStructure/Unserialize.hpp>

class ElementContainerItem : public QAbstractItemModel
{
public:
    ElementContainerItem();
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
private:
    Structure::Directory* root_dir;
};

#endif // ELEMENTCONTAINERITEM_H
