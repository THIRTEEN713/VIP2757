#include "TitleBar.h"
#include "ui_TitleBar.h"

#include <QMouseEvent>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TitleBar)
{
    ui->setupUi(this);
}

TitleBar::~TitleBar()
{
    delete ui;
}

void TitleBar::mousePressEvent(QMouseEvent *ev)
{
    // 判断鼠标是否按下的左键::计算一下y的值，0~30的范围才可以点击拖动
    if(ev->button() == Qt::LeftButton)
    {
        // 更改拖动状态为true
        isDrag = true;

        QWidget *pptr = static_cast<QWidget*>(parent());
        // 获取鼠标与窗口的坐标差值
        if(!pptr)
            dVal = ev->globalPosition() - pos();
        else
            dVal = ev->globalPosition() - pptr->pos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *ev)
{
    // 判断拖动状态是否为true
    if(isDrag)
    {
        QWidget *pptr = static_cast<QWidget*>(parent());
        if(!pptr)
            move((ev->globalPosition()-dVal).toPoint());
        else
            pptr->move((ev->globalPosition()-dVal).toPoint());
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
        isDrag = false;
}

void TitleBar::on_pushButton_clicked()
{
    QWidget *pptr = static_cast<QWidget*>(parent());
    if(!pptr)close();
    else pptr->close();
}

