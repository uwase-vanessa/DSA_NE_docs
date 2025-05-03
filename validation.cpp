#include <iostream>
#include <string>
#include <regex>

using namespace std;

bool isValidNumber(const string& input){
    const regex pattern("^(07[2389])\\d{7}$");
    return regex_match(input, pattern);
}

bool isValidRwandaNationalId(const string& input){
    const regex validRwandaId("^([123])(\\d{4})([78])(\\d{7})(\\d)(\\d{2})$");
    return regex_match(input, validRwandaId);
}

bool isValidDate(const string& input){
    const regex validDate(R"(\d{4}-\d{2}-\d{2})"); // YYYY-MM-DD
    return regex_match(input, validDate);
}

bool isValidEmail(const string& input){
    // the first part [] represent the part before the @ then part after @  then there comes  the part after. which can be two or more characters.
    const regex validEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"); 
    return regex_match(input, validEmail);
}

int main(){

    string rwandaId;
    
    cout << "Enter a valid Rwanda National Id : ";
    getline(cin, rwandaId);

    if(isValidRwandaNationalId(rwandaId))
        cout << "yes that's valid Rwanda id." << endl;
    else 
        cout << "Invalid rwandaId." << endl;
}

