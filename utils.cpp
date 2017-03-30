#include "utils.h"
#include <QtOpenGL/QGL>

bool verifyOrCreateTargetDirectory(QString targetDirectory)
{
    QDir *qDir = new QDir();
    if (qDir->exists(targetDirectory))
    {
        return true;
    }
    else
    {
        return qDir->mkpath(targetDirectory);
    }
}

const QString getHash(const QString& filePath)
{
    QString sMd5;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray bArray = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5);
        sMd5 = QString(bArray.toHex()).toUpper();
    }
    file.close();
    return sMd5;
}

QList<QString> getFullDirectory(QString target)
{
    QList<QString> result;
    QDir *dir=new QDir(target);
    QStringList filter;
    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    for (int i = 0;i < fileInfo->length();++i)
    {
        if (fileInfo->at(i).absoluteFilePath().length() <= target.length())
        {
            continue;
        }
        if (fileInfo->at(i).isDir())
        {
            result.append(getFullDirectory(fileInfo->at(i).absoluteFilePath()));
        }
        else if (fileInfo->at(i).isFile())
        {
            result.append(fileInfo->at(i).absoluteFilePath());
        }
    }
    return result;
}
