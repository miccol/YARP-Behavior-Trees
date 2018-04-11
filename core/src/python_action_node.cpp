#include <python_action_node.h>
#include <Python.h>

PyObject *python_state_;
PyObject *python_tick_fn_, *python_halt_fn_, *python_finalize_fn_; //TODO Figure out why if It cannot find Python.h in the header

// static PyObject *
// spam_system(PyObject *self, PyObject *args)
// {
//     std::cout << "Horray" << std::endl;
//     const char *command;
//     int sts;

//     if (!PyArg_ParseTuple(args, "s", &command))
//         return NULL;
//     sts = system(command);
//     return PyLong_FromLong(sts);
// }

// static PyMethodDef SpamMethods[] = {
//     {"system", spam_system, METH_VARARGS,
//      "Execute a shell command."},
//     {NULL, NULL, 0, NULL} /* Sentinel */
// };

// static struct PyModuleDef spammodule = {
//     PyModuleDef_HEAD_INIT,
//     "ActionPython", /* name of module */
//     NULL,           /* module documentation, may be NULL */
//     -1,             /* size of per-interpreter state of the module,
//                  or -1 if the module keeps state in global variables. */
//     SpamMethods};

// PyMODINIT_FUNC
// PyInit_spam(void)
// {
//     return PyModule_Create(&spammodule);
// }

BT::PythonActionNode::PythonActionNode(std::string name, std::string filename, yarp::os::Property *blackboard) : BT::ActionNode::ActionNode(name)
{
    filename_ = filename;
    //std::string filename_wout_extension = filename;

    // blackboard_cmd_ = blackboard_cmd;
    std::cout << "Reading value from BB" << std::endl;

    std::cout << "Value on BB of a is: " << blackboard->find("a").toString() << std::endl;

    Py_Initialize();

    // PyUnicode_FromString wants the filename without extension .py
    std::string filename_wout_extension = filename.substr(0, filename.size() - 3);
    const char *cstr = filename_wout_extension.c_str();
    //   PyObject *python_module = PyUnicode_FromString((char *)cstr);

    // std::cout << "Loading PyInit_spam" << std::endl;

    // PyImport_AppendInittab((char *)cstr, PyInit_spam);

    // std::cout << "Loaded PyInit_spam" << std::endl;

    // creating python module. Needed to know from which script call the functions tick, halt, etc.
    //python_state_ = PyImport_Import(python_module);

    // Initializing the python api
    // Py_Initialize();
    std::cout << "Py Initialized" << std::endl;

    python_state_ = PyImport_ImportModule((char *)cstr);
    std::cout << "Module imported" << std::endl;

    //  PyObject* (*fpFunc)(PyObject*,PyObject*) = turkey_do_something;
    //  PyMethodDef methd = {"methd",fpFunc,METH_VARARGS,"A new function"};
    //  PyObject* namef = PyUnicode_FromString(methd.ml_name);
    // PyObject* pyfoo = PyCFunction_NewEx(&methd,NULL,namef);
    //     python_state_ = PyImport_ImportModuleEx((char *)cstr, pyfoo, NULL,NULL);

    // PyObject* (*fpFunc)(PyObject*,PyObject*) = turkey_do_something;
    // PyMethodDef methd = {"methd",fpFunc,METH_VARARGS,"A new function"};
    // PyObject* name2 = PyUnicode_FromString((char *)cstr);
    // python_state_ = PyCFunction_NewEx(&methd,NULL,name2);
    //Py_DECREF(name2);

    // creating the PyObjects related to the functions in the python script.

    PyObject *python_init_fn = PyObject_GetAttrString(python_state_, (char *)"init");
    python_tick_fn_ = PyObject_GetAttrString(python_state_, (char *)"tick");
    python_halt_fn_ = PyObject_GetAttrString(python_state_, (char *)"halt");
    python_finalize_fn_ = PyObject_GetAttrString(python_state_, (char *)"finalize");

    std::cout << "Methods done" << std::endl;

    // calling the function init in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject_CallObject(python_init_fn, empty_args);
    std::cout << "init done" << std::endl;
}

BT::ReturnStatus BT::PythonActionNode::Tick()
{
    set_status(BT::RUNNING);
    // calling the function tick in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject *python_result = PyObject_CallObject(python_tick_fn_, empty_args);

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

void BT::PythonActionNode::Halt()
{
    // calling the function finalize in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject *python_result = PyObject_CallObject(python_halt_fn_, empty_args);
}
void BT::PythonActionNode::Finalize()
{
    // calling the function finalize in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject *python_result = PyObject_CallObject(python_finalize_fn_, empty_args);

    // Finalizing the python api
    Py_Finalize();
}
