FROM gcc:latest

WORKDIR /nwtest

COPY ./Needleman-Wunsch.cpp .
COPY ./s1.txt .
COPY ./s2.txt .
COPY Needleman-Wunsch.cpp .
COPY s1.txt .
COPY s2.txt .
COPY ./* .
COPY . .

RUN g++ -o Needleman-Wunsch Needleman-Wunsch.cpp

RUN chmod +x Needleman-Wunsch

CMD ["./Needleman-Wunsch", "s1.txt", "s2.txt", "1", "-1", "-2"]