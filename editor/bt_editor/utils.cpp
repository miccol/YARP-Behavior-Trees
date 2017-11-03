#include "utils.h"
#include <node_editor/Node>
#include <QDebug>
#include <set>
#include <node_editor/Node>
#include <bt_editor/BehaviorTreeNodeModel.hpp>
#include <bt_editor/YARPNodeModel.h>

#include <iostream>
#include <fstream>
#include "RootNodeModel.hpp"


#include <QThread>
#include <behavior_tree.h>


extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

std::vector<QtNodes::Node*> findRoots(const QtNodes::FlowScene &scene)
{
    std::set<QUuid> roots;
    for (auto& it: scene.nodes() ){
        roots.insert( it.first );
    }

    for (auto it: scene.connections())
    {
        std::shared_ptr<QtNodes::Connection> connection = it.second;
        QtNodes::Node* child  = connection->getNode( QtNodes::PortType::In );

        if( child ) {
            roots.erase( child->id() );
        }
    }

    std::vector<QtNodes::Node*> sorted_roots;
    for (auto uuid: roots)
    {
        sorted_roots.push_back( scene.nodes().find(uuid)->second.get() );
    }

    auto CompareFunction = [&](const QtNodes::Node* a, const QtNodes::Node* b)
    {
        return scene.getNodePosition( *a ).y() <  scene.getNodePosition( *b ).y();
    };
    std::sort(sorted_roots.begin(), sorted_roots.end(), CompareFunction );

    return sorted_roots;
}

std::vector<QtNodes::Node*> getChildren(const QtNodes::FlowScene &scene,
                                        const QtNodes::Node& parent_node)
{
    std::vector<QtNodes::Node*> children;

    for (auto it: scene.connections())
    {
        std::shared_ptr<QtNodes::Connection> connection = it.second;

        QtNodes::Node* parent = connection->getNode( QtNodes::PortType::Out );
        QtNodes::Node* child  = connection->getNode( QtNodes::PortType::In );

        if( parent && child )
        {
            if( parent->id() == parent_node.id())
            {
                children.push_back( child );
            }
        }
    }

    auto CompareFunction = [&](const QtNodes::Node* a, const QtNodes::Node* b)
    {
        return scene.getNodePosition( *a ).x() <  scene.getNodePosition( *b ).x();
    };
    std::sort(children.begin(), children.end(), CompareFunction );

   // std::cout << "Children are: " << children.size() << std::endl;
    return children;
}

QtNodes::Node* getParent(const QtNodes::FlowScene &scene,
                         const QtNodes::Node& node)
{

    for (auto it: scene.connections())
    {
        std::shared_ptr<QtNodes::Connection> connection = it.second;

        QtNodes::Node* parent = connection->getNode( QtNodes::PortType::Out );
        QtNodes::Node* child  = connection->getNode( QtNodes::PortType::In );

        if( parent && child )
        {
            if( child->id() == node.id())
            {
                return parent;
            }
        }
    }

    return NULL;

}



//---------------------------------------------------
void NodeReorderRecursive(QtNodes::FlowScene &scene,
                             QtNodes::Node& node,
                             QPointF cursor,
                             int level,
                             std::map<int, std::vector<QtNodes::Node*>>& nodes_by_level)
{
    const double vertical_spacing = 15;
    std::vector<QtNodes::Node*> children = getChildren(scene, node );

    double total_height = 0;
    for (QtNodes::Node* child_node: children)
    {
        total_height += child_node->nodeGeometry().width() + vertical_spacing;
    }



    auto this_level_it = nodes_by_level.find(level);
    auto next_level_it = nodes_by_level.find(level+1);

    double this_max_Y = 0;
    double next_max_Y = cursor.x();

    if( next_level_it != nodes_by_level.end() )
    {
        QtNodes::Node& last_node_right = *(next_level_it->second.back()) ;
        next_max_Y = vertical_spacing*3.0 +
                scene.getNodePosition( last_node_right ).x() +
                scene.getNodeSize( last_node_right ).width();
    }

    if( this_level_it != nodes_by_level.end() )
    {
        QtNodes::Node& last_node_right = *(this_level_it->second.back()) ;
        this_max_Y = vertical_spacing*2.0 +
                scene.getNodePosition( last_node_right ).x() +
                scene.getNodeSize( last_node_right ).width();
    }

    //---------------------------------------------
    // adjust cursor Y
    cursor.setX( std::max( this_max_Y, next_max_Y) ) ;

    scene.setNodePosition( node, cursor);
    nodes_by_level[level].push_back( &node );
    //---------------------------------------------

    QPointF children_cursor( cursor.x(), cursor.y() + node.nodeGeometry().height() + 100 ) ;

    if( children.size() > 1){
        children_cursor.setX( cursor.x() - total_height*0.5 );
    }

    for (int i=0; i< children.size(); i++)
    {
        QtNodes::Node* child_node = children[i];
        const double height = child_node->nodeGeometry().width();
        NodeReorderRecursive( scene, *child_node, children_cursor, level+1, nodes_by_level  );
        double child_x   =  children_cursor.x() + height + 2.0*vertical_spacing;
        children_cursor.setX( child_x );
        //qDebug() << ".... cursor shifted " << prev_cursor << " to " << children_cursor;
    }

    if( children.size() > 1)
    {
        double min_Y = scene.getNodePosition( *children.front() ).x() ;
        double max_Y = scene.getNodePosition( *children.back() ).x() + scene.getNodeSize(*children.back()).width();

        QPointF temp_cursor(   (max_Y + min_Y) * 0.5 - node.nodeGeometry().width() / 2.0, scene.getNodePosition( *children.back() ).y() - node.nodeGeometry().height() -  80 );
        if( temp_cursor.x() > cursor.x())
        {
            scene.setNodePosition( node, temp_cursor);
        }
    }
    else if ( children.size() > 0)
    {
        QPointF temp_cursor(   scene.getNodePosition( *children.front() ).x() + scene.getNodeSize(*children.front()).width() / 2.0 - node.nodeGeometry().width() / 2.0 , scene.getNodePosition( *children.front() ).y() - node.nodeGeometry().height() -  80 );
        scene.setNodePosition( node, temp_cursor);

    }


}






void SubtreeReorderRecursive(QtNodes::FlowScene &scene,
                             QtNodes::Node& node,
                             QtNodes::Node& root_node,
                             QPointF cursor,
                             int level,
                             std::map<int, std::vector<QtNodes::Node*>>& nodes_by_level)
{
    const double vertical_spacing = 15;
    std::vector<QtNodes::Node*> children = getChildren(scene, node );

    std::cout << "n of children " << children.size() <<std::endl;

    double total_height = 0;
    for (QtNodes::Node* child_node: children)
    {
        total_height += child_node->nodeGeometry().width() + vertical_spacing;
    }

    auto this_level_it = nodes_by_level.find(level);
    auto next_level_it = nodes_by_level.find(level+1);

    double this_max_Y = 0;
    double next_max_Y = cursor.x();

    if( next_level_it != nodes_by_level.end() )
    {
        QtNodes::Node& last_node_right = *(next_level_it->second.back()) ;
        next_max_Y = vertical_spacing*3.0 +
                scene.getNodePosition( last_node_right ).x() +
                scene.getNodeSize( last_node_right ).width();
    }

    if( this_level_it != nodes_by_level.end() )
    {
        QtNodes::Node& last_node_right = *(this_level_it->second.back()) ;
        this_max_Y = vertical_spacing*2.0 +
                scene.getNodePosition( last_node_right ).x() +
                scene.getNodeSize( last_node_right ).width();
    }

    //---------------------------------------------
    // adjust cursor Y
    cursor.setX( std::max( this_max_Y, next_max_Y) ) ;


    //    qDebug() << "node: " << node.nodeDataModel()->caption()<< " id: "<<
//                node.nodeDataModel()->name() << " pos: " << cursor;

    if (node.id() != root_node.id())
    {
        scene.setNodePosition( node, cursor);
    }
    nodes_by_level[level].push_back( &node );
    //---------------------------------------------

    QPointF children_cursor( cursor.x(), cursor.y() + node.nodeGeometry().height() + 100 ) ;

    if( children.size() > 1){
        children_cursor.setX( cursor.x() - total_height*0.5 );
    }

    for (int i=0; i< children.size(); i++)
    {
        QtNodes::Node* child_node = children[i];
        const double height = child_node->nodeGeometry().width();
        SubtreeReorderRecursive( scene, *child_node, root_node, children_cursor, level+1, nodes_by_level  );
        double child_x   =  children_cursor.x() + height + 2.0*vertical_spacing;
        children_cursor.setX( child_x );
        //qDebug() << ".... cursor shifted " << prev_cursor << " to " << children_cursor;
    }

    if( children.size() > 1)
    {
        double min_Y = scene.getNodePosition( *children.front() ).x() ;
        double max_Y = scene.getNodePosition( *children.back() ).x() + scene.getNodeSize(*children.back()).width();

        QPointF temp_cursor(   (max_Y + min_Y) * 0.5 - node.nodeGeometry().width() / 2.0, scene.getNodePosition( *children.back() ).y() - node.nodeGeometry().height() -  80 );
        if( temp_cursor.x() > cursor.x() && node.id() !=root_node.id())
        {
            scene.setNodePosition( node, temp_cursor);
        }
    }
    else if ( children.size() > 0 && node.id() != root_node.id())
    {
        QPointF temp_cursor(   scene.getNodePosition( *children.front() ).x() + scene.getNodeSize(*children.front()).width() / 2.0 - node.nodeGeometry().width() / 2.0 , scene.getNodePosition( *children.front() ).y() - node.nodeGeometry().height() -  80 );
        scene.setNodePosition( node, temp_cursor);

    }


}






void calculateForces(QtNodes::FlowScene* scene)
{

    double speed = 500;

    for (auto& it: scene->nodes() )
    {

        // Sum up all forces pushing this node away
        qreal xvel = 0;
        qreal yvel = 0;
        QtNodes::Node* node = it.second.get();

        if(node->nodeGraphicsObject().isSelected())
        {
            continue;
        }

        QPointF node_pos = scene->getNodePosition(*node);

        for (auto& other_it: scene->nodes())
        {
            QtNodes::Node* other_node = other_it.second.get();
            if (node == other_node)
            {
                continue;
            }

            QPointF other_node_pos = scene->getNodePosition(*other_node);

            QSizeF node_size = scene->getNodeSize(*node);
            QSizeF other_node_size = scene->getNodeSize(*other_node);


            qreal dx = node_pos.x() - other_node_pos.x();
            qreal dy = node_pos.y() - other_node_pos.y();


            xvel = 0;
            double l = 2.0 * (dx * dx + dy * dy);

            xvel += (dx * speed) / l;
            yvel += (dy * speed) / l;


            qreal width_to_check = 0.0;
            qreal height_to_check = 0.0;

            if (dx < 0 )
            {
                // node_pos on the left

                width_to_check = node->nodeGeometry().width() + 30 ;
            }
            else
            {
                width_to_check = other_node->nodeGeometry().width() + 30 ;

            }

            //std::cout << "width_to_check" << width_to_check << std::endl;

            if (dy < 0)
            {
                // node_pos on the top
                height_to_check = node->nodeGeometry().boundingRect().height() + 10;
            }
            else
            {
                height_to_check = other_node->nodeGeometry().boundingRect().height() + 10;
            }

            //std::cout << "height_to_check" << height_to_check << std::endl;

            if (qAbs(dy) > (height_to_check) || qAbs(dx) > (width_to_check) )
            {
                xvel = 0;
                yvel = 0;
            }

            QPointF newPos = scene->getNodePosition(*node) + QPointF(xvel, yvel);
            scene->setNodePosition(*node,newPos);
        }
    }
}







void NodeReorder(QtNodes::FlowScene &scene)
{
//return;
  //   qDebug() << "--------------------------";
    std::vector<QtNodes::Node*> roots = findRoots(scene);
    std::map<int, std::vector<QtNodes::Node*>> nodes_by_level;

    QPointF cursor(10,10);

    for (QtNodes::Node* node: roots)
    {
        NodeReorderRecursive(scene, *node, cursor, 0, nodes_by_level);
    }

    double right   = 0;
    double bottom  = 0;

    for (auto& it: scene.nodes() )
    {
        QtNodes::Node* node = it.second.get();
        node->nodeGeometry().recalculateSize();
        QPointF pos = scene.getNodePosition(*node) ;
        QSizeF rect =  scene.getNodeSize(*node);

        right  = std::max( right,  pos.x() + rect.width() );
        bottom = std::max( bottom, pos.y() + rect.height() );
    }

    scene.setSceneRect(-30, -30, right + 60, bottom + 60);
}


void SubtreeReorder(QtNodes::FlowScene &scene, QtNodes::Node &root_node)
{
    std::cout << "--------------------------" << std::endl;
    std::map<int, std::vector<QtNodes::Node*>> nodes_by_level;

    QPointF cursor(10,10);

    std::vector<QtNodes::Node*> children = getChildren(scene, root_node);



    for (QtNodes::Node* node: children)
    {
        SubtreeReorderRecursive(scene, *node, root_node, cursor, 0, nodes_by_level);
    }

    double right   = 0;
    double bottom  = 0;

    for (auto& it: scene.nodes() )
    {
        QtNodes::Node* node = it.second.get();
        node->nodeGeometry().recalculateSize();
        QPointF pos = scene.getNodePosition(*node) ;
        QSizeF rect =  scene.getNodeSize(*node);

        right  = std::max( right,  pos.x() + rect.width() );
        bottom = std::max( bottom, pos.y() + rect.height() );
    }

    scene.setSceneRect(-30, -30, right + 60, bottom + 60);
}


BT::TreeNode* getBTObject(QtNodes::FlowScene &scene, QtNodes::Node &node, lua_State* lua_state )
{

    int bt_type = node.nodeDataModel()->BTType();
    //std::cout << "The node is :" << bt_type << std::endl;

    switch (bt_type) {
    case QtNodes::LUAACTION:
    {

        std::string filename = ((LuaNodeModel*)node.nodeDataModel())->type().toStdString();
        BT::LuaActionNode* bt_node = new BT::LuaActionNode(filename,filename, lua_state);
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    case QtNodes::LUACONDITION:
    {
        std::string filename = ((LuaNodeModel*)node.nodeDataModel())->type().toStdString();
        BT::LuaConditionNode* bt_node = new BT::LuaConditionNode(filename,filename,lua_state);
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    case QtNodes::YARPACTION:
    {
        std::string server_name = ((YARPNodeModel*)node.nodeDataModel())->type().toStdString();

        BT::YARPActionNode* bt_node = new BT::YARPActionNode(server_name+"BTAction",server_name);
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    case QtNodes::YARPCONDITION:
    {
        std::string server_name = ((YARPNodeModel*)node.nodeDataModel())->type().toStdString();
        BT::YARPConditionNode* bt_node = new BT::YARPConditionNode(server_name+"BTCondition",server_name);
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    case QtNodes::SEQUENCE:
    {
        BT::SequenceNode* bt_node = new BT::SequenceNode("Sequence");

        std::vector<QtNodes::Node*> children = getChildren(scene, node );

        for(int i = 0; i < children.size(); i++)

        {
            bt_node->AddChild(getBTObject(scene,*children[i],lua_state));
        }
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    case QtNodes::SELECTOR:
    {
        BT::FallbackNode* bt_node = new BT::FallbackNode("Fallback");


        std::vector<QtNodes::Node*> children = getChildren(scene, node );

        for(int i = 0; i < children.size(); i++)

        {
            bt_node->AddChild(getBTObject(scene,*children[i],lua_state));
        }
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    case QtNodes::SEQUENCESTAR:
    {
        BT::SequenceNodeWithMemory* bt_node = new BT::SequenceNodeWithMemory("SequenceWithMemory");

        std::vector<QtNodes::Node*> children = getChildren(scene, node );

        for(int i = 0; i < children.size(); i++)

        {
            bt_node->AddChild(getBTObject(scene,*children[i],lua_state));
        }
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    case QtNodes::SELECTORSTAR:
    {
        BT::FallbackNodeWithMemory* bt_node = new BT::FallbackNodeWithMemory("FallbackWithMemory");
        std::vector<QtNodes::Node*> children = getChildren(scene, node );

        for(int i = 0; i < children.size(); i++)

        {
            bt_node->AddChild(getBTObject(scene,*children[i],lua_state));
        }
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    case QtNodes::ROOT:
    {
        BT::RootNode* bt_node = new BT::RootNode();
        std::vector<QtNodes::Node*> children = getChildren(scene, node );

        for(int i = 0; i < children.size(); i++)
        {
            bt_node->AddChild(getBTObject(scene,*children[i],lua_state));
        }
        node.linkBTNode(bt_node);
        return bt_node;
        break;
    }
    default:
    {
        std::cout << "The node is something else:" << bt_type << std::endl;
        break;
    }
    }


}

std::mutex mode_mutex;
int mode_;

void setMode(int mode)
{
    std::cout << "Setting mode: " << mode << std::endl;
     std::lock_guard<std::mutex> lock(mode_mutex);
    mode_ = mode;
}

int getMode()
{
    std::lock_guard<std::mutex> lock(mode_mutex);
    return mode_;
}



static int lua_get_mode(lua_State* L)
{
    int mode = getMode();
    lua_pushnumber(L, mode);

    return 1; //number of returning values
}

static int lua_is_halted(lua_State* L)
{
    int mode = getMode();
    lua_pushboolean(L, mode == 0);
    return 1; //number of returning values
}

void runTree(QtNodes::FlowScene* scene)
{


    QtNodes::Node* root = BTRoot(scene);

    lua_State *lua_state;
    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);

    /* register our function */
//    lua_register(lua_state, "is_halted", lua_is_halted);

    lua_createtable(lua_state, 1, 0);

    QtNodes::Node* lua_preamble = LuaPreamble(scene);

    if(lua_preamble != NULL)
    {
        //has a preamble, execute this before the tree
        RunPreamble(lua_state, (LuaPreambleNodeModel*)lua_preamble->nodeDataModel());
    }

    BT::TreeNode* bt_root = getBTObject(*scene, *root, lua_state);

    while (getMode() == 1)
    {
        //std::cout <<"Ticking the root node !"<< std::endl;

        // Ticking the root node
        bt_root->Tick();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    }

    std::cout << "Finalizing the BT" << std::endl;
    //bt_root->Halt();
    bt_root->Finalize();
    std::cout << "Closing the Lua state" << std::endl;
    lua_close(lua_state);

}

bool is_BT_valid(QtNodes::FlowScene* scene)
{

    std::vector<QtNodes::Node*> roots = findRoots( *scene );
    bool valid_root = false;
    for(int i = 0; i < roots.size(); i++)

    {
       valid_root = valid_root || dynamic_cast<RootNodeModel*>(roots.front()->nodeDataModel());
    }
    return valid_root ;
}

bool has_root(QtNodes::FlowScene* scene)
{
    for(QtNodes::Node* root : findRoots( *scene ))
    {
       if(dynamic_cast<RootNodeModel*>(root->nodeDataModel()))
       {
           return true;
       }
    }
    return false ;
}


QtNodes::Node* BTRoot(QtNodes::FlowScene* scene)
{
    for(QtNodes::Node* root : findRoots( *scene ))
    {
       if(dynamic_cast<RootNodeModel*>(root->nodeDataModel()))
       {
           return root;
       }
    }

    return NULL ;
}


bool has_yarp(QtNodes::FlowScene* scene)
{
    for(auto&it : scene->nodes())
    {
        QtNodes::Node* node = it.second.get();
       if(dynamic_cast<YARPNodeModel*>(node->nodeDataModel()))
       {
           return true;
       }
    }
    return false ;
}


bool has_lua_preable(QtNodes::FlowScene* scene)
{
    for(auto &it : scene->nodes())
    {
        QtNodes::Node* node = it.second.get();
       if(dynamic_cast<LuaPreambleNodeModel*>(node->nodeDataModel()))
       {
           return true;
       }
    }
    return false ;
}


QtNodes::Node* LuaPreamble(QtNodes::FlowScene* scene)
{
    for(auto &it : scene->nodes())
    {
        QtNodes::Node* node = it.second.get();
       if(dynamic_cast<LuaPreambleNodeModel*>(node->nodeDataModel()))
       {
           return node;
       }
    }
    return NULL ;
}


void RunPreamble(lua_State *lua_state, LuaPreambleNodeModel *lua_preamble_node)
{
    lua_State *my_lua_state = lua_state;
    std::string filename = lua_preamble_node->type().toStdString();
    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { NULL, NULL}
    };

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(my_lua_state);
        lua_settop(my_lua_state, 0);
    }
    // run the Lua script
    luaL_dofile(my_lua_state, filename.c_str());
}

