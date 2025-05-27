#include "../include/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFileInfo>
#include <QPushButton>
#include <QDir>
#include <QMessageBox>

#include "WorkerThread.hpp"
#include "HuffmanEncoder.hpp"
#include "HuffmanDecoder.hpp"

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
    connect(ui->pushButton_compress, &QPushButton::clicked, this, &MainWindow::compressFile);
    connect(ui->pushButton_decompress, &QPushButton::clicked, this, &MainWindow::decompressFile);
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &MainWindow::clearPaths);
}

void MainWindow::getInputFile() {
    //文件对话框，默认路径为空
    QString inputFilePath = QFileDialog::getOpenFileName(
        this,
        "选择要压缩的文件",
        QDir::homePath(),
        "所有文件 (*.*);;文本文件 (*.txt)"
    );

    //获取文件大小
    if(!inputFilePath.isEmpty()) {
        ui->lineEdit_filePath->setText(inputFilePath);

        //获取文件大小
        QFileInfo fileInfo(inputFilePath);
        qint64 fileSize = fileInfo.size();
        QString sizeText = QString("%1 bytes").arg(fileSize);
        if (fileSize > 1024) {
            // 使用 QString::asprintf 格式化浮点数
            sizeText += QString::asprintf(" (%.2f KB)", fileSize / 1024.0);
        }
        ui->label_fileSizeValue->setText(sizeText);

        ui->textEdit_log->append(QString("已选择文件: %1").arg(inputFilePath));

        this->inputFilePath = inputFilePath;

        if (!this->outputPath.isEmpty()) {
            ui->pushButton_compress->setEnabled(true);
            ui->pushButton_decompress->setEnabled(true);
        }
    }
}

void MainWindow::getOutputPath() {
    // QString outputDirPath = QFileDialog::getExistingDirectory(
    //     this,
    //     "选择输出压缩文件目录",
    //     "./",
    //     QFileDialog::ShowDirsOnly
    //     );

    QString outputDirPath = QFileDialog::getOpenFileName(
        this,
        "选择要输出文件路径",
        QDir::homePath(),
        "所有文件 (*.*);;文本文件 (*.txt)"
    );

    ui->lineEdit_outputPath->setText(outputDirPath);

    ui->textEdit_log->append(QString("已选择输出路径: %1").arg(outputDirPath));

    this->outputPath = outputDirPath;

    if(!this->inputFilePath.isEmpty()) {
        ui->pushButton_compress->setEnabled(true);
        ui->pushButton_decompress->setEnabled(true);
    }
}

void MainWindow::compressFile() {
    if (this->inputFilePath.isEmpty()) {
        QMessageBox::critical(this, "Error", "请选择被压缩文件");
        return;
    }
    if (this->outputPath.isEmpty()) {
        QMessageBox::critical(this, "Error", "请选择文件输出路径");
        return;
    }
    auto* compressThread = new CompressThread(this->inputFilePath.toStdString(),
        this->outputPath.toStdString(), this);

    //先进行信号与槽连接再启动线程
    //lambda表达式
    connect(compressThread, &CompressThread::compressedFinished, this, [this]() {
        ui->textEdit_log->append(QString("文件压缩完成，输出至：%1").arg(this->outputPath));
    });

    connect(compressThread, &CompressThread::errorOccurred, this, [this](const QString& error) {
        QMessageBox::critical(this, "Error", error);
    });
    compressThread->start();
}

void MainWindow::decompressFile() {
    if (this->inputFilePath.isEmpty()) {
        QMessageBox::critical(this, "Error", "请选择要解压文件路径");
        return;
    }
    if (this->outputPath.isEmpty()) {
        QMessageBox::critical(this, "Error", "请选择文件输出路径");
        return;
    }
    auto* decompressThread = new DecompressThread(this->inputFilePath.toStdString(),
        this->outputPath.toStdString(), this);

    connect(decompressThread, &DecompressThread::decompressedFinished, this, [this]() {
        ui->textEdit_log->append(QString("文件解压完成，输出至：%1").arg(this->outputPath));
    });

    connect(decompressThread, &DecompressThread::errorOccurred, this, [this](const QString& error) {
        QMessageBox::critical(this, "Error", error);
    });
    decompressThread->start();
}

void MainWindow::clearPaths() {
    this->inputFilePath.clear();
    this->outputPath.clear();

    ui->lineEdit_filePath->clear();
    ui->lineEdit_outputPath->clear();

    ui->textEdit_log->append("路径已清空");
}