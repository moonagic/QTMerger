#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QFileDialog>
#include "worker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(800, 300);
    setWindowTitle("增量对比生成工具");


    Worker *w = new Worker;
    w->moveToThread(&workerThread);
    connect(this, &MainWindow::operate, w, &Worker::doWork);
    connect(w, &Worker::workFinished, this, &MainWindow::workFinished);
    connect(w, &Worker::workProgress, this, &MainWindow::workProgress);
    workerThread.start();


    ui->label_5->hide();
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(dir);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory();
    ui->lineEdit_2->setText(dir);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString dir = QFileDialog::getExistingDirectory();
    ui->lineEdit_3->setText(dir);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString sourcePath = ui->lineEdit->text();
    QString newPath = ui->lineEdit_2->text();
    QString targetPath = ui->lineEdit_3->text();

    operate(sourcePath, newPath, targetPath);

    // 静默
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->label_5->hide();

}

void MainWindow::workProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

void MainWindow::workFinished()
{
    ui->label_5->show();

    // 恢复操作
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);

    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(1);
}
