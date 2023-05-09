#include <bits/stdc++.h>
#include </home/gerges/Desktop/student_project/room.cpp>

using namespace std;

#define ll long long
#define endl "\n"

//------------------------------------------------------------------------------------------------------------------------------------//


class customer
{
    private:
        int id;
        int age;
        int hotel_id;
        int total_price;
        bool payment_status;
        bool reservation_number;
        string national_id;
        string address;
        string nationality;
        string name;
        string email;
        string phone;
        date check_in;
        date check_out;
        int currunt_room_id;


    public:

        customer(int id = 0, int age = 0, int hotel_id = 0 ,bool payment_status = 0, bool reservation_number = 0, string national_id = "" , string addres ="" ,
         string nationality = "", string name = "", string email = "" , string phone = "" , date check_in = date(), date check_out = date(), int currunt_room = 0){
            this->id = id;
            this->age = age;
            this->payment_status = payment_status;
            this->reservation_number = reservation_number;
            this->national_id = national_id;
            this->address = address;
            this->nationality=nationality;
            this->name = name;
            this->email = email;
            this->phone = phone;
            this->check_in = check_in;
            this->check_out = check_out;
            this->currunt_room_id = currunt_room;
            this->hotel_id = hotel_id;
            total_price=0;
        }


        void set_id(int id){
            this->id = id;
        }
        void set_age(int age){
            this->age = age;
        }

        void set_payment_status(bool payment_status){
            this->payment_status = payment_status;
        }

        void set_reservation_number(bool reservation_number){
            this->reservation_number = reservation_number;
        }

        void set_national_id(string national_id){
            this->national_id = national_id;
        }

        void set_address(string address){
            this->address = address;
        }

        void set_nationality(string nationality){
            this->nationality = nationality;
        }

        void set_name(string name){
            this->name = name;
        }

        void set_email(string email){
            this->email = email;
        }

        void set_phone(string phone){
            this->phone = phone;
        }

        void set_check_in(date check_in){
            this->check_in = check_in;
        }

        void set_check_out(date check_out){
            this->check_out = check_out;
        }

        void set_currunt_room(int currunt_room){
            this->currunt_room_id = currunt_room;
            reservation_number = true;
        }
        
        void set_hotel_id(int hotel_id){
            this->hotel_id = hotel_id;
        }
        void set_total_price(int price){
            this->total_price += price;
        }

        int get_id(){
            return id;
        }

        int get_age(){
            return age;
        }

        bool get_payment_status(){
            return payment_status;
        }

        bool get_reservation_status(){
            return reservation_number;
        }

        string get_national_id(){
            return national_id;
        }

        string get_address(){
            return address;
        }

        string get_nationality(){
            return nationality;
        }

        string get_name(){
            return name;
        }

        string get_email(){
            return email;
        }

        string get_phone(){
            return phone;
        }

        date get_check_in(){
            return check_in;
        }

        date get_check_out(){
            return check_out;
        }

        int get_room(){
            return currunt_room_id;
        }

        int get_hotel_id(){
            return hotel_id;
        }
        int get_total_price(){
            return total_price;
        }

        void print(){
            cout << "{" << endl;
            cout << "\tid: "<< id << endl;
            cout << "\tage: "<< age << endl;
            cout << "\thotel_id: " << hotel_id << endl;
            cout << "\ttotal_price: " << total_price << endl;
            cout << "\tpayment_status: " << payment_status << endl;
            cout << "\treservation_number: " << reservation_number << endl;
            cout << "\tnational_id: " << national_id << endl;
            cout << "\taddress: " << address << endl;
            cout << "\tnationality: " << nationality << endl;
            cout << "\tname: " << name << endl;
            cout << "\temail: " << email << endl;
            cout << "\tphone: " << phone << endl;
            cout << "\tcheck_in: " << check_in.day << "/" << check_in.month << "/" << check_in.year << endl;
            cout << "\tcheck_out: " << check_out.day << "/" << check_out.month << "/" << check_out.year << endl;
            cout << "\tcurrunt_room: " << currunt_room_id << endl; 
            cout << "}" << endl;
        }

};
