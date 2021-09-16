//===========================================
//  trith source code
//  Copyright (c) 2021, q5sys
//  Available under the MIT license
//  See the LICENSE file for full details
//===========================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QGridLayout>


QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getImageFile();
    void getKey();
    void displayText();
    void getSecretText();
    void makeSecretText();
    void doXor();
    QLineEdit linePassword;
    QLabel labelPassword;
    QString keypass, secretTextExtracted, decodedText, encodedText, tempImageFile;
    QFileDialog imageFile;

private slots:
    void on_encodePushButton_clicked();
    void on_decodePushButton_clicked();
    void on_closePushButton_clicked();

    void on_updatePushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
