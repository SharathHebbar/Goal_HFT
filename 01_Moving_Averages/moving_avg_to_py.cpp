#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

// -----------------------------------
// Moving Average Function
// -----------------------------------

py::array_t<double> moving_average(
    py::array_t<double> input,
    int window
) {
    auto buf = input.request();

    double* ptr = static_cast<double*>(buf.ptr);

    size_t N = buf.shape[0];

    auto result = py::array_t<double>(N);

    auto result_buf = result.request();

    double* out = static_cast<double*>(result_buf.ptr);

    double sum = 0.0;

    for (size_t i = 0; i < N; ++i) {

        sum += ptr[i];

        if (i >= window) {
            sum -= ptr[i - window];
        }

        if (i >= window - 1) {
            out[i] = sum / window;
        } else {
            out[i] = 0.0;
        }
    }

    return result;
}

// -----------------------------------
// Pybind Module
// -----------------------------------

PYBIND11_MODULE(cppma, m) {

    m.doc() = "C++ Moving Average Module";

    m.def(
        "moving_average",
        &moving_average,
        "Compute moving average"
    );
}