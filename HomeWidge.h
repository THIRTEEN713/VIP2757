#ifndef HOMEWIDGE_H
#define HOMEWIDGE_H

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

    // 重写鼠标的事件
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private slots:
    void on_Closebutton_clicked();
    void on_Minibutton_clicked();

private:
    Ui::HomeWidge *ui;

    // 鼠标此时是否为拖动状态
    bool    isDrag;
    QPointF dVal;
};
#endif // HOMEWIDGE_H
