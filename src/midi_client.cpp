#include "midi_client.hpp"

#include "midi_output.hpp"

#include <iostream>

#include <CoreFoundation/CoreFoundation.h>
#include <mach/mach.h>
#include <mach/mach_time.h>

#define PACKET_LIST_SIZE 512

using namespace v8;

Persistent<FunctionTemplate> lemur::MidiClient::tpl;

lemur::MidiClient::MidiClient()
{
    MIDIClientCreate(CFSTR("Lemur MIDI Client"), NULL, NULL, &client_);
    MIDIOutputPortCreate(client_, CFSTR("Lemur MIDI Port"), &port_);
    packet_list_ = (MIDIPacketList*)malloc(PACKET_LIST_SIZE);
}

lemur::MidiClient::~MidiClient()
{
    MIDIPortDispose(port_);
    MIDIClientDispose(client_);
    free(packet_list_);
}

void lemur::MidiClient::init(Handle<Object> target)
{
    HandleScope _;
    
    Local<FunctionTemplate> ft = FunctionTemplate::New();
    ft->SetClassName(v8::String::NewSymbol("MidiClient"));
    
    Handle<ObjectTemplate> it = ft->InstanceTemplate();
    it->SetInternalFieldCount(1);
    
    NODE_SET_PROTOTYPE_METHOD(ft, "send", Send);

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

Handle<Value> lemur::MidiClient::Send(const Arguments& args)
{
    HandleScope _;
    
    if (!args[0]->IsObject() || !args[1]->IsNumber()) {
        return _.Close(Null());
    }
    
    Handle<Object> obj = Handle<Object>::Cast(args[0]);
    
    MidiClient *client = node::ObjectWrap::Unwrap<MidiClient>(args.This());
    MidiOutput *output = node::ObjectWrap::Unwrap<MidiOutput>(obj);
    
    uint32_t msg = args[1]->ToUint32()->Value();
    
    Byte midi_data[3];
    midi_data[0] = msg >> 16;
    midi_data[1] = msg >>  8;
    midi_data[2] = msg >>  0;
    
    MIDIPacket *packet;
    packet = MIDIPacketListInit(client->packet_list_);
    packet = MIDIPacketListAdd(client->packet_list_, PACKET_LIST_SIZE, packet, mach_absolute_time(), 3, midi_data);
    
    MIDISend(client->port_, output->endpoint(), client->packet_list_);
    
    return _.Close(Null());
}

