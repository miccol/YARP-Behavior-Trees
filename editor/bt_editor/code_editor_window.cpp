#include "code_editor_window.h"
#include "ui_code_editor_window.h"
#include <iostream>
#include <fstream>

#include <QSettings>
CodeEditorWindow::CodeEditorWindow(std::string filename, LuaNodeModel *bt_node_model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CodeEditorWindow)
{
    filename_ = filename;
    bt_node_model_ =  bt_node_model;

    std::string title = "Code Editor for ";//  filename_.c_str());
    title.append(filename_);

    ui->setupUi(this);
    setWindowTitle(title.c_str());
    ui->plainTextEdit->document()->setPlainText(bt_node_model_->get_source_code());
}

CodeEditorWindow::~CodeEditorWindow()
{
    delete ui;
}


void CodeEditorWindow::closeEvent(QCloseEvent *event)
{
    writeToFile();
    bt_node_model_->onCodeUpdated();
    QMainWindow::closeEvent(event);
}


void CodeEditorWindow::writeToFile()
{

    std::ofstream myfile;
    myfile.open (filename_);
    myfile << this->ui->plainTextEdit->toPlainText().toStdString();
    myfile.close();
}
