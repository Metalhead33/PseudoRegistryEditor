#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTreeWidget>
#include "ElementContainerItem.hpp"
#include "AddNewElement.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_treeView_clicked(const QModelIndex &index);

    void on_RevertNameButton_clicked();

    void on_AcceptNameChange_clicked();

    void on_DeleteButton_clicked();

    void on_RevertButton_clicked();

    void on_AcceptChangesButton_clicked();

    void on_NewElementButton_clicked();

    void on_actionSave_File_triggered();

private:
    Structure::Element* cur_elem;
    QModelIndex cur_index;
    ElementContainerItem* container;
    Ui::MainWindow *ui;
    AddNewElement* element_adder;
    void UpdateName();
    void UpdateElement();
    void UpdateDisplay();
};

#endif // MAINWINDOW_HPP
