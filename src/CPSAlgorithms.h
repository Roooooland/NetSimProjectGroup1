//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __INBAVERSIM_CPSALGORITHMS_H_
#define __INBAVERSIM_CPSALGORITHMS_H_

#include <omnetpp.h>
#include <cstdlib>
#include <string>
#include <queue>

#include "Demiurge.h"
#include "inbaver.h"
#include "RFC8609Messages_m.h"
#include "InternalMessages_m.h"
#include "Numen.h"
#include "RFC8569Forwarder.h"

using namespace omnetpp;
using namespace std;

class Demiurge;
class Numen;

using namespace omnetpp;


class CPSAlgorithms : public cSimpleModule
{
protected:
    virtual void initialize();
    virtual void handleMessage();
    virtual void finish();
private:
    int choose_algorithm;
    list<CSEntry *> cps_cs;
    list<PITEntry *> cps_pit;
    long currentCSSize;

//    simsignal_t cacheRemovalsBytesSignal;
//    simsignal_t cacheSizeBytesSignal;
//    simsignal_t cacheAdditionsBytesSignal;
//    simsignal_t totalContentObjsBytesSentSignal;
//    simsignal_t pitEntryCountSignal;

public:
    virtual int getPIThobcount(ContentObjMsg *contentObjMsg) const;


    virtual void setValues(int algorithm, list <CSEntry *> cs, list<PITEntry *> pit, long currentCSSize);

    virtual void ContentObjhandle(ContentObjMsg *contentObjMsg,CSEntry *csentry,int maximumContentStoreSize, long *additionalBytes,long *removed);
    virtual list <CSEntry *> getCS();

    virtual int Interesthandling(InterestMsg* interestMsg, PITEntry *pitEntry,ArrivalInfo *arrivalInfo,FaceEntry *arrivalFaceEntry,ExchangedTransportInfo *arrivalTransportInfo);
    virtual list <PITEntry *> getPIT();

    virtual long getcurrentCSSize();
    virtual void removeCSEntry(int maximumContentStoreSize,ContentObjMsg *contentObjMsg,long *removed);
    virtual void generellOperations(ContentObjMsg *contentObjMsg,CSEntry *csentry,int maximumContentStoreSize, long *additionalBytes,long *removed);

};

#endif
