#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->setModel(container = new ElementContainerItem());
    cur_elem = 0;
    UpdateDisplay();
    UpdateName();
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
            ui->BooleanCombobox->setHidden(true);
            ui->NewElementButton->setHidden(false);
        }
        else
        {
        ui->NewElementButton->setHidden(true);
        ui->ContextEditor->setHidden(false);
        ui->AcceptChangesButton->setHidden(false);
        ui->RevertButton->setHidden(false);
        ui->BooleanCombobox->setHidden(true);
        Structure::File* fail = (Structure::File*)cur_elem;
            switch(fail->GetFiletype())
            {
            case Structure::File::BOOL:
            {
                ui->ContextEditor->resize(ui->ContextEditor->width(),32);
                ui->ContextEditor->setHidden(true);
                ui->BooleanCombobox->setHidden(false);
                if(((Structure::BooleanFile*)fail)->GetContent()) ui->BooleanCombobox->setCurrentIndex(2);
                else ui->BooleanCombobox->setCurrentIndex(1);
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
        ui->BooleanCombobox->setHidden(true);
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

void MainWindow::on_RevertButton_clicked()
{
    UpdateDisplay();
}

void MainWindow::on_AcceptChangesButton_clicked()
{
    if(cur_elem)
    {
        if(cur_elem->IsData())
        {
            Structure::File* fail = (Structure::File*)cur_elem;
            switch(fail->GetFiletype())
            {
            case Structure::File::BOOL:
            {
                if(ui->BooleanCombobox->currentIndex() == 2) ((Structure::BooleanFile*)fail)->SetContent(true);
                else ((Structure::BooleanFile*)fail)->SetContent(false);
                break;
            }
            case Structure::File::STRING:
            {
                ((Structure::StringFile*)fail)->SetContent(ui->ContextEditor->toPlainText().toStdString()  );
                break;
            }
            case Structure::File::STRING16:
            {
                ((Structure::String16File*)fail)->SetContent(ui->ContextEditor->toPlainText().toStdU16String()  );
                break;
            }
            case Structure::File::STRING32:
            {
                ((Structure::String32File*)fail)->SetContent(ui->ContextEditor->toPlainText().toStdU32String()  );
                break;
            }
            case Structure::File::UINT8:
            {
                try {
                ((Structure::Uint8File*)fail)->SetContent((uint8_t)std::stoi(ui->ContextEditor->toPlainText().toStdString())); }
                catch(std::exception e)
                {
                    ;
                }
                break;
            }
            case Structure::File::SINT8:
            {
                try {
                ((Structure::Int8File*)fail)->SetContent((int8_t)std::stoi(ui->ContextEditor->toPlainText().toStdString()));
                }
                catch(std::exception e)
                {
                    ;
                }
                break;
            }
            case Structure::File::UINT64:
            {
                try {
                ((Structure::Uint64File*)fail)->SetContent((uint64_t)std::stoi(ui->ContextEditor->toPlainText().toStdString()));
                }
                catch(std::exception e)
                {
                    ;
                }
                break;
            }
            case Structure::File::SINT64:
            {
                try {
                ((Structure::Int64File*)fail)->SetContent((int64_t)std::stoi(ui->ContextEditor->toPlainText().toStdString()));
                }
                catch(std::exception e)
                {
                    ;
                }
                break;
            }
            case Structure::File::FLOAT:
            {
                try {
                ((Structure::FloatFile*)fail)->SetContent(std::stod(ui->ContextEditor->toPlainText().toStdString()));
                }
                catch(std::exception e)
                {
                    ;
                }
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
    UpdateDisplay();
}

void MainWindow::on_NewElementButton_clicked()
{
    element_adder = new AddNewElement(this,container,cur_index);
    element_adder->show();
}
