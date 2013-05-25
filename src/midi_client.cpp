#include "midi_client.hpp"

#include <iostream>

#include <CoreFoundation/CoreFoundation.h>

using namespace v8;

Persistent<FunctionTemplate> lemur::MidiClient::tpl;

lemur::MidiClient::MidiClient()
{
    MIDIClientCreate(CFSTR("Lemur MIDI Client"),
                     NULL,
                     NULL,
                     &client_);
}

lemur::MidiClient::~MidiClient()
{
    MIDIClientDispose(client_);
}

void lemur::MidiClient::init(Handle<Object> target)
{
    HandleScope _;
    
    Local<FunctionTemplate> ft = FunctionTemplate::New();
    ft->SetClassName(v8::String::NewSymbol("MidiClient"));
    
    Handle<ObjectTemplate> it = ft->InstanceTemplate();
    it->SetInternalFieldCount(1);

    MidiClient::tpl = Persistent<FunctionTemplate>::New(ft);
}

Handle<Value> lemur::MidiClient::create_instance()
{
    HandleScope _;
    
    Local<Object> instance = tpl->InstanceTemplate()->NewInstance();
    
    MidiClient *theClient = new MidiClient();
    theClient->Wrap(instance);
    
    return _.Close(instance);
}

// Handle<Value> lemur::MidiClient::wrap(MIDIEndpointRef endpoint)
// {
//     HandleScope _;
//     
//     Local<Object> instance = tpl->InstanceTemplate()->NewInstance();
//     
//     MidiClient *theOutput = new MidiClient(endpoint);
//     theOutput->Wrap(instance);
//     
//     return _.Close(instance);
// }
// 
// 
// 
// Handle<Value> lemur::MidiClient::New(const Arguments &args)
// {
//     return args.This();
// }
// 
// Handle<Value> lemur::MidiClient::GetName(Local<String> prop, const AccessorInfo &info)
// {
//     MidiClient *output = node::ObjectWrap::Unwrap<MidiClient>(info.Holder());
//     
//     char buffer[64];
//     CFStringGetCString(output->name(), buffer, 64, kCFStringEncodingASCII);
//     
//     return String::New(buffer);
// }
