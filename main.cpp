#include <bits/stdc++.h>
#include "hotel.cpp"
using namespace std;

#define ll long long
#define endl "\n"
#define sz size()
#define fileror(x) "file " << x << " not found."


//------------------------------------------------------------------------------------------------------------------------------------//

hotel curr_hotel;
vector < room > rooms;
vector < customer > customers;
vector < int > prices = {120, 300, 500};
fstream customer_file, room_file, hotel_file;
vector < string > room_types = {"single", "double", "suite"};
int rooms_count_template = 50, single_rooms = 25, double_rooms = 15, suites = 10;
vector < string > rooms_data_template = {"room_number", "hotel_id", "room_type", "room_price", "room_status", "room_capacity", "room_beds", "room_floor"};
vector < string > hotels_data_template = {"hotel_id", "stars", "rooms_count", "customers_count", "name", "address", "phone", "email", "website", "description"};
vector < string > customers_data_template = {"customer id", "hotel id", "age", "payment status", "reservation number", "national id", "address", "nationality", "name", "email", "phone", "check in", "check out", "currunt room"};


bool check_number(string num){
    for (auto &c : num)
        if (!isdigit(c))
            return false;
    return true;
}

bool check_str(string name){
    for (auto &c : name)
        if (!isalpha(c))
            return false;
    return true;
}

void startup(){
    cout << "Welcome to our hotel management system" << endl;
    rooms.push_back(room());
    customer_file.open("data_files/customers_data.csv", ios::in);
    room_file.open("rooms_data.csv", ios::in);

    if (!customer_file.is_open()){
        cout << fileror("data_files/customers_data.csv") << endl;
        exit(0);
    }

    if (!room_file.is_open()){
        cout << fileror("rooms_data.csv") << endl;
        exit(0);
    }

    vector < string > customers_data;
    while (!customer_file.eof()){
        string line;
        getline(customer_file, line);
        customers_data.push_back(line);
    }

    vector < string > rooms_data;
    while (!room_file.eof()){
        string line;
        getline(room_file, line);
        rooms_data.push_back(line);
    }

    bool first = true;
    for (auto &i : customers_data){
        if (first){
            first = false;
            continue;
        }
        customer curr_customer;
        vector < string > data;
        stringstream ss(i);
        string temp;

        while (getline(ss, temp, ',')){
            data.push_back(temp);
        }

        curr_customer.set_id(stoi(data[0]));
        curr_customer.set_hotel_id(stoi(data[1]));
        curr_customer.set_age(stoi(data[2]));
        curr_customer.set_payment_status(stoi(data[3]));
        curr_customer.set_reservation_number(stoi(data[4]));
        curr_customer.set_national_id(data[5]);
        curr_customer.set_address(data[6]);
        curr_customer.set_nationality(data[7]);
        curr_customer.set_name(data[8]);
        curr_customer.set_email(data[9]);
        curr_customer.set_phone(data[10]);

        date check_in, check_out;
        int year = stoi(data[11].substr(0, 4));
        int month = stoi(data[11].substr(4, 2));
        int day = stoi(data[11].substr(6, 2));
        check_in = date(day, month, year);

        year = stoi(data[12].substr(0, 4));
        month = stoi(data[12].substr(4, 2));
        day = stoi(data[12].substr(6, 2));
        check_out = date(day, month, year);

        curr_customer.set_check_in(check_in);
        curr_customer.set_check_out(check_out);
        curr_customer.set_currunt_room(stoi(data[13]));
        customers.push_back(curr_customer);
    }

    curr_hotel = hotel(1, 5, rooms_count_template, "Belmond hotel", "el cacola city - ismailia - Egypt", "+201216560102", "info@belmontbanbridge.com", "https://belmonthotelmanila.com/", "Belmont Hotel Manila is a 4-star hotel strategically located across NAIA Terminal 3 and within the renowned entertainment city, Newport City.It is a \"home away from home\" for local and international business travelers as well as vacationers who desire convenience, safety, and consistency in excellent service. Belmont Hotel Manila is proudly a local brand that is part of Megaworld Hotels & Resorts – one of the largest hospitality chains in the Philippines.");
    curr_hotel.set_customers(customers);
    first = true;

    for (auto &i : rooms_data){
        if (first){
            first = false;
            continue;
        }

        room curr_room;
        vector<string> data;
        stringstream ss(i);
        string temp;

        while (getline(ss, temp, ',')){
            data.push_back(temp);
        }

        vector < int > status(370);
        curr_room.set_room_number(stoi(data[0]));
        curr_room.set_hotel_id(stoi(data[1]));
        curr_room.set_room_type(data[2]);
        curr_room.set_room_price(stoi(data[3]));
        curr_room.set_room_capacity(stoi(data[4]));
        curr_room.set_room_beds(stoi(data[5]));
        curr_room.set_room_floor(stoi(data[6]));

        ss.clear();
        int x = 0;
        while (getline(ss, temp, ' ')){
            status[x] = stoi(temp);
            x++;
        }

        curr_room.set_rooms_status(status);
        rooms.push_back(curr_room);
    }

    curr_hotel.set_rooms(rooms);
    customer_file.close();
    room_file.close();
    hotel_file.close();
}

void add_new_customer()
{
    customer curr_customer = customer();
    curr_customer.set_id(curr_hotel.get_customers_count() + 1);
    curr_customer.set_hotel_id(curr_hotel.get_id());

    cout << "enter customer name: ";
    string name;
    cin >> name;
    while (!check_str(name)){
        cout << endl << "Enter a valid name : ";
        cin >> name;
    }
    curr_customer.set_name(name);

    cout << "enter customer age: ";
    string age;
    cin >> age;

    while (!check_number(age)){
        cout << endl << "Enter a valid age : ";
        cin >> age;
    }
    curr_customer.set_age(stoi(age));

    cout << "enter national id: ";
    string national_id;
    cin >> national_id;
    while (!check_number(national_id)){
        cout << endl << "Enter a valid National ID : ";
        cin >> national_id;
    }
    curr_customer.set_national_id(national_id);

    cout << "enter address: ";
    string address;
    cin >> address;
    curr_customer.set_address(address);

    cout << "enter nationality: ";
    string nationality;
    cin >> nationality;
    while (!check_str(nationality)){
        cout << endl << "Enter a valid Nationlity : ";
        cin >> nationality;
    }
    curr_customer.set_nationality(nationality);

    cout << "enter email: ";
    string email;
    cin >> email;
    curr_customer.set_email(email);

    cout << "enter phone: ";
    string phone;
    cin >> phone;
    while (!check_number(phone)){
        cout << endl << "Enter a valid phone number : ";
        cin >> phone;
    }
    curr_customer.set_phone(phone);

    cout << "enter check in date: \n";
    cout << "enter day: ";
    string day, month, year;
    cin >> day;
    while (!check_number(day) || !(stoi(day) > 0 && stoi(day) < 32)){
        cout << endl << "Enter a valid day : ";
        cin >> day;
    }

    cout << "enter month: ";
    cin >> month;
    while (!check_number(month) || !(stoi(month) > 0 && stoi(month) < 13)){
        cout << endl << "Enter a valid month : ";
        cin >> month;
    }

    cout << "enter year: ";
    cin >> year;
    while (!check_number(year)){
        cout << endl << "Enter a valid year : ";
        cin >> year;
    }

    date check_in = date(stoi(day), stoi(month), stoi(year));
    curr_customer.set_check_in(check_in);

    cout << "enter check out date: " << endl;
    cout << "enter day: ";
    cin >> day;

    while (!check_number(day) || !(stoi(day) > 0 && stoi(day) < 32)){
        cout << endl << "Enter a valid day : ";
        cin >> day;
    }

    cout << "enter month: ";
    cin >> month;
    while (!check_number(month) || !(stoi(month) > 0 && stoi(month) < 13)){
        cout << endl << "Enter a valid month : ";
        cin >> month;
    }

    cout << "enter year: ";
    cin >> year;
    while (!check_number(year) || (stoi(year) != check_in.year)){
        cout << endl << "Enter a valid year : ";
        cin >> year;
    }
    date check_out = date(stoi(day), stoi(month), stoi(year));
    curr_customer.set_check_out(check_out);

    cout << "enter the number of room type :\n  1- single \n  2- double \n  3- suite \n";
    string room_type;
    cin >> room_type;
    while (!check_number(room_type) || !(stoi(room_type) <= 3 && stoi(room_type) >= 1)){
        cout << endl << "Enter a valid room type number: ";
        cin >> room_type;
    }

    int room__id = curr_hotel.get_avilable_room_oftype(room_types[stoi(room_type) - 1], check_in, check_out);
    if (room__id == -1){
        cout << "no available rooms of this type in this period of time" << endl;
        return;
    }

    int total_price = prices[stoi(room_type) - 1] * (((check_out.month - 1) * 30 + check_out.day) - (((check_in.month - 1) * 30) + check_in.day));

    cout << "room price is " << total_price << endl;
    cout << "do you want to reserve this room ? \n  1- yes\n  2- no" << endl;
    string choice;
    cin >> choice;

    while (!check_number(choice) && (stoi(choice) > 2 || stoi(choice) < 1)){
        cout << endl << "Enter a valid choice number: ";
        cin >> choice;
    }

    if (stoi(choice) == 2){
        cout << "reservation canceled" << endl;
        return;
    }

    curr_customer.set_total_price(total_price);
    curr_customer.set_currunt_room(room__id);
    curr_customer.set_payment_status(1);
    curr_hotel.add_customer(curr_customer);
}

void update_room_data()
{
    string choicestr3;

    cout << "enter room number: ";
    string room_number;
    cin >> room_number;
    while (!check_number(room_number) || !(stoi(room_number) <= 50 && stoi(room_number) >= 1))
    {
        cout << endl;
        cout << "Enter a valid room number: ";
        cin >> room_number;
    }
    room curr_room = curr_hotel.get_room(stoi(room_number));
    do
    {
        cout << "enter which data you want to update: \n  1- room type \n  2- room price \n  3- room capacity \n  4- room beds \n  5- room floor \n  6- room status \n  7-exit \n";
        string choicestr;
        cin >> choicestr;
        while (!check_number(choicestr) || !(stoi(choicestr) <= 7 && stoi(choicestr) >= 1))
        {
            cout << endl;
            cout << "Enter a valid choice number: ";
            cin >> choicestr;
        }
        int choice = stoi(choicestr);
        if (choice == 1)
        {
            cout << "enter new room type: \n  1- single \n  2- double \n  3- suite \n";
            string room_type;
            cin >> room_type;
            while (!check_number(room_type) || !(stoi(room_type) <= 3 && stoi(room_type) >= 1))
            {
                cout << endl;
                cout << "Enter a valid room type number: ";
                cin >> room_type;
            }
            curr_room.set_room_type(room_types[stoi(room_type) - 1]);
        }
        if (choice == 2)
        {
            cout << "enter new room price: ";
            string room_price;
            cin >> room_price;
            while (!check_number(room_price))
            {
                cout << endl;
                cout << "Enter a valid room price: ";
                cin >> room_price;
            }
            curr_room.set_room_price(stoi(room_price));
        }
        if (choice == 3)
        {
            cout << "enter new room capacity: ";
            string room_capacity;
            cin >> room_capacity;
            while (!check_number(room_capacity))
            {
                cout << endl;
                cout << "Enter a valid room capacity: ";
                cin >> room_capacity;
            }
            curr_room.set_room_capacity(stoi(room_capacity));
        }
        if (choice == 4)
        {
            cout << "enter new room beds: ";
            string room_beds;
            cin >> room_beds;
            while (!check_number(room_beds))
            {
                cout << endl;
                cout << "Enter a valid room beds: ";
                cin >> room_beds;
            }
            curr_room.set_room_beds(stoi(room_beds));
        }
        if (choice == 5)
        {
            cout << "enter new room floor: ";
            string room_floor;
            cin >> room_floor;
            while (!check_number(room_floor))
            {
                cout << endl;
                cout << "Enter a valid room floor: ";
                cin >> room_floor;
            }
            curr_room.set_room_floor(stoi(room_floor));
        }
        if (choice == 6)
        {
            cout << "enter new room status: ";
            string room_status;
            cin >> room_status;
            while (!check_number(room_status))
            {
                cout << endl;
                cout << "Enter a valid room status: ";
                cin >> room_status;
            }
            cout << "enter the date of this status: " << endl;
            cout << "enter day: ";
            string day, month, year;
            cin >> day;
            while (!check_number(day) || !(stoi(day) <= 31 && stoi(day) >= 1))
            {
                cout << endl;
                cout << "Enter a valid day : ";
                cin >> day;
            }
            cout << "enter month: ";
            cin >> month;
            while (!check_number(month) || !(stoi(month) <= 12 && stoi(month) >= 1))
            {
                cout << endl;
                cout << "Enter a valid month : ";
                cin >> month;
            }
            cout << "enter year: ";
            cin >> year;
            while (!check_number(year))
            {
                cout << endl;
                cout << "Enter a valid year : ";
                cin >> year;
            }
            date status_date = date(stoi(day), stoi(month), stoi(year));
            curr_room.set_room_status_day(status_date, stoi(room_status));
        }
        if (choice == 7)
        {
            return;
        }
        // curr_room.print();
        curr_hotel.update_room(stoi(room_number), curr_room);
        cout << "do you want to update another field? \n 1- yes \n 2- no \n";
        cin >> choicestr3;
        while (!check_number(choicestr3) && (stoi(choicestr3) > 2 || stoi(choicestr3) < 1))
        {
            cout << endl;
            cout << "Enter a valid choice number: ";
            cin >> choicestr3;
        }
    } while (choicestr3 == "1");
}
void show_hotel_date()
{
    curr_hotel.print();
}

void update_customer_data()
{
    cout << "enter which method you want to search about the custmer by: \n";
    cout << "1- id\n";
    cout << "2- name\n";
    string choicestr;
    cin >> choicestr;
    while (!check_number(choicestr) || !(stoi(choicestr) <= 2 && stoi(choicestr) >= 1))
    {
        cout << endl;
        cout << "Enter a valid choice number: ";
        cin >> choicestr;
    }
    int choice = stoi(choicestr);
    customer curr_customer;
    if (choice == 1)
    {
        cout << "enter customer id: ";
        string id;
        cin >> id;
        while (!check_number(id) || curr_hotel.get_customers_by_id(stoi(id)).get_id() == 0)
        {
            cout << endl;
            cout << "Enter a valid customer id: ";
            cin >> id;
        }
        curr_customer = curr_hotel.get_customers_by_id(stoi(id));
    }
    if (choice == 2)
    {
        cout << "enter customer name: ";
        string name;
        cin >> name;
        while (!check_str(name) || curr_hotel.get_customers_by_name(name).sz == 0)
        {
            cout << endl;
            cout << "Enter a valid customer name: ";
            cin >> name;
        }
        auto result = curr_hotel.get_customers_by_name(name);
        cout << "choose the customer you want to update: \n";
        for (int i = 0; i < result.sz; i++)
        {
            cout << i + 1 << "- ";
            result[i].print();
        }
        string choice3str;
        cin >> choice3str;
        while (!check_number(choice3str) || !(stoi(choice3str) <= result.sz && stoi(choice3str) >= 1))
        {
            cout << endl;
            cout << "Enter a valid choice number: ";
            cin >> choice3str;
        }
        int choice3 = stoi(choice3str);
        curr_customer = result[choice3 - 1];
    }
    string choice3;
    do
    {
        cout << "enter which data you want to update: \n 1- customer id \n 2- customer age \n 3- customer hotel id \n 4- customer total price \n 5- customer payment status \n 6- customer reservation status \n 7- customer national id \n 8- customer address \n 9- customer nationality \n 10- customer name \n 11- customer email \n 12- customer phone number \n 13- customer check in date \n 14- customer check out date \n 15- customer room number \n 16- Exit \n";
        string choice2str;
        cin >> choice2str;
        while (!check_number(choice2str) || !(stoi(choice2str) <= 16 && stoi(choice2str) >= 1))
        {
            cout << endl;
            cout << "Enter a valid choice number: ";
            cin >> choice2str;
        }
        int choice2 = stoi(choice2str);
        if (choice2 == 1)
        {
            cout << "enter new customer id: ";
            string id;
            cin >> id;
            while (!check_number(id) || (curr_hotel.get_customers_by_id(stoi(id)).get_id() == stoi(id)))
            {
                cout << endl;
                cout << "Enter a valid customer id: ";
                cin >> id;
            }

            curr_customer.set_id(stoi(id));
        }
        if (choice2 == 2)
        {
            cout << "enter new customer age: ";
            string age;
            cin >> age;
            while (!check_number(age))
            {
                cout << endl;
                cout << "Enter a valid customer age: ";
                cin >> age;
            }
            curr_customer.set_age(stoi(age));
        }

        if (choice2 == 3)
        {
            cout << "enter new customer hotel id: ";
            string hotel_id;
            cin >> hotel_id;
            while (!check_number(hotel_id) || curr_hotel.get_id() != (stoi(hotel_id)))
            {
                cout << endl;
                cout << "Enter a valid customer hotel id: ";
                cin >> hotel_id;
            }
            curr_customer.set_hotel_id(stoi(hotel_id));
        }
        if (choice2 == 4)
        {
            cout << "enter new customer total price: ";
            string total_price;
            cin >> total_price;
            while (!check_number(total_price))
            {
                cout << endl;
                cout << "Enter a valid customer total price: ";
                cin >> total_price;
            }
            curr_customer.set_total_price(stoi(total_price));
        }
        if (choice2 == 5)
        {
            cout << "enter new customer payment status: ";
            string payment_status;
            cin >> payment_status;
            while (!check_number(payment_status))
            {
                cout << endl;
                cout << "Enter a valid customer payment status: ";
                cin >> payment_status;
            }
            curr_customer.set_payment_status(stoi(payment_status));
        }
        if (choice2 == 6)
        {
            cout << "enter new customer reservation status: ";
            string reservation_status;
            cin >> reservation_status;
            while (!check_number(reservation_status))
            {
                cout << endl;
                cout << "Enter a valid customer reservation status: ";
                cin >> reservation_status;
            }
            curr_customer.set_reservation_number(stoi(reservation_status));
        }
        if (choice2 == 7)
        {
            cout << "enter new customer national id: ";
            string national_id;
            cin >> national_id;
            while (!check_number(national_id))
            {
                cout << endl;
                cout << "Enter a valid customer national id: ";
                cin >> national_id;
            }
            curr_customer.set_national_id(national_id);
        }
        if (choice2 == 8)
        {
            cout << "enter new customer address: ";
            string address;
            cin >> address;
            curr_customer.set_address(address);
        }
        if (choice2 == 9)
        {
            cout << "enter new customer nationality: ";
            string nationality;
            cin >> nationality;
            while (!check_str(nationality))
            {
                cout << endl;
                cout << "Enter a valid customer nationality: ";
                cin >> nationality;
            }
            curr_customer.set_nationality(nationality);
        }
        if (choice2 == 10)
        {
            cout << "enter new customer name: ";
            string name;
            cin >> name;
            while (!check_str(name))
            {
                cout << endl;
                cout << "Enter a valid customer name: ";
                cin >> name;
            }
            curr_customer.set_name(name);
        }
        if (choice2 == 11)
        {
            cout << "enter new customer email: ";
            string email;
            cin >> email;
            curr_customer.set_email(email);
        }
        if (choice2 == 12)
        {
            cout << "enter new customer phone number: ";
            string phone_number;
            cin >> phone_number;
            while (!check_number(phone_number))
            {
                cout << endl;
                cout << "Enter a valid customer phone number: ";
                cin >> phone_number;
            }
            curr_customer.set_phone(phone_number);
        }
        if (choice2 == 13)
        {
            cout << "enter new customer check in date: \n";
            cout << "enter day: ";
            string day, month, year;
            cin >> day;
            while (!check_number(day) || !(stoi(day) <= 31 && stoi(day) >= 1))
            {
                cout << endl;
                cout << "Enter a valid day : ";
                cin >> day;
            }
            cout << "enter month: ";
            cin >> month;
            while (!check_number(month) || !(stoi(month) <= 12 && stoi(month) >= 1))
            {
                cout << endl;
                cout << "Enter a valid month : ";
                cin >> month;
            }
            cout << "enter year: ";
            cin >> year;
            while (!check_number(year))
            {
                cout << endl;
                cout << "Enter a valid year : ";
                cin >> year;
            }
            date check_in_date = date(stoi(day), stoi(month), stoi(year));
            curr_customer.set_check_in(check_in_date);
        }
        if (choice2 == 14)
        {
            cout << "enter new customer check out date: \n";
            cout << "enter day: ";
            string day, month, year;
            cin >> day;
            while (!check_number(day) || !(stoi(day) <= 31 && stoi(day) >= 1))
            {
                cout << endl;
                cout << "Enter a valid day : ";
                cin >> day;
            }
            cout << "enter month: ";
            cin >> month;
            while (!check_number(month) || !(stoi(month) <= 12 && stoi(month) >= 1))
            {
                cout << endl;
                cout << "Enter a valid month : ";
                cin >> month;
            }
            cout << "enter year: ";
            cin >> year;
            while (!check_number(year) || stoi(year) != curr_customer.get_check_in().year)
            {
                cout << endl;
                cout << "Enter a valid year : ";
                cin >> year;
            }
            date check_out_date = date(stoi(day), stoi(month), stoi(year));
            curr_customer.set_check_out(check_out_date);
        }
        if (choice2 == 15)
        {
            cout << "enter new customer room number: ";
            string room_number;
            cin >> room_number;
            while (!check_number(room_number) || curr_hotel.get_room(stoi(room_number)).get_room_status(curr_customer.get_check_in()) != 0 || !(stoi(room_number) <= 50 && stoi(room_number) >= 1))

            {
                cout << endl;
                cout << "Enter a valid room number: ";
                cin >> room_number;
            }
            curr_customer.set_currunt_room(stoi(room_number));
        }
        if(choice2==16){
            return;
        }
        curr_hotel.update_customer(curr_customer.get_id(), curr_customer);

        cout << "do you want to update another field? \n  1-yes\n  2-no\n ";
        cin >> choice3;
        while (!check_number(choice3) || !(stoi(choice3) <= 2 && stoi(choice3) >= 1))
        {
            cout << endl;
            cout << "Enter a valid choice: ";
            cin >> choice3;
        }
    } while (choice3 == "1");
}
void search_for_customer()
{
    cout << "enter which method you want to search about the custmer by: \n";
    cout << "1- id\n";
    cout << "2- name\n";
    string choicestr;
    cin >> choicestr;
    while (!check_number(choicestr) || !(stoi(choicestr) <= 2 && stoi(choicestr) >= 1))
    {
        cout << endl;
        cout << "Enter a valid choice: ";
        cin >> choicestr;
    }
    int choice = stoi(choicestr);
    customer curr_customer;
    if (choice == 1)
    {
        cout << "enter customer id: ";
        string id;
        cin >> id;
        while (!check_number(id))
        {
            cout << endl;
            cout << "Enter a valid customer id: ";
            cin >> id;
        }
        curr_customer = curr_hotel.get_customers_by_id(stoi(id));
        if (curr_customer.get_id() == 0)
        {
            cout << "customer not found\n";
            return;
        }
    }
    if (choice == 2)
    {
        cout << "enter customer name: ";
        string name;
        cin >> name;
        while (!check_str(name))
        {
            cout << endl;
            cout << "Enter a valid customer name: ";
            cin >> name;
        }
        auto result = curr_hotel.get_customers_by_name(name);
        if (result.size() == 0)
        {
            cout << "customer not found\n";
            return;
        }
        cout << "all customers with the name \"" << name << "\": \n";
        for (int i = 0; i < result.size(); i++)
        {
            cout << i + 1 << "- ";
            result[i].print();
        }
        return;
    }
    curr_customer.print();
}
void show_all_customers()
{
    curr_hotel.print_customers();
}

void delete_customer()
{
    cout << "enter which method you want to delete the custmer by: \n";
    cout << "1- id\n";
    cout << "2- name\n";
    int choice;
    string choicestr;
    cin >> choicestr;
    while (!check_number(choicestr) || !(stoi(choicestr) <= 2 && stoi(choicestr) >= 1))
    {
        cout << endl;
        cout << "Enter a valid choice: ";
        cin >> choicestr;
    }
    choice = stoi(choicestr);
    int curr_id;
    if (choice == 1)
    {
        cout << "enter customer id: ";
        string id;
        cin >> id;
        while (!check_number(id))
        {
            cout << endl;
            cout << "Enter a valid customer id: ";
            cin >> id;
        }
        curr_id = stoi(id);
    }
    if (choice == 2)
    {
        customer curr_customer;
        cout << "enter customer name: ";
        string name;
        cin >> name;
        while (!check_str(name))
        {
            cout << endl;
            cout << "Enter a valid customer name: ";
            cin >> name;
        }
        auto result = curr_hotel.get_customers_by_name(name);
        if (result.size() == 0)
        {
            cout << "customer not found\n";
            return;
        }
        cout << "all customers with the name \"" << name << "\": \n";
        for (int i = 0; i < result.size(); i++)
        {
            cout << i + 1 << "- ";
            result[i].print();
        }
        cout << "enter the number of the customer you want to delete: ";
        string num;
        cin >> num;
        while (!check_number(num) || !(stoi(num) <= result.size() && stoi(num) >= 1))
        {
            cout << endl;
            cout << "Enter a valid number: ";
            cin >> num;
        }
        curr_customer = result[stoi(num) - 1];
        curr_id = curr_customer.get_id();
    }
    curr_hotel.remove_customer(curr_id);

}

void show_all_available_rooms()
{
    date now;
    cout << "enter today's date: \n";
    cout << "enter day: ";
    string day, month, year;
    cin >> day;
    while (!check_number(day) || !(stoi(day) <= 31 && stoi(day) >= 1))
    {
        cout << endl;
        cout << "Enter a valid day : ";
        cin >> day;
    }
    cout << "enter month: ";
    cin >> month;
    while (!check_number(month) || !(stoi(month) <= 12 && stoi(month) >= 1))
    {
        cout << endl;
        cout << "Enter a valid month : ";
        cin >> month;
    }
    cout << "enter year: ";
    cin >> year;
    while (!check_number(year))
    {
        cout << endl;
        cout << "Enter a valid year : ";
        cin >> year;
    }
    now = date(stoi(day), stoi(month), stoi(year));
    curr_hotel.show_available_rooms(now);
}

void show_all_reserved_rooms()
{
    date now;
    cout << "enter today's date: \n";
    cout << "enter day: ";
    string day, month, year;
    cin >> day;
    while (!check_number(day) || !(stoi(day) <= 31 && stoi(day) >= 1))
    {
        cout << endl;
        cout << "Enter a valid day : ";
        cin >> day;
    }
    cout << "enter month: ";
    cin >> month;
    while (!check_number(month) || !(stoi(month) <= 12 && stoi(month) >= 1))
    {
        cout << endl;
        cout << "Enter a valid month : ";
        cin >> month;
    }
    cout << "enter year: ";
    cin >> year;
    while (!check_number(year))
    {
        cout << endl;
        cout << "Enter a valid year : ";
        cin >> year;
    }
    now = date(stoi(day), stoi(month), stoi(year));
    curr_hotel.show_reserved_rooms(now);
}

void show_all_rooms()
{
    curr_hotel.print_rooms();
}

void show_hotel_data()
{
    curr_hotel.print();
}

void menu()
{
    int choice;
    do
    {
        cout << "choose one of the following options" << endl << endl;
        cout << "1- Add new customer" << endl;
        cout << "2- update customer data" << endl;
        cout << "3- update room data" << endl;
        cout << "4- delete customer" << endl;
        cout << "5- search for customer" << endl;
        cout << "6- show all customers" << endl;
        cout << "7- show all available rooms" << endl;
        cout << "8- show all reserved rooms" << endl;
        cout << "9- show all rooms" << endl;
        cout << "10- show hotel data" << endl;
        cout << "11- exit" << endl;
        cin >> choice;
        while (choice < 1 or choice > 11)
        {
            cout << "Wrong choice, Enter a number between 1 and 11 : ";
            cin >> choice;
        }
        int choice2;
        string choice2str;
        if (choice == 1)
        {
            do
            {
                add_new_customer();
                cout << "do you want to add another customer?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 2)
        {
            do
            {
                update_customer_data();
                cout << "do you want to update another customer?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 3)
        {
            do
            {
                update_room_data();
                cout << "do you want to update another room?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 4)
        {
            do
            {
                delete_customer();
                cout << "do you want to delete another customer?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 5)
        {
            do
            {
                search_for_customer();
                cout << "do you want to search for another customer?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 6)
        {
            do
            {
                show_all_customers();
                cout << "do you want to show all customers again?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 7)
        {
            do
            {
                show_all_available_rooms();
                cout << "do you want to show all available rooms again?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 8)
        {
            do
            {
                show_all_reserved_rooms();
                cout << "do you want to show all reserved rooms again?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 9)
        {
            do
            {
                show_all_rooms();
                cout << "do you want to show all rooms again?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 10)
        {
            do
            {
                show_hotel_data();
                cout << "do you want to show hotel data again?\n  1-yes\n  2-no\n ";
                cin >> choice2str;
                while (!check_number(choice2str) || !(stoi(choice2str) <= 2 && stoi(choice2str) >= 1))
                {
                    cout << endl;
                    cout << "Enter a valid choice: ";
                    cin >> choice2str;
                }
                choice2 = stoi(choice2str);
            } while (choice2 == 1);
        }
        if (choice == 11)
        {
            cout << "thank you for using our program\n";
        }

    } while (choice != 11);
}

void shut_down(){
    fstream customer_file, room_file;
    customer_file.open("data_files/customers_data.csv", ios::out);
    room_file.open("rooms_data.csv", ios::out);

    if (!customer_file.is_open()){
        cout << fileror("data_files/customers_data.csv") << endl;
        exit(0);
    }

    if (!room_file.is_open()){
        cout << fileror("rooms_data.csv") << endl;
        exit(0);
    }

    cout<<"saving data...\n";
    customer_file << customers_data_template[0];
    for(int i = 1; i < customers_data_template.sz; i++){
        customer_file << " ," << customers_data_template[i];
    }

    customer_file << endl;

    vector < customer > customers = curr_hotel.get_customers();
    for(int i = 0; i < customers.sz; i++){
        customer_file << customers[i].get_id() << "," << customers[i].get_hotel_id() << "," << customers[i].get_age() << "," << customers[i].get_payment_status() << ","
        << customers[i].get_reservation_status() << "," << customers[i].get_national_id() << "," << customers[i].get_address() << "," << customers[i].get_nationality() << ','
        << customers[i].get_name() << ',' << customers[i].get_email() << ',' << customers[i].get_phone() << ',';
        customer_file << customers[i].get_check_in().year;

        if(customers[i].get_check_in().month<10){
            customer_file << 0;
        }

        customer_file << customers[i].get_check_in().month;
        if(customers[i].get_check_in().day < 10){
            customer_file << 0;
        }

        customer_file << customers[i].get_check_in().day << ',';
        customer_file << customers[i].get_check_out().year;
        if(customers[i].get_check_out().month < 10){
            customer_file << 0;
        }

        customer_file << customers[i].get_check_out().month;
        if(customers[i].get_check_out().day < 10){
            customer_file << 0;
        }

        customer_file << customers[i].get_check_out().day << ',';
        customer_file << customers[i].get_room();
        if(i!=customers.sz - 1){
            customer_file << endl;
        }
    }

    room_file << rooms_data_template[0];
    for(int i = 1;i < rooms_data_template.sz; i++){
        room_file << "," << rooms_data_template[i];
    }
    room_file << endl;
    vector < room > rooms=curr_hotel.get_rooms();
    for(int i = 1; i <rooms.sz; i++){
        room_file << rooms[i].get_room_number() << "," << rooms[i].get_hotel_id() << "," << rooms[i].get_room_type() << "," << rooms[i].get_room_price() << ','
         << rooms[i].get_room_capacity() << ',' << rooms[i].get_room_capacity() << ',' << rooms[i].get_room_beds() << ',' << rooms[i].get_room_floor() << ',';

        vector < int > status = rooms[i].get_room_status();
        for(auto j: status){
            room_file << j;
        }

        if(i != rooms.sz - 1){
            room_file << endl;
        }
    }

    customer_file.close();
    room_file.close();
    cout << "data saved successfully\n";

}
int main()
{
    startup();
    menu();
    shut_down();
    return 0;
}

