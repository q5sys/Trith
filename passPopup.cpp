//===========================================
//  trith source code
//  Copyright (c) 2021, q5sys
//  Available under the MIT license
//  See the LICENSE file for full details
//===========================================


passPopup::passPopup(QWidget parent) : QDialog(parent) {
makePopup();
setWindowTitle( tr("Enter password") );
setModal( true );
}

void passPopup::makePopup(){

// set up the layout
QGridLayout formGridLayout = new QGridLayout( this );
editPassword = new QLineEdit( this );
editPassword->setEchoMode( QLineEdit::Password );

// create label
labelPassword = new QLabel( this );
labelPassword->setText( tr( "Password" ) );
labelPassword->setBuddy( setPassword );

// create buttons
buttons = new QDialogButtonBox( this );
buttons->addButton( QDialogButtonBox::Ok );
buttons->addButton( QDialogButtonBox::Cancel );
buttons->button( QDialogButtonBox::Ok )->setText( tr("Ok") );
buttons->button( QDialogButtonBox::Cancel )->setText( tr("Cancel") );

// connect slots
connect( buttons->button( QDialogButtonBox::Cancel ), SIGNAL (clicked()), this, SLOT (close()) );
connect( buttons->button( QDialogButtonBox::Ok ), SIGNAL (clicked()), this, SLOT (emitPassword()) );

// Add UI layout
formGridLayout->addWidget( labelUsername, 0, 0 );
formGridLayout->addWidget( comboUsername, 0, 1 );
formGridLayout->addWidget( labelPassword, 0, 0 );
formGridLayout->addWidget( editPassword, 0, 1);
formGridLayout->addWidget( buttons, 2, 0, 1, 2 );
setPassword->setFocus();
}

void passPopup::setPassword(QString &password){
setPassword->setText( password );
password = setPassword->text();
// Emit password

// close this dialog
close();
}
