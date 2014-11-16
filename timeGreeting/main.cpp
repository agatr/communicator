#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    string name;

    time_t now =  time(0); //current system time
    tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)

    int hr = ltm->tm_hour;

    cout << "What's your name?" << endl;
    cin >> name;

    if ((hr > 6) && (hr < 12))
    {
        cout << "Good morning, " << name;
    }
    else
    if ((hr > 12) && (hr < 18))
    {
        cout << "Good Afternoon, " << name;
    }
    else
    if ((hr > 18) && (hr < 22))
    {
        cout << "Good Evening, " << name;
    }
    else
    {
        cout << "Good night, " << name;
    }
}
