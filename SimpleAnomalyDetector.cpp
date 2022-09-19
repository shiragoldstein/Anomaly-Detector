
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"


SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
    //copy to a not const timeseries
    TimeSeries ts1 = ts;
    //find all the correlative features
    //i is the feature 1
    for(int i = 0; i < ts1.getMap().size(); i++) {
        float m = 0;
        float c = -1;
        vector<float> f_i = ts1.getMap()[(string)ts1.getKeysOfMap()[i]];
        //j is the feature 2
        for(int j = i + 1; j < ts1.getMap().size(); j++) {
            vector<float> f_j = ts1.getMap()[(string)ts1.getKeysOfMap()[j]];
            //save the pearson value in p
            float p = abs(pearson(f_i.data(), f_j.data(), f_i.size()));
            if (p > m) {
                m = p;
                c = j;
            }
        }
        if (c != -1) {
            //check if they are correlative
            if (m > 0.9) {
                vector<float> f_c = ts1.getMap()[(string) ts1.getKeysOfMap()[c]];
                //create new correlative feature
                correlatedFeatures new_correlative;
                new_correlative.feature1 = ts1.getKeysOfMap()[i];
                new_correlative.feature2 = ts1.getKeysOfMap()[c];
                new_correlative.corrlation = m;
                new_correlative.lin_reg = linear_reg(pointVector(f_i, f_c).data(), (int)f_i.size());
                new_correlative.threshold = biggestDev(new_correlative.lin_reg, pointVector(f_i, f_c));
                //add them to the vector of cf
                this->cf.push_back(new_correlative);
            }
        }
    }
}

//find the maximal
float biggestDev(Line line, vector<Point*> points) {
    float threshold = 0;
    float t = 0.0;
    for (int i = 0; i < points.size(); i++) {
        t = dev(*(points[i]), line);
        if(t > threshold) {
            threshold = t;
        }
    }
    return threshold * (float)1.1;
}



//return vector of pointer to points that made of the given columns vectors
std::vector<Point*> pointVector(vector<float> f1, vector<float> f2) {
    vector<Point*> points;
    for (int i = 0; i < f1.size(); i++) {
        Point* p = new Point((float)f1[i],(float)f2[i]);
        points.push_back(p);
    }
    return points;
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts) {
    //float arr[] = ts.giveData();
    vector<AnomalyReport> repotrs;
    vector<correlatedFeatures> my_cf = getNormalModel();
    TimeSeries realTs = ts;
    std::map<string, vector<float>> myMap = realTs.getMap();
    //realTs.print();
    unsigned long size_cf = my_cf.size();
    for (int i=0; i<size_cf; i++){
        string f1 = my_cf[i].feature1;
        string f2 = my_cf[i].feature2;
        std::vector<Point*> pointsVector = pointVector(myMap[f1], myMap[f2]);
        unsigned long points_vector_size = pointsVector.size();
        for (int j=0; j<points_vector_size; j++){
            float t = dev(*pointsVector[j], my_cf[i].lin_reg);
            if(t > my_cf[i].threshold) {
                string report_str = f1 + "-" + f2;
                AnomalyReport* report = new AnomalyReport(report_str, j+1);
                repotrs.push_back(*report);
            }
        }

    }
    return repotrs;
	// TODO Auto-generated destructor stub
}

