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

#include "CPSAlgorithms.h"
#include "InternalMessages_m.h"

Define_Module(CPSAlgorithms);

void CPSAlgorithms::initialize()
{

}
void CPSAlgorithms::handleMessage()
{

}
void CPSAlgorithms::finish() {}

void CPSAlgorithms::ContentObjhandle(ContentObjMsg *contentObjMsg,CSEntry *csentry,int maximumContentStoreSize,long *additionalBytes, long *removed)
{
    long add = 0;
    long rem = 0;
    if (this->choose_algorithm == 0) { //LCE algorithm
        EV_INFO << "\n LCE Algorithm \n";

        this->generellOperations(contentObjMsg, csentry, maximumContentStoreSize,&add,&rem);
    } else if (this->choose_algorithm == 1) { //Leave copy probability
        EV_INFO << "\n LCP Algorithm\n";

        float probability = 1/((float)this->getPIThobcount(contentObjMsg));

        if ((rand() % 100) < probability*100) {
            this->generellOperations(contentObjMsg, csentry, maximumContentStoreSize,&add,&rem);
        }

    } else if (this->choose_algorithm == 2) {   //Leave copy down
        EV_INFO << "\n LCD Algorithm\n";
        this->generellOperations(contentObjMsg, csentry, maximumContentStoreSize,&add,&rem);

    }
    *additionalBytes = add;
    *removed = rem;
    return;
}
void CPSAlgorithms::generellOperations(ContentObjMsg *contentObjMsg,CSEntry *csentry,int maximumContentStoreSize, long *additionalBytes,long *removed)
{
    long rem = 0;
    this->removeCSEntry(maximumContentStoreSize, contentObjMsg,&rem); //remove a cs entry if necessary

    csentry->prefixName = contentObjMsg->getPrefixName();
    csentry->dataName = contentObjMsg->getDataName();
    csentry->versionName = contentObjMsg->getVersionName();
    csentry->segmentNum = contentObjMsg->getSegmentNum();
    csentry->cachetime = contentObjMsg->getCachetime();
    csentry->expirytime = contentObjMsg->getExpirytime();
    csentry->totalNumSegments = contentObjMsg->getTotalNumSegments();
    csentry->payloadAsString = contentObjMsg->getPayloadAsString();
    csentry->payloadSize = contentObjMsg->getPayloadSize();
    this->cps_cs.push_back(csentry);
    this->currentCSSize += contentObjMsg->getPayloadSize();

    EV_INFO << simTime() << "Added Cache entry: "
                << " " << csentry->prefixName
                << " " << csentry->dataName
                << " " << csentry->versionName
                << " " << csentry->segmentNum
                << " " << csentry->payloadSize
                << " " << currentCSSize
                << endl;


    *additionalBytes = csentry->payloadSize;
    *removed = rem;
}


int CPSAlgorithms::getPIThobcount(ContentObjMsg *contentObjMsg) const
{
    const char *prefName = contentObjMsg->getPrefixName();
    const char *dataName = contentObjMsg->getDataName();
    const char *versionName = contentObjMsg->getVersionName();
    for (PITEntry* pit_i : this->cps_pit)
    {
        if ((pit_i->prefixName.compare(prefName)==0) && (pit_i->dataName.compare(dataName)==0) && (pit_i->versionName.compare(versionName) == 0))
        {
            return pit_i->hopsTravelled;
        }
    }
    return 2147483647; //else return 2147483647(int limit) so that probability is low

}
void CPSAlgorithms::setValues(int algorithm, list <CSEntry *> cs, list<PITEntry *> pit, long currentCSSize)
{
    this->choose_algorithm = algorithm;
    this->cps_cs = cs;
    this->cps_pit = pit;
    this->currentCSSize = currentCSSize;
}
long CPSAlgorithms::getcurrentCSSize()
{
    return this->currentCSSize;
}
void CPSAlgorithms::removeCSEntry(int maximumContentStoreSize,ContentObjMsg *contentObjMsg,long *removed)
{

    // before adding content to CS, check if size will exceed the limit
        // when so, remove cache entries until the new content can be added
        if (maximumContentStoreSize > 0) {
            long removedBytes = 0;
            while ((currentCSSize + contentObjMsg->getPayloadSize()) > maximumContentStoreSize) {
                CSEntry *removingCSEntry = this->cps_cs.front();
                this->cps_cs.pop_front();
                currentCSSize -= removingCSEntry->payloadSize;
                removedBytes += removingCSEntry->payloadSize;

                EV_INFO << simTime() << "Cache is full, cannot insert, removing: "
                        << " " << removingCSEntry->prefixName
                        << " " << removingCSEntry->dataName
                        << " " << removingCSEntry->versionName
                        << " " << removingCSEntry->segmentNum
                        << " " << removingCSEntry->payloadSize
                        << " " << currentCSSize
                        << endl;

                delete removingCSEntry;
            }
            *removed = removedBytes;
        }
}

int CPSAlgorithms::Interesthandling(InterestMsg* interestMsg, PITEntry *pitEntry,ArrivalInfo *arrivalInfo,FaceEntry *arrivalFaceEntry,ExchangedTransportInfo *arrivalTransportInfo)
{
    if(this->choose_algorithm < 2) {
        // when there is already a PIT entry, means previous Interests were
            // received, so add the current Interest to the PIT entry
            if (pitEntry != NULL) {

                // Check if the same Interest was received through the same Face and transport address
                bool found = false;
                for (int i = 0; i < pitEntry->arrivalInfoList.size(); i++) {
                    if (pitEntry->arrivalInfoList[i]->receivedFace->faceID == arrivalFaceEntry->faceID) {
                        if (arrivalTransportInfo != NULL) {
                            if (arrivalTransportInfo->transportAddress == pitEntry->arrivalInfoList[i]->receivedFace->transportAddress) {
                                found = true;
                                break;
                            }
                        } else {
                            found = true;
                            break;
                        }
                    }
                }

                // when same Interest was not received from same Face and same transport address
                // then add it to PIT entry
                if (!found) {
                    ArrivalInfo *arrivalInfo = new ArrivalInfo();
                    arrivalInfo->receivedFace = arrivalFaceEntry;
                    if (arrivalTransportInfo != NULL) {
                        arrivalInfo->transportAddress = arrivalTransportInfo->transportAddress;
                    } else {
                        arrivalInfo->transportAddress = "";
                    }

                    EV_INFO << simTime() << "PIT entry exists. Adding new arrival Face: "
                            << pitEntry->prefixName
                            << " " << pitEntry->dataName
                            << " " << pitEntry->versionName
                            << " " << pitEntry->segmentNum
                            << " " << pitEntry->hopLimit
                            << " " << pitEntry->hopsTravelled
                            << " " << arrivalFaceEntry->faceID
                            << " " << arrivalInfo->transportAddress
                            << endl;

                    pitEntry->arrivalInfoList.push_back(arrivalInfo);
                }

                // discard Interest
                delete interestMsg;
                return -1;
            }

            // discard interest if it has reached the maximum hop count
            // only if they arrive from transport type faces (not applications)
            if (arrivalFaceEntry->faceType == TransportTypeFace && (interestMsg->getHopLimit() - 1) <= 0) {

                EV_INFO << simTime() << "Hop limit exceeded. Discarding Interest: "
                        << interestMsg->getHopLimit()
                        << " " << interestMsg->getHopsTravelled()
                        << " " << arrivalFaceEntry->faceDescription
                        << endl;

                delete interestMsg;
                return -1;
            }

        // save Interest in PIT - create new PIT entry
        pitEntry = new PITEntry;
        pitEntry->prefixName = interestMsg->getPrefixName();
        pitEntry->dataName = interestMsg->getDataName();
        pitEntry->versionName = interestMsg->getVersionName();
        pitEntry->segmentNum = interestMsg->getSegmentNum();
        pitEntry->hopLimit = interestMsg->getHopLimit() - 1;
        pitEntry->hopsTravelled = interestMsg->getHopsTravelled() + 1;

        arrivalInfo->receivedFace = arrivalFaceEntry;
        if (arrivalTransportInfo != NULL) {
            arrivalInfo->transportAddress = arrivalTransportInfo->transportAddress;
        } else {
            arrivalInfo->transportAddress = "";

        }
        pitEntry->arrivalInfoList.push_back(arrivalInfo);

        EV_INFO << simTime() << "Adding PIT entry: "
                << pitEntry->prefixName
                << " " << pitEntry->dataName
                << " " << pitEntry->versionName
                << " " << pitEntry->segmentNum
                << " " << pitEntry->hopLimit
                << " " << pitEntry->hopsTravelled
                << " " << arrivalFaceEntry->faceID
                << " " << arrivalInfo->transportAddress
                << endl;

        this->cps_pit.push_back(pitEntry);

    }
    return 0;
}

list <PITEntry *> CPSAlgorithms::getPIT()
{
    return this->cps_pit;
}
list <CSEntry *> CPSAlgorithms::getCS()
{
    return this->cps_cs;
}
