#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int g_time = 0;

void print_time()
{
    int hour = g_time / 60, minute = g_time % 60;
    cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " ";
}

class Weapon
{
private:
    int id, durability;

public:
    Weapon(int id_)
    {
        id = id_;
        if (id == 0)
        {
            durability = 0x7fffffff;
        }
        else if (id == 1)
        {
            durability = 1;
        }
        else if (id == 2)
        {
            durability = 2;
        }
    }
    int get_id()
    {
        return id;
    }
    int get_durability()
    {
        return durability;
    }
    void use()
    {
        durability--;
    }
};

class Warriors
{
protected:
    string color, name;
    int id, lifebar, force, weapon_num;
    Weapon *bag[10];

public:
    Warriors(string color_, string name_, int id_, int lifebar_, int force_) : color(color_), name(name_), id(id_), lifebar(lifebar_), force(force_)
    {
        weapon_num = 0;
        for (int i = 0; i < 10; ++i)
        {
            bag[i] = NULL;
        }
    }
    virtual ~Warriors()
    {
        for (int i = 0; i < 10; ++i)
        {
            if (bag[i] != NULL)
            {
                delete bag[i];
            }
        }
    }
    virtual void march(int city, int total_cities)
    {
        print_time();
        if (color == "blue" && city == 0)
        {
            cout << color << " " << name << " " << id << " reached red headquarter with " << lifebar << " elements and force " << force << endl;
        }
        else if (color == "red" && city == total_cities + 1)
        {
            cout << color << " " << name << " " << id << " reached blue headquarter with " << lifebar << " elements and force " << force << endl;
        }
        else
        {
            cout << color << " " << name << " " << id << " marched to city " << city << " with " << lifebar << " elements and force " << force << endl;
        }
    }
    virtual bool run_away()
    {
        return false;
    }
    void warrior_situation()
    {
        int num0 = 0, num1 = 0, num2 = 0;
        for (int i = 0; i < weapon_num; ++i)
        {
            if (bag[i] == NULL)
                continue;
            if (bag[i]->get_id() == 0)
            {
                num0++;
            }
            else if (bag[i]->get_id() == 1)
            {
                num1++;
            }
            else if (bag[i]->get_id() == 2)
            {
                num2++;
            }
        }
        print_time();
        cout << color << " " << name << " " << id << " has " << num0 << " sword " << num1 << " bomb " << num2 << " arrow and " << lifebar << " elements" << endl;
    }
    void sort_weapons()
    {
        for (int i = 0; i < weapon_num - 1; ++i)
        {
            for (int j = 0; j < weapon_num - i - 1; ++j)
            {
                if (bag[j]->get_id() > bag[j + 1]->get_id())
                {
                    Weapon *temp;
                    temp = bag[j];
                    bag[j] = bag[j + 1];
                    bag[j + 1] = temp;
                }
                else if (bag[j]->get_id() == bag[j + 1]->get_id() && bag[j]->get_durability() > bag[j + 1]->get_durability())
                {
                    Weapon *temp;
                    temp = bag[j];
                    bag[j] = bag[j + 1];
                    bag[j + 1] = temp;
                }
            }
        }
    }
    string get_name()
    {
        return name;
    }
    int get_weapon_num()
    {
        return weapon_num;
    }
    int get_target_weapon()
    {
        return bag[0]->get_id();
    }
    Weapon *get_weapon_at(int index)
    {
        return bag[index];
    }
    Weapon *take_weapon_at(int index)
    {
        Weapon *w = bag[index];
        bag[index] = NULL;
        return w;
    }
    void reorganize_bag()
    {
        Weapon *temp[10];
        int new_num = 0;
        for (int i = 0; i < weapon_num; ++i)
        {
            if (bag[i] != NULL)
                temp[new_num++] = bag[i];
        }
        for (int i = 0; i < 10; ++i)
        {
            if (i < new_num)
                bag[i] = temp[i];
            else
                bag[i] = NULL;
        }
        weapon_num = new_num;
    }
    string get_color()
    {
        return color;
    }
    int get_id()
    {
        return id;
    }
    void loot(Warriors *loser)
    {
        loser->reorganize_bag();
        int count = loser->get_weapon_num();
        Weapon *temp[10];
        for (int i = 0; i < count; ++i)
            temp[i] = loser->get_weapon_at(i);
        for (int i = 0; i < count - 1; ++i)
        {
            for (int j = 0; j < count - i - 1; ++j)
            {
                if (temp[j]->get_id() > temp[j + 1]->get_id() ||
                    (temp[j]->get_id() == temp[j + 1]->get_id() && temp[j]->get_durability() < temp[j + 1]->get_durability()))
                {
                    swap(temp[j], temp[j + 1]);
                }
            }
        }
        for (int i = 0; i < count; ++i)
        {
            if (weapon_num < 10)
            {
                bag[weapon_num++] = temp[i];
                for (int k = 0; k < loser->get_weapon_num(); ++k)
                {
                    if (loser->get_weapon_at(k) == temp[i])
                    {
                        loser->set_weapon_at(k, NULL);
                        break;
                    }
                }
            }
        }
    }
    void set_weapon_at(int index, Weapon *w)
    {
        bag[index] = w;
    }
    int get_lifebar()
    {
        return lifebar;
    }
    void set_lifebar(int i)
    {
        lifebar = i;
    }
    int get_force()
    {
        return force;
    }
    void decrease_lifebar(int d)
    {
        lifebar -= d;
    }
};

class Dragon : public Warriors
{
private:
    int weapon_type;
    double morale;

public:
    Dragon(string color_, string name_, int id_, int lifebar_, int force_, int hp_) : Warriors(color_, name_, id_, lifebar_, force_), weapon_type(id_ % 3)
    {
        morale = (double)hp_ / lifebar;
        bag[weapon_num] = new Weapon(weapon_type);
        weapon_num++;
    }
    void march(int city, int total_cities)
    {
        Warriors::march(city, total_cities);
    }
    void yell(int city)
    {
        print_time();
        cout << color << " dragon " << id << " yelled in city " << city << endl;
    }
};

class Ninja : public Warriors
{
private:
    int weapon_type;

public:
    Ninja(string color_, string name_, int id_, int lifebar_, int force_, int hp_) : Warriors(color_, name_, id_, lifebar_, force_), weapon_type(id_ % 3)
    {
        bag[weapon_num] = new Weapon(weapon_type);
        weapon_num++;
        bag[weapon_num] = new Weapon((weapon_type + 1) % 3);
        weapon_num++;
    }
    void march(int city, int total_cities)
    {
        Warriors::march(city, total_cities);
    }
};

class Iceman : public Warriors
{
private:
    int weapon_type;

public:
    Iceman(string color_, string name_, int id_, int lifebar_, int force_, int hp_) : Warriors(color_, name_, id_, lifebar_, force_), weapon_type(id_ % 3)
    {
        bag[weapon_num] = new Weapon(weapon_type);
        weapon_num++;
    }
    void march(int city, int total_cities)
    {
        lifebar -= lifebar / 10;
        Warriors::march(city, total_cities);
    }
};

class Lion : public Warriors
{
private:
    int loyalty, weapon_type;
    static int loyalty_miss;

public:
    Lion(string color_, string name_, int id_, int lifebar_, int force_, int hp_) : Warriors(color_, name_, id_, lifebar_, force_), loyalty(hp_), weapon_type(id_ % 3)
    {
        bag[weapon_num] = new Weapon(weapon_type);
        weapon_num++;
    }
    static void set_miss(int n)
    {
        loyalty_miss = n;
    }
    void march(int city, int total_cities)
    {
        loyalty -= loyalty_miss;
        Warriors::march(city, total_cities);
    }
    bool run_away()
    {
        if (loyalty <= 0)
        {
            print_time();
            cout << color << " lion " << id << " ran away" << endl;
            return true;
        }
        return false;
    }
};

int Lion::loyalty_miss = 0;

class Wolf : public Warriors
{
public:
    Wolf(string color_, string name_, int id_, int lifebar_, int force_, int hp_) : Warriors(color_, name_, id_, lifebar_, force_) {}
    void march(int city, int total_cities)
    {
        Warriors::march(city, total_cities);
    }
    void rob(Warriors *enemy, int city_id)
    {
        if (enemy->get_name() == "wolf")
            return;
        if (weapon_num == 10 || enemy->get_weapon_num() == 0)
            return;
        int target = enemy->get_target_weapon();
        int enemy_has = 0;
        for (int i = 0; i < enemy->get_weapon_num(); ++i)
        {
            if (enemy->get_weapon_at(i)->get_id() == target)
            {
                enemy_has++;
            }
        }
        int take = min(enemy_has, (10 - weapon_num));
        for (int i = enemy_has - 1; i >= enemy_has - take; --i)
        {
            bag[weapon_num++] = enemy->take_weapon_at(i);
        }
        enemy->reorganize_bag();
        sort_weapons();
        string w_names[3] = {"sword", "bomb", "arrow"};
        print_time();
        cout << color << " wolf " << id << " took " << take << " " << w_names[target] << " from " << enemy->get_color() << " " << enemy->get_name() << " " << enemy->get_id() << " in city " << city_id << endl;
    }
};

class Headquarter
{
private:
    static string warriors_names[5];
    static int warriors_lifebar[5], warriors_force[5];
    int total_blood, current_index, total_warriors, make_sequence[5];
    string color;
    bool is_stopped;

public:
    Headquarter(string color_, int blood, int seq[]) : color(color_), total_blood(blood)
    {
        current_index = 0, total_warriors = 0, is_stopped = false;
        for (int i = 0; i < 5; ++i)
        {
            make_sequence[i] = seq[i];
        }
    }
    static void set_lifebar(int lifebar[])
    {
        for (int i = 0; i < 5; i++)
        {
            warriors_lifebar[i] = lifebar[i];
        }
    }
    static void set_force(int force[])
    {
        for (int i = 0; i < 5; ++i)
        {
            warriors_force[i] = force[i];
        }
    }
    Warriors *produce()
    {
        if (is_stopped)
            return NULL;
        int warrior_type = make_sequence[current_index];
        if (total_blood >= warriors_lifebar[warrior_type])
        {
            total_blood -= warriors_lifebar[warrior_type];
            total_warriors += 1;
            print_born(warriors_names[warrior_type]);
            Warriors *ptr = NULL;
            switch (warrior_type)
            {
            case 0:
            {
                ptr = new Dragon(color, warriors_names[warrior_type], total_warriors, warriors_lifebar[warrior_type], warriors_force[warrior_type], total_blood);
                break;
            }
            case 1:
            {
                ptr = new Ninja(color, warriors_names[warrior_type], total_warriors, warriors_lifebar[warrior_type], warriors_force[warrior_type], total_blood);
                break;
            }
            case 2:
            {
                ptr = new Iceman(color, warriors_names[warrior_type], total_warriors, warriors_lifebar[warrior_type], warriors_force[warrior_type], total_blood);
                break;
            }
            case 3:
            {
                ptr = new Lion(color, warriors_names[warrior_type], total_warriors, warriors_lifebar[warrior_type], warriors_force[warrior_type], total_blood);
                break;
            }
            case 4:
            {
                ptr = new Wolf(color, warriors_names[warrior_type], total_warriors, warriors_lifebar[warrior_type], warriors_force[warrior_type], total_blood);
                break;
            }
            }
            if (ptr != NULL)
            {
                current_index = (current_index + 1) % 5;
                return ptr;
            }
            return NULL;
        }
        is_stopped = true;
        return NULL;
    }
    void print_born(string name)
    {
        print_time();
        cout << color << " " << name << " " << total_warriors << " born" << endl;
        if (name == "lion")
        {
            cout << "Its loyalty is " << total_blood << endl;
        }
    }
    void print_elements()
    {
        print_time();
        cout << total_blood << " elements in " << color << " headquarter" << endl;
    }
};

string Headquarter::warriors_names[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Headquarter::warriors_lifebar[5] = {0, 0, 0, 0, 0};
int Headquarter::warriors_force[5] = {0, 0, 0, 0, 0};

class City
{
private:
    int id;
    Warriors *red_warrior;
    Warriors *blue_warrior;

public:
    City()
    {
        id = 0, red_warrior = NULL, blue_warrior = NULL;
    }
    void set_id(int n)
    {
        id = n;
    }
    int get_id()
    {
        return id;
    }
    void set_red(Warriors *w)
    {
        red_warrior = w;
    }
    void set_blue(Warriors *w)
    {
        blue_warrior = w;
    }
    Warriors *get_red()
    {
        return red_warrior;
    }
    Warriors *get_blue()
    {
        return blue_warrior;
    }
    void clear_red()
    {
        red_warrior = NULL;
    }
    void clear_blue()
    {
        blue_warrior = NULL;
    }
    void battle()
    {
        if (get_red() == NULL || get_blue() == NULL)
            return;
        Warriors *first = (id % 2 == 1) ? get_red() : get_blue();
        Warriors *second = (id % 2 == 0) ? get_red() : get_blue();
        int first_idx = 0, second_idx = 0, turn = 0, still_judge = 0;
        while (first->get_lifebar() > 0 && second->get_lifebar() > 0)
        {
            Warriors *attacker = (turn == 0) ? first : second;
            Warriors *defender = (turn == 0) ? second : first;
            int &current_idx = (turn == 0) ? first_idx : second_idx;
            bool state_changed = false;
            bool has_weapon = false;
            int search_times = 0;
            while (search_times < 10)
            {
                search_times++;
                if (attacker->get_weapon_at(current_idx) != NULL && attacker->get_weapon_at(current_idx)->get_durability() > 0)
                {
                    has_weapon = true;
                    break;
                }
                current_idx = (current_idx + 1) % 10;
            }
            if (has_weapon)
            {
                Weapon *w = attacker->get_weapon_at(current_idx);
                int w_id = w->get_id(), damage = 0, self_damage = 0;
                if (w_id == 0)
                {
                    damage = attacker->get_force() * 2 / 10;
                }
                else if (w_id == 1)
                {
                    damage = attacker->get_force() * 4 / 10;
                    self_damage = damage / 2;
                    if (attacker->get_name() == "ninja")
                        self_damage = 0;
                    w->use();
                    delete w;
                    attacker->set_weapon_at(current_idx, NULL);
                }
                else if (w_id == 2)
                {
                    damage = attacker->get_force() * 3 / 10;
                    w->use();
                    if (w->get_durability() == 0)
                    {
                        delete w;
                        attacker->set_weapon_at(current_idx, NULL);
                    }
                }
                current_idx = (current_idx + 1) % 10;
                if (damage > 0)
                {
                    defender->decrease_lifebar(damage);
                    state_changed = true;
                    if (self_damage > 0)
                    {
                        attacker->decrease_lifebar(self_damage);
                    }
                }
            }
            if (state_changed)
                still_judge = 0;
            else
                still_judge++;
            if (red_warrior->get_lifebar() <= 0 || blue_warrior->get_lifebar() <= 0)
            {
                if (red_warrior->get_lifebar() <= 0) red_warrior->set_lifebar(0);
                if (blue_warrior->get_lifebar() <= 0) blue_warrior->set_lifebar(0);
                break;
            }
            if (still_judge > 40)
                break;
            turn = 1 - turn;
        }
        first->reorganize_bag();
        second->reorganize_bag();
        if (first->get_lifebar() <= 0 && second->get_lifebar() > 0)
        {
            second->loot(first);
            print_time();
            if (second->get_color() == "red")
            {
                cout << "red " << second->get_name() << " " << second->get_id() << " killed blue " << first->get_name() << " " << first->get_id() << " in city " << id << " remaining " << second->get_lifebar() << " elements" << endl;
                clear_blue();
            }
            else if (second->get_color() == "blue")
            {
                cout << "blue " << second->get_name() << " " << second->get_id() << " killed red " << first->get_name() << " " << first->get_id() << " in city " << id << " remaining " << second->get_lifebar() << " elements" << endl;
                clear_red();
            }
            if (second->get_name() == "dragon")
            {
                ((Dragon *)second)->yell(id);
            }
            delete first;
        }
        else if (first->get_lifebar() > 0 && second->get_lifebar() <= 0)
        {
            first->loot(second);
            print_time();
            if (first->get_color() == "red")
            {
                cout << "red " << first->get_name() << " " << first->get_id() << " killed blue " << second->get_name() << " " << second->get_id() << " in city " << id << " remaining " << first->get_lifebar() << " elements" << endl;
                clear_blue();
            }
            else if (first->get_color() == "blue")
            {
                cout << "blue " << first->get_name() << " " << first->get_id() << " killed red " << second->get_name() << " " << second->get_id() << " in city " << id << " remaining " << first->get_lifebar() << " elements" << endl;
                clear_red();
            }
            if (first->get_name() == "dragon")
            {
                ((Dragon *)first)->yell(id);
            }
            delete second;
        }
        else if (first->get_lifebar() <= 0 && second->get_lifebar() <= 0)
        {
            print_time();
            if (first->get_color() == "red")
            {
                cout << "both red " << first->get_name() << " " << first->get_id() << " and blue " << second->get_name() << " " << second->get_id() << " died in city " << id << endl;
            }
            else if (first->get_color() == "blue")
            {
                cout << "both red " << second->get_name() << " " << second->get_id() << " and blue " << first->get_name() << " " << first->get_id() << " died in city " << id << endl;
            }
            delete first;
            delete second;
            clear_red(), clear_blue();
        }
        else if (first->get_lifebar() > 0 && second->get_lifebar() > 0)
        {
            print_time();
            if (first->get_color() == "red")
            {
                cout << "both red " << first->get_name() << " " << first->get_id() << " and blue " << second->get_name() << " " << second->get_id() << " were alive in city " << id << endl;
                if (first->get_name() == "dragon")
                    ((Dragon *)first)->yell(id);
                if (second->get_name() == "dragon")
                    ((Dragon *)second)->yell(id);
            }
            else if (first->get_color() == "blue")
            {
                cout << "both red " << second->get_name() << " " << second->get_id() << " and blue " << first->get_name() << " " << first->get_id() << " were alive in city " << id << endl;
                if (second->get_name() == "dragon")
                    ((Dragon *)second)->yell(id);
                if (first->get_name() == "dragon")
                    ((Dragon *)first)->yell(id);
            }
        }
    }
};

class World
{
private:
    static int red_sequence[5], blue_sequence[5];
    int cities, finish_time;
    Headquarter redHQ, blueHQ;
    City map[25];
    bool game_over;

public:
    World(int health_, int cities_, int loyalty_miss_, int finish_time_, int temp_lifebar[], int temp_force[]) : redHQ("red", health_, red_sequence), blueHQ("blue", health_, blue_sequence)
    {
        finish_time = finish_time_, game_over = false, cities = cities_;
        Lion::set_miss(loyalty_miss_);
        Headquarter::set_lifebar(temp_lifebar);
        Headquarter::set_force(temp_force);
        for (int i = 0; i <= cities + 1; ++i)
        {
            map[i].set_id(i);
        }
    }
    void run()
    {
        while (g_time <= finish_time && !game_over)
        {
            switch (g_time % 60)
            {
            case 0:
            {
                Warriors *r = redHQ.produce();
                if (r != NULL)
                    map[0].set_red(r);
                Warriors *b = blueHQ.produce();
                if (b != NULL)
                    map[cities + 1].set_blue(b);
                break;
            }
            case 5:
            {
                for (int i = 0; i <= cities + 1; ++i)
                {
                    if (i != cities + 1)
                    {
                        Warriors *r = map[i].get_red();
                        if (r != NULL && r->run_away())
                        {
                            delete r;
                            map[i].clear_red();
                        }
                    }
                    if (i != 0)
                    {
                        Warriors *b = map[i].get_blue();
                        if (b != NULL && b->run_away())
                        {
                            delete b;
                            map[i].clear_blue();
                        }
                    }
                }
                break;
            }
            case 10:
            {
                for (int i = 0; i <= cities; ++i)
                {
                    map[i].set_blue(map[i + 1].get_blue());
                    map[i + 1].clear_blue();
                }
                for (int i = cities + 1; i > 0; --i)
                {
                    map[i].set_red(map[i - 1].get_red());
                    map[i - 1].clear_red();
                }
                for (int i = 0; i <= cities + 1; ++i)
                {
                    if (map[i].get_red() != NULL)
                    {
                        map[i].get_red()->march(i, cities);
                        if (i == cities + 1)
                        {
                            print_time();
                            cout << "blue headquarter was taken" << endl;
                            game_over = true;
                        }
                    }
                    if (map[i].get_blue() != NULL)
                    {
                        map[i].get_blue()->march(i, cities);
                        if (i == 0)
                        {
                            print_time();
                            cout << "red headquarter was taken" << endl;
                            game_over = true;
                        }
                    }
                }
                break;
            }
            case 35:
            {
                for (int i = 0; i <= cities + 1; ++i)
                {
                    if (map[i].get_red() != NULL)
                    {
                        map[i].get_red()->reorganize_bag();
                        map[i].get_red()->sort_weapons();
                    }
                    if (map[i].get_blue() != NULL)
                    {
                        map[i].get_blue()->reorganize_bag();
                        map[i].get_blue()->sort_weapons();
                    }
                    if (map[i].get_red() != NULL && map[i].get_blue() != NULL)
                    {
                        if (map[i].get_red()->get_name() == "wolf")
                        {
                            ((Wolf *)map[i].get_red())->rob(map[i].get_blue(), i);
                        }
                        if (map[i].get_blue()->get_name() == "wolf")
                        {
                            ((Wolf *)map[i].get_blue())->rob(map[i].get_red(), i);
                        }
                    }
                }
                break;
            }
            case 40:
            {
                for (int i = 1; i <= cities; ++i)
                {
                    map[i].battle();
                }
                break;
            }
            case 50:
            {
                redHQ.print_elements();
                blueHQ.print_elements();
                break;
            }
            case 55:
            {
                for (int i = 0; i <= cities + 1; ++i)
                {
                    if (map[i].get_red() != NULL)
                    {
                        map[i].get_red()->warrior_situation();
                    }
                    if (map[i].get_blue() != NULL)
                    {
                        map[i].get_blue()->warrior_situation();
                    }
                }
                break;
            }
            }
            g_time += 5;
        }
    }
};

int World::red_sequence[5] = {2, 3, 4, 1, 0};
int World::blue_sequence[5] = {3, 0, 1, 2, 4};

int main()
{
    int n;
    cin >> n;
    int temp_lifebar[5], temp_force[5];
    for (int i = 0; i < n; ++i)
    {
        g_time = 0;
        int health, cities, loyalty_miss, finish_time;
        cin >> health >> cities >> loyalty_miss >> finish_time;
        for (int j = 0; j < 5; ++j)
        {
            cin >> temp_lifebar[j];
        }
        for (int j = 0; j < 5; ++j)
        {
            cin >> temp_force[j];
        }
        cout << "Case " << i + 1 << ":" << endl;
        World world(health, cities, loyalty_miss, finish_time, temp_lifebar, temp_force);
        world.run();
    }
    return 0;
}