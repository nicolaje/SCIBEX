#include "CtcFactory.h"

using namespace std;
using namespace ibex;

ibex::Ctc* CtcFactory::getCtc(const int &dim, const string &ctcName, const QJsonObject &params)
{
    switch (stringToInt(ctcName))
    {
    case CPLUS:
    {
        cout << "CPLUS" << endl;
        // Why do I have to declare a pointer on NumConstraint?
        NumConstraint *numC=new NumConstraint("z", "x", "y", "z=x+y");
        Ctc *ctc = new CtcFwdBwd(*numC);
        return ctc;
        break;
    }
    default:
        return 0;
    }
}

int CtcFactory::stringToInt(const std::string &ctcName)
{
    if (ctcName == "CPLUS")
    {
        return CPLUS;
    }
    else if (ctcName == "CMOINS")
    {
        return CMOINS;
    }
    else
    {
        return ERROR;
    }
}