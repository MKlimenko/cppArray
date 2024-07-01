function testCppArray()
    % Test the cppArray class functionality
    
    % Test construction
    disp('Testing construction...');
    try
        A = cppArray(rand(5, 1));
        disp('Construction passed.');
    catch e
        disp('Construction failed.');
        disp(e.message);
    end
    
    % Test display
    disp('Testing display...');
    try
        disp('Array A:');
        disp(A);
    catch e
        disp('Display failed.');
        disp(e.message);
    end
    
    % Test element-wise addition
    disp('Testing element-wise addition...');
    try
        B = cppArray(rand(5, 1));
        C = A + B;
        disp('Addition result:');
        disp(C);
        disp('Addition passed.');
    catch e
        disp('Addition failed.');
        disp(e.message);
    end
    
    % Test gather method
    disp('Testing gather method...');
    try
        data = C.gather();
        disp('Data from C:');
        disp(data);
        disp('gather passed.');
    catch e
        disp('gather failed.');
        disp(e.message);
    end
    
    % Test size mismatch error
    disp('Testing size mismatch error...');
    try
        D = cppArray(rand(4, 1));
        E = A + D; % This should raise an error
        disp('Size mismatch test failed.');
    catch e
        disp('Size mismatch test passed.');
        disp(e.message);
    end
    
    % Test deletion
    disp('Testing deletion...');
    try
        clear A B C D E;
        disp('Deletion passed.');
    catch e
        disp('Deletion failed.');
        disp(e.message);
    end
    
    disp('All tests completed.');
end
