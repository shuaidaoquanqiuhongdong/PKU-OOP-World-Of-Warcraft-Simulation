#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Headquarter {
    private:
        int total_blood, current_index, total_warriors, warriors_counts[5], make_sequence[5];
        string color;
        bool is_stopped;
    public:
        Headquarter(string color_, int blood, int seq[]): color(color_), total_blood(blood) {
            current_index = 0, total_warriors = 0, is_stopped = false;
            for (int i = 0; i < 5; ++i) {
                warriors_counts[i] = 0;
                make_sequence[i] = seq[i];
            }
        }
        void produce(int time, int warriors_lifebar[], string warriors_names[]) {
            if (is_stopped) return;
            int count = 0;
            while (count < 5) {
                if (total_blood >= warriors_lifebar[make_sequence[current_index]]) {
                    total_blood -= warriors_lifebar[make_sequence[current_index]];
                    total_warriors += 1;
                    warriors_counts[make_sequence[current_index]] += 1;
                    print(warriors_names[make_sequence[current_index]], warriors_lifebar[make_sequence[current_index]], time);
                    current_index = (current_index + 1) % 5;  
                    return;                                      
                }
                else {
                    current_index = (current_index + 1) % 5;
                    count++;
                }
            }
            stop_print(time);
            is_stopped = true;
        }
        bool isStopped() {
            return is_stopped;
        }
        void print(string name, int lifebar, int time) {
            cout << setfill('0') << setw(3) << time << " " << color << " " << name << " " << total_warriors << " born with strength " << lifebar << "," << warriors_counts[make_sequence[current_index]] << " " << name << " in " << color << " headquarter" << endl;
        }
        void stop_print(int time) {
            cout << setfill('0') << setw(3) << time << " " << color << " headquarter stops making warriors" << endl;
        }
};

int main() {
    int n; cin >> n;
    string warriors_names[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
    int red_sequence[5] = {2, 3, 4, 1, 0}, blue_sequence[5] = {3, 0, 1, 2, 4};
    int warriors_lifebar[5];
    for (int i = 0; i < n; ++i) {
        int time = 0;
        int health; cin >> health;
        Headquarter redHQ("red", health, red_sequence), blueHQ("blue", health, blue_sequence);
        for (int j = 0; j < 5; ++j) {
            cin >> warriors_lifebar[j];
        }
        cout << "Case:" << i + 1 << endl;
        while(!redHQ.isStopped() || !blueHQ.isStopped()) {
            redHQ.produce(time, warriors_lifebar, warriors_names);
            blueHQ.produce(time, warriors_lifebar, warriors_names);
            time++;
        }
    }
}