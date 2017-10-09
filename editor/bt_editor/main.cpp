
#include <QApplication>
#include <node_editor/NodeStyle>
#include <node_editor/FlowViewStyle>
#include <node_editor/ConnectionStyle>

#include "ControlNodeModel.hpp"
#include "mainwindow.h"
#include "ActionNodeModel.hpp"
#include "RootNodeModel.hpp"
#include "NodeFactory.hpp"

#include <node_editor/DataModelRegistry>
#include <yarp/os/Network.h>
#include <yarp/os/ResourceFinder.h>
using QtNodes::DataModelRegistry;
using QtNodes::FlowViewStyle;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;

int
main(int argc, char *argv[])
{


//    // YARP setting
//    yarp::os::Network yarp;
//    if (!yarp::os::Network::checkNetwork(5.0))
//    {
//        std::cout << " YARP server not available!";
//        return EXIT_FAILURE;
//    }

  QApplication app(argc, argv);

  MainWindow win;
  win.show();

  return app.exec();
}
