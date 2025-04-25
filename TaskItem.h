#ifndef TASKITEM_H
#define TASKITEM_H

#include <QWidget>

namespace Ui {
class TaskItem;
}

class TaskItem : public QWidget
{
    Q_OBJECT

public:
    explicit TaskItem(QWidget *parent = nullptr);
    ~TaskItem();

    void setFileName(QString name);
    void setNodeName(QString name);
    void setTaskType(QString Type);
    void setTaskValue(int value);

    QString getFileName();
    QString getNodeName();
    QString getTaskType();
    int getTaskValue();

private:
    Ui::TaskItem *ui;
};

#endif // TASKITEM_H
