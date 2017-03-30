#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);

signals:
    void workFinished();
    void workProgress(qint64 bytesRead, qint64 totalBytes);

public slots:
    void doWork(QString sourcePath, QString newPath, QString targetPath);

};

#endif // WORKER_H
