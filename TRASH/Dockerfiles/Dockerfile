FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/catchorg/Catch2.git /opt/Catch2
#RUN mkdir /opt/Catch2/build && cd /opt/Catch2/build && cmake .. && make && make install

WORKDIR /nwtest

COPY . /nwtest














# Set up the build environment
RUN mkdir build

# Configure and build Catch2
RUN cd /opt/Catch2 && cmake -Bbuild -H. && cmake --build build/ --target install

# Set the include directory for Catch2
ENV CATCH2_INCLUDE_DIR /opt/Catch2/single_include

# Set up the build environment for your project
RUN cd /nwtest/build && cmake ..

# Build the main program
RUN cd /nwtest/build && make myprogram














#RUN mkdir build && cd build && cmake ..

#RUN cd build && make

#RUN g++ -o Needleman-Wunsch Needleman-Wunsch.cpp

#RUN chmod +x Needleman-Wunsch

CMD ["bash", "-c", "cd build && ctest --output-on-failiure"]