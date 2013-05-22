#include "midi_output.hpp"

#include <iostream>

#include <CoreFoundation/CoreFoundation.h>

using namespace v8;

Persistent<FunctionTemplate> lemur::MidiOutput::tpl;

lemur::MidiOutput::MidiOutput(MIDIEndpointRef endpoint)
    : endpoint_(endpoint)
{
    MIDIObjectGetStringProperty(endpoint_, kMIDIPropertyName, &name_);
    CFRetain(name_);
}

lemur::MidiOutput::~MidiOutput()
{
    CFRelease(name_);
}

Handle<Value> lemur::MidiOutput::wrap(MIDIEndpointRef endpoint)
{
    HandleScope _;
    
    Local<Object> instance = tpl->InstanceTemplate()->NewInstance();
    
    MidiOutput *theOutput = new MidiOutput(endpoint);
    theOutput->Wrap(instance);
    
    return _.Close(instance);
}

void lemur::MidiOutput::Init(Handle<Object> target)
{
    HandleScope _;
    
    Local<FunctionTemplate> ft = FunctionTemplate::New();
    ft->SetClassName(v8::String::NewSymbol("MidiOutput"));
    
    Handle<ObjectTemplate> it = ft->InstanceTemplate();
    it->SetInternalFieldCount(1);
    it->SetAccessor(String::New("name"), GetName);

    MidiOutput::tpl = Persistent<FunctionTemplate>::New(ft);
}

Handle<Value> lemur::MidiOutput::New(const Arguments &args)
{
    return args.This();
}

Handle<Value> lemur::MidiOutput::GetName(Local<String> prop, const AccessorInfo &info)
{
    MidiOutput *output = node::ObjectWrap::Unwrap<MidiOutput>(info.Holder());
    
    char buffer[64];
    CFStringGetCString(output->name(), buffer, 64, kCFStringEncodingASCII);
    
    return String::New(buffer);
}
