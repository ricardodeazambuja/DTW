
import numpy
import ctypes

DTW=ctypes.CDLL("/usr/local/lib/dtw_python.so")

# void generates_distances(int len_x, int len_y, int dim, float *distances, float *x, float *y)
generates_distances = DTW.generates_distances
generates_distances.restype = None
generates_distances.argtypes = [
    ctypes.c_int32,
    ctypes.c_int32,
    ctypes.c_int32,
    numpy.ctypeslib.ndpointer(dtype=numpy.float32, flags='ALIGNED,C_CONTIGUOUS'),
    numpy.ctypeslib.ndpointer(dtype=numpy.float32, flags='ALIGNED,C_CONTIGUOUS'),
    numpy.ctypeslib.ndpointer(dtype=numpy.float32, flags='ALIGNED,C_CONTIGUOUS')]

def distances_matrix(x,y):

    assert len(x.shape)==len(y.shape), "Inputs must have the same number of columns"

    if len(x.shape)==1:
        dim = ctypes.c_int32(1)
    else:
        dim = ctypes.c_int32(x.shape[1])

    len_x = ctypes.c_int32(x.shape[0])
    len_y = ctypes.c_int32(y.shape[0])

    distances = numpy.empty((x.shape[0],y.shape[0]),dtype=numpy.float32)


    generates_distances(len_x, len_y, dim, distances, x.astype(dtype=numpy.float32), y.astype(dtype=numpy.float32))

    return distances#.reshape((x.shape[0],y.shape[0]))

# void generates_accumulated_cost(int len_x, int len_y, float *accumulated_cost, float *distances)
generates_accumulated_cost = DTW.generates_accumulated_cost
generates_accumulated_cost.restype = None
generates_accumulated_cost.argtypes = [
    ctypes.c_int32,
    ctypes.c_int32,
    numpy.ctypeslib.ndpointer(dtype=numpy.float32, flags='ALIGNED,C_CONTIGUOUS'),
    numpy.ctypeslib.ndpointer(dtype=numpy.float32, flags='ALIGNED,C_CONTIGUOUS')]

def accumulated_cost_matrix(x,y,distances):
    len_x = ctypes.c_int32(x.shape[0])
    len_y = ctypes.c_int32(y.shape[0])
    accumulated_cost = numpy.empty((x.shape[0],y.shape[0]),dtype=numpy.float32)

    generates_accumulated_cost(len_x, len_y, accumulated_cost, distances)

    return accumulated_cost

# float path_cost(int len_x, int len_y, float *accumulated_cost, float *distances)
path_cost = DTW.path_cost
path_cost.restype = ctypes.c_float
path_cost.argtypes = [
    ctypes.c_int32,
    ctypes.c_int32,
    numpy.ctypeslib.ndpointer(dtype=numpy.float32, flags='ALIGNED,C_CONTIGUOUS'),
    numpy.ctypeslib.ndpointer(dtype=numpy.float32, flags='ALIGNED,C_CONTIGUOUS')]

# int returns_path_length()
returns_path_length = DTW.returns_path_length
returns_path_length.restype = ctypes.c_int32
returns_path_length.argtypes = []

# void returns_path(int *output, int size)
returns_path = DTW.returns_path
returns_path.restype = None
returns_path.argtypes = [
    numpy.ctypeslib.ndpointer(dtype=numpy.int32, flags='ALIGNED,C_CONTIGUOUS'),
    ctypes.c_int32]


def path_cost_calculation(x,y,distances,accumulated_cost):
    len_x = ctypes.c_int32(x.shape[0])
    len_y = ctypes.c_int32(y.shape[0])

    cost = path_cost(len_x, len_y, accumulated_cost, distances)

    path_length = returns_path_length()

    path = numpy.empty((path_length,2),dtype=numpy.int32)

    returns_path(path, path_length)

    return path,cost
