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

class Warriors
{
protected:
    string color, name;
    int id, lifebar, force, sword_force, arrow_uses;
    bool bomb_has, reached_hq;

public:
    Warriors(string color_, string name_, int id_, int lifebar_, int force_) : color(color_), name(name_), id(id_), lifebar(lifebar_), force(force_)
    {
        sword_force = 0, arrow_uses = 0, bomb_has = false, reached_hq = false;
    }
    virtual ~Warriors() {}
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
        int num0 = sword_force, num2 = arrow_uses;
        bool num1 = bomb_has;
        print_time();
        cout << color << " " << name << " " << id << " has ";
        if (num0 == 0 && !num1 && num2 == 0)
        {
            cout << "no weapon";
        }
        if (num2 != 0)
        {
            cout << "arrow(" << arrow_uses << ")";
        }
        if (num1)
        {
            if (num2 != 0)
            {
                cout << ",";
            }
            cout << "bomb";
        }
        if (num0 != 0)
        {
            if (num2 != 0 || num1)
            {
                cout << ",";
            }
            cout << "sword(" << sword_force << ")";
        }
        cout << endl;
    }
    bool get_reached_hq()
    {
        return reached_hq;
    }
    void set_reached_hq(bool i)
    {
        reached_hq = i;
    }
    string get_name()
    {
        return name;
    }
    string get_color()
    {
        return color;
    }
    int get_id()
    {
        return id;
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
    void weapon_equip(int weapon_type)
    {
        if (weapon_type == 0)
        {
            sword_force = force * 2 / 10;
        }
        else if (weapon_type == 1)
        {
            bomb_has = true;
        }
        else if (weapon_type == 2)
        {
            arrow_uses = 3;
        }
    }
    void weapon_use(int weapon_type)
    {
        if (weapon_type == 0)
        {
            sword_force = sword_force * 8 / 10;
        }
        else if (weapon_type == 1)
        {
            bomb_has = false;
        }
        else if (weapon_type == 2)
        {
            arrow_uses--;
        }
    }
    int get_arrow_uses()
    {
        return arrow_uses;
    }
    int get_sword_force()
    {
        return sword_force;
    }
    bool get_bomb_has()
    {
        return bomb_has;
    }
    void dead_lion(Warriors *p, int h)
    {
        if (p->get_name() == "lion")
        {
            h = max(h, 0);
            set_lifebar(get_lifebar() + h);
        }
    }
    virtual void yell(int city) {}
    virtual void change_morale(int i) {}
    virtual void change_loyalty() {}
    virtual void loot(Warriors *p) {}
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
        weapon_equip(weapon_type);
    }
    void march(int city, int total_cities)
    {
        Warriors::march(city, total_cities);
    }
    void yell(int city)
    {
        if (morale <= 0.8)
        {
            return;
        }
        print_time();
        cout << color << " dragon " << id << " yelled in city " << city << endl;
    }
    void change_morale(int i)
    {
        if (i)
        {
            morale += 0.2;
        }
        else
        {
            morale -= 0.2;
        }
    }
};

class Ninja : public Warriors
{
private:
    int weapon_type;

public:
    Ninja(string color_, string name_, int id_, int lifebar_, int force_, int hp_) : Warriors(color_, name_, id_, lifebar_, force_), weapon_type(id_ % 3)
    {
        weapon_equip(weapon_type);
        weapon_equip((weapon_type + 1) % 3);
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
    bool decrese_lifebar;

public:
    Iceman(string color_, string name_, int id_, int lifebar_, int force_, int hp_) : Warriors(color_, name_, id_, lifebar_, force_), weapon_type(id_ % 3)
    {
        weapon_equip(weapon_type);
        decrese_lifebar = false;
    }
    void march(int city, int total_cities)
    {
        if (decrese_lifebar)
        {
            if (lifebar <= 9)
            {
                lifebar = 1;
            }
            else
            {
                lifebar -= 9;
            }
            force += 20;
            decrese_lifebar = false;
        }
        else
        {
            decrese_lifebar = true;
        }
        Warriors::march(city, total_cities);
    }
};

class Lion : public Warriors
{
private:
    int loyalty, weapon_type;
    static int loyalty_miss;

public:
    Lion(string color_, string name_, int id_, int lifebar_, int force_, int hp_) : Warriors(color_, name_, id_, lifebar_, force_), loyalty(hp_), weapon_type(id_ % 3) {}
    static void set_miss(int n)
    {
        loyalty_miss = n;
    }
    void march(int city, int total_cities)
    {
        Warriors::march(city, total_cities);
    }
    void change_loyalty()
    {
        loyalty -= loyalty_miss;
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
    void loot(Warriors *loser)
    {
        if (sword_force == 0 && loser->get_sword_force() > 0)
        {
            sword_force = loser->get_sword_force();
        }
        if (arrow_uses == 0 && loser->get_arrow_uses() > 0)
        {
            arrow_uses = loser->get_arrow_uses();
        }
        if (!bomb_has && loser->get_bomb_has())
        {
            bomb_has = true;
        }
    }
};

class Headquarter
{
private:
    static string warriors_names[5];
    static int warriors_lifebar[5], warriors_force[5];
    int total_blood, current_index, total_warriors, make_sequence[5], enemy_count;
    string color;

public:
    Headquarter(string color_, int blood, int seq[]) : color(color_), total_blood(blood)
    {
        current_index = 0, total_warriors = 0, enemy_count = 0;
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
        return NULL;
    }
    void print_born(string name)
    {
        print_time();
        cout << color << " " << name << " " << total_warriors << " born" << endl;
        if (name == "dragon")
        {
            cout << "Its morale is " << fixed << setprecision(2) << ((double)total_blood / warriors_lifebar[0]) << endl;
        }
        else if (name == "lion")
        {
            cout << "Its loyalty is " << total_blood << endl;
        }
    }
    void print_elements()
    {
        print_time();
        cout << total_blood << " elements in " << color << " headquarter" << endl;
    }
    int get_enemy_count()
    {
        return enemy_count;
    }
    void increase_enemy_count()
    {
        enemy_count++;
    }
    void increase_elements(int i)
    {
        total_blood += i;
    }
    int get_total_blood()
    {
        return total_blood;
    }
    void decrease_total_blood(int i)
    {
        total_blood -= i;
    }
};

string Headquarter::warriors_names[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Headquarter::warriors_lifebar[5] = {0, 0, 0, 0, 0};
int Headquarter::warriors_force[5] = {0, 0, 0, 0, 0};

class City
{
private:
    int id, flag, elements, last_winner;
    Warriors *red_warrior;
    Warriors *blue_warrior;

public:
    City()
    {
        id = 0, flag = 0, elements = 0, last_winner = 0, red_warrior = NULL, blue_warrior = NULL;
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
        Warriors *first = NULL;
        Warriors *second = NULL;
        if (flag == 1)
        {
            first = get_red();
            second = get_blue();
        }
        else if (flag == -1)
        {
            first = get_blue();
            second = get_red();
        }
        else if (flag == 0)
        {
            first = (id % 2 == 1) ? get_red() : get_blue();
            second = (id % 2 == 0) ? get_red() : get_blue();
        }
        int first_before = first->get_lifebar(), second_before = second->get_lifebar();
        bool first_alive_before = (first->get_lifebar() > 0), second_alive_before = (second->get_lifebar() > 0);
        if (first_alive_before && second_alive_before)
        {
            int damage = first->get_force() + first->get_sword_force(), back_damage = (second->get_force()) / 2 + second->get_sword_force();
            second->decrease_lifebar(damage);
            first->weapon_use(0);
            print_time();
            cout << first->get_color() << " " << first->get_name() << " " << first->get_id() << " attacked " << second->get_color() << " " << second->get_name() << " " << second->get_id() << " in city " << id << " with " << first->get_lifebar() << " elements and force " << first->get_force() << endl;
            if (second->get_lifebar() > 0 && second->get_name() != "ninja")
            {
                first->decrease_lifebar(back_damage);
                second->weapon_use(0);
                print_time();
                cout << second->get_color() << " " << second->get_name() << " " << second->get_id() << " fought back against " << first->get_color() << " " << first->get_name() << " " << first->get_id() << " in city " << id << endl;
            }
        }
        if (first->get_lifebar() <= 0 && second->get_lifebar() > 0)
        {
            second->dead_lion(first, first_before);
            second->change_morale(1);
            if (first_alive_before)
            {
                print_time();
                cout << first->get_color() << " " << first->get_name() << " " << first->get_id() << " was killed in city " << id << endl;
            }
            print_time();
            cout << second->get_color() << " " << second->get_name() << " " << second->get_id() << " earned " << elements << " elements for his headquarter" << endl;
            if (second->get_color() == "red" && last_winner == 1 && flag != 1)
            {
                flag = 1;
                print_time();
                cout << "red flag raised in city " << id << endl;
            }
            else if (second->get_color() == "red" && last_winner != 1)
            {
                last_winner = 1;
            }
            else if (second->get_color() == "blue" && last_winner == -1 && flag != -1)
            {
                flag = -1;
                print_time();
                cout << "blue flag raised in city " << id << endl;
            }
            else if (second->get_color() == "blue" && last_winner != -1)
            {
                last_winner = -1;
            }
            second->loot(first);
        }
        else if (first->get_lifebar() > 0 && second->get_lifebar() <= 0)
        {
            first->dead_lion(second, second_before);
            first->change_morale(1);
            if (second_alive_before)
            {
                print_time();
                cout << second->get_color() << " " << second->get_name() << " " << second->get_id() << " was killed in city " << id << endl;
            }
            first->yell(id);
            print_time();
            cout << first->get_color() << " " << first->get_name() << " " << first->get_id() << " earned " << elements << " elements for his headquarter" << endl;
            if (first->get_color() == "red" && last_winner == 1 && flag != 1)
            {
                flag = 1;
                print_time();
                cout << "red flag raised in city " << id << endl;
            }
            else if (first->get_color() == "red" && last_winner != 1)
            {
                last_winner = 1;
            }
            else if (first->get_color() == "blue" && last_winner == -1 && flag != -1)
            {
                flag = -1;
                print_time();
                cout << "blue flag raised in city " << id << endl;
            }
            else if (first->get_color() == "blue" && last_winner != -1)
            {
                last_winner = -1;
            }
            first->loot(second);
        }
        else if (first->get_lifebar() > 0 && second->get_lifebar() > 0)
        {
            first->change_morale(0), second->change_morale(0), first->change_loyalty(), second->change_loyalty();
            first->yell(id);
            last_winner = 0;
        }
    }
    void produce_elements()
    {
        elements += 10;
    }
    int pick_elements()
    {
        int temp = elements;
        elements = 0;
        return temp;
    }
    void bomb()
    {
        if (get_red() == NULL || get_blue() == NULL)
            return;
        Warriors *first = NULL;
        Warriors *second = NULL;
        if (flag == 1)
        {
            first = get_red();
            second = get_blue();
        }
        else if (flag == -1)
        {
            first = get_blue();
            second = get_red();
        }
        else if (flag == 0)
        {
            first = (id % 2 == 1) ? get_red() : get_blue();
            second = (id % 2 == 0) ? get_red() : get_blue();
        }
        if (first->get_lifebar() > 0 && second->get_lifebar() > 0)
        {
            int damage = first->get_force() + first->get_sword_force(), back_damage = (second->get_force()) / 2 + second->get_sword_force();
            if (second->get_lifebar() - damage <= 0)
            {
                if (second->get_bomb_has())
                {
                    print_time();
                    cout << second->get_color() << " " << second->get_name() << " " << second->get_id() << " used a bomb and killed " << first->get_color() << " " << first->get_name() << " " << first->get_id() << endl;
                    first->set_lifebar(0);
                    second->set_lifebar(0);
                    delete first;
                    delete second;
                    clear_red();
                    clear_blue();
                }
                return;
            }
            if (second->get_name() != "ninja" && first->get_lifebar() - back_damage <= 0 && first->get_bomb_has())
            {
                print_time();
                cout << first->get_color() << " " << first->get_name() << " " << first->get_id() << " used a bomb and killed " << second->get_color() << " " << second->get_name() << " " << second->get_id() << endl;
                second->set_lifebar(0);
                first->set_lifebar(0);
                delete first;
                delete second;
                clear_red();
                clear_blue();
            }
        }
    }
};

class World
{
private:
    static int red_sequence[5], blue_sequence[5];
    int cities, finish_time, arrow_force;
    Headquarter redHQ, blueHQ;
    City map[25];
    bool game_over;

public:
    World(int health_, int cities_, int loyalty_miss_, int finish_time_, int temp_lifebar[], int temp_force[], int arrow_f) : redHQ("red", health_, red_sequence), blueHQ("blue", health_, blue_sequence)
    {
        finish_time = finish_time_, game_over = false, cities = cities_, arrow_force = arrow_f;
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
                    if (i == 0 && map[1].get_blue() == NULL)
                        continue;
                    map[i].set_blue(map[i + 1].get_blue());
                    map[i + 1].clear_blue();
                }
                for (int i = cities + 1; i > 0; --i)
                {
                    if (i == cities + 1 && map[cities].get_red() == NULL)
                        continue;
                    map[i].set_red(map[i - 1].get_red());
                    map[i - 1].clear_red();
                }
                for (int i = 0; i <= cities + 1; ++i)
                {
                    if (map[i].get_red() != NULL)
                    {
                        if (i == cities + 1 && map[cities + 1].get_red()->get_reached_hq())
                            continue;
                        map[i].get_red()->march(i, cities);
                        if (i == cities + 1)
                        {
                            blueHQ.increase_enemy_count();
                            if (blueHQ.get_enemy_count() == 2)
                            {
                                print_time();
                                cout << "blue headquarter was taken" << endl;
                                game_over = true;
                            }
                            map[i].get_red()->set_reached_hq(true);
                        }
                    }
                    if (map[i].get_blue() != NULL)
                    {
                        if (i == 0 && map[0].get_blue()->get_reached_hq())
                            continue;
                        map[i].get_blue()->march(i, cities);
                        if (i == 0)
                        {
                            redHQ.increase_enemy_count();
                            if (redHQ.get_enemy_count() == 2)
                            {
                                print_time();
                                cout << "red headquarter was taken" << endl;
                                game_over = true;
                            }
                            map[i].get_blue()->set_reached_hq(true);
                        }
                    }
                }
                break;
            }
            case 20:
            {
                for (int i = 1; i <= cities; ++i)
                {
                    map[i].produce_elements();
                }
                break;
            }
            case 30:
            {
                for (int i = 1; i <= cities; ++i)
                {
                    if (map[i].get_red() != NULL && map[i].get_blue() == NULL)
                    {
                        int earned = map[i].pick_elements();
                        redHQ.increase_elements(earned);
                        print_time();
                        cout << "red " << map[i].get_red()->get_name() << " " << map[i].get_red()->get_id() << " earned " << earned << " elements for his headquarter" << endl;
                    }
                    else if (map[i].get_blue() != NULL && map[i].get_red() == NULL)
                    {
                        int earned = map[i].pick_elements();
                        blueHQ.increase_elements(earned);
                        print_time();
                        cout << "blue " << map[i].get_blue()->get_name() << " " << map[i].get_blue()->get_id() << " earned " << earned << " elements for his headquarter" << endl;
                    }
                }
                break;
            }
            case 35:
            {
                for (int i = 1; i <= cities; ++i)
                {
                    if (map[i].get_red() != NULL && map[i + 1].get_blue() != NULL && map[i].get_red()->get_arrow_uses() > 0 && i < cities)
                    {
                        map[i].get_red()->weapon_use(2);
                        map[i + 1].get_blue()->decrease_lifebar(arrow_force);
                        print_time();
                        if (map[i + 1].get_blue()->get_lifebar() <= 0)
                            cout << "red " << map[i].get_red()->get_name() << " " << map[i].get_red()->get_id() << " shot and killed blue " << map[i + 1].get_blue()->get_name() << " " << map[i + 1].get_blue()->get_id() << endl;
                        else
                            cout << "red " << map[i].get_red()->get_name() << " " << map[i].get_red()->get_id() << " shot" << endl;
                    }
                    if (map[i].get_blue() != NULL && map[i - 1].get_red() != NULL && map[i].get_blue()->get_arrow_uses() > 0 && i > 1)
                    {
                        map[i].get_blue()->weapon_use(2);
                        map[i - 1].get_red()->decrease_lifebar(arrow_force);
                        print_time();
                        if (map[i - 1].get_red()->get_lifebar() <= 0)
                            cout << "blue " << map[i].get_blue()->get_name() << " " << map[i].get_blue()->get_id() << " shot and killed red " << map[i - 1].get_red()->get_name() << " " << map[i - 1].get_red()->get_id() << endl;
                        else
                            cout << "blue " << map[i].get_blue()->get_name() << " " << map[i].get_blue()->get_id() << " shot" << endl;
                    }
                }
                break;
            }
            case 38:
            {
                for (int i = 0; i <= cities; ++i)
                {
                    map[i].bomb();
                }
                break;
            }
            case 40:
            {
                for (int i = 1; i <= cities; ++i)
                {
                    map[i].battle();
                }
                for (int i = 1; i <= cities; ++i)
                {
                    if (blueHQ.get_total_blood() < 8)
                        break;
                    if (map[i].get_red() == NULL || map[i].get_blue() == NULL)
                        continue;
                    Warriors *r = map[i].get_red();
                    Warriors *b = map[i].get_blue();
                    if (b->get_lifebar() > 0 && r->get_lifebar() <= 0)
                    {
                        b->set_lifebar(b->get_lifebar() + 8);
                        blueHQ.decrease_total_blood(8);
                    }
                }
                for (int i = cities; i >= 1; --i)
                {
                    if (redHQ.get_total_blood() < 8)
                        break;
                    if (map[i].get_red() == NULL || map[i].get_blue() == NULL)
                        continue;
                    Warriors *r = map[i].get_red();
                    Warriors *b = map[i].get_blue();
                    if (r->get_lifebar() > 0 && b->get_lifebar() <= 0)
                    {
                        r->set_lifebar(r->get_lifebar() + 8);
                        redHQ.decrease_total_blood(8);
                    }
                }
                for (int i = 1; i <= cities; ++i)
                {
                    Warriors *r = map[i].get_red();
                    Warriors *b = map[i].get_blue();
                    if (r != NULL && r->get_lifebar() > 0 && b != NULL && b->get_lifebar() <= 0)
                    {
                        redHQ.increase_elements(map[i].pick_elements());
                    }
                    else if (r != NULL && r->get_lifebar() <= 0 && b != NULL && b->get_lifebar() > 0)
                    {
                        blueHQ.increase_elements(map[i].pick_elements());
                    }
                    if (r != NULL && r->get_lifebar() <= 0)
                    {
                        delete r;
                        map[i].clear_red();
                    }
                    if (b != NULL && b->get_lifebar() <= 0)
                    {
                        delete b;
                        map[i].clear_blue();
                    }
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
                }
                for (int i = 0; i <= cities + 1; ++i)
                {
                    if (map[i].get_blue() != NULL)
                    {
                        map[i].get_blue()->warrior_situation();
                    }
                }
                break;
            }
            }
            if (g_time % 60 == 35)
            {
                g_time += 3;
            }
            else if (g_time % 60 == 38)
            {
                g_time += 2;
            }
            else
            {
                g_time += 5;
            }
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
        int health, cities, loyalty_miss, finish_time, arrow_force;
        cin >> health >> cities >> arrow_force >> loyalty_miss >> finish_time;
        for (int j = 0; j < 5; ++j)
        {
            cin >> temp_lifebar[j];
        }
        for (int j = 0; j < 5; ++j)
        {
            cin >> temp_force[j];
        }
        cout << "Case " << i + 1 << ":" << endl;
        World world(health, cities, loyalty_miss, finish_time, temp_lifebar, temp_force, arrow_force);
        world.run();
    }
    return 0;
}