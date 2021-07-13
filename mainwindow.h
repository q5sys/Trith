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
    openImageFile();
    QDialog makePopup();
    QDialog passPopup();
    QLineEdit linePassword;
    QLabel labelPassword;
    QString password;
    QFileDialog imageFile;
    QDialogButtonBox buttons;
    QString setPassword();

private slots:
    void on_encodePushButton_clicked();
    void on_decodePushButton_clicked();
    void on_plainTextEdit_textChanged();
    void on_closePushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
