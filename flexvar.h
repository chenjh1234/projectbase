#ifndef FLEXVAR_H
#define FLEXVAR_H

using namespace std;
#include "sysdefine.h"
#include <stdio.h>
#include <string>
#include <vector>
#include "comfun.h"

class flexVar
{
public:
    flexVar(){m_type = TP_UNKNOWN;};
    ~flexVar(){};
    flexVar(int f){ set(f);};
    flexVar(float f){ set(f);};
    flexVar(double f){set(f);};
    flexVar(string f){set(f);};
    flexVar(char *f){ set(f);};
    void set(int f){ m_int = f;m_type = TP_INT;};
    void set(float f){ m_float = f;m_type = TP_FLOAT;};
    void set(double f){ m_double = f;m_type = TP_DOUBLE;};
    void set(string f){ m_string = f;m_type = TP_STRING;};
    void set(char *f){ m_string = f;m_type = TP_STRING;};

    int getInt(){return m_type == TP_INT?m_int:-1;};
    float getFloat(){return m_type == TP_FLOAT?m_float:-1;};
    double getDouble(){return m_type == TP_DOUBLE?m_double:-1;};
    string getString(){return m_type == TP_STRING?m_string:"err";};

    int type(){return m_type;};

    string toString()
    {
        switch (m_type) 
        {
        case TP_UNKNOWN:
            return "UNKOWN";
        case TP_INT:
            return toStr(m_int);
        case TP_FLOAT:
            return toStr(m_float);
        case TP_DOUBLE:
            return toStr(m_double);
        case TP_STRING:
            return m_string;
        }
        return  "UNKOWN";
    }; 

    int m_int;
    float m_float;
    double m_double;
    string m_string;

    enum VAR_TYPE
    {
       TP_UNKNOWN,
       TP_INT,
       TP_FLOAT,
       TP_DOUBLE,
       TP_STRING
    } m_type;
};





#endif
