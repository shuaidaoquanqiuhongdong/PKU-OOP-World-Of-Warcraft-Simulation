#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Warriors {
    protected:
        string hq_color, name;
        int id, lifebar;
    public:
        Warriors(string color, string name_, int id_, int lifebar_): hq_color(color), name(name_), id(id_), lifebar(lifebar_) {}
};

class Dragon: public Warriors {
    private:
        int weapon_type;
        double morale;
    public:
        Dragon(string color, string name_, int id_, int lifebar_, int hp_): Warriors(color, name_, id_, lifebar_), weapon_type(id_ % 3) {
            morale = (double)hp_ / lifebar;}
        void print_details() {
            string weapon[3] = {"sword", "bomb", "arrow"};
            cout << "It has a " << weapon[weapon_type] << ",and it's morale is " << fixed << setprecision(2) << morale << endl;
        }
};

class Ninja: public Warriors {
    private:
        int weapon_type;
    public:
        Ninja(string color, string name_, int id_, int lifebar_, int hp_): Warriors(color, name_, id_, lifebar_), weapon_type(id_ % 3) {}
        void print_details() {
            string weapon[3] = {"sword", "bomb", "arrow"};
            cout << "It has a " << weapon[weapon_type] << " and a " << weapon[(weapon_type + 1) % 3] << endl;
        }
};

class Iceman: public Warriors {
    private:
        int weapon_type;
    public:
        Iceman(string color, string name_, int id_, int lifebar_, int hp_): Warriors(color, name_, id_, lifebar_), weapon_type(id_ % 3) {}
        void print_details() {
            string weapon[3] = {"sword", "bomb", "arrow"};
            cout << "It has a " << weapon[weapon_type] << endl;
        }
};

class Lion: public Warriors {
    private:
        int loyalty;
    public:
        Lion(string color, string name_, int id_, int lifebar_, int hp_): Warriors(color, name_, id_, lifebar_), loyalty(hp_) {}
        void print_details() {
            cout << "It's loyalty is " << loyalty << endl;
        }
};

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
                    switch(make_sequence[current_index]) {
                        case 0: {
                            Dragon temp0(color, warriors_names[make_sequence[current_index]], total_warriors, warriors_lifebar[make_sequence[current_index]], total_blood);
                            temp0.print_details();
                            break;
                        }
                        case 1: {
                            Ninja temp1(color, warriors_names[make_sequence[current_index]], total_warriors, warriors_lifebar[make_sequence[current_index]], total_blood);
                            temp1.print_details();
                            break;
                        }
                        case 2: {
                            Iceman temp2(color, warriors_names[make_sequence[current_index]], total_warriors, warriors_lifebar[make_sequence[current_index]], total_blood);
                            temp2.print_details();
                            break;
                        }
                        case 3: {
                            Lion temp3(color, warriors_names[make_sequence[current_index]], total_warriors, warriors_lifebar[make_sequence[current_index]], total_blood);
                            temp3.print_details();
                            break;
                        }
                        default: break;
                    }
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