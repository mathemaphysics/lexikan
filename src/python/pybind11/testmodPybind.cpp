// pybind11
#include <pybind11/pybind11.h>

// Test function to export
int add(int i, int j)
{
    return i + j;
}

// A struct to test
struct Item
{
    Item(const std::string &name_, int value_) : name(name_), value{value_} {}
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
    void setValue(int value_) { value = value_; }
    int getValue() { return value; }

    std::string name;
    int value;
};

// Definition of the test module
PYBIND11_MODULE(testmod, module)
{
    module.def("add", &add, pybind11::arg("i") = 1, pybind11::arg("j") = 1, "A function which adds two numbers");
    module.attr("answer") = 23;
    pybind11::object result = pybind11::cast("string");
    module.attr("result") = result;

    // Definition of the Item class
    pybind11::class_<Item>(module, "Item")
        .def(pybind11::init<const std::string&, int>())
        .def("setName", &Item::setName)
        .def("getName", &Item::getName)
        .def("setValue", &Item::setValue)
        .def("getValue", &Item::getValue);
}
