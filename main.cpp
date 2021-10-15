#include <iostream>
#include <vector>
using namespace std;

int str_to_int(string x) {
    int num = 0;
    for (unsigned long long int i = 0; i < x.length(); i++) {
        num = num * 10 + (int(x[i]) - 48);
    }
    return num;
}

class Time{
    public:
        int hours = 0, minutes = 0, clock_day = 0;
        
        void set_time(int hours, int minutes){
            this->hours = hours;
            this->minutes = minutes;
        }

        int calc_difference(Time cartime){
            int difference = 0;
            difference += ((24 - cartime.hours) + this->hours) * 60;
            difference = difference - cartime.minutes + this->minutes;
            return difference;
        }

        void add_minutes(int minutes){
            this->minutes += minutes;
            if(this->minutes >= 60){
                this->hours += this->minutes / 60;
                this->minutes = this->minutes % 60;
            }
            if(this->hours >= 24){
                this->hours = this->hours % 24;
                this->clock_day++;
            }   
        }

        void show_time(){
            if(this->hours < 10 && this->minutes < 10){
                cout<<"0"<<this->hours<<":"<<"0"<<this->minutes;
            }else if(this->hours < 10){
                cout<<"0"<<this->hours<<":"<<this->minutes;
            }else if(this->minutes < 10){
                cout<<this->hours<<":"<<"0"<<this->minutes;
            }else{
                cout<<this->hours<<":"<<this->minutes;
            }
        }     
};

struct Car{
    int car_day;
    Time time;
};

class RiverBank{
    public:
    vector<Car> vec;

    void add_car(Car car){
        this->vec.push_back(car);
    }

    void remove_cars(int amount){
        vector<Car> tmp_vec;
        for(unsigned long long int i=0;i<this->vec.size();i++){
            if(i<amount){
                continue;
            }else{
                tmp_vec.push_back(this->vec[i]);
            }
        }
        this->vec = tmp_vec;
    }
};

int main(){
    bool verbose = false;
    string bank, cartime;
    int maxHourL = 0, maxHourR = 0, ferrySize, this_dayLB = 0, this_dayRB = 0;
    cout << "Enter the ferry size: ";
    cin >> ferrySize;

    Time clock;
    RiverBank leftBank;
    RiverBank rightBank;
    bool is_leftBank = true;

    while(cin>> bank >> cartime){
        Car instance;

        if(bank[0] == 'L'){
            instance.time.set_time(cartime.size()==4?str_to_int(cartime.substr(0,1)):str_to_int(cartime.substr(0,2)),cartime.size()==4?str_to_int(cartime.substr(2,2)):str_to_int(cartime.substr(3,2)));
            leftBank.add_car(instance);
            if(leftBank.vec[leftBank.vec.size()-1].time.hours >=maxHourL){
                leftBank.vec[leftBank.vec.size()-1].car_day = this_dayLB;
                maxHourL = leftBank.vec[leftBank.vec.size()-1].time.hours;
            }else{
                this_dayLB++;
                leftBank.vec[leftBank.vec.size()-1].car_day = this_dayLB;
                maxHourL = leftBank.vec[leftBank.vec.size()-1].time.hours;
            }
            if(verbose){
                cout<<"Day at left bank of river: "<< this_dayLB <<endl;
            }
        }else{
            instance.time.set_time(cartime.size()==4?str_to_int(cartime.substr(0,1)):str_to_int(cartime.substr(0,2)),cartime.size()==4?str_to_int(cartime.substr(2,2)):str_to_int(cartime.substr(3,2)));
            rightBank.add_car(instance);
            if(rightBank.vec[rightBank.vec.size()-1].time.hours >=maxHourR){
                rightBank.vec[rightBank.vec.size()-1].car_day = this_dayRB;
                maxHourR = rightBank.vec[rightBank.vec.size()-1].time.hours;
            }else{
                this_dayRB++;
                rightBank.vec[rightBank.vec.size()-1].car_day = this_dayRB;
                maxHourR = rightBank.vec[rightBank.vec.size()-1].time.hours;
            }
            if(verbose){
                cout<<"Day at right bank of river: "<< this_dayRB <<endl;
            }
        }

        
        
        while((is_leftBank && leftBank.vec.size() >= ferrySize) || (!is_leftBank && rightBank.vec.size() >= ferrySize)){
            if(is_leftBank){
                if(leftBank.vec[ferrySize - 1].car_day > clock.clock_day){
                    if(verbose){
                        cout<<"The another day"<<endl;
                    }                                  
                    clock.minutes = leftBank.vec[ferrySize - 1].time.minutes;
                    clock.hours = leftBank.vec[ferrySize - 1].time.hours;                
                    clock.clock_day = leftBank.vec[ferrySize - 1].car_day;
                }else if(leftBank.vec[ferrySize - 1].car_day == clock.clock_day){
                    if(verbose){
                        cout<<"The same day"<<endl;
                    }                    
                    if(leftBank.vec[ferrySize - 1].time.hours > clock.hours){                
                        clock.minutes = leftBank.vec[ferrySize - 1].time.minutes;
                        clock.hours = leftBank.vec[ferrySize - 1].time.hours;                
                    }
                    if(leftBank.vec[ferrySize - 1].time.hours == clock.hours && leftBank.vec[ferrySize - 1].time.minutes > clock.minutes){
                        clock.minutes = leftBank.vec[ferrySize - 1].time.minutes;
                    }
                }else{
                    if(verbose){
                        cout<<"The day before."<<endl<<endl;   
                    }
                }

                cout<<"Ferry goes at  ";
                clock.show_time();
                cout<<" from left river bank."<<endl;
                clock.add_minutes(5);

                for(unsigned long long int i=0;i<ferrySize;i++){
                    cout<<"The car came at "; 
                    leftBank.vec[i].time.show_time();
                    cout<<" and went at ";
                    clock.show_time();
                    cout<<" on opposite bank river."<<endl;
                }
                leftBank.remove_cars(ferrySize);
                is_leftBank = false;
                
            }else{
                if(rightBank.vec[ferrySize - 1].car_day > clock.clock_day){
                    if(verbose){
                        cout<<"The another day."<<endl;
                    }              
                    clock.minutes = rightBank.vec[ferrySize - 1].time.minutes;
                    clock.hours = rightBank.vec[ferrySize - 1].time.hours;                
                    clock.clock_day = rightBank.vec[ferrySize - 1].car_day;
                }else if(rightBank.vec[ferrySize - 1].car_day == clock.clock_day){
                    if(verbose){
                        cout<<"The same day."<<endl;
                    }
                    if(rightBank.vec[ferrySize - 1].time.hours > clock.hours){                
                        clock.minutes = rightBank.vec[ferrySize - 1].time.minutes;
                        clock.hours = rightBank.vec[ferrySize - 1].time.hours;                
                    }
                    if(rightBank.vec[ferrySize - 1].time.hours == clock.hours && rightBank.vec[ferrySize - 1].time.minutes > clock.minutes){
                        clock.minutes = rightBank.vec[ferrySize - 1].time.minutes;
                    }
                }else{
                    if(verbose){
                        cout<<"The another day."<<endl<<endl;
                        
                    }
                }
                

                cout<<"Ferry goes at ";
                clock.show_time();
                cout<<" from right bank of river."<<endl;
                clock.add_minutes(7);

                for(unsigned long long int i=0;i<ferrySize;i++){
                    cout<<"The car came at "; 
                    rightBank.vec[i].time.show_time();
                    cout<<" and went at ";
                    clock.show_time();
                    cout<<" on opposite bank of river."<<endl;
                }
                rightBank.remove_cars(ferrySize);
                is_leftBank = true;
            }
        }
    }
}