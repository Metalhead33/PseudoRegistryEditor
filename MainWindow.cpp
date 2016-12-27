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
    Structure::Element* elem = elements.find(item)->second;
    if(!elem) throw -1;
    if(elem->IsData())
    {
        Structure::File* fail = (Structure::File*)elem;
        switch(fail->GetFiletype())
        {
        case Structure::File::BOOL:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),32);
            if( ((Structure::BooleanFile*)fail)->GetContent()  ) ui->plainTextEdit->setPlainText(QString("true"));
            else ui->plainTextEdit->setPlainText(QString("false"));
            break;
        }
        case Structure::File::STRING:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),120);
            ui->plainTextEdit->setPlainText(QString::fromStdString(((Structure::StringFile*)fail)->c_str())   );
            break;
        }
        case Structure::File::STRING16:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),120);
            ui->plainTextEdit->setPlainText(QString::fromStdU16String(((Structure::String16File*)fail)->c_str())  );
            break;
        }
        case Structure::File::STRING32:
        {
            ui->plainTextEdit->resize(ui->plainTextEdit->width(),120);
            ui->plainTextEdit->setPlainText(QString::fromStdU32String(((Structure::String32File*)fail)->c_str())  );
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
}
