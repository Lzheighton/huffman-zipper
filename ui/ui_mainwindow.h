/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtSvgWidgets/QSvgWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open;
    QAction *action_recent;
    QAction *action_exit;
    QAction *action_about;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_main;
    QGroupBox *groupBox_fileInfo;
    QVBoxLayout *verticalLayout_fileInfo;
    QHBoxLayout *horizontalLayout_filePath;
    QLabel *label_filePath;
    QLineEdit *lineEdit_filePath;
    QPushButton *pushButton_browse;
    QSvgWidget *widget_compressLoading;
    QHBoxLayout *horizontalLayout_fileSize;
    QLabel *label_fileSize;
    QLabel *label_fileSizeValue;
    QSpacerItem *horizontalSpacer_fileSize;
    QHBoxLayout *horizontalLayout_outputPath;
    QLabel *label_outputPath;
    QLineEdit *lineEdit_outputPath;
    QPushButton *pushButton_selectOutput;
    QSvgWidget *widget_decompressLoading;
    QHBoxLayout *horizontalLayout_buttons;
    QSpacerItem *horizontalSpacer_left;
    QPushButton *pushButton_decompress;
    QPushButton *pushButton_compress;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_sha256check;
    QSpacerItem *horizontalSpacer_right;
    QGroupBox *groupBox_progress;
    QVBoxLayout *verticalLayout_progress;
    QTextEdit *textEdit_log;
    QMenuBar *menubar;
    QMenu *menu_file;
    QMenu *menu_about;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 440);
        MainWindow->setMinimumSize(QSize(800, 440));
        MainWindow->setMaximumSize(QSize(800, 440));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/app.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        action_open = new QAction(MainWindow);
        action_open->setObjectName("action_open");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/open.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_open->setIcon(icon1);
        action_recent = new QAction(MainWindow);
        action_recent->setObjectName("action_recent");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/recent.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_recent->setIcon(icon2);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName("action_exit");
        action_about = new QAction(MainWindow);
        action_about->setObjectName("action_about");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_main = new QVBoxLayout(centralwidget);
        verticalLayout_main->setSpacing(10);
        verticalLayout_main->setObjectName("verticalLayout_main");
        verticalLayout_main->setContentsMargins(15, 15, 15, 15);
        groupBox_fileInfo = new QGroupBox(centralwidget);
        groupBox_fileInfo->setObjectName("groupBox_fileInfo");
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        groupBox_fileInfo->setFont(font);
        verticalLayout_fileInfo = new QVBoxLayout(groupBox_fileInfo);
        verticalLayout_fileInfo->setSpacing(8);
        verticalLayout_fileInfo->setObjectName("verticalLayout_fileInfo");
        horizontalLayout_filePath = new QHBoxLayout();
        horizontalLayout_filePath->setObjectName("horizontalLayout_filePath");
        label_filePath = new QLabel(groupBox_fileInfo);
        label_filePath->setObjectName("label_filePath");
        label_filePath->setMinimumSize(QSize(70, 0));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        label_filePath->setFont(font1);

        horizontalLayout_filePath->addWidget(label_filePath);

        lineEdit_filePath = new QLineEdit(groupBox_fileInfo);
        lineEdit_filePath->setObjectName("lineEdit_filePath");
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(true);
        lineEdit_filePath->setFont(font2);
        lineEdit_filePath->setReadOnly(true);

        horizontalLayout_filePath->addWidget(lineEdit_filePath);

        pushButton_browse = new QPushButton(groupBox_fileInfo);
        pushButton_browse->setObjectName("pushButton_browse");
        pushButton_browse->setMinimumSize(QSize(80, 30));
        pushButton_browse->setMaximumSize(QSize(80, 30));

        horizontalLayout_filePath->addWidget(pushButton_browse);

        widget_compressLoading = new QSvgWidget(groupBox_fileInfo);
        widget_compressLoading->setObjectName("widget_compressLoading");
        widget_compressLoading->setMinimumSize(QSize(40, 40));
        widget_compressLoading->setMaximumSize(QSize(40, 40));

        horizontalLayout_filePath->addWidget(widget_compressLoading);


        verticalLayout_fileInfo->addLayout(horizontalLayout_filePath);

        horizontalLayout_fileSize = new QHBoxLayout();
        horizontalLayout_fileSize->setObjectName("horizontalLayout_fileSize");
        label_fileSize = new QLabel(groupBox_fileInfo);
        label_fileSize->setObjectName("label_fileSize");
        label_fileSize->setMinimumSize(QSize(70, 0));
        label_fileSize->setFont(font2);

        horizontalLayout_fileSize->addWidget(label_fileSize);

        label_fileSizeValue = new QLabel(groupBox_fileInfo);
        label_fileSizeValue->setObjectName("label_fileSizeValue");
        label_fileSizeValue->setFont(font2);

        horizontalLayout_fileSize->addWidget(label_fileSizeValue);

        horizontalSpacer_fileSize = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_fileSize->addItem(horizontalSpacer_fileSize);


        verticalLayout_fileInfo->addLayout(horizontalLayout_fileSize);

        horizontalLayout_outputPath = new QHBoxLayout();
        horizontalLayout_outputPath->setObjectName("horizontalLayout_outputPath");
        label_outputPath = new QLabel(groupBox_fileInfo);
        label_outputPath->setObjectName("label_outputPath");
        label_outputPath->setMinimumSize(QSize(70, 0));
        label_outputPath->setFont(font1);

        horizontalLayout_outputPath->addWidget(label_outputPath);

        lineEdit_outputPath = new QLineEdit(groupBox_fileInfo);
        lineEdit_outputPath->setObjectName("lineEdit_outputPath");
        lineEdit_outputPath->setFont(font2);

        horizontalLayout_outputPath->addWidget(lineEdit_outputPath);

        pushButton_selectOutput = new QPushButton(groupBox_fileInfo);
        pushButton_selectOutput->setObjectName("pushButton_selectOutput");
        pushButton_selectOutput->setMinimumSize(QSize(80, 30));
        pushButton_selectOutput->setMaximumSize(QSize(80, 30));

        horizontalLayout_outputPath->addWidget(pushButton_selectOutput);

        widget_decompressLoading = new QSvgWidget(groupBox_fileInfo);
        widget_decompressLoading->setObjectName("widget_decompressLoading");
        widget_decompressLoading->setMinimumSize(QSize(40, 40));
        widget_decompressLoading->setMaximumSize(QSize(40, 40));

        horizontalLayout_outputPath->addWidget(widget_decompressLoading);


        verticalLayout_fileInfo->addLayout(horizontalLayout_outputPath);

        horizontalLayout_buttons = new QHBoxLayout();
        horizontalLayout_buttons->setObjectName("horizontalLayout_buttons");
        horizontalSpacer_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_buttons->addItem(horizontalSpacer_left);

        pushButton_decompress = new QPushButton(groupBox_fileInfo);
        pushButton_decompress->setObjectName("pushButton_decompress");
        pushButton_decompress->setEnabled(false);
        pushButton_decompress->setMinimumSize(QSize(120, 40));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        pushButton_decompress->setFont(font3);

        horizontalLayout_buttons->addWidget(pushButton_decompress);

        pushButton_compress = new QPushButton(groupBox_fileInfo);
        pushButton_compress->setObjectName("pushButton_compress");
        pushButton_compress->setEnabled(false);
        pushButton_compress->setMinimumSize(QSize(120, 40));
        pushButton_compress->setFont(font3);

        horizontalLayout_buttons->addWidget(pushButton_compress);

        pushButton_clear = new QPushButton(groupBox_fileInfo);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setMinimumSize(QSize(80, 40));
        pushButton_clear->setFont(font);

        horizontalLayout_buttons->addWidget(pushButton_clear);

        pushButton_sha256check = new QPushButton(groupBox_fileInfo);
        pushButton_sha256check->setObjectName("pushButton_sha256check");
        pushButton_sha256check->setEnabled(false);
        pushButton_sha256check->setMinimumSize(QSize(90, 40));
        pushButton_sha256check->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                                                    background-color: #002FA7;\n"
"                                                    color: white;\n"
"                                                    border: none;\n"
"                                                    border-radius: 5px;\n"
"											  font-weight: bold;\n"
"                                                    padding: 8px;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:hover {\n"
"                                                    background-color: #0041C7;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:pressed {\n"
"                                                    background-color: #001F87;\n"
"                                                   }		\n"
"\n"
"										QPushButton:disabled {\n"
"                                                    bac"
                        "kground-color: #cccccc;\n"
"                                                    color: #666666;\n"
"                                                    }"));

        horizontalLayout_buttons->addWidget(pushButton_sha256check);

        horizontalSpacer_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_buttons->addItem(horizontalSpacer_right);


        verticalLayout_fileInfo->addLayout(horizontalLayout_buttons);


        verticalLayout_main->addWidget(groupBox_fileInfo);

        groupBox_progress = new QGroupBox(centralwidget);
        groupBox_progress->setObjectName("groupBox_progress");
        groupBox_progress->setFont(font);
        verticalLayout_progress = new QVBoxLayout(groupBox_progress);
        verticalLayout_progress->setObjectName("verticalLayout_progress");
        textEdit_log = new QTextEdit(groupBox_progress);
        textEdit_log->setObjectName("textEdit_log");
        textEdit_log->setMaximumSize(QSize(16777215, 120));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Consolas")});
        font4.setPointSize(9);
        font4.setBold(true);
        textEdit_log->setFont(font4);
        textEdit_log->setReadOnly(true);

        verticalLayout_progress->addWidget(textEdit_log);


        verticalLayout_main->addWidget(groupBox_progress);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 33));
        menu_file = new QMenu(menubar);
        menu_file->setObjectName("menu_file");
        menu_about = new QMenu(menubar);
        menu_about->setObjectName("menu_about");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_file->menuAction());
        menubar->addAction(menu_about->menuAction());
        menu_file->addAction(action_open);
        menu_file->addAction(action_recent);
        menu_file->addSeparator();
        menu_file->addAction(action_exit);
        menu_about->addAction(action_about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Huffman \350\247\243\345\216\213\347\274\251\345\267\245\345\205\267", nullptr));
        action_open->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266(&O)", nullptr));
#if QT_CONFIG(tooltip)
        action_open->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\246\201\345\244\204\347\220\206\347\232\204\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_open->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_recent->setText(QCoreApplication::translate("MainWindow", "\346\234\200\350\277\221\346\226\207\344\273\266(&R)", nullptr));
#if QT_CONFIG(tooltip)
        action_recent->setToolTip(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\346\234\200\350\277\221\346\211\223\345\274\200\347\232\204\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        action_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272(&X)", nullptr));
#if QT_CONFIG(shortcut)
        action_exit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        action_about->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", nullptr));
        groupBox_fileInfo->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\344\277\241\346\201\257", nullptr));
        label_filePath->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\350\267\257\345\276\204", nullptr));
        lineEdit_filePath->setText(QString());
        lineEdit_filePath->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\350\276\223\345\205\245\346\226\207\344\273\266\350\267\257\345\276\204...", nullptr));
        pushButton_browse->setText(QCoreApplication::translate("MainWindow", "\346\265\217\350\247\210...", nullptr));
        label_fileSize->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\244\247\345\260\217:", nullptr));
        label_fileSizeValue->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
        label_outputPath->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272\350\267\257\345\276\204:", nullptr));
        lineEdit_outputPath->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\350\276\223\345\207\272\346\226\207\344\273\266\350\267\257\345\276\204...", nullptr));
        pushButton_selectOutput->setText(QCoreApplication::translate("MainWindow", "\346\265\217\350\247\210...", nullptr));
        pushButton_decompress->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"                                                    background-color: #4CAF50;\n"
"                                                    color: white;\n"
"                                                    border: none;\n"
"                                                    border-radius: 5px;\n"
"                                                    padding: 8px;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:hover {\n"
"                                                    background-color: #45a049;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:pressed {\n"
"                                                    background-color: #3d8b40;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:disabled {\n"
"                                                  "
                        "  background-color: #cccccc;\n"
"                                                    color: #666666;\n"
"                                                    }", nullptr));
        pushButton_decompress->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\216\213\347\274\251", nullptr));
        pushButton_compress->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"                                                    background-color: #2196F3;\n"
"                                                    color: white;\n"
"                                                    border: none;\n"
"                                                    border-radius: 5px;\n"
"                                                    padding: 8px;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:hover {\n"
"                                                    background-color: #1976D2;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:pressed {\n"
"                                                    background-color: #1565C0;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:disabled {\n"
"                                                  "
                        "  background-color: #cccccc;\n"
"                                                    color: #666666;\n"
"                                                    }", nullptr));
        pushButton_compress->setText(QCoreApplication::translate("MainWindow", "\345\216\213\347\274\251", nullptr));
        pushButton_clear->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"                                                    background-color: #f44336;\n"
"                                                    color: white;\n"
"                                                    border: none;\n"
"                                                    border-radius: 5px;\n"
"                                                    padding: 8px;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:hover {\n"
"                                                    background-color: #d32f2f;\n"
"                                                    }\n"
"\n"
"                                                    QPushButton:pressed {\n"
"                                                    background-color: #b71c1c;\n"
"                                                    }", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        pushButton_sha256check->setText(QCoreApplication::translate("MainWindow", "SHA256\346\240\241\351\252\214", nullptr));
        groupBox_progress->setTitle(QCoreApplication::translate("MainWindow", "\350\277\233\345\272\246\344\277\241\346\201\257", nullptr));
        textEdit_log->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234\346\227\245\345\277\227\345\260\206\346\230\276\347\244\272\345\234\250\346\255\244\345\244\204...", nullptr));
        menu_file->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menu_about->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
