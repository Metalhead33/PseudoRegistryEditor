#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    addElement(Structure::ROOT_DIRECTORY);
    ui->setupUi(this);
    for(IndexIterator it=elements.begin();it != elements.end(); ++it)
    {
        if(it->first) it->first->setText(0,QString(it->second->GetName().c_str()));
    }
    ui->treeWidget->addTopLevelItem(LookupIndex(Structure::ROOT_DIRECTORY));
    cur_item = LookupIndex(Structure::ROOT_DIRECTORY);
    ui->plainTextEdit->hide();
    ui->buttonAcceptChanges->hide();
    ui->revertButton->hide();
    ui->comboBox->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem* MainWindow::LookupIndex(Structure::Element* elem)
{
    for(IndexIterator it=elements.begin();it != elements.end(); ++it)
    {
        if(it->second == elem) return it->first;
    }
    return 0;
}

void MainWindow::addElement(Structure::Element* elem)
{
    IndexPair temp_pair;
    if(elem->GetParent())
    {
        QTreeWidgetItem* parent = LookupIndex(elem->GetParent());
        if(parent) elements.insert(IndexPair(new QTreeWidgetItem(parent,50),elem));
        else temp_pair = IndexPair(new QTreeWidgetItem(50),elem);
    }
    else temp_pair = IndexPair(new QTreeWidgetItem(50),elem);
    //if(elem) temp_pair.first->setText(1,QString(elem->GetName().c_str()  )  );
    elements.insert(temp_pair);
    if(elem->IsDirectory())
    {
        if(((Structure::Directory*)elem)->GetNumChildren()) {
        Structure::ElementContainer* temp_dir = ((Structure::Directory*)elem)->GetContainer();
        for(Structure::ElementIterator it = temp_dir->begin(); it != temp_dir->end();++it) addElement(*it); }
    }
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    cur_item = item;
    UpdateDisplayer();
}

void MainWindow::UpdateDisplayer()
{
    Structure::Element* elem = elements.find(cur_item)->second;
    if(!elem) return;
    if(elem->IsData())
    {
        ui->plainTextEdit->show();
        ui->buttonAcceptChanges->show();
        ui->revertButton->show();
        ui->comboBox->hide();
        Structure::File* fail = (Structure::File*)elem;
        switch(fail->GetFiletype())
        {
        case Structure::File::BOOL:
        {
            ui->plainTextEdit->hide();
            ui->comboBox->show();
            if( ((Structure::BooleanFile*)fail)->GetContent()  ) ui->comboBox->setCurrentIndex(1);
            else ui->comboBox->setCurrentIndex(2);
            break;
        }
        case Structure::File::STRING:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),120);
            ui->plainTextEdit->setPlainText(QString::fromStdString(((Structure::StringFile*)fail)->GetContent())   );
            break;
        }
        case Structure::File::STRING16:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),120);
            ui->plainTextEdit->setPlainText(QString::fromStdU16String(((Structure::String16File*)fail)->GetContent())  );
            break;
        }
        case Structure::File::STRING32:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),120);
            ui->plainTextEdit->setPlainText(QString::fromStdU32String(((Structure::String32File*)fail)->GetContent())  );
            break;
        }
        case Structure::File::UINT8:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),32);
            std::stringstream convert;
            convert << ((Structure::Uint8File*)fail)->GetContent();
            ui->plainTextEdit->setPlainText((QString)convert.str().c_str()  );
            break;
        }
        case Structure::File::SINT8:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),32);
            std::stringstream convert;
            convert << ((Structure::Int8File*)fail)->GetContent();
            ui->plainTextEdit->setPlainText((QString)convert.str().c_str()  );
            break;
        }
        case Structure::File::UINT64:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),32);
            std::stringstream convert;
            convert << ((Structure::Uint64File*)fail)->GetContent();
            ui->plainTextEdit->setPlainText((QString)convert.str().c_str()  );
            break;
        }
        case Structure::File::SINT64:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),32);
            std::stringstream convert;
            convert << ((Structure::Int64File*)fail)->GetContent();
            ui->plainTextEdit->setPlainText((QString)convert.str().c_str()  );
            break;
        }
        case Structure::File::FLOAT:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),32);
            std::stringstream convert;
            convert << ((Structure::FloatFile*)fail)->GetContent();
            ui->plainTextEdit->setPlainText((QString)convert.str().c_str()  );
            break;
        }
        default:
        {
            ui->plainTextEdit->clear();
            break;
        }
        }
    }
    else
    {
        if(elem->IsDirectory())
        {
            ui->plainTextEdit->show();
            ui->buttonAcceptChanges->show();
            ui->revertButton->show();
            ui->comboBox->hide();
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),32);
            ui->plainTextEdit->setPlainText(QString::fromStdString(((Structure::Directory*)elem)->GetName())   );
        }
        else {
        ui->plainTextEdit->hide();
        ui->buttonAcceptChanges->hide();
        ui->revertButton->hide();
        ui->comboBox->hide();
        }
    }
}

void MainWindow::on_buttonAcceptChanges_clicked()
{
    Structure::Element* elem = elements.find(cur_item)->second;
    if(!elem) throw -1;
    if(elem->IsData())
    {
        Structure::File* fail = (Structure::File*)elem;
        switch(fail->GetFiletype())
        {
        case Structure::File::BOOL:
        {
            break;
        }
        case Structure::File::STRING:
        {
            ((Structure::StringFile*)fail)->SetContent(ui->plainTextEdit->toPlainText().toStdString());
            break;
        }
        case Structure::File::STRING16:
        {
            ((Structure::String16File*)fail)->SetContent(ui->plainTextEdit->toPlainText().toStdU16String());
            break;
        }
        case Structure::File::STRING32:
        {
            ((Structure::String32File*)fail)->SetContent(ui->plainTextEdit->toPlainText().toStdU32String());
            break;
        }
        case Structure::File::UINT8:
        {
            try {
            ((Structure::Uint8File*)fail)->SetContent((uint8_t)std::stoi(ui->plainTextEdit->toPlainText().toStdString())); }
            catch(std::exception e)
            {
                ;
            }
            break;
        }
        case Structure::File::SINT8:
        {
            try {
            ((Structure::Int8File*)fail)->SetContent((int8_t)std::stoi(ui->plainTextEdit->toPlainText().toStdString()));
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
            ((Structure::Uint64File*)fail)->SetContent((uint64_t)std::stoi(ui->plainTextEdit->toPlainText().toStdString()));
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
            ((Structure::Int64File*)fail)->SetContent((int64_t)std::stoi(ui->plainTextEdit->toPlainText().toStdString()));
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
            ((Structure::FloatFile*)fail)->SetContent(std::stod(ui->plainTextEdit->toPlainText().toStdString()));
            }
            catch(std::exception e)
            {
                ;
            }
            break;
        }
        default:
        {
            ui->plainTextEdit->clear();
            break;
        }
        }
    }
    else
    {
        if(elem->IsDirectory())
        {
            elem->SetName(ui->plainTextEdit->toPlainText().toStdString());
            cur_item->setText(0,ui->plainTextEdit->toPlainText());
        }
    }
    UpdateDisplayer();
}

void MainWindow::on_revertButton_clicked()
{
    UpdateDisplayer();
}

void MainWindow::on_DeleteButton_clicked()
{
    DeleteElement(cur_item);
}

void MainWindow::DeleteElement(QTreeWidgetItem *item)
{
    if(item) {
    QList<QTreeWidgetItem *> children = item->takeChildren();
    if(!children.isEmpty())
    {
        while(!children.isEmpty()) DeleteElement(children.takeFirst());
    }
    if(item->parent() )
    {
        cur_item = item->parent();
        item->parent()->removeChild(item);
    }
    else cur_item = 0;
    delete (elements.find(item)->second);
    elements.erase(elements.find(item));
    delete item; }
    /*if(!item) return;
    Structure::Element* elem = (elements.find(item))->second;
    if(item->parent() ) {
    cur_item = item->parent();
    UpdateDisplayer();
    item->parent()->removeChild(item);}
    else cur_item = 0;
    if(elem)
    {
        if(elem->IsDirectory())
        {
            if(((Structure::Directory*)elem)->GetNumChildren()) {
            QList<QTreeWidgetItem *> children = item->takeChildren();
            while(!children.isEmpty())
            {
                DeleteElement(children.front());
            }
            }
        }
        //elem->SetParent(0);
        delete elem;
    }
    elements.erase(elements.find(item));
    delete item;*/
}
