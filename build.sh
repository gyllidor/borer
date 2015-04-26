
#! /bin/bash
cd ./build
cmake -DUNIT_TESTS:BOOL=ON -DVERBOSE_LOGGER:BOOL=ON -DCMAKE_BUILD_TYPE=debug ..
make -j8
cd -