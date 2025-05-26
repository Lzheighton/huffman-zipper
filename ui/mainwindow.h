#ifndef ZIPPERWIDGET_HPP
#define ZIPPERWIDGET_HPP

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
//namespace 中的窗口UI类，独立于派生得到的同名类
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};


#endif //ZIPPERWIDGET_HPP