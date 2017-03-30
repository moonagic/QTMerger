#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(800, 300);
    setWindowTitle("增量对比生成工具");
}

MainWindow::~MainWindow()
{
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
    }
}
