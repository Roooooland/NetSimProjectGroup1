//
// Generated file, do not edit! Created by opp_msgtool 6.0 from InternalMessages.msg.
//

#ifndef __INTERNALMESSAGES_M_H
#define __INTERNALMESSAGES_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class AppRegistrationMsg;
class TransportRegistrationMsg;
class PrefixRegistrationMsg;
class NeighbourListMsg;
/**
 * Class generated from <tt>InternalMessages.msg:13</tt> by opp_msgtool.
 * <pre>
 * //
 * // Format of app registration msg (sent by any app to forwarder).
 * //
 * packet AppRegistrationMsg
 * {
 *     // ID that uniquely identifies the registering app
 *     long appID;
 * 
 *     // is it a content server or a client application?
 *     bool contentServerApp;
 * 
 *     // if content server, the prefixs for which content exist
 *     string hostedPrefixNames[];
 * 
 *     // a description
 *     string appDescription;
 * }
 * </pre>
 */
class AppRegistrationMsg : public ::omnetpp::cPacket
{
  protected:
    long appID = 0;
    bool contentServerApp = false;
    omnetpp::opp_string *hostedPrefixNames = nullptr;
    size_t hostedPrefixNames_arraysize = 0;
    omnetpp::opp_string appDescription;

  private:
    void copy(const AppRegistrationMsg& other);

  protected:
    bool operator==(const AppRegistrationMsg&) = delete;

  public:
    AppRegistrationMsg(const char *name=nullptr, short kind=0);
    AppRegistrationMsg(const AppRegistrationMsg& other);
    virtual ~AppRegistrationMsg();
    AppRegistrationMsg& operator=(const AppRegistrationMsg& other);
    virtual AppRegistrationMsg *dup() const override {return new AppRegistrationMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual long getAppID() const;
    virtual void setAppID(long appID);

    virtual bool getContentServerApp() const;
    virtual void setContentServerApp(bool contentServerApp);

    virtual void setHostedPrefixNamesArraySize(size_t size);
    virtual size_t getHostedPrefixNamesArraySize() const;
    virtual const char * getHostedPrefixNames(size_t k) const;
    virtual void setHostedPrefixNames(size_t k, const char * hostedPrefixNames);
    virtual void insertHostedPrefixNames(size_t k, const char * hostedPrefixNames);
    [[deprecated]] void insertHostedPrefixNames(const char * hostedPrefixNames) {appendHostedPrefixNames(hostedPrefixNames);}
    virtual void appendHostedPrefixNames(const char * hostedPrefixNames);
    virtual void eraseHostedPrefixNames(size_t k);

    virtual const char * getAppDescription() const;
    virtual void setAppDescription(const char * appDescription);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AppRegistrationMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AppRegistrationMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>InternalMessages.msg:32</tt> by opp_msgtool.
 * <pre>
 * //
 * // Format of transport registration msg (sent by any transport to forwarder).
 * //
 * packet TransportRegistrationMsg
 * {
 *     // ID that uniquely identifies the registering transport
 *     long transportID;
 * 
 *     // a description
 *     string transportDescription;
 * 
 *     // transport address (MAC like address)
 *     string transportAddress;
 * 
 * }
 * </pre>
 */
class TransportRegistrationMsg : public ::omnetpp::cPacket
{
  protected:
    long transportID = 0;
    omnetpp::opp_string transportDescription;
    omnetpp::opp_string transportAddress;

  private:
    void copy(const TransportRegistrationMsg& other);

  protected:
    bool operator==(const TransportRegistrationMsg&) = delete;

  public:
    TransportRegistrationMsg(const char *name=nullptr, short kind=0);
    TransportRegistrationMsg(const TransportRegistrationMsg& other);
    virtual ~TransportRegistrationMsg();
    TransportRegistrationMsg& operator=(const TransportRegistrationMsg& other);
    virtual TransportRegistrationMsg *dup() const override {return new TransportRegistrationMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual long getTransportID() const;
    virtual void setTransportID(long transportID);

    virtual const char * getTransportDescription() const;
    virtual void setTransportDescription(const char * transportDescription);

    virtual const char * getTransportAddress() const;
    virtual void setTransportAddress(const char * transportAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TransportRegistrationMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TransportRegistrationMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>InternalMessages.msg:49</tt> by opp_msgtool.
 * <pre>
 * //
 * // Format of a prefix registration message used in registering
 * // additional FIB entries at the forwarding layer
 * //
 * packet PrefixRegistrationMsg
 * {
 *     // prefix to register
 *     string prefixName;
 * 
 *     // face ID of the face to use as the outgoing face
 *     long faceID;
 * }
 * </pre>
 */
class PrefixRegistrationMsg : public ::omnetpp::cPacket
{
  protected:
    omnetpp::opp_string prefixName;
    long faceID = 0;

  private:
    void copy(const PrefixRegistrationMsg& other);

  protected:
    bool operator==(const PrefixRegistrationMsg&) = delete;

  public:
    PrefixRegistrationMsg(const char *name=nullptr, short kind=0);
    PrefixRegistrationMsg(const PrefixRegistrationMsg& other);
    virtual ~PrefixRegistrationMsg();
    PrefixRegistrationMsg& operator=(const PrefixRegistrationMsg& other);
    virtual PrefixRegistrationMsg *dup() const override {return new PrefixRegistrationMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const char * getPrefixName() const;
    virtual void setPrefixName(const char * prefixName);

    virtual long getFaceID() const;
    virtual void setFaceID(long faceID);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PrefixRegistrationMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PrefixRegistrationMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>InternalMessages.msg:63</tt> by opp_msgtool.
 * <pre>
 * //
 * // Format of neighbour list message sent regularly by direct type
 * // transports to the forwrder.
 * //
 * packet NeighbourListMsg
 * {
 *     // ID that uniquely identifies the transport
 *     long transportID;
 * 
 *     string neighbourAddressList[];
 * }
 * </pre>
 */
class NeighbourListMsg : public ::omnetpp::cPacket
{
  protected:
    long transportID = 0;
    omnetpp::opp_string *neighbourAddressList = nullptr;
    size_t neighbourAddressList_arraysize = 0;

  private:
    void copy(const NeighbourListMsg& other);

  protected:
    bool operator==(const NeighbourListMsg&) = delete;

  public:
    NeighbourListMsg(const char *name=nullptr, short kind=0);
    NeighbourListMsg(const NeighbourListMsg& other);
    virtual ~NeighbourListMsg();
    NeighbourListMsg& operator=(const NeighbourListMsg& other);
    virtual NeighbourListMsg *dup() const override {return new NeighbourListMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual long getTransportID() const;
    virtual void setTransportID(long transportID);

    virtual void setNeighbourAddressListArraySize(size_t size);
    virtual size_t getNeighbourAddressListArraySize() const;
    virtual const char * getNeighbourAddressList(size_t k) const;
    virtual void setNeighbourAddressList(size_t k, const char * neighbourAddressList);
    virtual void insertNeighbourAddressList(size_t k, const char * neighbourAddressList);
    [[deprecated]] void insertNeighbourAddressList(const char * neighbourAddressList) {appendNeighbourAddressList(neighbourAddressList);}
    virtual void appendNeighbourAddressList(const char * neighbourAddressList);
    virtual void eraseNeighbourAddressList(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NeighbourListMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NeighbourListMsg& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline AppRegistrationMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<AppRegistrationMsg*>(ptr.get<cObject>()); }
template<> inline TransportRegistrationMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<TransportRegistrationMsg*>(ptr.get<cObject>()); }
template<> inline PrefixRegistrationMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<PrefixRegistrationMsg*>(ptr.get<cObject>()); }
template<> inline NeighbourListMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<NeighbourListMsg*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INTERNALMESSAGES_M_H

