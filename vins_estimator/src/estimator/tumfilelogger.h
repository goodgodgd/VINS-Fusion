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
        pose_log.clear();
        time_log.clear();
    }

    void push_pose(vector<double> pose)
    {
        pose_log.push_back(pose);
    }

    void push_time(double time)
    {
        time_log.push_back(time);
    }

    void dump()
    {
        cout << "dump pose results on " << filename << endl;
        cout << "len(poses) = " << pose_log.size() << ", len(times) = " << time_log.size() << endl;
        ofstream fout(filename, ios::trunc);
        fout.setf(ios::fixed, ios::floatfield);
        fout.precision(6);
        for(size_t i=0; i<pose_log.size(); i++)
        {
            for(double val: pose_log[i])
                fout << val << " ";
            if(i < time_log.size())
                fout << time_log[i] << " ";
            else
                fout << 0. << " ";
            fout << endl;
        }
    }

private:
    TumFileLogger() {}
    vector<vector<double>> pose_log;
    vector<double> time_log;
    string filename;
};

#endif
