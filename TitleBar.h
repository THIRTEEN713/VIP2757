#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    // 重写鼠标的事件
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::TitleBar *ui;

    // 鼠标此时是否为拖动状态
    bool    isDrag;
    QPointF dVal;
};

#endif // TITLEBAR_H
