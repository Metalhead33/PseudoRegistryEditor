#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTreeWidget>
#include <RegistryStructure/Seeker.hpp>
#include <RegistryStructure/Unserialize.hpp>
#include <map>

typedef std::map<QTreeWidgetItem*,Structure::Element*> IndexContainer;
typedef std::map<QTreeWidgetItem*,Structure::Element*>::iterator IndexIterator;
typedef std::pair<QTreeWidgetItem*,Structure::Element*> IndexPair;

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
    void on_actionExit_triggered();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_buttonAcceptChanges_clicked();

    void on_revertButton_clicked();

    void on_DeleteButton_clicked();

    void on_RenameButton_clicked();

    void on_RevertName_clicked();

private:
    QTreeWidgetItem* cur_item;
    IndexContainer elements;
    QTreeWidgetItem* LookupIndex(Structure::Element* elem);
    void addElement(Structure::Element* elem);
    Ui::MainWindow *ui;

    void DeleteElement(QTreeWidgetItem *item);
    void UpdateDisplayer();
};

#endif // MAINWINDOW_HPP
