//===========================================
//  trith source code
//  Copyright (c) 2021, q5sys
//  Available under the MIT license
//  See the LICENSE file for full details
//===========================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_encodePushButton_clicked();
    void on_decodePushButton_clicked();
    void on_plainTextEdit_textChanged();
    void on_closePushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
