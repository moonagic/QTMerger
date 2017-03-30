#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
public slots:
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

private:
    Ui::MainWindow *ui;
    /**
     * @brief workerThread
     */
    QThread workerThread;

signals:
    /**
     * @brief operate
     * @param sourcePath
     * @param newPath
     * @param targetPath
     */
    void operate(QString sourcePath, QString newPath, QString targetPath);
};

#endif // MAINWINDOW_H
