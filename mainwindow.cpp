//===========================================
//  trith source code
//  Copyright (c) 2021, q5sys
//  Available under the MIT license
//  See the LICENSE file for full details
//===========================================
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <QDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_encodePushButton_clicked(){
  getImageFile();
  getKey();
  makeSecretText();
  //send base64 string with pass into encoding class
  encode(imageFile, encodedText);
}

void MainWindow::on_decodePushButton_clicked(){
  getImageFile();
  getKey();
  decode(imageFile);
  getSecretText();
  displayText();
  //savetempimagefile
}

void MainWindow::on_updatePushButton_clicked(){
    getKey();
    makeSecretText();
    encode(tempImageFile, encodedText);
}

void MainWindow::displayText(){
  ui->textEdit->setText(decodedText);
}

void MainWindow::makeSecretText(){
QString text = ui->textEdit->toPlainText();
  const char* inputE = ui->textEdit->toPlainText().toUtf8().data();
  int inputLengthE = ui->textEdit->toPlainText().toUtf8().length();
  const char* keypass = ui->lineEdit->text().toUtf8().data();
  int keyLength = ui->lineEdit->text().toUtf8().length();
  char xorOutputE[inputLengthE];
  for (int i = 0; i < inputLengthE + 1; ++i){
    xorOutputE[i] = inputE[i] ^ keypass[i % keyLength + 1];
    }
  QString xorText = QString::fromUtf8(xorOutputE, inputLengthE);
  QByteArray utf8E = xorText.toUtf8();
  QByteArray b64textE = utf8E.toBase64();
  encodedText = QString(b64textE);
}

void MainWindow::getSecretText(){
QByteArray b64TextD = secretTextExtracted.fromBase64();
//do xor on b64textD with keypass
QByteArray utf8D = b64TextD.fromUtf8();
QString decodedText = QString(utf8D);
  const char* inputD = decodedText.toUtf8().data();
  int inputLengthD = decodedText.toUtf8().length();
  const char* keypass = ui->lineEdit->text().toUtf8().data();
  int keyLength = ui->lineEdit->text().toUtf8().length();
  char xorOutputD[inputLengthD];
  for (int i = 0; i < inputLengthD + 1; ++i){
    xorOutputD[i] = inputD[i] ^ keypass[i % keyLength + 1];
    }
  QString xorText = QString::fromUtf8(xorOutputD, inputLengthD);
  QByteArray utf8E = xorText.toUtf8();
  QByteArray b64textE = utf8E.toBase64();
  encodedText = QString(b64textE);
}

void MainWindow::getImageFile(){
  QString imageFile = QFileDialog::getOpenFileName(this, tr("Open File"), ("*.png"));
}

void MainWindow::getKey(){
  QString keypass = ui->lineEdit->text();
}

bool shred(const QString & fileName) {
  QFile file(fileName);
  QFileInfo fi(file);
  qint64 fileSize = fi.size();
  if (! file.open(QIODevice::ReadWrite | QIODevice::Unbuffered)) return false;
  QByteArray block(65536, '\0');
    while (fileSize > 0) {
    if (fileSize < block.size()) block.truncate(fileSize);
    qint64 written = file.write(block);
    if (written != block.size()) return false;
    fileSize -= written;
    }
  Q_ASSERT(fileSize == 0);
  fsync(file.handle());
  return file.remove();
}

void MainWindow::on_closePushButton_clicked(){
  // Messagebox exit without saving?
  //if yes - exit
  shred(tempImageFile);
  //if no - cancel
}
