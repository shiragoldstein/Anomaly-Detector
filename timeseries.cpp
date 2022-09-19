#include "timeseries.h"
#include <map>
#include <sstream>
#include <fstream>
#include <stdlib.h>
using namespace std;

/*TimeSeries::TimeSeries() : TimeSeries(this->CSVfileName){

}*/
TimeSeries::TimeSeries(const char* CSVfileName){
    /*if(!CSVfileName){
        cout << "wrong, there is no csv file name yet, exit the function" << '\n';
        return;
    }*/
    int i=0;
    std::vector<float> valueVect;
    std::vector<string> keyVect;
    std::vector<float> emptyVect;
    std::map<string, vector<float>> myMap;
    string line;
    ifstream myfile (CSVfileName);
    if (myfile.is_open())
    {
        while (getline (myfile,line)) {
            if (i==0){
                stringstream ss(line);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    keyVect.push_back(substr);
                }
                for (size_t k = 0; k < keyVect.size(); k++) {
                    string currentKey = keyVect[k];
                    myMap[currentKey] = emptyVect;
                }
            }
            else{
                stringstream ss(line);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    valueVect.push_back(stof(substr));
                }
                for (size_t k = 0; k < keyVect.size(); k++) {
                    myMap[keyVect[k]].push_back(valueVect[k]);
                }
                valueVect = emptyVect;
            }
            i++;
        }
        myfile.close();
    }
    //else cout << "Unable to open file\n";
    this->map = myMap;
    this->keysOfMap = keyVect;
    this->CSVfileName = CSVfileName;
}

/*void TimeSeries::print(){
    *//*print map*//*
    cout << "start printing the map:" << '\n';
    for (std::size_t k = 0; k < this->keysOfMap.size(); k++){
        cout << "the key is: " << this->keysOfMap[k] << " and its value are:\n";
        for (int m=0; m<this->map[this->keysOfMap[k]].size(); m++){
            cout << this->map[this->keysOfMap[k]][m] << endl;
        }
    }
    cout << "the map size is (number of columns): " << this->map.size() << "\n\n";
}

const char* TimeSeries::getCSVfileName() {
    return this->CSVfileName;
}*/

std::vector<string> TimeSeries::getKeysOfMap() {
    return this->keysOfMap;
}

std::map<string, vector<float>> TimeSeries::getMap() {
    return this->map;
}




/*std::map<string, vector<float>> readFromFile(){
    int i=0;
    std::vector<float> valueVect;
    std::vector<string> keyVect;
    std::vector<float> emptyVect;
    std::map<string, vector<float>> myMap;
    string line;
    ifstream myfile ("trainFile1.csv");
    if (myfile.is_open())
    {
        while (getline (myfile,line)) {
            cout << line << '\n';
            if (i==0){
                stringstream ss(line);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    keyVect.push_back(substr);
                }
                for (size_t k = 0; k < keyVect.size(); k++) {
                    string currentKey = keyVect[k];
                    myMap[currentKey] = emptyVect;
                    cout << keyVect[k] << '\n';
                }
                cout << keyVect.size() << '\n';
            }
            else{
                stringstream ss(line);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    valueVect.push_back(stof(substr));
                }
                for (size_t k = 0; k < keyVect.size(); k++) {
                    myMap[keyVect[k]].push_back(valueVect[k]);
                }
                valueVect = emptyVect;
            }
            i++;

        }
        myfile.close();
    }
    else cout << "Unable to open file";
    cout << myMap.size() << '\n';
    cout << i << '\n';*/

    /*print map
    cout << "start printing the map" << '\n';
    for (std::size_t k = 0; k < keyVect.size(); k++){
        cout << keyVect[k] << '\n';
        for (int m=0; m<myMap[keyVect[k]].size(); m++){
            cout << myMap[keyVect[k]][m] << endl;
        }
    }*/
   /* return myMap;
}*/
