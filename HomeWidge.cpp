#include "FileItem.h"
#include "HomeWidge.h"
#include "TaskItem.h"
#include "ui_HomeWidge.h"

#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QLineEdit>
#include <QMouseEvent>

HomeWidge::HomeWidge(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeWidge)
{
    ui->setupUi(this);
    nw = new NetWork(this);

    GuiInit();
    EventInit();
    on_change_stackedWidget(0);

    TestValue();
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

void HomeWidge::EventInit()
{
    connect(ui->Upload,&QPushButton::clicked,this,[=]{on_change_stackedWidget(0);});
    connect(ui->Download,&QPushButton::clicked,this,[=]{on_change_stackedWidget(1);});
    connect(ui->Tasklist,&QPushButton::clicked,this,[=]{on_change_stackedWidget(2);});
    connect(ui->Nodelist,&QPushButton::clicked,this,[=]{on_change_stackedWidget(3);});
}

void HomeWidge::TestValue()
{
    QListWidgetItem *item = new QListWidgetItem(ui->DownloadingList);
    TaskItem *taskItem = new TaskItem(ui->DownloadingList);
    item->setSizeHint(taskItem->size());

    taskItem->setFileName("1.txt");
    taskItem->setNodeName("本地节点1");
    taskItem->setTaskType("上传");
    taskItem->setTaskValue(50);


    ui->DownloadingList->addItem(item);
    ui->DownloadingList->setItemWidget(item,taskItem);
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

void HomeWidge::on_change_stackedWidget(int index)
{
    static int oldIndex = 0;// 静态变量，随程序持续的。所有的对象共享同一个静态变量

    ui->FunctionList->setCurrentIndex(index);
    switch(index)
    {
    case 0:
        ui->Upload->setStyleSheet(ui->Upload->styleSheet()+"#Upload:active{background-color: rgb(10, 55, 103);}");
        break;
    case 1:
        ui->Download->setStyleSheet(ui->Download->styleSheet()+"#Download:active{background-color: rgb(10, 55, 103);}");
        break;
    case 2:
        ui->Tasklist->setStyleSheet(ui->Tasklist->styleSheet()+"#Tasklist:active{background-color: rgb(10, 55, 103);}");
        break;
    case 3:
        ui->Nodelist->setStyleSheet(ui->Nodelist->styleSheet()+"#Nodelist:active{background-color: rgb(10, 55, 103);}");
        break;
    }
    if(oldIndex == index)return;
    switch(oldIndex)
    {
    case 0:
        ui->Upload->setStyleSheet(ui->Upload->styleSheet().remove("#Upload:active{background-color: rgb(10, 55, 103);}"));
        break;
    case 1:
        ui->Download->setStyleSheet(ui->Download->styleSheet().remove("#Download:active{background-color: rgb(10, 55, 103);}"));
        break;
    case 2:
        ui->Tasklist->setStyleSheet(ui->Tasklist->styleSheet().remove("#Tasklist:active{background-color: rgb(10, 55, 103);}"));
        break;
    case 3:
        ui->Nodelist->setStyleSheet(ui->Nodelist->styleSheet().remove("#Nodelist:active{background-color: rgb(10, 55, 103);}"));
        break;
    }
    oldIndex = index;
}

void HomeWidge::on_CheckFiles_clicked()
{
    ui->FilesTree->clear();
    QStringList fileList = QFileDialog::getOpenFileNames();
    for(QString file : fileList)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->FilesTree);
        FileItem *fileItem = new FileItem(ui->FilesTree);
        item->setSizeHint(fileItem->size());

        QFileInfo fileInfor(file);
        fileItem->setFileName(fileInfor.fileName());
        fileItem->setFileSize(fileInfor.size());
        fileItem->setFilePath(fileInfor.filePath());
        // fileItem->setFileType(fileInfor.file)
        fileItem->setItemIndex(ui->FilesTree->row(item));

        connect(fileItem,&FileItem::checkStatusChanged,this,&HomeWidge::changeCheckedItem);

        ui->FilesTree->addItem(item);
        ui->FilesTree->setItemWidget(item,fileItem);
    }
    ui->CheckStackedWidget->setCurrentIndex(1);
}

void HomeWidge::on_comboBox_currentIndexChanged(int index)
{
    ui->RemoteStacked->setCurrentIndex(1);


    ui->RemoteName->setText(ui->comboBox->currentText());
}

void HomeWidge::on_EnterUpload_clicked()
{
    // 实现上传备份操作
    // 遍历文件树，逐个的上传文件


    ui->FilesTree->clear();
    ui->CheckStackedWidget->setCurrentIndex(0);
}

void HomeWidge::on_CancelUpload_clicked()
{
    ui->FilesTree->clear();
    ui->CheckStackedWidget->setCurrentIndex(0);
}

void HomeWidge::changeCheckedItem(bool status, QWidget *item)
{
    // 被选中了
    if(status)
        checkFileItems[static_cast<FileItem*>(item)->getItemIndex()]=item;
    else
        checkFileItems.remove(static_cast<FileItem*>(item)->getItemIndex());
}


void HomeWidge::on_CheckAll_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == Qt::Checked)
    {
        // 将所有的Item都设置为选中状态
        for(int index = 0;index < ui->FilesTree->count();index++)
        {
            QListWidgetItem * item = ui->FilesTree->item(index);
            FileItem *fileItem = static_cast<FileItem*>(ui->FilesTree->itemWidget(item));
            if(!fileItem)continue;
            fileItem->setCheckStatus(Qt::Checked);

            checkFileItems[index] = fileItem;
        }
        ui->CheckAll->setText("取消全选");
    }
    else // 如果是取消选择状态，说明是取消全选
    {
        // 将所有的Item都设置为非选中状态
        for(int index = 0;index < ui->FilesTree->count();index++)
        {
            QListWidgetItem * item = ui->FilesTree->item(index);
            FileItem *fileItem = static_cast<FileItem*>(ui->FilesTree->itemWidget(item));
            if(!fileItem)continue;
            fileItem->setCheckStatus(Qt::Unchecked);
            checkFileItems.remove(index);
        }
        ui->CheckAll->setText("选择全部");
    }
}


void HomeWidge::on_RemoveAll_clicked()
{
    ui->FilesTree->clear();
}


void HomeWidge::on_RemoveFiles_clicked()
{
    for(int index : checkFileItems.keys())
    {
        ui->FilesTree->removeItemWidget(ui->FilesTree->item(index));
        ui->FilesTree->takeItem(index);
        if(!checkFileItems[index])continue;
        delete checkFileItems[index];
    }
    checkFileItems.clear();
}


void HomeWidge::on_AppendFiles_clicked()
{
    QStringList fileList = QFileDialog::getOpenFileNames();
    for(QString file : fileList)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->FilesTree);
        FileItem *fileItem = new FileItem(ui->FilesTree);
        item->setSizeHint(fileItem->size());

        QFileInfo fileInfor(file);
        fileItem->setFileName(fileInfor.fileName());
        fileItem->setFileSize(fileInfor.size());
        fileItem->setFilePath(fileInfor.filePath());
        // fileItem->setFileType(fileInfor.file)
        fileItem->setItemIndex(ui->FilesTree->row(item));

        connect(fileItem,&FileItem::checkStatusChanged,this,&HomeWidge::changeCheckedItem);

        ui->FilesTree->addItem(item);
        ui->FilesTree->setItemWidget(item,fileItem);
    }
}


void HomeWidge::on_NewFolder_clicked()
{
    QDialog *log = new QDialog(this);
    QLineEdit *edit = new QLineEdit(log);
    QVBoxLayout *layout = new QVBoxLayout(log);
    QPushButton *enter = new QPushButton(log);
    log->setLayout(layout);
    layout->addWidget(edit);
    layout->addWidget(enter);

    connect(enter,&QPushButton::clicked,this,[=]{log->setVisible(false);  nw->Command(NetWork::CREATE,edit->text());log->close();});
    log->exec();
}

