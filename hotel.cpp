#include <bits/stdc++.h>
#include "customer.cpp"
using namespace std;
#define ll long long


//------------------------------------------------------------------------------------------------------------------------------------//

class hotel
{
    private:
        int id;
        int stars;
        int rooms_count;
        int customers_count;
        string name;
        string address;
        string phone;
        string email;
        string website;
        string description;
        vector < room > rooms;
        vector < customer > customers;

    public:
        hotel(int id = 0, int stars = 0, int rooms_count = 0, string name = "", string address = "", string phone = "", string email = "", string website = "", string description = "",int customers_count=0){
            this -> id = id;
            this -> stars = stars;
            this -> rooms_count = rooms_count;
            this -> name = name;
            this -> address = address;
            this -> phone = phone;
            this -> email = email;
            this -> website = website;
            this -> description = description;
            this -> customers_count=customers_count;

        }

        void set_id(int id){
           this -> id = id;
        }

        void set_stars(int stars) {
            this -> stars = stars;
        }

        void set_rooms_count(int rooms_count){
            this -> rooms_count = rooms_count;
        }

        void set_name(string name){
            this -> name = name;
        }

        void set_address(string address){
            this -> address = address;
        }

        void set_phone(string phone){
            this -> phone = phone;
        }

        void set_email(string email){
            this -> email = email;
        }

        void set_website(string website){
            this -> website = website;
        }

        void set_description(string description){
            this -> description = description;
        }

        void set_rooms(vector<room> rooms){
            this -> rooms = rooms;
        }

        void set_customers(vector<customer> customers){
            this -> customers = customers;
            customers_count = customers.size();
        }

        void set_customers_count(int customers_count){
            this -> customers_count = customers_count;
        }

        int get_id(){
            return this -> id;
        }

        int get_stars(){
            return this -> stars;
        }

        int get_rooms_count(){
            return this -> rooms_count;
        }

        string get_name(){
            return this -> name;
        }

        string get_address(){
            return this -> address;
        }

        string get_phone(){
            return this -> phone;
        }

        string get_email(){
            return this -> email;
        }

        string get_website(){
            return this -> website;
        }

        string get_description(){
            return this -> description;
        }

        vector<room> get_rooms(){
            return this -> rooms;
        }

        vector<customer> get_customers(){
            return this -> customers;
        }

        room get_room(int id){
            for(int i = 0; i < this -> rooms.size(); i++){
                if(this -> rooms[i].get_room_number() == id){
                    return this -> rooms[i];
                }
            }
            return room();
        }

        int get_customers_count(){
            return this -> customers_count;
        }

        void add_room(room r){
            this -> rooms.push_back(r);
        }

        void remove_room(int id)
        {
            for (int i = 0; i < this -> rooms.size(); i++)
            {
                if (this->rooms[i].get_room_number() == id)
                {
                    this -> rooms.erase(this -> rooms.begin() + i);
                    break;
                }
            }
        }

        void remove_customer(int id)
        {
            for (int i = 0; i < this->customers.size(); i++)
            {
                if (this -> customers[i].get_id() == id)
                {
                    this -> customers.erase(this -> customers.begin() + i);
                    customers_count--;
                    cout << "customer deleted successfully\n";
                    return;
                }
            }
            cout << "customer not found to delete" << endl;
        }

        void update_room(int id, room r){
            rooms[id] = r;
        }

        void update_customer(int id, customer c)
        {
            for(int i =0 ;i < this -> customers.size(); i++){
                if(this -> customers[i].get_id() == id){
                    this -> customers[i] = c;
                    break;
                }
            }
        }

        void edit_customer(int id, customer c)
        {
            for (int i = 0; i < this->customers.size(); i++)
            {
                if (this->customers[i].get_id() == id)
                {
                    this->customers[i] = c;
                    break;
                }
            }
        }

        int get_number_of_available_rooms(){
            return this->rooms.size()- this -> rooms_count;
        }

        vector < int > number_of_rooms_of_type(string type,date now)
        {
            vector < int > rooms_numbers;
            for (int i = 0; i < this->rooms.size(); i++){
                if (this -> rooms[i].get_room_type() == type && this -> rooms[i].get_room_status(now) == false){
                    rooms_numbers.push_back(this -> rooms[i].get_room_number());
                }
            }
            return rooms_numbers;
        }

        void add_customer(customer new_customer){
            this -> customers.push_back(new_customer);
            rooms[new_customer.get_room()].update_room_status(new_customer.get_check_in(), new_customer.get_check_out(),new_customer.get_id());
            customers_count++;
            rooms_count++;
        }

        int get_avilable_room_oftype(string type, date left, date right){
            for(int i = 0; i < rooms.size(); i++){
                if(rooms[i].get_room_type() == type && rooms[i].check_room_status(left, right) == true){
                    return rooms[i].get_room_number();
                }
            }
            return -1;
        }

        customer get_customers_by_id(int id){
            for(int i = 0; i < customers.size(); i++){
                if(customers[i].get_id() == id){
                    return customers[i];
                }
            }
            return customer();
        }

        vector < customer > get_customers_by_name(string name){
            vector < customer > result;
            for(int i = 0; i < customers.size(); i++){
                if(customers[i].get_name() == name){
                    result.push_back(customers[i]);
                }
            }
            return result;
        }

        void search_customer_by_name(string name){
            bool is_found = false;
            for(auto& cur:customers){
                if(cur.get_name() == name){
                    cout << "customer found"<<endl;
                    cur.print();
                    cout << endl;
                    is_found = true;
                    break;
                }
            }
            if(!is_found) cout<<"not found"<<endl;
        }

        void search_customer_by_id(int id){
            bool is_found = false;
            for(auto& cur:customers){
                if(cur.get_id() == id){
                    cout << "customer found" << endl;
                    cur.print();
                    cout << endl;
                    is_found = true;
                    break;
                }
            }
            if(!is_found) cout<<"not found"<<endl;
        }

        void show_available_rooms(date current){
             bool is_found = false;
            for(auto& cur:rooms){
                if(cur.get_room_status(current) == 0){
                    is_found = true;
                    cur.print();
                    cout<<endl;
                }
            }
            if(!is_found) cout<<"no available rooms in this day found."<<endl;
        }

        void show_reserved_rooms(date current){
            bool is_found = false;
            for(auto& cur:rooms){
                if(cur.get_room_status(current) != 0){
                    is_found = true;
                    cur.print();
                    cout << endl;
                }
            }
            if(!is_found) cout<<"no reserved rooms in this day found."<<endl;
        }

        void show_all_rooms(){
            for(auto& cur:rooms){
                cur.print();
                cout << endl;
            }
        }

        void show_all_customers(){
            for(auto& cur:customers){
                cur.print();
                cout << endl;
            }
        }

        void print_customers(){
            for(auto& cur:customers){
                cur.print();
                cout << endl;
            }
        }

        void print_rooms(){
            for(auto& cur:rooms){
                cur.print();
                cout << endl;
            }
        }


        void print()
        {
            cout << "id: " << this -> id << endl;
            cout << "stars: " << this -> stars << endl;
            cout << "rooms_count: " << this -> rooms_count << endl;
            cout << "name: " << this -> name << endl;
            cout << "address: " << this -> address << endl;
            cout << "phone: " << this -> phone << endl;
            cout << "email: " << this -> email << endl;
            cout << "website: " << this -> website << endl;
            cout << "description: " << this -> description << endl;
            cout << "rooms: " << endl;

            for (int i = 0; i < this->rooms.size(); i++){
                this -> rooms[i].print();
            }

            cout << "customers: " << endl;
            for (int i = 0; i < this->customers.size(); i++){
                this -> customers[i].print();
            }
        }
};
