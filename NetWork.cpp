#include "NetWork.h"

NetWork::NetWork(QObject *object)
    : QTcpSocket(object)
{

}

NetWork::~NetWork()
{

}

bool NetWork::FileUpload(QString filePath)
{
    return true;
}

bool NetWork::FileDownload(QString fileName, QString filePath)
{
    return true;
}

QStringList NetWork::FileList()
{
    return QStringList();
}

bool NetWork::Command(CMD cmd, QString name)
{
    return true;
}
