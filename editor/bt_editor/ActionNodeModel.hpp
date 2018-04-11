#pragma once

#include "BehaviorTreeNodeModel.hpp"
#include "LuaNodeModel.h"
#include "PythonNodeModel.h"
#include "YARPNodeModel.h"
#include "BlackboardNodeModel.h"

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


class PythonActionNodeModel : public PythonNodeModel
{
public:
    PythonActionNodeModel(): PythonNodeModel("Action", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return QtNodes::PYTHONACTION;
    }
    virtual ~PythonActionNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new PythonActionNodeModel ); }

    virtual QString name() const override { return QString("PythonAction"); }
};


class YarpBlackboardNodeModel : public BlackboardNodeModel
{
public:
    YarpBlackboardNodeModel(): BlackboardNodeModel("Blackboard", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return QtNodes::PYTHONACTION;
    }
    virtual ~YarpBlackboardNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return 0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new YarpBlackboardNodeModel ); }

    virtual QString name() const override { return QString("Blackboard"); }
};


// class YarpBlackboardNodeModel : public BlackboardNodeModel // TODO consider to move this in a separate file
// {
// public:
//     YarpBlackboardNodeModel(): BlackboardNodeModel("Blackboard", NodeFactory::get().getActionParameterModel() )
//     { }
//     int BTType()
//     {
//         return -1;
//     }
//     virtual ~YarpBlackboardNodeModel() {}

//     virtual unsigned int  nPorts(PortType portType) const override
//     { return 0; }

//     virtual std::unique_ptr<NodeDataModel> clone() const override
//     { return  std::unique_ptr<NodeDataModel>( new YarpBlackboardNodeModel ); }

//     virtual QString name() const override { return QString("YARPBlackboard"); }
// };


class LuaPreambleNodeModel : public LuaNodeModel // TODO consider to remove this
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
        YARPNodeModel("YARP Action", NodeFactory::get().getActionParameterModel() )
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
