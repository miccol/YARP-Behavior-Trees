#include <python_condition_node.h>
#include <Python.h>

PyObject *python_state_condition_;
PyObject *python_tick_fn_condition_, *python_finalize_fn_condition_; //TODO Figure out why if It cannot find Python.h in the header (that why I need different name _condition)

BT::PythonConditionNode::PythonConditionNode(std::string name, std::string filename, BlackBoardCmd *blackboard_cmd) : BT::ConditionNode::ConditionNode(name)
{
    filename_ = filename;
    //std::string filename_wout_extension = filename;

    blackboard_cmd_ = blackboard_cmd;

    // Initializing the python api
    Py_Initialize();

    // PyUnicode_FromString wants the filename without extension .py
    std::string filename_wout_extension = filename.substr(0, filename.size() - 3);
    const char *cstr = filename_wout_extension.c_str();

    // creating python module. Needed to know from which script call the functions tick, halt, etc.
    PyObject *python_module = PyUnicode_FromString((char *)cstr);
    python_state_condition_ = PyImport_Import(python_module);

    // creating the PyObject related to the functions in the python script.
    PyObject *python_init_fn = PyObject_GetAttrString(python_state_condition_, (char *)"init");
    python_tick_fn_condition_ = PyObject_GetAttrString(python_state_condition_, (char *)"tick");
    python_finalize_fn_condition_ = PyObject_GetAttrString(python_state_condition_, (char *)"finalize");

    // calling the function init in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject_CallObject(python_init_fn, empty_args);
}

BT::ReturnStatus BT::PythonConditionNode::Tick()
{
    set_status(BT::RUNNING);
    // calling the function tick in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject *python_result = PyObject_CallObject(python_tick_fn_condition_, empty_args);

    // parsing the final return from the python script. The python script has to return True (Success) or False (Failure).
    // The Running status is taken for granted while running the script

    bool has_succeeded = PyObject_IsTrue(python_result);

    if (has_succeeded)
    {
        set_status(BT::SUCCESS);
        return BT::SUCCESS;
    }
    else
    {
        set_status(BT::FAILURE);
        return BT::FAILURE;
    }
}

void BT::PythonConditionNode::Finalize()
{
    // calling the function finalize in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject *python_result = PyObject_CallObject(python_finalize_fn_condition_, empty_args);

    // Finalizing the python api
    Py_Finalize();
}
