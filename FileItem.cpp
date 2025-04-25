#include "FileItem.h"
#include "ui_FileItem.h"

FileItem::FileItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileItem)
{
    ui->setupUi(this);
}

FileItem::~FileItem()
{
    delete ui;
}

void FileItem::setFileName(QString name)
{
    ui->FileName->setText(name);
}

void FileItem::setFileType(QString type)
{
    ui->FileType->setText(type);
}

void FileItem::setFileSize(int size)
{
    ui->FileSize->setText(QString::number(size));
}

void FileItem::setFilePath(QString path)
{
    ui->FilePath->setText(path);
    ui->FilePath->setToolTip("存储路径:"+path);
}

void FileItem::setItemIndex(int index)
{
    itemIndex = index;
}

QString FileItem::getFileName()
{
    return ui->FileName->text();
}

QString FileItem::getFileType()
{
    return ui->FileType->text();
}

int FileItem::getFileSize()
{
    return ui->FileSize->text().toInt();
}

QString FileItem::getFilePath()
{
    return ui->FilePath->text();
}

int FileItem::getItemIndex()
{
    return itemIndex;
}

void FileItem::setCheckStatus(Qt::CheckState status)
{
    ui->CheckStatus->setCheckState(status);
}

Qt::CheckState FileItem::getCheckStatus()
{
    return ui->CheckStatus->checkState();
}

void FileItem::on_CheckStatus_checkStateChanged(const Qt::CheckState &arg1)
{
    emit checkStatusChanged(ui->CheckStatus->isChecked(),this);
}

