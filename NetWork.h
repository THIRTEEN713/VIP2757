#ifndef NETWORK
#define NETWORK

#include <QTcpSocket>

class NetWork : QTcpSocket
{
    Q_OBJECT
public:
    typedef enum{
        CREATE,
        DELETE
    }CMD;

    NetWork(QObject *object);
    ~NetWork();

    // 文件的上传
    bool FileUpload(QString filePath);

    // 文件的下载
    bool FileDownload(QString fileName,QString filePath);

    // 远程节点的文件列表的获取
    QStringList FileList();

    // 指令操作
    bool Command(NetWork::CMD cmd,QString name);
};

#endif // NETWORK
