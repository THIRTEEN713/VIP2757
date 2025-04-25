#ifndef HOMEWIDGE_H
#define HOMEWIDGE_H

#include "NetWork.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class HomeWidge;
}
QT_END_NAMESPACE

class HomeWidge : public QWidget
{
    Q_OBJECT

public:
    HomeWidge(QWidget *parent = nullptr);
    ~HomeWidge();

protected:
    void GuiInit();
    void EventInit();

    void TestValue();

    // 重写鼠标的事件
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private slots:
    void on_Closebutton_clicked();
    void on_Minibutton_clicked();
    void on_CheckFiles_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_EnterUpload_clicked();
    void on_CancelUpload_clicked();

    void on_CheckAll_checkStateChanged(const Qt::CheckState &arg1);

    void on_RemoveAll_clicked();

    void on_RemoveFiles_clicked();

    void on_AppendFiles_clicked();

    void on_NewFolder_clicked();

protected slots:
    void changeCheckedItem(bool status,QWidget *item);

private:
    void on_change_stackedWidget(int index);

private:
    Ui::HomeWidge *ui;

    // 鼠标此时是否为拖动状态
    bool    isDrag;
    QPointF dVal;

    // 存储选中的item
    QMap<int,QWidget*> checkFileItems;

    // 网络类
    NetWork *nw;
};
#endif // HOMEWIDGE_H
