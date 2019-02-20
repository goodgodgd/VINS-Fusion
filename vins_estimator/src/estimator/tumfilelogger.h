#ifndef TUMFILELOGGER_H
#define TUMFILELOGGER_H

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class TumFileLogger 
{
public:
    static TumFileLogger& instance() 
    { 
        static TumFileLogger* instance = new TumFileLogger(); 
        return *instance; 
    }

    void init(string filename_)
    {
        filename = filename_;
        frame_log.clear();
    }

    void push(vector<double> frameres)
    {
        frame_log.push_back(frameres);
    }

    void dump()
    {
        cout << "dump pose results on " << filename << endl;
        cout << "num frames = " << frame_log.size() << endl;
        ofstream fout(filename, ios::trunc);
        fout.setf(ios::fixed, ios::floatfield);
        fout.precision(6);
        for(auto frameres: frame_log)
        {
            for(double val: frameres)
                fout << val << " ";
            fout << endl;
        }
    }

private:
    TumFileLogger() {}
    vector<vector<double>> frame_log;
    string filename;
};

#endif
