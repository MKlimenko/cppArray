#pragma once

#include "common.hpp"
#include "src/cppArray.hpp"
#include "mex_functions/constructor.hpp"
#include "mex_functions/deleter.hpp"
#include "mex_functions/gather.hpp"
#include "mex_functions/plus.hpp"

std::map<std::string, std::function<void(mxArray**, int, const mxArray**)>> function_map {
    {"new", Constructor},
    {"delete", Deleter},
    {"gather", Gather},
    {"plus", Plus},
};

void mexFunction(int nlhs, mxArray** plhs, int nrhs, const mxArray** prhs) {
    std::string command = mxArrayToString(prhs[0]);

    auto function = function_map.find(command);
    if (function == function_map.end()) {
        mexErrMsgTxt("Unknown command.");
        return;
    }
    function->second(plhs, nrhs, prhs);
}
