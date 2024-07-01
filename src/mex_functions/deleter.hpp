#pragma once

#include "../common.hpp"

void Deleter(mxArray** plhs, int nrhs, const mxArray** prhs) {
    if (nrhs != 2) {
        mexErrMsgTxt("Delete requires one input argument.");
    }
    size_t id = static_cast<size_t>(mxGetScalar(prhs[1]));
    objects.at(id) = nullptr;
}
