#ifndef ZIPPERWIDGET_HPP
#define ZIPPERWIDGET_HPP

#include "../ui/ui_mainwindow.h"
#include "HuffmanEncoder.hpp"

QT_BEGIN_NAMESPACE
//namespace 中的窗口UI类，独立于派生得到的同名类
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void getInputFile();
    void getOutputPath();
    void compressFile();
    void decompressFile();
    void clearPaths();

private:
    Ui::MainWindow *ui;
    //连接UI信号与槽函数
    void connectSignals();

    //类内通用文件路径
    QString inputFilePath;
    QString outputPath;
};


#endif //ZIPPERWIDGET_HPP