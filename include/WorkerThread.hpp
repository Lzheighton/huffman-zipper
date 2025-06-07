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
    explicit CompressThread(MainWindow* parent = nullptr,
        const std::string& inputFilePath = "",
        const std::string& outputPath = "") {
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
    void errorOccurred(const QString error);
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
    explicit DecompressThread(MainWindow* parent = nullptr,
        const std::string& inputFilePath = "",
        const std::string& outputPath = "") {
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
    void errorOccurred(const QString error);
    void decompressedFinished(bool success);

private:
    //通过构造函数向线程传入的文件输入输出路径
    std::string inputFilePath;
    std::string outputPath;

    //指向运行UI实例的指针
    MainWindow *mainWindowInstance;
};

class CheckSHA256Thread : public QThread {
    Q_OBJECT
public:
    explicit CheckSHA256Thread(MainWindow* parent = nullptr,
        const std::string& inputFilePath = "",
        const std::string& outputPath = "") {
        this->mainWindowInstance = parent;
        this->inputFilePath = inputFilePath;
        this->outputPath = outputPath;
    };

    void run() override {
        QMutexLocker locker(&mainWindowInstance->CheckSHA256Mutex);
        try {
            std::string fileA = sha256(this->inputFilePath);
            std::string fileB = sha256(this->outputPath);
            //线程内检查，成功则返回唯一SHA256值，校验失败返回两个SHA256值
            if (fileA == fileB) {
                emit checkSuccess(fileA);
            }else {
                emit checkFailed(fileA, fileB);
            }
        }catch (std::exception& e) {
            emit errorOccurred(QString(e.what()));
        }
    }

    signals:
    void errorOccurred(QString error);
    void checkFailed(std::string sha256A, std::string sha256B);
    void checkSuccess(std::string sha256);

private:
    //通过构造函数向线程传入的文件输入输出路径
    std::string inputFilePath;
    std::string outputPath;

    //指向运行UI实例的指针
    MainWindow *mainWindowInstance;
};

class AnalysisThread : public QThread {
    Q_OBJECT
public:
    explicit AnalysisThread(MainWindow* parent = nullptr, const std::string& inputFilePath = "") {
        this->mainWindowInstance = parent;
        this->inputFilePath = inputFilePath;
    };

    void run() override {
        QMutexLocker locker(&mainWindowInstance->AnalysisMutex);
        try {
            HuffmanDecoder decoder;
            uint64_t HuffmanTableSize = 0;
            HuffmanHeader header = decoder.analysisHeader(this->inputFilePath, HuffmanTableSize);
            if (header.magicNum[0] != 'Y' || header.magicNum[1] != 'G') {
                throw std::runtime_error("Invalid type of file");
            }
            emit analysisFinished(header.originalSize, header.compressedSize, HuffmanTableSize);
        }catch (std::exception& e) {
            emit errorOccurred(QString(e.what()));
        }
    }

    signals:
    void errorOccurred(QString error);
    //信号传出元数据两个参数，源文件大小与压缩后大小
    void analysisFinished(uint64_t srcFileSize, uint64_t hufFileSize, uint64_t huffmanTableSize);

private:
    //通过构造函数向线程传入的文件输入路径
    std::string inputFilePath;

    //指向运行UI实例的指针
    MainWindow *mainWindowInstance;
};

#endif //WORKERTHREAD_HPP
