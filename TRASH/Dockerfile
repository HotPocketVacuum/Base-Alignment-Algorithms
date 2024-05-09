FROM gcc:latest

RUN apt-get update
RUN apt-get install -y make
RUN apt-get install -y cmake git
RUN apt-get install build-essential

RUN git clone https://github.com/catchorg/Catch2.git && \
    cd Catch2 && \
    cmake -Bbuild -H. -DBUILD_TESTING=OFF && \
    cmake --build build/ --target install && \
    cd .. && \
    rm -rf Catch2

WORKDIR /nwp

RUN mkdir src
RUN mkdir test
RUN mkdir include

COPY nw.cpp /nwp/src/nw.cpp
COPY tests.cpp /nwp/test/tests.cpp

RUN echo "cmake_minimum_required(VERSION 3.10)" >> /nwp/CMakeLists.txt
RUN echo "project(nwp)" >> /nwp/CMakeLists.txt
RUN echo "find_package(Catch2 REQUIRED)" >> /nwp/CMakeLists.txt
#RUN echo "add_executable(nw src/nw.cpp)" >> /nwp/CMakeLists.txt
RUN echo "add_library(nwl src/nw.cpp)" >> /nwp/CMakeLists.txt
RUN echo "add_executable(tests test/tests.cpp)" >> /nwp/CMakeLists.txt
RUN echo "target_link_libraries(tests PRIVATE Catch2::Catch2WithMain PRIVATE nwl)" >> /nwp/CMakeLists.txt
RUN echo "include(CTest)" >> /nwp/CMakeLists.txt
RUN echo "include(Catch)" >> /nwp/CMakeLists.txt
RUN echo "catch_discover_tests(tests)" >> /nwp/CMakeLists.txt

RUN mkdir build
RUN cd build
RUN cmake /nwp
RUN cmake --build .

RUN ls tests > /tmp/tests_dir.txt
CMD cat /tmp/tests_dir.txt

#CMD ["./tests"]
