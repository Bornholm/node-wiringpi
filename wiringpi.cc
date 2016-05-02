/* wiringpi.cc
**
** Copyright (c) 2012 Meadhbh S. Hamrick, All Rights Reserved
**
** @License( https://raw.github.com/OhMeadhbh/node-wiringpi/master/LICENSE )
**
** This is the C++ code that wraps calls to libwiringPi.
*/

#include <node.h>
#include <v8.h>
#include <wiringPi.h>

using namespace v8;

void Num_Pins( const v8::FunctionCallbackInfo<v8::Value>& info ) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);
    info.GetReturnValue().Set( Number::New( isolate, NUM_PINS ) );
}

void Pin_Mode( const v8::FunctionCallbackInfo<v8::Value>& info ) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);

    if( info.Length() != 2 ) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Wrong number of arguments" ) ) );
        info.GetReturnValue().Set( Undefined( isolate ) );
    }

    if( !info[0]->IsNumber() || !info[1]->IsNumber() ) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Bad argument type" ) ) );
        info.GetReturnValue().Set( Undefined( isolate ) );
    }

    if( ( info[0]->NumberValue() < 0 ) ||
        ( info[0]->NumberValue() >= NUM_PINS ) ) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Bad argument" ) ) );
        info.GetReturnValue().Set( Undefined( isolate ) );
    }

    pinMode( info[0]->NumberValue(), info[1]->NumberValue() );

    info.GetReturnValue().Set( Undefined( isolate ) );
}

void Digital_Write( const v8::FunctionCallbackInfo<v8::Value>& info ) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);

    if( info.Length() != 2 ) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Wrong number of arguments" ) ) );
        info.GetReturnValue().Set( Undefined( isolate ) );
    }

    if( !info[0]->IsNumber() || !info[1]->IsNumber() ) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Bad argument type" ) ) );
        info.GetReturnValue().Set( Undefined( isolate ) );
    }

    if( ( info[0]->NumberValue() < 0 ) ||
        ( info[0]->NumberValue() >= NUM_PINS ) ) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Bad argument" ) ) );
        info.GetReturnValue().Set( Undefined( isolate ) );
    }

    digitalWrite( info[0]->NumberValue(), info[1]->NumberValue() );

    info.GetReturnValue().Set( Undefined( isolate ) );
}

void Wiring_Pi_Setup( const v8::FunctionCallbackInfo<v8::Value>& info ) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);

    info.GetReturnValue().Set( Number::New( isolate, wiringPiSetup() ) );
}

void Delay_Microseconds( const v8::FunctionCallbackInfo<v8::Value>& info ) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);

    if( info.Length() != 1) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Wrong number of arguments !" ) ) );
    }

    if( !info[0]->IsNumber() ) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Bad argument type, must be an integer !" ) ) );
        info.GetReturnValue().Set( Undefined( isolate ) );
    }

    delayMicroseconds( info[0]->NumberValue() );

    info.GetReturnValue().Set( Undefined( isolate ) );
}

void Digital_Read( const v8::FunctionCallbackInfo<v8::Value>& info ) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);

    if( info.Length() != 1) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Wrong number of arguments !" ) ) );
    }

    if( !info[0]->IsNumber() ) {
        isolate->ThrowException( Exception::TypeError( String::NewFromUtf8( isolate, "Bad argument type, must be an integer !" ) ) );
        info.GetReturnValue().Set( Undefined( isolate ) );
    }

    info.GetReturnValue().Set( Number::New( isolate, digitalRead( info[0]->NumberValue() ) ) );
}

void init( Handle<Object> target ) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Setup a few constants
    Local<Object> PIN_MODE = Object::New( isolate );
    target->Set(String::NewFromUtf8( isolate, "PIN_MODE" ), PIN_MODE );
    PIN_MODE->Set( String::NewFromUtf8( isolate, "INPUT" ), Number::New( isolate, INPUT ) );
    PIN_MODE->Set( String::NewFromUtf8( isolate, "OUTPUT" ), Number::New( isolate, OUTPUT ) );
    PIN_MODE->Set( String::NewFromUtf8( isolate, "PWM_OUTPUT" ), Number::New( isolate, PWM_OUTPUT ) );

    Local<Object> WRITE = Object::New( isolate );
    target->Set( String::NewFromUtf8( isolate, "WRITE" ), WRITE );
    WRITE->Set( String::NewFromUtf8( isolate, "LOW" ), Number::New( isolate, LOW ) );
    WRITE->Set( String::NewFromUtf8( isolate, "HIGH" ), Number::New( isolate, HIGH ) );

    target->Set(String::NewFromUtf8(isolate, "numPins", v8::String::kInternalizedString),
                FunctionTemplate::New(isolate, Num_Pins)->GetFunction());
    target->Set(String::NewFromUtf8(isolate, "pinMode", v8::String::kInternalizedString),
                FunctionTemplate::New(isolate, Pin_Mode)->GetFunction());
    target->Set(String::NewFromUtf8(isolate, "digitalWrite", v8::String::kInternalizedString),
                FunctionTemplate::New(isolate, Digital_Write)->GetFunction());
    target->Set(String::NewFromUtf8(isolate, "wiringPiSetup", v8::String::kInternalizedString),
                FunctionTemplate::New(isolate, Wiring_Pi_Setup)->GetFunction());
    target->Set(String::NewFromUtf8(isolate, "delayMicroseconds", v8::String::kInternalizedString),
                FunctionTemplate::New(isolate, Delay_Microseconds)->GetFunction());
    target->Set(String::NewFromUtf8(isolate, "digitalRead", v8::String::kInternalizedString),
                FunctionTemplate::New(isolate, Digital_Read)->GetFunction());
}

NODE_MODULE(wiringpi, init)
