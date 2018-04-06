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
    lua_bt_node_model_ =  bt_node_model;

    std::string title = "Code Editor for ";//  filename_.c_str());
    title.append(filename_);

    ui->setupUi(this);
    setWindowTitle(title.c_str());
    ui->plainTextEdit->document()->setPlainText(lua_bt_node_model_->get_source_code());
}


CodeEditorWindow::CodeEditorWindow(std::string filename, PythonNodeModel *bt_node_model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CodeEditorWindow)
{
    filename_ = filename;
    python_bt_node_model_ =  bt_node_model;

    std::string title = "Code Editor for ";//  filename_.c_str());
    title.append(filename_);

    ui->setupUi(this);
    setWindowTitle(title.c_str());
    ui->plainTextEdit->document()->setPlainText(python_bt_node_model_->get_source_code());
}

CodeEditorWindow::~CodeEditorWindow()
{
    delete ui;
}


void CodeEditorWindow::closeEvent(QCloseEvent *event)
{
    writeToFile();

    //Tric to figure of if it is python or lua script.
    if (python_bt_node_model_ !=NULL)
    {
    python_bt_node_model_->onCodeUpdated();

    }else
    {
    lua_bt_node_model_->onCodeUpdated();
    }
    QMainWindow::closeEvent(event);
}


void CodeEditorWindow::writeToFile()
{

    std::ofstream myfile;
    myfile.open (filename_);
    myfile << this->ui->plainTextEdit->toPlainText().toStdString();
    myfile.close();
}
