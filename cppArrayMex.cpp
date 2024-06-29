#include "mex.h"
#include "matrix.h"
#include <vector>
#include <memory>
#include <stdexcept>

class cppArray {
public:
    cppArray(const mxArray *data) {
        if (!mxIsDouble(data)) {
            throw std::invalid_argument("Input must be a double array.");
        }
        size_t numElements = mxGetNumberOfElements(data);
        array_.assign(mxGetPr(data), mxGetPr(data) + numElements);
    }

    std::vector<double> getData() const {
        return array_;
    }

    cppArray operator+(const cppArray &other) const {
        if (array_.size() != other.array_.size()) {
            throw std::invalid_argument("Arrays must be of the same size.");
        }
        cppArray result(*this);
        for (size_t i = 0; i < array_.size(); ++i) {
            result.array_[i] += other.array_[i];
        }
        return result;
    }

private:
    std::vector<double> array_;
};

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    static std::vector<std::shared_ptr<cppArray>> objects;
    std::string command = mxArrayToString(prhs[0]);

    if (command == "new") {
        if (nrhs != 2) {
            mexErrMsgTxt("Constructor requires one input argument.");
        }
        objects.push_back(std::make_shared<cppArray>(prhs[1]));
        plhs[0] = mxCreateDoubleScalar(objects.size() - 1);
    } else if (command == "delete") {
        if (nrhs != 2) {
            mexErrMsgTxt("Delete requires one input argument.");
        }
        size_t id = static_cast<size_t>(mxGetScalar(prhs[1]));
        objects.at(id) = nullptr;
    } else if (command == "getData") {
        if (nrhs != 2) {
            mexErrMsgTxt("getData requires one input argument.");
        }
        size_t id = static_cast<size_t>(mxGetScalar(prhs[1]));
        auto data = objects.at(id)->getData();
        plhs[0] = mxCreateDoubleMatrix(data.size(), 1, mxREAL);
        std::copy(data.begin(), data.end(), mxGetPr(plhs[0]));
    } else if (command == "plus") {
        if (nrhs != 3) {
            mexErrMsgTxt("plus requires two input arguments.");
        }
        size_t id1 = static_cast<size_t>(mxGetScalar(prhs[1]));
        size_t id2 = static_cast<size_t>(mxGetScalar(prhs[2]));
        auto result = std::make_shared<cppArray>(*objects.at(id1) + *objects.at(id2));
        objects.push_back(result);
        plhs[0] = mxCreateDoubleScalar(objects.size() - 1);
    } else {
        mexErrMsgTxt("Unknown command.");
    }
}
