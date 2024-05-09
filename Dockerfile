FROM gcc:latest

COPY nw.cpp .
COPY tests.cpp .

RUN g++ -o tests tests.cpp && \
    ./tests