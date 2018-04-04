#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <node_editor/NodeData>
#include <node_editor/FlowScene>
#include <bt_editor/ActionNodeModel.hpp>

// extern "C"
// {
// # include "lua.h"
// # include "lauxlib.h"
// # include "lualib.h"
// }

std::vector<QtNodes::Node*> findRoots(const QtNodes::FlowScene &scene);

std::vector<QtNodes::Node*> getChildren(const QtNodes::FlowScene &scene,
                                        const QtNodes::Node &parent_node);




void NodeReorder(QtNodes::FlowScene& scene);

void SubtreeReorder(QtNodes::FlowScene &scene, QtNodes::Node &root_node);

void runTree(QtNodes::FlowScene *scene);

void calculateForces(QtNodes::FlowScene *scene);

void setMode(int mode);

int getMode();

bool is_BT_valid(QtNodes::FlowScene* scene);
bool has_root(QtNodes::FlowScene* scene);
bool has_lua_preable(QtNodes::FlowScene* scene);
bool has_yarp(QtNodes::FlowScene* scene);
QtNodes::Node* LuaPreamble(QtNodes::FlowScene* scene);
// void RunPreamble(lua_State *lua_state, LuaPreambleNodeModel* lua_preamble_node);
QtNodes::Node* BTRoot(QtNodes::FlowScene* scene);

#endif // NODE_UTILS_H
