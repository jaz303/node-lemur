#ifndef LEMUR_MIDI_CLIENT_HPP
#define LEMUR_MIDI_CLIENT_HPP

#include <v8.h>
#include <node.h>

#include <CoreMIDI/CoreMIDI.h>

using namespace v8;

namespace lemur
{

class MidiClient : node::ObjectWrap
{
public:
    MidiClient();
    ~MidiClient();
    
    inline MIDIClientRef client() { return client_; }
    inline MIDIPortRef port() { return port_; }

private:
    MIDIClientRef       client_;
    MIDIPortRef         port_;
    MIDIPacketList      *packet_list_;
    
public:
    
    //
    // Node bindings
    
    static Persistent<FunctionTemplate> tpl;
    static void init(Handle<Object> target);
    static Handle<Value> create_instance();
    
    static Handle<Value> Send(const Arguments& args);
    
    // static Handle<Value> wrap(MIDIEndpointRef endpoint);
    // 
    
    // static Handle<Value> New(const Arguments &args);
    // static Handle<Value> GetName(Local<String> prop, const AccessorInfo &info);

};

}

#endif