#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <andres/partition-comparison.hxx>

namespace py = pybind11;

typedef andres::RandError<> RandError;
typedef andres::VariationOfInformation<> VariationOfInformation;


// custom constructors for easier usage in python

RandError rand_error
(
    const py::array_t<size_t>& labels0,
    const py::array_t<size_t>& labels1,
    bool ignoreDefaultLabel = true
) 
{
    if (labels0.size() != labels1.size())
        throw std::runtime_error("size of inputs not equal.");

    return RandError(labels0.data(), labels0.data() + labels0.size(), labels1.data(), ignoreDefaultLabel);
}

VariationOfInformation variation_of_information
(
    const py::array_t<size_t>& labels0,
    const py::array_t<size_t>& labels1,
    bool ignoreDefaultLabel = true
) 
{
    if (labels0.size() != labels1.size())
        throw std::runtime_error("size of inputs not equal.");

    return VariationOfInformation(labels0.data(), labels0.data() + labels0.size(), labels1.data(), ignoreDefaultLabel);
}


// wrapping cpp classes to use in python
PYBIND11_MODULE(partition_comparison, m)
{
    m.doc() = "pybind11 partition_comparison module";

    py::class_<RandError>(m, "RandError")
        .def(py::init(&rand_error), "Constructor", py::arg("labels0"), py::arg("labels1"), py::arg("ignoreDefaultLabel") = true)
        .def("elements", &RandError::elements)
        .def("pairs", &RandError::pairs)
        .def("trueJoins", &RandError::trueJoins)
        .def("trueCuts", &RandError::trueCuts)
        .def("falseJoins", &RandError::falseJoins)
        .def("falseCuts", &RandError::falseCuts)
        .def("joinsInPrediction", &RandError::joinsInPrediction)
        .def("cutsInPrediction", &RandError::cutsInPrediction)
        .def("joinsInTruth", &RandError::joinsInTruth)
        .def("cutsInTruth", &RandError::cutsInTruth)
        .def("recallOfCuts", &RandError::recallOfCuts)
        .def("precisionOfCuts", &RandError::precisionOfCuts)
        .def("recallOfJoins", &RandError::recallOfJoins)
        .def("precisionOfJoins", &RandError::precisionOfJoins)
        .def("error", &RandError::error)
        .def("index", &RandError::index);

    py::class_<VariationOfInformation>(m, "VariationOfInformation")
        .def(py::init(&variation_of_information), "Constructor", py::arg("labels0"), py::arg("labels1"), py::arg("ignoreDefaultLabel") = true)
        .def("value", &VariationOfInformation::value)
        .def("valueFalseCut", &VariationOfInformation::valueFalseCut)
        .def("valueFalseJoin", &VariationOfInformation::valueFalseJoin);
}