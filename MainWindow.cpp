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
