#ifndef CODE_EDITOR_WINDOW_H
#define CODE_EDITOR_WINDOW_H

#include <QMainWindow>
#include <bt_editor/LuaNodeModel.h>

namespace Ui {
class CodeEditorWindow;
}

class CodeEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CodeEditorWindow(std::string title, LuaNodeModel* bt_node_model, QWidget *parent = 0);
    ~CodeEditorWindow();
    void closeEvent(QCloseEvent *event);


private:
    LuaNodeModel* bt_node_model_;
    std::string filename_;

    Ui::CodeEditorWindow *ui;
    void writeToFile();


};

#endif // CODE_EDITOR_WINDOW_H
