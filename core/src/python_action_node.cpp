#include <python_action_node.h>
#include <Python.h>

PyObject *python_state_,*python_state_2;
PyObject *python_tick_fn_, *python_halt_fn_, *python_finalize_fn_; //TODO Figure out why if It cannot find Python.h in the header

static PyObject *
SetValueOnBlackboard(PyObject *self, PyObject *args)
{

    const char *key;

    int int_value;
    const char *str_value;
    float float_value;
    bool bool_value;


    if (PyArg_ParseTuple(args, "si", &key, &int_value))
    {
        std::cout << "*****************Setting Value int **********************" << key << int_value << std::endl;
    }
    else if (PyArg_ParseTuple(args, "sf", &key, &float_value))
    {
        std::cout << "*****************Setting Value float**********************" << key << float(float_value) << std::endl;
    }

    else if (PyArg_ParseTuple(args, "ss", &key, &str_value))
    {
        std::cout << "*****************Setting Value str **********************" << key << str_value << std::endl;
    }
        else if (PyArg_ParseTuple(args, "sp", &key, &bool_value))
    {
        std::cout << "*****************Setting Value bool **********************" << key << bool_value << std::endl;
    }
    else
    {
        std::cout << " Invalid Argument Passed " << std::endl;
        return NULL;
    }
    std::cout << " Returning " << std::endl;
     Py_DECREF(args);
     Py_DECREF(self);
//return PyLong_FromLong(1);
    Py_RETURN_NONE;
}

static PyObject *
GetValueOnBlackboard(PyObject *self, PyObject *args)
{
    int value = 1;

    std::cout << "*****************Getting Value**********************" << std::endl;
    return PyLong_FromLong(value);
}

static PyMethodDef BlackboardMethods[] = {
    {"set", SetValueOnBlackboard, METH_VARARGS,
     "Set Value on Blackboard."},
    {"get", GetValueOnBlackboard, METH_VARARGS,
     "Get Value on Blackboard."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef blackboard_module = {
    PyModuleDef_HEAD_INIT,
    "blackboard", /* name of module */
    NULL,         /* module documentation, may be NULL */
    -1,           /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    BlackboardMethods};

BT::PythonActionNode::PythonActionNode(std::string name, std::string filename, yarp::os::Property *blackboard) : BT::ActionNode::ActionNode(name)
{

    std::cout << "Node created" << std::endl;
    filename_ = filename;

    // PyUnicode_FromString wants the filename without extension .py
    std::string filename_wout_extension = filename.substr(0, filename.size() - 3);
    const char *cstr = filename_wout_extension.c_str();

    Py_Initialize();
    python_state_ = PyImport_ImportModule((char *)cstr);
    python_state_2 = PyImport_ImportModule((char *)cstr);

    if (!python_state_)
    {
        std::cout << "Unable to open script " << std::endl;
    }

    // creating the PyObjects related to the functions in the python script.

    PyObject *python_init_fn = PyObject_GetAttrString(python_state_2, (char *)"init");
    python_tick_fn_ = PyObject_GetAttrString(python_state_, (char *)"tick");
    python_halt_fn_ = PyObject_GetAttrString(python_state_, (char *)"halt");
    python_finalize_fn_ = PyObject_GetAttrString(python_state_, (char *)"finalize");

    std::cout << "Methods done" << std::endl;

    // calling the function init in the python script with empty argument

    // PyObject* topass = PyModule_Create(&spammodule);
    PyObject *topass = PyModule_Create(&blackboard_module);

    //PyObject* topass = PyFloat_FromDouble(2.0);
    //PyObject *empty_args = PyTuple_New(0);
    PyObject *args = PyTuple_Pack(1, topass);
    PyObject_CallObject(python_init_fn, args);
    Py_DECREF(args);

    //Py_DECREF(args);                // used for managing reference counts of Python objects.
    Py_DECREF(python_init_fn);      // used for managing reference counts of Python objects.
    Py_DECREF(python_tick_fn_);     // used for managing reference counts of Python objects.
    Py_DECREF(python_halt_fn_);     // used for managing reference counts of Python objects.
    Py_DECREF(python_finalize_fn_); // used for managing reference counts of Python objects.

    std::cout << "init done" << std::endl;
}

BT::PythonActionNode::~PythonActionNode()
{
    std::cout << "Destructor" << std::endl;
}

void BT::PythonActionNode::SomeFunction()
{
    std::cout << "HELLO" << std::endl;
}

BT::ReturnStatus BT::PythonActionNode::Tick()
{
    //    return BT::SUCCESS;
    set_status(BT::RUNNING);
    // calling the function tick in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    
    PyObject *python_result = PyObject_CallObject(python_tick_fn_, empty_args);
Py_DECREF(empty_args);

    std::cout << "I am fooling you" << std::endl;
    //Py_DECREF(empty_args);      // used for managing reference counts of Python objects.

    // parsing the final return from the python script. The python script has to return True (Success) or False (Failure).
    // The Running status is taken for granted while running the script

    bool has_succeeded = true; PyObject_IsTrue(python_result);
//Py_DECREF(python_result);

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

void BT::PythonActionNode::Halt()
{
    // calling the function finalize in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject_CallObject(python_halt_fn_, empty_args);

    Py_DECREF(empty_args);      // used for managing reference counts of Python objects.
}
void BT::PythonActionNode::Finalize()
{
    // calling the function finalize in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject_CallObject(python_finalize_fn_, empty_args);

    Py_DECREF(empty_args);          // used for managing reference counts of Python objects.

    // Finalizing the python api
    Py_Finalize();
}
