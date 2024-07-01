#pragma once

#include "../common.hpp"


void Gather(mxArray** plhs, int nrhs, const mxArray** prhs) {
    if (nrhs != 2) {
        mexErrMsgTxt("Gather requires one input argument.");
    }
    size_t id = static_cast<size_t>(mxGetScalar(prhs[1]));
    std::visit([&](const auto& data) {
        using data_type = std::remove_reference_t<decltype (data)>::value_type;
        auto data_enum = mxSINGLE_CLASS; // convert to type map
        if constexpr (std::is_same_v<data_type, float>) {
            data_enum = mxSINGLE_CLASS;
        }
        else if constexpr (std::is_same_v<data_type, double>) {
            data_enum = mxDOUBLE_CLASS;
        }
        else {
            static_assert(sizeof(data_type) == 0, "Unexpected data type");
        }
        plhs[0] = mxCreateUninitNumericMatrix(data.size(), 1, mxDOUBLE_CLASS, mxREAL);
        std::copy(data.begin(), data.end(), mxGetPr(plhs[0]));

    }, objects.at(id)->data);
}
