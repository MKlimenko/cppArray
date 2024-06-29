classdef cppArray < handle
    properties (Access = private)
        % This will hold a pointer to the C++ object
        cppHandle
    end
    
    methods
        function obj = cppArray(data)
            % Constructor: Create the C++ object and initialize with data
            obj.cppHandle = cppArrayMex('new', data);
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
        end
        
        function data = getData(obj)
            % Get the array data
            data = cppArrayMex('getData', obj.cppHandle);
        end
    end
end
