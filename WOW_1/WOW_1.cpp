#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

int Time = 0, totalrednum = 0, totalbluenum = 0, totalredblood = 0, totalblueblood = 0;

class Warriors {
    private:
        int num_red, num_blue, lifebar;
        char name[10];
    public:
        Warriors(char * s, int lb = 0, int n = 0) {
            strcpy(name, s);
            lifebar = lb;
            num_red = n;
            num_blue = 0;
        }
        void GetLifebar(int lb) {
            lifebar = lb;
        }
        void WarriorsBorn_red(int & blood) {
            num_red++;
            blood -= lifebar;
            totalrednum++;
        }
        void WarriorsBorn_blue(int & blood) {
            num_blue++;
            blood -= lifebar;
            totalbluenum++;
        }
        void RedPrint() {
            cout << setfill('0') << setw(3) << Time << " red " << name << " " << totalrednum << " born with strength " << lifebar << "," << num_red << " " << name << " in red headquarter" << endl;
        }
        void BluePrint() {
            cout << setfill('0') << setw(3) << Time << " blue " << name << " " << totalbluenum << " born with strength " << lifebar << "," << num_blue << " " << name << " in blue headquarter" << endl;
        }
        void Reset() {
            num_red = 0;
            num_blue = 0;
        }
        bool judge_red(int blood) {
            return lifebar <= blood;
        }
        bool judge_blue(int blood) {
            return lifebar <= blood;
        }
};

void RedPrint_finish() {
    cout << setfill('0') << setw(3) << Time << " red headquarter stops making warriors" << endl;
}

void BluePrint_finish() {
    cout << setfill('0') << setw(3) << Time << " blue headquarter stops making warriors" << endl;
}

int main()
{
    Warriors dragon("dragon"), ninja("ninja"), iceman("iceman"), lion("lion"), wolf("wolf");
    int totaln = 0;
    cin >> totaln;
    for (int i = 0; i < totaln; i++) {
        cout << "Case:" << i + 1 << endl;
        cin >> totalredblood;
        totalblueblood = totalredblood;
        int temp = 0, min_blood = 0;
        cin >> temp; dragon.GetLifebar(temp); min_blood = temp;
        cin >> temp; ninja.GetLifebar(temp); min_blood = min(min_blood, temp);
        cin >> temp; iceman.GetLifebar(temp); min_blood = min(min_blood, temp);
        cin >> temp; lion.GetLifebar(temp); min_blood = min(min_blood, temp);
        cin >> temp; wolf.GetLifebar(temp); min_blood = min(min_blood, temp);
        int turn_red = 1, turn_blue = 1, judge_red = 1, judge_blue = 1;
        while(totalredblood >= min_blood || totalblueblood >= min_blood) {
            if(totalredblood < min_blood && judge_red == 1) {
                RedPrint_finish();
                judge_red = 0;
            }
            if (totalredblood >= min_blood) {
                switch(turn_red) {
                    case 1:
                        if (iceman.judge_red(totalredblood)) {
                            iceman.WarriorsBorn_red(totalredblood);
                            iceman.RedPrint();
                            turn_red = 2;
                            break;
                        }                        
                    case 2:
                        if (lion.judge_red(totalredblood)) {
                            lion.WarriorsBorn_red(totalredblood);
                            lion.RedPrint();
                            turn_red = 3;
                            break;
                        }  
                    case 3:                      
                        if (wolf.judge_red(totalredblood)) {
                            wolf.WarriorsBorn_red(totalredblood);
                            wolf.RedPrint();
                            turn_red = 4;
                            break;
                        }                        
                    case 4:
                        if (ninja.judge_red(totalredblood)) {
                            ninja.WarriorsBorn_red(totalredblood);
                            ninja.RedPrint();
                            turn_red = 5;
                            break;
                        }                        
                    default:
                        if (dragon.judge_red(totalredblood)) {
                            dragon.WarriorsBorn_red(totalredblood);
                            dragon.RedPrint();
                            turn_red = 1;
                            break;
                        }
                        turn_red = 1;
                        switch(turn_red) {
                            case 1:
                                if (iceman.judge_red(totalredblood)) {
                                iceman.WarriorsBorn_red(totalredblood);
                                iceman.RedPrint();
                                turn_red = 2;
                                break;
                                }                        
                            case 2:
                                if (lion.judge_red(totalredblood)) {
                                lion.WarriorsBorn_red(totalredblood);
                                lion.RedPrint();
                                turn_red = 3;
                                break;
                                }   
                            case 3:                     
                                if (wolf.judge_red(totalredblood)) {
                                wolf.WarriorsBorn_red(totalredblood);
                                wolf.RedPrint();
                                turn_red = 4;
                                break;
                                }                        
                            case 4:
                                if (ninja.judge_red(totalredblood)) {
                                ninja.WarriorsBorn_red(totalredblood);
                                ninja.RedPrint();
                                turn_red = 5;
                                break;
                                }
                        }                        
                }
            }
            if(totalblueblood < min_blood && judge_blue == 1) {
                BluePrint_finish();
                judge_blue = 0;
            }
            if (totalblueblood >= min_blood) {
                switch(turn_blue) {
                    case 1:
                        if (lion.judge_blue(totalblueblood)) {
                            lion.WarriorsBorn_blue(totalblueblood);
                            lion.BluePrint();
                            turn_blue = 2;
                            break;
                        }                        
                    case 2:
                        if (dragon.judge_blue(totalblueblood)) {
                            dragon.WarriorsBorn_blue(totalblueblood);
                            dragon.BluePrint();
                            turn_blue = 3;
                            break;
                        }                        
                    case 3:
                        if (ninja.judge_blue(totalblueblood)) {
                            ninja.WarriorsBorn_blue(totalblueblood);
                            ninja.BluePrint();
                            turn_blue = 4;
                            break;
                        }                       
                    case 4:
                        if (iceman.judge_blue(totalblueblood)) {
                            iceman.WarriorsBorn_blue(totalblueblood);
                            iceman.BluePrint();
                            turn_blue = 5;
                            break;
                        }
                    default:
                        if (wolf.judge_blue(totalblueblood)) {
                            wolf.WarriorsBorn_blue(totalblueblood);
                            wolf.BluePrint();
                            turn_blue = 1;
                            break;
                        }
                        turn_blue = 1;
                        switch(turn_blue) {
                            case 1:
                                if (lion.judge_blue(totalblueblood)) {
                                lion.WarriorsBorn_blue(totalblueblood);
                                lion.BluePrint();
                                turn_blue = 2;
                                break;
                            }                        
                            case 2:
                                if (dragon.judge_blue(totalblueblood)) {
                                dragon.WarriorsBorn_blue(totalblueblood);
                                dragon.BluePrint();
                                turn_blue = 3;
                                break;
                            }                        
                            case 3:
                                if (ninja.judge_blue(totalblueblood)) {
                                ninja.WarriorsBorn_blue(totalblueblood);
                                ninja.BluePrint();
                                turn_blue = 4;
                                break;
                            }                       
                            case 4:
                                if (iceman.judge_blue(totalblueblood)) {
                                iceman.WarriorsBorn_blue(totalblueblood);
                                iceman.BluePrint();
                                turn_blue = 5;
                                break;
                            }
                        }
                }
            }
            Time++;
        }
        if(totalredblood < min_blood && judge_red == 1) {
            RedPrint_finish();
            judge_red = 0;
        }
        if(totalblueblood < min_blood && judge_blue == 1) {
            BluePrint_finish();
            judge_blue = 0;
        }
        Time = 0, turn_red = 1, turn_blue = 1, judge_red = 1, judge_blue = 1, totalrednum = 0, totalbluenum = 0;
        iceman.Reset(), lion.Reset(), wolf.Reset(), ninja.Reset(), dragon.Reset();
    }
    return 0;
}