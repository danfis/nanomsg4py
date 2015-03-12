#include <Python.h>
#include <nanomsg/nn.h>
#include <nanomsg/pair.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/pubsub.h>
#include <nanomsg/survey.h>
#include <nanomsg/pipeline.h>
#include <nanomsg/bus.h>

typedef struct {
    PyObject_HEAD
    int sock;
} sock_t;

static void sockDealloc(sock_t *sock)
{
}

static PyObject *sockNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    sock_t *self;
    self = (sock_t *)type->tp_alloc(type, 0);
    self->sock = -1;
    return (PyObject *)self;
}

static int sockInit(sock_t *self, PyObject *args, PyObject *kwds)
{
    int domain, protocol;

    if (!PyArg_ParseTuple(args, "ii", &domain, &protocol))
        return -1;
    self->sock = nn_socket(domain, protocol);
    if (self->sock == -1){
        PyErr_SetString(PyExc_RuntimeError, nn_strerror(errno));
        return -1;
    }
    return 0;
}

static PyMethodDef sock_methods[] = {
    /*
    {"name", (PyCFunction)Noddy_name, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    */
    {NULL}  /* Sentinel */
};

static PyTypeObject SocketType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "nanomsg2.Socket",             /*tp_name*/
    sizeof(sock_t),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)sockDealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    sock_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)sockInit,      /* tp_init */
    0,                         /* tp_alloc */
    sockNew,                 /* tp_new */
};

static PyMethodDef methods[] = {
    {NULL}  /* Sentinel */
};

#define CONST(m, name) \
    PyModule_AddIntConstant(m, #name, name)


#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initnanomsg2(void) 
{
    PyObject* m;

    SocketType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&SocketType) < 0)
        return;

    m = Py_InitModule3("nanomsg2", methods, "TODO");
    CONST(m, AF_SP);
    CONST(m, AF_SP_RAW);
    CONST(m, NN_PAIR);
    CONST(m, NN_REQ);
    CONST(m, NN_REP);
    CONST(m, NN_PUB);
    CONST(m, NN_SUB);
    CONST(m, NN_SURVEYOR);
    CONST(m, NN_RESPONDENT);
    CONST(m, NN_PUSH);
    CONST(m, NN_PULL);
    CONST(m, NN_BUS);


    Py_INCREF(&SocketType);
    PyModule_AddObject(m, "Socket", (PyObject *)&SocketType);
}
