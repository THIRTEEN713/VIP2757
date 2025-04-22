#include "HomeWidge.h"
#include "ui_HomeWidge.h"

#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

HomeWidge::HomeWidge(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeWidge)
{
    ui->setupUi(this);

    GuiInit();
}

HomeWidge::~HomeWidge()
{
    delete ui;
}

void HomeWidge::GuiInit()
{
    // 设置窗口为无标题栏窗口
    setWindowFlag(Qt::FramelessWindowHint);

    // 把窗口设置成透明背景
    setAttribute(Qt::WA_TranslucentBackground);

    // 为主窗口添加内部阴影
    QGraphicsDropShadowEffect *window = new QGraphicsDropShadowEffect(this);
    window->setBlurRadius(6);
    window->setOffset(0);
    window->setColor(QColor(0x00,0x00,0x00,255));
    setGraphicsEffect(window);
}

void HomeWidge::mousePressEvent(QMouseEvent *ev)
{
    // 判断鼠标是否按下的左键::计算一下y的值，0~30的范围才可以点击拖动
    if(ev->button() == Qt::LeftButton)
    {
        // 更改拖动状态为true
        isDrag = true;

        // 获取鼠标与窗口的坐标差值
        dVal = ev->globalPosition() - pos();
    }
}

void HomeWidge::mouseMoveEvent(QMouseEvent *ev)
{
    // 判断拖动状态是否为true
    if(isDrag)
        move((ev->globalPosition()-dVal).toPoint());
}

void HomeWidge::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
        isDrag = false;
}

void HomeWidge::on_Closebutton_clicked()
{
    close();
}


void HomeWidge::on_Minibutton_clicked()
{
    showMinimized();
}

