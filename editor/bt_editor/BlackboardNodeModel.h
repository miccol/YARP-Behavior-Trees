#ifndef BLACKBOARDNODEMODEL_H
#define BLACKBOARDNODEMODEL_H

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
#include <QTableView>

#include <yarp/os/Property.h> // the blackboard is a yarp property


using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;


class BlackboardNodeModel : public BehaviorTreeNodeModel
{
  Q_OBJECT
public:
  BlackboardNodeModel(QString name, const NodeFactory::ParametersModel& parameter_model);

  virtual ~BlackboardNodeModel() {}

  virtual bool captionVisible() const override
  { return false; }

public:

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override final
  { return NodeDataType {"", ""}; }

  virtual std::shared_ptr<NodeData> outData(PortIndex port) override
  { return nullptr; }

  void setInData(std::shared_ptr<NodeData> data, int) override final {}

  virtual QString caption() const override;

  std::vector<std::pair<QString, QString> > getCurrentParameters() const;

  virtual QWidget *embeddedWidget() override { return _main_widget; }

  virtual QJsonObject save() const override;

  void restore(std::map<QString, QString> attributes);

  virtual void restore(QJsonObject const &nodeJson) override;

  virtual void lock(bool locked);

  void update_blackboard();
  void lastComboItem();
  //bool eventFilter(QObject *object, QEvent *event);

void set_blackboard(yarp::os::Property *blackboard );
//QLabel* blackboard_content_ ;

void set_blackboard_text(QString text);
public slots:


private:
  QWidget*   _main_widget;
  QWidget*   _params_widget;
  QFormLayout *_form_layout;
  QLabel*    _label;
  QString    _ID;
  QLabel* blackboard_content_;
  //QTextEdit * _text_edit;
  yarp::os::Property *blackboard_ ;
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
