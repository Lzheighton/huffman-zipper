#pragma once
#ifndef WORKERTHREAD_HPP
#define WORKERTHREAD_HPP
#include <QThread>

#include "HuffmanDecoder.hpp"
#include "mainwindow.h"

class CompressThread : public QThread {
    Q_OBJECT
public:
    //构造一个QThread来管理一个新线程， parent拥有QThread的所有权
    explicit CompressThread(const std::string& inputFilePath,
        const std::string& outputPath,
        MainWindow* parent = nullptr) {
        this->mainWindowInstance = parent;
        this->inputFilePath = inputFilePath;
        this->outputPath = outputPath;
    };

    void run() override {
        //线程互斥锁，线程安全改进，防止在线程中运行的函数受到影响
        QMutexLocker locker(&mainWindowInstance->CompressMutex);
        try {
            HuffmanEncoder encoder;
            encoder.encode(inputFilePath, outputPath);
            emit compressedFinished();
        }catch (std::exception& e) {
            emit errorOccurred(QString(e.what()));
        }
    }

    //两种信号，出现错误或是压缩操作完成
    signals:
    void errorOccurred(const QString& error);
    void compressedFinished();

private:
    //通过构造函数向线程传入的文件输入输出路径
    std::string inputFilePath;
    std::string outputPath;

    //指向运行UI实例的指针
    MainWindow *mainWindowInstance;
};

class DecompressThread : public QThread {
    Q_OBJECT
public:
    explicit DecompressThread(const std::string& inputFilePath,
        const std::string& outputPath,
        MainWindow* parent = nullptr) {
        this->mainWindowInstance = parent;
        this->inputFilePath = inputFilePath;
        this->outputPath = outputPath;
    };

    void run() override {
        QMutexLocker locker(&mainWindowInstance->CompressMutex);
        try {
            HuffmanDecoder decoder;
            decoder.decode(inputFilePath, outputPath);
            emit decompressedFinished(true);
        }catch (std::exception& e) {
            emit errorOccurred(QString(e.what()));
        }
    }

    signals:
    void errorOccurred(const QString& error);
    void decompressedFinished(bool success);

private:
    //通过构造函数向线程传入的文件输入输出路径
    std::string inputFilePath;
    std::string outputPath;

    //指向运行UI实例的指针
    MainWindow *mainWindowInstance;
};

#endif //WORKERTHREAD_HPP
