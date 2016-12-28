#ifndef ADDNEWELEMENT_H
#define ADDNEWELEMENT_H

#include <QDialog>
#include "ElementContainerItem.hpp"

namespace Ui {
class AddNewElement;
}

class AddNewElement : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewElement(QWidget *parent = 0,ElementContainerItem* container = 0, QModelIndex index = QModelIndex() );
    ~AddNewElement();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_AddNewElement_accepted();

    void on_AddNewElement_rejected();

private:
    Ui::AddNewElement *ui;
    QModelIndex m_index;
    ElementContainerItem* m_container;
};

#endif // ADDNEWELEMENT_H
