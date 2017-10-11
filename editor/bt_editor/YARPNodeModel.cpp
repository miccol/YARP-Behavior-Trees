#include "ActionNodeModel.hpp"
#include "ConditionNodeModel.hpp"
#include "bt_editor/YARPNodeModel.h"
#include <QTextEdit>
#include <QBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QEvent>


#include <iostream>




YARPNodeModel::YARPNodeModel(QString name, const NodeFactory::ParametersModel& parameter_model):
    BehaviorTreeNodeModel(name, parameter_model), _parameter_model(parameter_model)
{


    _main_widget = new QWidget;
    _label = new QLabel( _main_widget );
    _label->setText( name );

    QVBoxLayout *main_layout = new QVBoxLayout( _main_widget );
    QHBoxLayout *top_layout  = new QHBoxLayout(  );
    _line_edit = new QLineEdit(_main_widget);
    _line_edit->setText("YARP Server Module");

    _line_edit->setStyleSheet("background-color: white; color: black");

    _params_widget = new QWidget( _main_widget );
    _form_layout = new QFormLayout( _params_widget );

    top_layout->addWidget( _label );
    top_layout->addWidget( _line_edit );



    QFont font = _label->font();
    font.setPointSize(10);
    font.setBold(true);
    _label->setFont(font);

    QPalette palette = _label->palette();
    palette.setColor(_label->foregroundRole(), Qt::white);
    _label->setPalette(palette);

    _main_widget->setAttribute(Qt::WA_NoSystemBackground);

    _main_widget->setLayout( main_layout );

    main_layout->addLayout(top_layout);


    _form_layout->setHorizontalSpacing(5);
    _form_layout->setVerticalSpacing(2);
    _form_layout->setContentsMargins(0, 0, 0, 0);
    _params_widget->setStyleSheet("color: white;");

    main_layout->setMargin(0);
    _main_widget->setStyleSheet("background-color: transparent; color: white; ");
}



QString YARPNodeModel::caption() const {
    return type();
}

QString YARPNodeModel::type() const
{
    return _line_edit->text();
}

QString YARPNodeModel::get_line_edit()
{
    return _line_edit->text();
}



std::vector<std::pair<QString, QString>> YARPNodeModel::getCurrentParameters() const
{
    std::vector<std::pair<QString, QString>> out;

    for(int row = 0; row < _form_layout->rowCount(); row++)
    {
        auto label_item = _form_layout->itemAt(row, QFormLayout::LabelRole);
        auto field_item  = _form_layout->itemAt(row, QFormLayout::FieldRole);
        if( label_item && field_item )
        {
            QLabel* label = static_cast<QLabel*>( label_item->widget() );

            QLineEdit* line  = dynamic_cast<QLineEdit*>( field_item->widget() );
            QComboBox* combo = dynamic_cast<QComboBox*>( field_item->widget() );
            if( line ){
                out.push_back( { label->text(), line->text() } );
            }
            else if( combo )
            {
                out.push_back( { label->text(), combo->currentText() } );
            }
            break;
        }
    }
    return out;
}

QJsonObject YARPNodeModel::save() const
{
    QJsonObject nodeJson;
    nodeJson["type"] = type();
    nodeJson["ID"] = caption();
    return nodeJson;
}

void YARPNodeModel::restore(std::map<QString,QString> attributes)
{
    // we expect to find at least two attributes, "name" and "ID".
    // Other nodes represent parameters.

    std::cout << "restoring: " << std::endl;
    {
        auto v_type = attributes.find("ID");

        if (  v_type == attributes.end() )
        {
            throw std::runtime_error("the TreeNodeModel needs a [ID] to be restored");
        }
        const QString type_name = v_type->second;

        _line_edit->setText( type_name );
        attributes.erase(v_type);
        //--------------------------
        auto v_name = attributes.find("name");
        if (  v_name != attributes.end() )
        {
            _ID = v_name->second;
            attributes.erase(v_name);
        }
        else{
            _ID = v_type->second;
        }
    }

    for (auto it: attributes)
    {
        const QString& param_name = it.first;
        const QString& value      = it.second;

        bool found = false;
        for(int row = 0; row < _form_layout->rowCount(); row++)
        {
            auto label_item  = _form_layout->itemAt(row, QFormLayout::LabelRole);
            auto field_item  = _form_layout->itemAt(row, QFormLayout::FieldRole);
            if( label_item && field_item )
            {
                QLabel* label = static_cast<QLabel*>( label_item->widget() );
                //-----------------------------
                if(label->text() == param_name)
                {
                    QLineEdit* line  = dynamic_cast<QLineEdit*>( field_item->widget() );
                    QComboBox* combo = dynamic_cast<QComboBox*>( field_item->widget() );
                    if( line ){
                        line->setText(value);
                        found = true;
                    }
                    else if( combo )
                    {
                        int res = combo->findText(value);
                        if( res < 0) {
                            qDebug() << "Error: the combo ["<< param_name <<
                                        "] does not contain the value '"<< value ;
                        }
                        else {
                            combo->setCurrentText(value);
                            found = true;
                        }
                    }
                    break;
                }
            } // end for
            if( !found )
            {
                qDebug() << "Error: the parameter ["<< param_name <<
                            "] is not present in " << name() << " / " << type();
            }
        }
    }
}

void YARPNodeModel::restore(const QJsonObject &nodeJson)
{
    std::map<QString,QString> attributes;
    for(auto it = nodeJson.begin(); it != nodeJson.end(); it++ )
    {
        attributes.insert( std::make_pair(it.key(), it.value().toString()) );
    }
    restore(attributes);
}

void YARPNodeModel::lock(bool locked)
{
    _line_edit->setEnabled(!locked);

}
