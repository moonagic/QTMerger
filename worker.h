#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT

signals:
    /**
     * @brief workFinished
     */
    void workFinished();
    /**
     * @brief workProgress
     * @param bytesRead
     * @param totalBytes
     */
    void workProgress(qint64 bytesRead, qint64 totalBytes);

public slots:
    /**
     * @brief doWork
     * @param sourcePath
     * @param newPath
     * @param targetPath
     */
    void doWork(QString sourcePath, QString newPath, QString targetPath);

};

#endif // WORKER_H
