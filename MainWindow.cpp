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
    UpdateElement();
    UpdateName();
    UpdateDisplay();
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
    if(cur_index.isValid()) cur_elem = (Structure::Element*)cur_index.internalPointer();
    else cur_elem = 0;
}
void MainWindow::UpdateDisplay()
{
    if(cur_elem)
    {
        if(cur_elem->IsDirectory())
        {
            ui->ContextEditor->setHidden(true);
            ui->AcceptChangesButton->setHidden(true);
            ui->RevertButton->setHidden(true);
        }
        else
        {
        ui->ContextEditor->setHidden(false);
        ui->AcceptChangesButton->setHidden(false);
        ui->RevertButton->setHidden(false);
        Structure::File* fail = (Structure::File*)cur_elem;
            switch(fail->GetFiletype())
            {
            case Structure::File::BOOL:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),32);
                if( ((Structure::BooleanFile*)fail)->GetContent()  ) ui->ContextEditor->setPlainText(QString("true"));
                else ui->ContextEditor->setPlainText(QString("false"));
                break;
            }
            case Structure::File::STRING:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),120);
                ui->ContextEditor->setPlainText(QString::fromStdString(((Structure::StringFile*)fail)->GetContent()   ));
                break;
            }
            case Structure::File::STRING16:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),120);
                ui->ContextEditor->setPlainText(QString::fromStdU16String(((Structure::String16File*)fail)->GetContent())  );
                break;
            }
            case Structure::File::STRING32:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),120);
                ui->ContextEditor->setPlainText(QString::fromStdU32String(((Structure::String32File*)fail)->GetContent())  );
                break;
            }
            case Structure::File::UINT8:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),32);
                std::stringstream convert;
                convert << ((Structure::Uint8File*)fail)->GetContent();
                ui->ContextEditor->setPlainText(QString::fromStdString(convert.str( ))  );
                break;
            }
            case Structure::File::SINT8:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),32);
                std::stringstream convert;
                convert << ((Structure::Int8File*)fail)->GetContent();
                ui->ContextEditor->setPlainText(QString::fromStdString(convert.str( ))  );
                break;
            }
            case Structure::File::UINT64:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),32);
                std::stringstream convert;
                convert << ((Structure::Uint64File*)fail)->GetContent();
                ui->ContextEditor->setPlainText(QString::fromStdString(convert.str( ))  );
                break;
            }
            case Structure::File::SINT64:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),32);
                std::stringstream convert;
                convert << ((Structure::Int64File*)fail)->GetContent();
                ui->ContextEditor->setPlainText(QString::fromStdString(convert.str( ))  );
                break;
            }
            case Structure::File::FLOAT:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),32);
                std::stringstream convert;
                convert << ((Structure::FloatFile*)fail)->GetContent();
                ui->ContextEditor->setPlainText(QString::fromStdString(convert.str( ))  );
                break;
            }
            default:
            {
                ui->ContextEditor->clear();
                break;
            }
            }
        }
    }
    else
    {
        ui->ContextEditor->setHidden(true);
        ui->AcceptChangesButton->setHidden(true);
        ui->RevertButton->setHidden(true);
    }
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
