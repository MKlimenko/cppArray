classdef cppArray < handle
    properties (Access = private)
        % This will hold a pointer to the C++ object
        cppHandle
        dims
    end
    
    methods
        function obj = cppArray(data)
            % Constructor: Create the C++ object and initialize with data
            obj.cppHandle = cppArrayMex('new', data);
            obj.dims = size(data);
        end
        
        function delete(obj)
            % Destructor: Delete the C++ object
            cppArrayMex('delete', obj.cppHandle);
        end
        
        function disp(obj)
            % Display the array
            data = cppArrayMex('getData', obj.cppHandle);
            disp(data);
        end
        
        function result = plus(obj, other)
            % Overload the plus operator for element-wise addition
            resultHandle = cppArrayMex('plus', obj.cppHandle, other.cppHandle);
            result = cppArray([]);
            result.cppHandle = resultHandle;
            result.dims = obj.dims; % Assume the dimensions remain the same
        end
        
        function data = getData(obj)
            % Get the array data
            data = cppArrayMex('getData', obj.cppHandle);
        end

        function s = size(obj, dim)
            % Return the size of the array
            if nargin == 1
                s = obj.dims;
            else
                s = obj.dims(dim);
            end
        end
        
        function l = length(obj)
            % Return the length of the array
            l = max(obj.dims);
        end
    end
end
