#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->mainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->mainTextEdit->setText(QString());
    setWindowTitle("New File");
}

void MainWindow::on_actionOpen_triggered()
{
    // Opens a dialog that allows you to select a file to open
       QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

       // An object for reading and writing files
       QFile file(fileName);

       // Store the currentFile name
       currentFile = fileName;

       // Try to open the file as a read only file if possible or display a
       // warning dialog box
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
           return;
       }

       // Set the title for the window to the file name
       setWindowTitle(fileName);

       // Interface for reading text
       QTextStream in(&file);

       // Copy text in the string
       QString text = in.readAll();

       // Put the text in the textEdit widget
       ui->mainTextEdit->setText(text);

       // Close the file
       file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    // Opens a dialog for saving a file
     QString fileName = QFileDialog::getSaveFileName(this, "Save as");

     // An object for reading and writing files
     QFile file(fileName);

     // Try to open a file with write only options
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
         return;
     }

     // Store the currentFile name
     currentFile = fileName;

     // Set the title for the window to the file name
     setWindowTitle(fileName);

     // Interface for writing text
     QTextStream out(&file);

     // Copy text in the textEdit widget and convert to plain text
     QString text = ui->mainTextEdit->toPlainText();

     // Output to file
     out << text;

     // Close the file
     file.close();

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer,this);
    if(pDialog.exec()==QDialog::Rejected){
        QMessageBox::warning(this,
                             "Warning",
                             "Cannot Access Printer");
        return;
    }
    ui->mainTextEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->mainTextEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
      ui->mainTextEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
      ui->mainTextEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
      ui->mainTextEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
      ui->mainTextEdit->redo();
}

//this is for text to zoom in and out to increment and decrement value


void MainWindow::on_actionIn_triggered()
{
    QFont font;
    font.setPixelSize(defaultSize);
    ui->mainTextEdit->setFont(font);
    defaultSize++;

}

void MainWindow::on_actionOut_triggered()
{
    defaultSize-- ;
    QFont font;
    font.setPixelSize(defaultSize);
    ui->mainTextEdit->setFont(font);
}


void MainWindow::on_actionReset_triggered()
{
    QFont font;
    font.setPixelSize(12);
    ui->mainTextEdit->setFont(font);
    defaultSize = 12;
}
