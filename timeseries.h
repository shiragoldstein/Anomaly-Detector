

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <map>
#include <vector>

using namespace std;
class TimeSeries{
   private :const char* CSVfileName;
   private :std::vector<string> keysOfMap;
   private :std::map<string, vector<float>> map;
public:
	explicit TimeSeries(const char* CSVfileName);
    //TimeSeries();
    /*void print();
    const char* getCSVfileName();*/
    std::vector<string> getKeysOfMap();
    std::map<string, vector<float>> getMap();
};
#endif /* TIMESERIES_H_ */