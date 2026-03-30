#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Warriors {
    protected:
        int id, lifebar;
    public:
        Warriors(int id_, int lifebar_): id(id_), lifebar(lifebar_) {}
        virtual void print_details() = 0;
        virtual ~Warriors() {}
};

class Dragon: public Warriors {
    private:
        int weapon_type;
        double morale;
    public:
        Dragon(int id_, int lifebar_, int hp_): Warriors(id_, lifebar_), weapon_type(id_ % 3) {
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
        Ninja(int id_, int lifebar_, int hp_): Warriors(id_, lifebar_), weapon_type(id_ % 3) {}
        void print_details() {
            string weapon[3] = {"sword", "bomb", "arrow"};
            cout << "It has a " << weapon[weapon_type] << " and a " << weapon[(weapon_type + 1) % 3] << endl;
        }
};

class Iceman: public Warriors {
    private:
        int weapon_type;
    public:
        Iceman(int id_, int lifebar_, int hp_): Warriors(id_, lifebar_), weapon_type(id_ % 3) {}
        void print_details() {
            string weapon[3] = {"sword", "bomb", "arrow"};
            cout << "It has a " << weapon[weapon_type] << endl;
        }
};

class Lion: public Warriors {
    private:
        int loyalty;
    public:
        Lion(int id_, int lifebar_, int hp_): Warriors(id_, lifebar_), loyalty(hp_) {}
        void print_details() {
            cout << "It's loyalty is " << loyalty << endl;
        }
};

class Wolf: public Warriors {
    public:
        Wolf(int id_, int lifebar_, int hp_): Warriors(id_, lifebar_) {}
        void print_details() {}
};

class Headquarter {
    private:
        static string warriors_names[5];
        static int warriors_lifebar[5];
        int total_blood, current_index, total_warriors, warriors_counts[5], make_sequence[5], time;
        string color;
        bool is_stopped;
    public:
        Headquarter(string color_, int blood, int seq[]): color(color_), total_blood(blood) {
            current_index = 0, total_warriors = 0, is_stopped = false, time = 0;
            for (int i = 0; i < 5; ++i) {
                warriors_counts[i] = 0;
                make_sequence[i] = seq[i];
            }
        }
        static void set_lifebar(int lifebar[]) {
            for (int i = 0; i < 5; i++) {
                warriors_lifebar[i] = lifebar[i];
            }
        }
        void produce() {
            if (is_stopped) return;
            int count = 0;
            while (count < 5) {
                int warrior_type = make_sequence[current_index];
                if (total_blood >= warriors_lifebar[warrior_type]) {
                    total_blood -= warriors_lifebar[warrior_type];
                    total_warriors += 1;
                    warriors_counts[warrior_type] += 1;
                    print(warriors_names[warrior_type], warriors_lifebar[warrior_type]);
                    Warriors* ptr = NULL;
                    switch(warrior_type) {
                        case 0: {ptr = new Dragon(total_warriors, warriors_lifebar[warrior_type], total_blood); break;}
                        case 1: {ptr = new Ninja(total_warriors, warriors_lifebar[warrior_type], total_blood); break;}
                        case 2: {ptr = new Iceman(total_warriors, warriors_lifebar[warrior_type], total_blood); break;}
                        case 3: {ptr = new Lion(total_warriors, warriors_lifebar[warrior_type], total_blood); break;}
                        case 4: {ptr = new Wolf(total_warriors, warriors_lifebar[warrior_type], total_blood); break;}
                    }
                    if (ptr != NULL) {
                        ptr -> print_details();
                        delete ptr;
                    }
                    time++;
                    current_index = (current_index + 1) % 5;  
                    return;                                      
                }
                else {
                    current_index = (current_index + 1) % 5;
                    count++;
                }
            }
            stop_print();
            is_stopped = true;
        }
        bool isStopped() {
            return is_stopped;
        }
        void print(string name, int lifebar) {
            cout << setfill('0') << setw(3) << time << " " << color << " " << name << " " << total_warriors << " born with strength " << lifebar << "," << warriors_counts[make_sequence[current_index]] << " " << name << " in " << color << " headquarter" << endl;
        }
        void stop_print() {
            cout << setfill('0') << setw(3) << time << " " << color << " headquarter stops making warriors" << endl;
        }
};

string Headquarter::warriors_names[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Headquarter::warriors_lifebar[5] = {0, 0, 0, 0, 0};

int main() {
    int n;
    cin >> n;
    int red_sequence[5] = {2, 3, 4, 1, 0}, blue_sequence[5] = {3, 0, 1, 2, 4};
    int temp_lifebar[5];
    for (int i = 0; i < n; ++i) {
        int health;
        cin >> health;
        for (int j = 0; j < 5; ++j) {
            cin >> temp_lifebar[j];
        }
        Headquarter::set_lifebar(temp_lifebar);
        Headquarter redHQ("red", health, red_sequence), blueHQ("blue", health, blue_sequence);        
        cout << "Case:" << i + 1 << endl;
        while(!redHQ.isStopped() || !blueHQ.isStopped()) {
            redHQ.produce();
            blueHQ.produce();
        }
    }
}