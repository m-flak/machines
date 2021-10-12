/*
 * E V E N T Q . H P P
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

#ifndef _DEVICE_EVENTQ_HPP
#define _DEVICE_EVENTQ_HPP

#include "base/base.hpp"
#include "ctl/list.hpp"
#include "device/butevent.hpp"

#include "recorder/recorder.hpp"
#include "recorder/private/recpriv.hpp"
#include "utility/DependencyProvider.hpp"
template<>
inline RecRecorder& DependencyProvider<RecRecorder>::getProvided()
{
    return RecRecorder::instance();
}
template<>
inline RecRecorderPrivate& DependencyProvider<RecRecorderPrivate>::getProvided()
{
    return RecRecorderPrivate::instance();
}


//class ostream;
//template <class T> class ctl_list;

// Stores a FIFO of input device events (currently just button events).
template<typename RecRecorderDep = RecRecorder, typename RecRecorderPrivDep = RecRecorderPrivate, typename DevTimeDep = DevTime>
class DevEventQueueT
{
public:
    // No dependency provider for: DevTimeDep
    using DevButtonEventType = DevButtonEventT<DevTimeDep>;
    typedef typename DevButtonEventType::ScanCode	ScanCode;
    typedef typename DevButtonEventType::Action		Action;

    //  Singleton class
    static DevEventQueueT& instance();
    virtual ~DevEventQueueT();

	// Removes the oldest event from the queue.  If an event has a repeat
	// counts greater than one, this fn. will return multiple copies each of
	// which has its count set to one, hence the post-condition.
	// PRE(!isEmpty());
	// POST(result.repeatCount() == 1);
    DevButtonEventType oldestEvent();

	// For each scan-code you must request that events be queued; otherwise they
	// won't be added to the queue.  You can request both press and release
	// events, using the first form; or you can request just one or the other.
	// By default no events are stored in the queue.
	// PRE(code < DevKey::MAX_CODE);  applies to all ScanCode args
	void queueEvents(ScanCode);
	void dontQueueEvents(ScanCode);
	void queueEvents(ScanCode, Action);
	void dontQueueEvents(ScanCode, Action);

	// Throw away certain events.  Four flavours: absolutely everything; all
	// events relating to a given button; any event older than a given time;
	// and events relating to a given button, older than the given time.
	void discardAll();
	void discard(ScanCode);
	void discardOlderThan(double time);
	void discardOlderThan(double time, ScanCode);

	size_t length() const;
	bool   isEmpty() const;		// length() == 0

    void CLASS_INVARIANT;

protected:
    DevEventQueueT();

    DependencyProvider<RecRecorderDep>         recorderDependency_;
    DependencyProvider<RecRecorderPrivDep>     recorderPrivDependency_;

    constexpr inline uchar getReleaseFilterFor(ScanCode code) const { return releaseFilter_[code]; }
    constexpr inline uchar getPressFilterFor(ScanCode code) const { return pressFilter_[code]; }

    // PRE(event.scanCode() < DevKey::MAX_CODE);
    void queueEvent(const DevButtonEventType&);

private:
	// Only these classes can add events to the back of the queue.
	friend class DevWin95Keyboard;
	friend class DevSdlKeyboard;
	friend class DevMouse;

	// Internal convenience methods.
    bool filterEvent(const DevButtonEventType&) const;

    ctl_list<DevButtonEventType>*	list_;

	// These tables determine which events are queued.
	uchar	releaseFilter_[DevKey::MAX_CODE];
	uchar	  pressFilter_[DevKey::MAX_CODE];

    // Operation deliberately revoked
    DevEventQueueT( const DevEventQueueT& );
    DevEventQueueT& operator =( const DevEventQueueT& );
    bool operator ==( const DevEventQueueT& );

public:
    friend inline ostream& operator << ( ostream& o, const DevEventQueueT<RecRecorderDep, RecRecorderPrivDep, DevTimeDep>& t )
    {
        o << "Event queue:" << std::endl;

        // Ayy Lmao
        using ButtonEvent = typename DevEventQueueT<RecRecorderDep, RecRecorderPrivDep, DevTimeDep>::DevButtonEventType;
        using ButtonEvent_Iterator = typename ctl_list<ButtonEvent>::const_iterator;

        ButtonEvent_Iterator it = t.list_->begin();
        while (it != t.list_->end())
        {
            o << "\t" << *it << std::endl;
            ++it;
        }

        o << std::endl;

        o << "Filter tables:	(press)		(release)\n";

        for (int i=0; i!=DevKey::MAX_CODE; ++i)
        {
            o << i << "\t\t\t\t   " << static_cast<int>( t.pressFilter_[i] ) << "\t\t   " << static_cast<int>( t.releaseFilter_[i] ) << "\n";
        }

        o << std::endl;

        return o;
    }
};

// !!!!!!!! CONCRETE !!!!!!!!!!!!!!!!!!!!!!!!!!!!
using DevEventQueue = DevEventQueueT<RecRecorder, RecRecorderPrivate, DevTime>;
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif

/* End EVENTQ.HPP ***************************************************/
