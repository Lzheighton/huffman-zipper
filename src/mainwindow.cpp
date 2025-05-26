#include "../include/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFileInfo>
#include <QPushButton>
#include <QDir>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui -> setupUi(this);
    connectSignals();

    //初始化界面，禁用进度条，写入启动日志
    ui->progressBar -> setVisible(false);
    ui->textEdit_log->append("程序启动完毕，请选择被解压文件");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connectSignals() {
    connect(ui->pushButton_browse, &QPushButton::clicked, this, &MainWindow::getInputFile);
    connect(ui->pushButton_selectOutput, &QPushButton::clicked, this, &MainWindow::getOutputPath);
}

void MainWindow::getInputFile() {
    //文件对话框，默认路径为空
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "选择要压缩的文件",
        QDir::homePath(),
        "所有文件 (*.*);;文本文件 (*.txt)"
    );

    //获取文件大小
    if(!fileName.isEmpty()) {
        ui->lineEdit_filePath->setText(fileName);

        //显示文件大小
        QFileInfo fileInfo(fileName);
        qint64 fileSize = fileInfo.size();
        QString sizeText = QString("%1 bytes").arg(fileSize);
        if (fileSize > 1024) {
            sizeText += QString(" (%.2f KB)").arg(fileSize / 1024.0);
        }
        ui->label_fileSizeValue->setText(sizeText);

        ui->textEdit_log->append(QString("已选择文件: %1").arg(fileName));
    }
}

void MainWindow::getOutputPath() {
    QString outputDirPath = QFileDialog::getExistingDirectory(
        this,
        "选择输出压缩文件目录",
        "./",
        QFileDialog::ShowDirsOnly
        );

    ui->lineEdit_outputPath->setText(outputDirPath);
    ui->textEdit_log->append(outputDirPath);

    ui->textEdit_log->append(QString("已选择输出路径: %1").arg(outputDirPath));
}