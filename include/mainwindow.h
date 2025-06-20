#ifndef ZIPPERWIDGET_HPP
#define ZIPPERWIDGET_HPP

#include "../ui/ui_mainwindow.h"
#include "HuffmanEncoder.hpp"
#include <QMutex>
#include <QtSvgWidgets/QSvgWidget>

QT_BEGIN_NAMESPACE
//namespace 中的窗口UI类，独立于派生得到的同名类
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    //工作线程类，通过友类共享线程访问权
    friend class CompressThread;
    friend class DecompressThread;
    friend class CheckSHA256Thread;
    friend class AnalysisThread;

private slots:
    void getInputFile();
    void getOutputPath();
    void getCheckFile();
    void compressFile();
    void decompressFile();
    void clearPaths();
    void checkSHA256();

private:
    Ui::MainWindow *ui;
    //连接UI信号与槽
    void connectSignals();

    //工作线程，压缩，解压，校验线程
    QMutex CompressMutex;
    QMutex DecompressMutex;
    QMutex CheckSHA256Mutex;

    //文件元数据校验线程
    QMutex AnalysisMutex;

    //类内共享文件路径
    QString inputFilePath;
    QString outputPath;
};


#endif //ZIPPERWIDGET_HPP