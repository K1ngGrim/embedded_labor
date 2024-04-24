#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <ctime>
#include <sstream>

clock_t start_t, end_t;

using namespace std;

struct RegisterInfo {
    int reg1;
    int reg2;
};

RegisterInfo infos[24] = {
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

std::vector<int> chip_sequences[24];
std::vector<int> sat_sequence;

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
        chip_sequences[id - 1].push_back(val == 0? -1 : 1);
    }

}

int dot_product(vector<int> &sequence, vector<int> &chip_sequence, int offset) {
    int sum = 0;
    for(int i = 0; i < 1023; i++) {
        sum += sequence[(i + offset) % 1023] * chip_sequence[i];
    }

    return sum;
}

pair<int, int> cross_correlation(vector<int> &sequence, vector<int> &chip_sequence, int threshold = 800) {

    int neg_peak = 0;
    int pos_peak = 0;
    int delta_delta = 0;

    for(int delta = 0; delta < 1023; delta++) {

        int sum = dot_product(sequence, chip_sequence, delta);
        //cout << sum << " ";

        if(sum > pos_peak) {
            pos_peak = sum;
            delta_delta = delta;

        }else
        if(sum < neg_peak) {
            neg_peak = sum;
            delta_delta = delta;
        }
    }

//threshold als hart codierte konstante
//macht es einen unterschied int oder const int
    if(pos_peak > threshold || neg_peak < -threshold) {
        if(pos_peak > -neg_peak) {
            return make_pair(1, delta_delta);
        }else if(pos_peak < -neg_peak) {
            return make_pair(0, delta_delta);
        }
    }

    return make_pair(-1, -1);

}

void read_sequence(vector<int>& sequence, const string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Fehler: Konnte die Datei nicht öffnen: " << filePath << std::endl;
        return;
    }

    int number;
    while (file >> number) {
        sequence.push_back(number);
    }

    file.close();
}

void test() {
    start_t = clock();
    for(int i = 0; i <24; i++) {
        pair<int, int> result = cross_correlation(sat_sequence, chip_sequences[i]);
    }
    end_t = clock();
    printf("This took %fs\n", ((double) (end_t - start_t)) / CLOCKS_PER_SEC);
}

int main(int argc, char* argv[]) {
    string path = "gps_sequence_7.txt";
    if (argc == 2) {
        path = argv[1];
    }

    for (int i = 0; i < 24; ++i) {
        generateSequence(i+1);
    }

    read_sequence(sat_sequence, path);

    test();
}


