#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define endl "\n"


//------------------------------------------------------------------------------------------------------------------------------------//

struct date{
    int day;
    int month;
    int year;
    date(int day=0, int month=0, int year=0){
        this->day = day;
        this->month = month;
        this->year = year;
    }
};


class room{
    private:
        int room_number;
        int room_price;
        int room_floor;
        int room_capacity;
        int room_beds;
        int hotel_id;
        string room_type;
        vector<int> room_status;

    public:

        room(int room_number = 0, int room_price = 0, int room_floor = 0, int room_capacity = 0, int room_beds = 0, string room_type = "", int hotel_id = 0){

            this -> room_number = room_number;
            this -> room_price = room_price;
            this -> room_floor = room_floor;
            this -> room_capacity = room_capacity;
            this -> room_beds = room_beds;
            this -> room_type = room_type;
            this -> hotel_id = hotel_id;
            room_status = vector < int > (370, 0);
        }
        
        void set_room_number(int room_number){
            this -> room_number = room_number;
        }

        void set_room_price(int room_price){
            this -> room_price = room_price;
        }

        void set_room_floor(int room_floor){
            this -> room_floor = room_floor;
        }

        void set_room_capacity(int room_capacity){
            this -> room_capacity = room_capacity;
        }

        void set_room_beds(int room_beds){
            this -> room_beds = room_beds;
        }

        void set_hotel_id(int hotel_id){
            this -> hotel_id = hotel_id;
        }

        void set_room_type(string room_type){
            this -> room_type = room_type;
        }

        void set_room_status_day(date day, int status){
            int cur_day = day.day + (day.month - 1) * 30;
            this -> room_status[cur_day] = status;
        }
        void set_rooms_status(vector < int > room_status){
            this -> room_status = room_status;
        }

        void update_room_status(date left, date right , int status){
            int leftday = left.day + (left.month - 1) * 30, rightday = right.day + (right.month - 1) * 30;
            for(int i = leftday; i <= rightday; i++){
                room_status[i] = status;
            }
        }

        bool check_room_status(date left, date right){
            int leftday = left.day + (left.month - 1) * 30, rightday = right.day + (right.month - 1) * 30;
            for(int i = leftday; i <= rightday; i++){
                if(room_status[i] != 0){
                    return false;
                }
            }
            return true;
        }

        int get_room_number(){
            return this -> room_number;
        }

        int get_room_price(){
            return this -> room_price;
        }

        int get_room_floor(){
            return this -> room_floor;
        }

        int get_room_capacity(){
            return this -> room_capacity;
        }

        int get_room_beds(){
            return this -> room_beds;
        }

        int get_hotel_id(){
            return this -> hotel_id;
        }

        string get_room_type(){
            return this -> room_type;
        }

        int get_room_status(date now){
            int nowday = now.day + (now.month - 1) * 30;
            return this -> room_status[nowday];
        }

        vector < int > get_room_status(){
            return this -> room_status;
        }

        void print(){
            cout << "{" << endl;
            cout << "   Room Number: " << room_number << endl;
            cout << "   Room Price: " << room_price << endl;
            cout << "   Room Floor: " << room_floor << endl;
            cout << "   Room Capacity: " << room_capacity << endl;
            cout << "   Room Beds: " << room_beds << endl;
            cout << "   Room Type: " << room_type << endl;
            cout << "   Hotel ID: " << hotel_id << endl;
            cout << "}" << endl;
        }


};
