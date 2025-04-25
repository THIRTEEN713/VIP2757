#include "TaskItem.h"
#include "ui_TaskItem.h"

TaskItem::TaskItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskItem)
{
    ui->setupUi(this);
}

TaskItem::~TaskItem()
{
    delete ui;
}

void TaskItem::setFileName(QString name)
{
    ui->FileName->setText(name);
}

void TaskItem::setNodeName(QString name)
{
    ui->NodeName->setText(name);
}

void TaskItem::setTaskType(QString type)
{
    ui->TaskType->setText(type);
}

void TaskItem::setTaskValue(int value)
{
    ui->Value->clear();
    ui->Value->setText(QString::number(value)+"%");
}

QString TaskItem::getFileName()
{
    return ui->FileName->text();
}

QString TaskItem::getNodeName()
{
    return ui->NodeName->text();
}

QString TaskItem::getTaskType()
{
    return ui->TaskType->text();
}

int TaskItem::getTaskValue()
{
    return ui->Value->text().toInt();
}
