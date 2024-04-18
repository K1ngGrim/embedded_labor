//
// Created by Florian Kaiser on 17.04.24.
//

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <ctime>
#include <cstring>
#include <sstream>

clock_t start_t, end_t;

struct RegisterInfo {
    int reg1;
    int reg2;
};

RegisterInfo infos[24] ={
        {2, 6},
        {3, 7},
        {4, 8},
        {5, 9},
        {1,9},
        {2, 10},
        {1, 8},
        {2, 9},
        {3, 10},
        {2, 3},
        {3, 4},
        {5, 6},
        {6, 7},
        {7, 8},
        {8, 9},
        {9, 10},
        {1, 4},
        {2, 5},
        {3, 6},
        {4, 7},
        {5, 8},
        {6, 9},
        {1, 3},
        {4, 6}
};

int chip_sequences[24][1023];
int sat_sequence[2046];

void generateSequence(int id) {
    RegisterInfo info = infos[id-1];

    std::bitset<10> top{0b1111111111};
    std::bitset<10> bot{0b1111111111};

    for(int i = 0; i<1023; i++) {
        int val_top = top[9];
        auto new_top = top[2] xor top[9];
        top <<= 1;
        top[0] = new_top;

        auto val_bot = bot[info.reg1-1] xor bot[info.reg2-1];
        auto new_bot = bot[1] xor bot[2] xor bot[5] xor bot[7] xor bot[8] xor bot[9];
        bot <<= 1;
        bot[0] = new_bot;
        auto val = val_top xor val_bot;
        chip_sequences[id - 1][i] = (val == 0? -1 : 1);
    }

}


void stringInput(int sequence[])
{
    std::string input = "-2 0 0 -2 4 -2 -2 -4 2 0 0 0 -2 -2 2 0 0 -2 0 -2 -2 -2 0 -2 0 2 0 0 0 -2 -2 0 -4 -2 0 2 0 0 2 2 0 2 0 0 0 -2 -2 0 0 0 0 0 -2 0 2 2 0 -2 -2 2 2 0 2 2 -2 2 -2 -4 4 -2 0 2 4 -2 -2 0 2 0 -2 0 0 0 -2 -2 -2 0 0 -2 -2 -2 2 2 2 0 2 -2 0 -2 -2 -4 -2 0 0 2 2 -2 2 0 -2 0 2 2 2 -2 -2 -4 0 2 2 -2 -2 0 0 4 -2 -4 -4 0 0 0 0 2 2 2 -4 -2 2 0 0 -4 2 2 -4 -2 0 -2 2 0 2 0 -2 0 0 -2 -2 2 0 0 4 0 0 0 -4 0 2 0 4 0 -2 -4 0 -2 0 0 2 -2 0 0 2 4 0 -2 0 -2 2 -2 0 0 -2 2 2 2 2 0 -2 0 0 2 -2 2 0 -4 0 0 2 -2 -2 0 -2 0 0 0 0 -2 0 -2 2 -4 2 2 -4 -2 2 -4 2 2 -2 0 -2 2 -2 -2 0 -2 0 -2 0 2 4 0 4 0 0 0 0 -2 2 2 0 0 0 -2 -2 0 0 0 4 0 0 0 4 0 -2 0 0 0 -2 -4 2 0 -2 0 -2 2 2 2 -2 0 2 -2 -2 0 -2 0 2 0 2 -2 0 0 4 0 2 -2 2 -2 2 0 0 -4 0 0 -2 -2 0 -2 0 2 2 -2 0 0 4 -2 0 -2 0 -2 0 0 0 -2 0 0 4 -2 -2 -2 2 -2 2 -2 2 -2 -2 0 0 0 0 -2 0 0 0 0 0 4 -2 0 0 2 4 0 0 2 0 2 -2 -2 0 2 2 0 0 -4 2 2 0 -2 0 2 -2 2 4 0 0 0 0 0 -2 0 2 2 0 -4 -2 2 0 -2 0 0 0 2 0 -2 0 0 -2 2 0 2 0 0 -4 0 0 0 0 2 0 0 2 -2 -2 0 -2 0 -2 0 2 0 -2 2 0 -2 0 -2 2 2 0 0 0 -4 0 -2 0 0 2 0 0 0 -2 0 0 0 2 2 4 0 0 2 0 -4 0 2 2 0 -2 0 4 2 0 2 2 0 -2 0 -2 -2 -2 0 -2 2 0 0 0 0 0 0 -2 -2 -2 2 4 2 -2 -2 0 0 -2 4 -4 0 2 -2 0 0 2 -2 0 2 2 2 2 4 0 0 -2 2 0 0 -4 -2 0 -2 2 4 0 -2 -4 2 0 -2 0 -2 4 0 0 0 -2 0 2 4 2 2 0 2 2 0 2 -2 -2 2 -2 0 0 0 0 -2 2 0 0 -2 -4 0 0 2 4 2 0 2 -2 0 -2 2 0 -2 -4 2 2 2 -4 -4 4 0 0 -2 -2 -2 -4 0 2 -2 -2 0 -2 -4 -4 0 -2 -4 -2 -2 2 4 0 0 0 4 0 -2 0 -2 0 -4 4 -2 0 2 -4 -2 -4 0 0 0 0 -2 -4 2 2 4 -2 -2 2 0 2 4 0 0 0 2 0 0 2 0 -2 0 2 0 -2 4 0 0 0 0 2 -2 -2 0 0 0 0 -2 2 -4 4 2 2 -2 2 -2 -2 4 0 0 0 2 -4 2 0 -4 -2 2 2 -2 2 0 0 -2 -2 -4 0 0 0 2 2 0 -2 -2 0 2 2 -2 2 2 2 0 -2 0 0 0 0 2 0 -4 2 2 0 4 0 -2 4 2 2 2 2 -4 2 0 -2 4 0 2 0 0 2 0 0 0 2 2 -2 2 0 2 2 -2 0 2 0 0 -2 0 4 -2 0 0 0 0 2 2 -2 2 0 -2 -2 2 0 4 0 0 0 0 0 2 2 0 2 4 0 0 0 0 0 0 -2 2 0 -2 2 0 0 0 0 2 2 -2 2 0 0 2 2 2 0 0 2 2 0 -4 -2 0 -2 0 2 0 -2 0 0 -4 0 0 -2 0 0 0 0 0 2 4 0 0 0 0 -2 0 4 -2 0 0 0 0 0 2 0 0 0 0 0 2 0 2 0 0 -4 -4 2 2 4 4 -4 -2 0 -2 0 4 0 -4 0 0 -4 -2 2 2 0 0 0 0 0 0 -2 0 0 2 0 2 -2 -2 -2 0 -2 -2 -2 -2 0 0 2 -2 -4 0 -2 0 0 -2 0 2 -2 0 4 4 -2 -2 -2 -2 2 2 2 2 -2 4 2 0 -2 0 -4 0 2 0 0 -2 0 0 -2 -4 0 0 2 0 -2 0 0 2 2 0 0 2 0 2 -2 2 -2 2 0 2 0 -2 -4 -2 0 -2 2 -2 2 -2 0 -2 4 0 2 0 2 0 0 2 2 0 0 0 0 -2 0 0 0 2 2 0 0 -2 -4 -2 0 0 2 -2 2 -2 0 2 0 2 2 0 0 0 0 0 2 0 0 2 0 2 4 0 2 4 2 2 0 0 2 0 4 -2 -2 -2 2 2 4 2 0 4 -2 4 -2 ";
    std::istringstream iss(input);
    int num;
    for (int i = 0; i < 1023; ++i) {
        if(iss >> num) {
            sequence[i] = num;
            sequence[1023 + i] = num;
        }
    }
}

int dot_product_optimal(const int sequence[], const int chip_sequence[], int offset) {
    PROFILE_START("dot_product");
    int sum = 0;

    for(int i = 0; i < 1023; i++) {
        sum += sequence[offset + i] * chip_sequence[i];
    }

    PROFILE_STOP("dot_product");
    return sum;
}

void cross_correlation_optimal(const int sequence[], const int chip_sequence[], int result[], int threshold = 800) {

    for(int delta = 0; delta < 1023; delta++) {

        int sum = dot_product_optimal(sequence, chip_sequence, delta);

        if(sum > threshold) {
            result[0] = 1;
            result[1] = delta;
            return;
        }else if(sum < -threshold) {
            result[0] = 1;
            result[1] = delta;
            return;
        }
    }
}

void test_optimal() {
    PROFILE_START("total");
    for(int i = 0; i <24; i++) {
        int result[] = {-1, -1};
        PROFILE_START("cross_crocko");
        cross_correlation_optimal(sat_sequence, chip_sequences[i], result);
        if(!(result[0] == -1 && result[1] == -1)) {
            printf("Satellite %d has sent bit %d (delta %d)\n", i, result[0], result[1]);
        PROFILE_STOP("cross_crocko");

    }
    PROFILE_STOP("total");
}

int main() {
    stringInput(sat_sequence);

    for (int i = 0; i < 24; ++i) {
        generateSequence(i+1);
    }

    PROFILE_RUN_ALL(1000, 100,
                    test_optimal();
    );

}