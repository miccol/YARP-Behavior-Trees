#ifndef PYTHONNODEMODEL_H
#define PYTHONNODEMODEL_H

#include <QObject>
#include <QLabel>
#include <QFormLayout>
#include <QComboBox>
#include <QTextEdit>

#include <bt_editor/BehaviorTreeNodeModel.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include "NodeFactory.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;


class PythonNodeModel : public BehaviorTreeNodeModel
{
  Q_OBJECT
public:
  PythonNodeModel(QString name, const NodeFactory::ParametersModel& parameter_model);

  virtual ~PythonNodeModel() {}

  virtual bool captionVisible() const override
  { return false; }

public:

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override final
  { return NodeDataType {"", ""}; }

  virtual std::shared_ptr<NodeData> outData(PortIndex port) override
  { return nullptr; }

  void setInData(std::shared_ptr<NodeData> data, int) override final {}

  virtual QString caption() const override;

  QString type() const;

  std::vector<std::pair<QString, QString> > getCurrentParameters() const;

  virtual QWidget *embeddedWidget() override { return _main_widget; }

  virtual QJsonObject save() const override;

  void restore(std::map<QString, QString> attributes);

  virtual void restore(QJsonObject const &nodeJson) override;

  virtual void lock(bool locked);

  QString get_line_edit();
  //QString get_text_edit();
  QStringList get_all_files_names_within_folder(std::string folder, std::string type);

  void lastComboItem();
  //bool eventFilter(QObject *object, QEvent *event);
  std::string filename();
public slots:
  void onCodeUpdated();
  void onComboBoxUpdated(QString item_text);

  QString get_source_code();
private:
  QWidget*   _main_widget;
  QWidget*   _params_widget;
  QFormLayout *_form_layout;
  QLabel*    _label;
  QComboBox* _ID_selection_combobox;
  QString    _ID;
  QLineEdit* _line_edit;
  //QTextEdit * _text_edit;
  QString     source_code_;
  const NodeFactory::ParametersModel& _parameter_model;

private slots:
  //void onTextBoxUpdated();


signals:
  void adjustSize();
};
//------------------------------------------------


//------------------------------------------------

#endif
