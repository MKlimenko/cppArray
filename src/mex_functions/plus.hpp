#pragma once

#include "../common.hpp"

void Plus(mxArray** plhs, int nrhs, const mxArray** prhs) {
    if (nrhs != 3) {
        mexErrMsgTxt("Plus requires two input arguments");
    }
    auto id1 = static_cast<std::size_t>(mxGetScalar(prhs[1]));
    auto id2 = static_cast<std::size_t>(mxGetScalar(prhs[2]));

    auto result = std::make_shared<cppArray>(*objects.at(id1));
    const auto& vec_rhs = *objects.at(id2);

    std::visit([](auto& lhs, const auto& rhs) {
        if (lhs.size() != rhs.size())
            throw std::invalid_argument("Arrays must be of the same size");

        for (std::size_t i = 0; i < lhs.size(); ++i)
            lhs[i] += rhs[i];
        }, result->data, vec_rhs.data);

    objects.push_back(result);
    plhs[0] = mxCreateDoubleScalar(objects.size() - 1);
}
