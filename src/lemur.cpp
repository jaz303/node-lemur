#include <v8.h>
#include <node.h>
#include <iostream>
#include <CoreMIDI/CoreMIDI.h>

#include "midi_output.hpp"

using namespace v8;
using namespace lemur;

Handle<Value> getMidiOutputs(const Arguments& args) {
    HandleScope _;
    Local<Array> outputs = Array::New();
    
    ItemCount destination_count = MIDIGetNumberOfDestinations();
    for (ItemCount i = 0; i < destination_count; ++i) {
        outputs->Set(i, MidiOutput::wrap(MIDIGetDestination(i)));
    }
    
    return _.Close(outputs);
}

void init(Handle<Object> target) {
    
    MidiOutput::Init(target);
    
    NODE_SET_METHOD(target,     "getMidiOutputs",       getMidiOutputs);

}

NODE_MODULE(lemur_bindings, init);
