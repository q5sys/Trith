//===========================================
//  trith source code
//  Copyright (c) 2021, q5sys
//  Available under the MIT license
//  See the LICENSE file for full details
//===========================================
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_encodePushButton_clicked(){
  imageFile = QFileDialog::getOpenFileName(this, tr("Open Image"), tr("Image File (*.png *.jpg *.bmp)"));
  passPopup();
  //save temp text to file as base64
  plainTextEditor *cur = currentEditor();
  QTextStream b64text;
  b64text << *cur.toUtf8().toBase64();
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

void MainWindow::passPopup(QWidget parent) : QDialog(parent) {
makePopup();
setWindowTitle( tr("Enter password") );
setModal( true );
}

void MainWindow::makePopup(){
// set up the layout
QGridLayout formGridLayout = new QGridLayout( this );
linePassword = new QLineEdit( this );
linePassword->setEchoMode( QLineEdit::Password );

// create label
labelPassword = new QLabel( this );
labelPassword->setText( tr( "Password" ) );
labelPassword->setBuddy( linePassword" );

// create buttons
buttons = new QDialogButtonBox( this );
buttons->addButton( QDialogButtonBox::Ok );
buttons->addButton( QDialogButtonBox::Cancel );
buttons->button( QDialogButtonBox::Ok )->setText( tr("Ok") );
buttons->button( QDialogButtonBox::Cancel )->setText( tr("Cancel") );

// connect slots
connect( buttons->button( QDialogButtonBox::Cancel ), SIGNAL (clicked()), this, SLOT (close()) );
connect( buttons->button( QDialogButtonBox::Ok ), SIGNAL (clicked()), this, SLOT (setPassword()) );

// Add UI layout
QGridLayout formGridLayout = new QGridLayout( this );
formGridLayout->addWidget( labelUsername, 0, 0 );
formGridLayout->addWidget( comboUsername, 0, 1 );
formGridLayout->addWidget( labelPassword, 0, 0 );
formGridLayout->addWidget( editPassword, 0, 1);
formGridLayout->addWidget( buttons, 2, 0, 1, 2 );
linePassword->setFocus();
}

void MainWindow::setPassword(QString &password){
linePassword->setText( password );
password = linePassword->text();
// close this dialog
close();
}
