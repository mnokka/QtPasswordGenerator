#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QString password;
    password=generatePassword(lenght);
    qDebug() << password;
    fflush(stdout);
    createMenus();
}

MainWindow::~MainWindow() {
}

void MainWindow::createMenus()
{
    aboutMenu = menuBar()->addMenu(tr("&New password"));
    aboutAct = new QAction(tr("&Generate"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::generate);
    aboutMenu->addAction(aboutAct);

    aboutMenu = menuBar()->addMenu(tr("&Password lenght"));
    aboutAct = new QAction(tr("&Set"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::setPasswordLength);
    aboutMenu->addAction(aboutAct);
}


void MainWindow::generate()
{
    QString password;
    password=generatePassword(lenght);
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(password);

    QMessageBox::about(this, tr("Generated password"),
                       tr("\n") +password +("\n\nCopied to clipboard!"));
}


QString MainWindow::generatePassword(int lenght)
{

    QString characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ"
                         "abcdefghijklmnopqrstuvwxyzåäö"
                         "0123456789"
                         "!@#$%^&*()_+-=[]{}|;:,.<>?";
    QString password;

    for (int i = 0; i < lenght; ++i)
    {
        int index = QRandomGenerator::global()->bounded(characters.size());
        password.append(characters.at(index));
    }
    return password;
}

void MainWindow::OkButtonClicked(void) {
    lenght= spinBox->value();
    //QString password = generatePassword(lenght);
    qDebug() << "Lenght" << lenght;
    dialog->accept();
}

void MainWindow::setPasswordLength(void) {
        dialog=new QDialog(this);
        dialog->setWindowTitle("Set length");

        QVBoxLayout *layout = new QVBoxLayout(dialog);

        spinBox = new QSpinBox(dialog);
        spinBox->setRange(4, 64);
        spinBox->setValue(lenght);
        layout->addWidget(spinBox);

        QPushButton *okButton = new QPushButton("OK", dialog);
        layout->addWidget(okButton);

        dialog->setLayout(layout);

        connect(okButton, &QPushButton::clicked, this, &MainWindow::OkButtonClicked);
        dialog->exec();
}
