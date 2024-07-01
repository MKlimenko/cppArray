#pragma once

#include "../common.hpp"

void Constructor(mxArray** plhs, int nrhs, const mxArray** prhs) {
    if (nrhs != 2) {
        mexErrMsgTxt("Constructor requires one input argument.");
    }
    objects.push_back(std::make_shared<cppArray>(prhs[1]));
    plhs[0] = mxCreateDoubleScalar(objects.size() - 1);
}
