#include "worker.h"
#include "utils.h"

void Worker::doWork(QString sourcePath, QString newPath, QString targetPath)
{
    QList<QString> r = getFullDirectory(newPath);
    for (int i = 0;i < r.length();++i)
    {
        QString newFilePath = QString(r.at(i));
        QString sourceFilePath = QString(r.at(i)).replace(newPath, sourcePath);

        QFile sourceFile(sourceFilePath);
        bool isNew = false;
        if (sourceFile.exists())
        {
            if (getHash(sourceFilePath) != getHash(newFilePath))
            {
                isNew = true;
            }
        }
        else
        {
            isNew = true;
        }
        if (isNew)
        {
            QString targetFilePath = QString(r.at(i)).replace(newPath, targetPath);
            QFileInfo fi = QFileInfo(targetFilePath);
            verifyOrCreateTargetDirectory(fi.absolutePath());
            QFile::copy(newFilePath, targetFilePath);
        }
        workProgress(i, r.length());
    }
    workFinished();
}
