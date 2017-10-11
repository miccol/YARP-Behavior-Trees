#pragma once

#include "BehaviorTreeNodeModel.hpp"
#include "LuaNodeModel.h"
#include "YARPNodeModel.h"


class ActionNodeModel : public BehaviorTreeNodeModel
{
public:
    ActionNodeModel():
        BehaviorTreeNodeModel("Action", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ACTION;
    }
    virtual ~ActionNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new ActionNodeModel ); }

    virtual QString name() const override { return QString("Action"); }
//    virtual QString name() const override { return QString("Action"); }
};


class LuaActionNodeModel : public LuaNodeModel
{
public:
    LuaActionNodeModel(): LuaNodeModel("Action", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return QtNodes::LUAACTION;
    }
    virtual ~LuaActionNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new LuaActionNodeModel ); }

    virtual QString name() const override { return QString("LuaAction"); }
};


class LuaPreambleNodeModel : public LuaNodeModel
{
public:
    LuaPreambleNodeModel(): LuaNodeModel("LuaPreamble", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return -1;
    }
    virtual ~LuaPreambleNodeModel() {}


    virtual unsigned int  nPorts(PortType portType) const override
    { return 0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new LuaPreambleNodeModel ); }

    virtual QString name() const override { return QString("LuaPreamble"); }
};


class YARPActionNodeModel : public YARPNodeModel
{
public:
    YARPActionNodeModel():
        YARPNodeModel("Action", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return QtNodes::YARPACTION;
    }
    virtual ~YARPActionNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new YARPActionNodeModel ); }

    virtual QString name() const override { return QString("YARPAction"); }
};
