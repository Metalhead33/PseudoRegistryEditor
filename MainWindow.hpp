#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTreeWidget>
#include "ElementContainerItem.hpp"

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

private:
    Ui::MainWindow *ui;
    Structure::Element* cur_elem;
    QModelIndex cur_index;
    void UpdateName();
    void UpdateElement();
    void UpdateDisplay();
};

#endif // MAINWINDOW_HPP
