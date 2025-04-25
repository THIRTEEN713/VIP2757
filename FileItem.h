#ifndef FILEITEM_H
#define FILEITEM_H

#include <QWidget>

namespace Ui {
class FileItem;
}

class FileItem : public QWidget
{
    Q_OBJECT

public:
    explicit FileItem(QWidget *parent = nullptr);
    ~FileItem();
    void setFileName(QString name);
    void setFileType(QString type);
    void setFileSize(int size);
    void setFilePath(QString path);
    void setItemIndex(int index);

    QString getFileName();
    QString getFileType();
    int getFileSize();
    QString getFilePath();
    int getItemIndex();

    void setCheckStatus(Qt::CheckState);
    Qt::CheckState getCheckStatus();
signals:
    void checkStatusChanged(bool,QWidget*);
private slots:
    void on_CheckStatus_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::FileItem *ui;
    int itemIndex;
};

#endif // FILEITEM_H
