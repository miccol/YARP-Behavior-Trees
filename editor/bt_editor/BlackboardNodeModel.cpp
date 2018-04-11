#include "ActionNodeModel.hpp"
#include "ConditionNodeModel.hpp"
#include "LuaNodeModel.h"
#include <QTextEdit>
#include <QBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QEvent>
#include <QStandardItemModel>
#include <QStandardItem>
#include "BlackboardNodeModel.h"
#include <yarp/os/Property.h> // the blackboard is a yarp property



BlackboardNodeModel::BlackboardNodeModel(QString name, const NodeFactory::ParametersModel &parameter_model) : BehaviorTreeNodeModel(name, parameter_model), _parameter_model(parameter_model)
{

    _main_widget = new QWidget;
    _label = new QLabel(_main_widget);
    _label->setText(name);

    // TODO use QTableView to make the BB editable
    blackboard_ = new yarp::os::Property();

    blackboard_content_ = new QLabel(_main_widget);
    //blackboard_content_->setText("init");
    //blackboard_content_->setText("init2");

    //blackboard_content_->setText(blackboard_->toString().c_str());

    //std::cout << blackboard_->toString() << std::endl;

    QVBoxLayout *main_layout = new QVBoxLayout(_main_widget);
    QHBoxLayout *top_layout = new QHBoxLayout();
    QHBoxLayout *bottom_layout = new QHBoxLayout();

    _params_widget = new QWidget(_main_widget);
    _form_layout = new QFormLayout(_params_widget);

    top_layout->addWidget(_label);
    bottom_layout->addWidget(blackboard_content_);

    main_layout->addLayout(top_layout);
    main_layout->addLayout(bottom_layout);

    QFont font = _label->font();
    font.setPointSize(10);
    font.setBold(true);
    _label->setFont(font);

    QPalette palette = _label->palette();
    palette.setColor(_label->foregroundRole(), Qt::white);
    _label->setPalette(palette);

    _main_widget->setAttribute(Qt::WA_NoSystemBackground);
    _main_widget->setLayout(main_layout);

    _form_layout->setHorizontalSpacing(5);
    _form_layout->setVerticalSpacing(2);
    _form_layout->setContentsMargins(0, 0, 0, 0);
    _params_widget->setStyleSheet("color: white;");

    main_layout->setMargin(0);
    _main_widget->setStyleSheet("background-color: transparent; color: white; ");

    blackboard_content_->setText("init3");
set_blackboard_text("init4");

            std::cout << blackboard_content_ << std::endl;
            std::cout << blackboard_content_ << std::endl;
            std::cout << blackboard_content_ << std::endl;
            std::cout << blackboard_content_ << std::endl;
            std::cout << blackboard_content_->text().toStdString() << std::endl;

}


void BlackboardNodeModel::set_blackboard_text(QString text)
{
        blackboard_content_->setText(text);

}

QString BlackboardNodeModel::caption() const
{
    return type();
}

void BlackboardNodeModel::set_blackboard(yarp::os::Property *blackboard)
{
    blackboard_ = blackboard;
    std::cout << "****************************************** BB set ******************************************" << std::endl;
        std::cout << blackboard_->toString()<< std::endl;
            std::cout << "****************************************** OK ******************************************" << std::endl;


}

std::vector<std::pair<QString, QString>> BlackboardNodeModel::getCurrentParameters() const
{
    std::vector<std::pair<QString, QString>> out;

    for (int row = 0; row < _form_layout->rowCount(); row++)
    {
        auto label_item = _form_layout->itemAt(row, QFormLayout::LabelRole);
        auto field_item = _form_layout->itemAt(row, QFormLayout::FieldRole);
        if (label_item && field_item)
        {
            QLabel *label = static_cast<QLabel *>(label_item->widget());

            QLineEdit *line = dynamic_cast<QLineEdit *>(field_item->widget());
            QComboBox *combo = dynamic_cast<QComboBox *>(field_item->widget());
            if (line)
            {
                out.push_back({label->text(), line->text()});
            }
            else if (combo)
            {
                out.push_back({label->text(), combo->currentText()});
            }
            break;
        }
    }
    return out;
}

QJsonObject BlackboardNodeModel::save() const
{
    QJsonObject nodeJson;
    nodeJson["type"] = type();
    nodeJson["ID"] = caption();
    return nodeJson;
}

void BlackboardNodeModel::restore(std::map<QString, QString> attributes)
{
    // we expect to find at least two attributes, "name" and "ID".
    // Other nodes represent parameters.

    std::cout << "restoring: " << std::endl;
    {
        auto v_type = attributes.find("ID");

        if (v_type == attributes.end())
        {
            throw std::runtime_error("the TreeNodeModel needs a [ID] to be restored");
        }
        const QString type_name = v_type->second;

        attributes.erase(v_type);
        //--------------------------
        auto v_name = attributes.find("name");
        if (v_name != attributes.end())
        {
            _ID = v_name->second;
            attributes.erase(v_name);
        }
        else
        {
            _ID = v_type->second;
        }
    }

    for (auto it : attributes)
    {
        const QString &param_name = it.first;
        const QString &value = it.second;

        bool found = false;
        for (int row = 0; row < _form_layout->rowCount(); row++)
        {
            auto label_item = _form_layout->itemAt(row, QFormLayout::LabelRole);
            auto field_item = _form_layout->itemAt(row, QFormLayout::FieldRole);
            if (label_item && field_item)
            {
                QLabel *label = static_cast<QLabel *>(label_item->widget());
                //-----------------------------
                if (label->text() == param_name)
                {
                    QLineEdit *line = dynamic_cast<QLineEdit *>(field_item->widget());
                    QComboBox *combo = dynamic_cast<QComboBox *>(field_item->widget());
                    if (line)
                    {
                        line->setText(value);
                        found = true;
                    }
                    else if (combo)
                    {
                        int res = combo->findText(value);
                        if (res < 0)
                        {
                            qDebug() << "Error: the combo [" << param_name << "] does not contain the value '" << value;
                        }
                        else
                        {
                            combo->setCurrentText(value);
                            found = true;
                        }
                    }
                    break;
                }
            } // end for
            if (!found)
            {
                qDebug() << "Error: the parameter [" << param_name << "] is not present in " << name() << " / " << type();
            }
        }
    }
}

void BlackboardNodeModel::restore(const QJsonObject &nodeJson)
{
    std::map<QString, QString> attributes;
    for (auto it = nodeJson.begin(); it != nodeJson.end(); it++)
    {
        attributes.insert(std::make_pair(it.key(), it.value().toString()));
    }
    restore(attributes);
}

void BlackboardNodeModel::lock(bool locked)
{
    //_text_edit->setEnabled(!locked);
}

void BlackboardNodeModel::update_blackboard()
{
    std::string blackboard_as_str = blackboard_->toString() ;
    if (!blackboard_as_str.empty())
    {

        set_blackboard_text(QString(blackboard_as_str.c_str()));
    }
}
