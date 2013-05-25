#ifndef LEMUR_MIDI_OUTPUT_HPP
#define LEMUR_MIDI_OUTPUT_HPP

#include <v8.h>
#include <node.h>

#include <CoreMIDI/CoreMIDI.h>

using namespace v8;

namespace lemur
{

class MidiOutput : node::ObjectWrap
{
public:
    MidiOutput(MIDIEndpointRef endpoint);
    ~MidiOutput();
    
    inline MIDIEndpointRef endpoint() { return endpoint_; }
    inline CFStringRef name() { return name_; }
    
private:
    MIDIEndpointRef     endpoint_;
    CFStringRef         name_;
    
public:
    
    //
    // Node bindings
    
    static Persistent<FunctionTemplate> tpl;
    static void init(Handle<Object> target);
    static Handle<Value> wrap(MIDIEndpointRef endpoint);
    
    static Handle<Value> New(const Arguments &args);
    static Handle<Value> GetName(Local<String> prop, const AccessorInfo &info);
};

}

#endif