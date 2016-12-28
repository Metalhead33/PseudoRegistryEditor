#include "AddNewElement.h"
#include "ui_AddNewElement.h"

AddNewElement::AddNewElement(QWidget *parent,ElementContainerItem* container, QModelIndex index) :
    QDialog(parent),
    ui(new Ui::AddNewElement)
{
    m_index = index;
    m_container = container;
    ui->setupUi(this);
}

AddNewElement::~AddNewElement()
{
    delete ui;
}

void AddNewElement::on_buttonBox_accepted()
{
    if(m_index.isValid() && ui->plainTextEdit->toPlainText().toStdString() != "" )
    {
        switch(ui->comboBox->currentIndex() )
        {
        case 0:
            m_container->AddDirectory(m_index,ui->plainTextEdit->toPlainText());
            break;
        case 1:
            m_container->AddFile(m_index,Structure::File::BOOL,ui->plainTextEdit->toPlainText());
            break;
        case 2:
            m_container->AddFile(m_index,Structure::File::UINT8,ui->plainTextEdit->toPlainText());
            break;
        case 3:
            m_container->AddFile(m_index,Structure::File::SINT8,ui->plainTextEdit->toPlainText());
            break;
        case 4:
            m_container->AddFile(m_index,Structure::File::UINT64,ui->plainTextEdit->toPlainText());
            break;
        case 5:
            m_container->AddFile(m_index,Structure::File::SINT64,ui->plainTextEdit->toPlainText());
            break;
        case 6:
            m_container->AddFile(m_index,Structure::File::FLOAT,ui->plainTextEdit->toPlainText());
            break;
        case 7:
            m_container->AddFile(m_index,Structure::File::STRING,ui->plainTextEdit->toPlainText());
            break;
        case 8:
            m_container->AddFile(m_index,Structure::File::STRING16,ui->plainTextEdit->toPlainText());
            break;
        case 9:
            m_container->AddFile(m_index,Structure::File::STRING32,ui->plainTextEdit->toPlainText());
            break;
        default:
            break;
        }
    }
    delete this;
}

void AddNewElement::on_buttonBox_rejected()
{
    delete this;
}

void AddNewElement::on_AddNewElement_accepted()
{
    on_buttonBox_accepted();
}

void AddNewElement::on_AddNewElement_rejected()
{
    on_buttonBox_rejected();
}
