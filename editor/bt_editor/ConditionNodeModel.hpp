#pragma once

#include "BehaviorTreeNodeModel.hpp"


class ConditionNodeModel : public BehaviorTreeNodeModel
{
public:
    ConditionNodeModel():
        BehaviorTreeNodeModel("Condition", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::CONDITION;
    }
    virtual ~ConditionNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new ConditionNodeModel ); }

    virtual QString name() const override { return QString("Condition"); }
};



class LuaConditionNodeModel : public LuaNodeModel
{
public:
    LuaConditionNodeModel(): LuaNodeModel("Condition", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return QtNodes::LUACONDITION;
    }
    virtual ~LuaConditionNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new LuaConditionNodeModel ); }

    virtual QString name() const override { return QString("LuaCondition"); }
};



class YARPConditionNodeModel : public YARPNodeModel
{
public:
    YARPConditionNodeModel():
        YARPNodeModel("YARP Condition", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return QtNodes::YARPCONDITION;
    }
    virtual ~YARPConditionNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new YARPConditionNodeModel ); }

    virtual QString name() const override { return QString("YARPCondition"); }
};
