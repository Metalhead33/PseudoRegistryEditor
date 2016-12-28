#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->setModel(new ElementContainerItem());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateName()
{
    if(cur_elem) ui->NameEditor->setPlainText(QString::fromStdString(cur_elem->GetName() )  );
    else ui->NameEditor->clear();
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    cur_index = index;
    cur_elem = (Structure::Element*)cur_index.internalPointer();
    UpdateName();
}

void MainWindow::on_RevertNameButton_clicked()
{
    UpdateName();
}

void MainWindow::on_AcceptNameChange_clicked()
{
    if(cur_elem)
    {
        cur_elem->SetName(ui->NameEditor->toPlainText().toStdString()  );
    }
    UpdateName();
}
void MainWindow::UpdateElement()
{
    cur_elem = (Structure::Element*)cur_index.internalPointer();
}

void MainWindow::on_DeleteButton_clicked()
{
    if(cur_index.isValid())
    {
        QModelIndex temp_index = cur_index;
        cur_index = temp_index.parent();
        UpdateElement();
        UpdateName();
        if(temp_index.parent().isValid()) ui->treeView->model()->removeRow(temp_index.row(),temp_index.parent());
    }
}
