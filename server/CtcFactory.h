#ifndef CTCFACTORY_H
#define	CTCFACTORY_H

#include <ibex/ibex.h>
#include <QJsonObject>
#include <string>

enum {
    ERROR, CPLUS, CMOINS
};

class CtcFactory {
public:

    // TODO: don't forget to delete the Ctc
    static ibex::Ctc *getCtc(const int &dim, const std::string &ctcName, const QJsonObject &params);

    // Enables the use of a switch control from a string
    static int stringToInt(const std::string &ctcName);
};

#endif	/* CTCFACTORY_H */

