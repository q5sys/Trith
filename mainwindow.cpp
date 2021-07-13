//===========================================
//  trith source code
//  Copyright (c) 2021, q5sys
//  Available under the MIT license
//  See the LICENSE file for full details
//===========================================
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_encodePushButton_clicked(){
  imageFile = QFileDialog::getOpenFileName(this, tr("Open Image"), tr("Image File (*.png *.jpg *.bmp)"));
  passPopup* passPopup= new passPopup(this);
  //save temp text to file as base64
  plainTextEditor *cur = currentEditor();
    QTextStream b64text;
    b64text << *cur.toUtf8().toBase64();
  }
  //send base64 string with pass into encoding class
  encodeCLASS(imageFile, password, b64text);
}


void MainWindow::on_decodePushButton_clicked()
{
//findfile
//askforpass
//decodefile
//displaytext
//savetemporiginalfile

}

void MainWindow::openImageFile(){
 imageFile = QFileDialog::getOpenFileName(this, tr("Open Image"), tr("Image File (*.png *.jpg *.bmp)"));

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
  // shred any files left
  //if no - cancel
}
