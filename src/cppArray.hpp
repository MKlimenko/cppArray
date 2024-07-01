#pragma once

#include "common.hpp"

struct cppArray {
    std::variant<std::vector<double>, std::vector<float>> data;

    template <typename T>
    auto GetVector(T* ptr, std::size_t num_elements) {
        return std::vector<T>(ptr, ptr + num_elements);
    }

    cppArray(const mxArray* src) {
        if (!mxIsDouble(src) && !mxIsSingle(src)) {
            throw std::invalid_argument("Input must be a double or a float array.");
        }
        size_t numElements = mxGetNumberOfElements(src);
        if (mxIsDouble(src))
            data = GetVector(reinterpret_cast<double*>(mxGetData(src)), numElements);
        else if (mxIsSingle(src))
            data = GetVector(reinterpret_cast<float*>(mxGetData(src)), numElements);
    }

    cppArray(const cppArray &other) : data(other.data) {}
};

static inline std::vector<std::shared_ptr<cppArray>> objects;
