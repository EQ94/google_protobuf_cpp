#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
using namespace std;

// Iterates though all people in the AddressBook and printfs info about them
void ListPeople(const tutorial::AddressBook& address_book) {
    for(int i=0; i<address_book.person_size(); i++) {
        const tutorial::Person& person = address_book.person(i);

        cout<<"Person ID: "<<person.id()<<endl;
        cout<<" Name: "<<person.name()<<endl;
        if(person.has_email()) {
            cout<<" E-mail address: "<<person.email() << endl;
        }

        for(int j=0; j<person.phone_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phone(i);

            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    cout<<" Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    cout<<" Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    cout<<" Work phonw #: ";
                    break;
            }
            cout<< phone_number.number() <<endl;
        }
    }
}

// Main function: Reads the entire address book from a file and prints all the information inside
int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if(argc !=2) {
        cerr<<"Usage: "<<argv[0]<<" ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
        // Read the existing address book
        fstream input(argv[1], ios::in | ios::binary);
        if(!address_book.ParseFromIstream(&input)) {
            cerr <<"Failed to parse address book." << endl;
            return -1;
        }
    }
    ListPeople(address_book);
    google::protobuf::ShutdownProtobufLibrary();

    return 0;

}
// g++ read_file.cpp addressbook.pb.cc -L /usr/lib/x86_64-linux-gnu -l protobuf -o read_file
