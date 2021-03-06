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

Handle<Value> Num_Pins( const Arguments& args ) {
    HandleScope scope;
    return scope.Close( Number::New( NUM_PINS ) );
}

Handle<Value> Pin_Mode( const Arguments& args ) {
    HandleScope scope;

    if( args.Length() != 2 ) {
        ThrowException( Exception::TypeError( String::New( "Wrong number of arguments" ) ) );
        return scope.Close( Undefined() );
    }

    if( !args[0]->IsNumber() || !args[1]->IsNumber() ) {
        ThrowException( Exception::TypeError( String::New( "Bad argument type" ) ) );
        return scope.Close( Undefined() );
    }

    if( ( args[0]->NumberValue() < 0 ) ||
        ( args[0]->NumberValue() >= NUM_PINS ) ) {
        ThrowException( Exception::TypeError( String::New( "Bad argument" ) ) );
        return scope.Close( Undefined() );
    }

    pinMode( args[0]->NumberValue(), args[1]->NumberValue() );

    return scope.Close( Undefined() );
}

Handle<Value> Digital_Write( const Arguments& args ) {
    HandleScope scope;

    if( args.Length() != 2 ) {
        ThrowException( Exception::TypeError( String::New( "Wrong number of arguments" ) ) );
        return scope.Close( Undefined() );
    }

    if( !args[0]->IsNumber() || !args[1]->IsNumber() ) {
        ThrowException( Exception::TypeError( String::New( "Bad argument type" ) ) );
        return scope.Close( Undefined() );
    }

    if( ( args[0]->NumberValue() < 0 ) ||
        ( args[0]->NumberValue() >= NUM_PINS ) ) {
        ThrowException( Exception::TypeError( String::New( "Bad argument" ) ) );
        return scope.Close( Undefined() );
    }

    digitalWrite( args[0]->NumberValue(), args[1]->NumberValue() );

    return scope.Close( Undefined() );
}

Handle<Value> Wiring_Pi_Setup( const Arguments& args ) {
    HandleScope scope;
    return scope.Close( Number::New( wiringPiSetup() ) );
}

Handle<Value> Delay_Microseconds( const Arguments& args ) {
    HandleScope scope;

    if( args.Length() != 1) {
        ThrowException( Exception::TypeError( String::New( "Wrong number of arguments !" ) ) );
    }

    if( !args[0]->IsNumber() ) {
        ThrowException( Exception::TypeError( String::New( "Bad argument type, must be an integer !" ) ) );
        return scope.Close( Undefined() );
    }

    delayMicroseconds( args[0]->NumberValue() );

    return scope.Close( Undefined() );
}

Handle<Value> Digital_Read( const Arguments& args ) {
    HandleScope scope;

    if( args.Length() != 1) {
        ThrowException( Exception::TypeError( String::New( "Wrong number of arguments !" ) ) );
    }

    if( !args[0]->IsNumber() ) {
        ThrowException( Exception::TypeError( String::New( "Bad argument type, must be an integer !" ) ) );
        return scope.Close( Undefined() );
    }

    return scope.Close( Number::New( digitalRead( args[0]->NumberValue() ) ) );
}

void init(Handle<Object> target) {

    // Setup a few constants
    Local<Object> PIN_MODE = Object::New();
    target->Set( String::New( "PIN_MODE" ), PIN_MODE );
    PIN_MODE->Set( String::New( "INPUT" ), Number::New( INPUT ) );
    PIN_MODE->Set( String::New( "OUTPUT" ), Number::New( OUTPUT ) );
    PIN_MODE->Set( String::New( "PWM_OUTPUT" ), Number::New( PWM_OUTPUT ) );

    Local<Object> WRITE = Object::New();
    target->Set( String::New( "WRITE" ), WRITE );
    WRITE->Set( String::New( "LOW" ), Number::New( LOW ) );
    WRITE->Set( String::New( "HIGH" ), Number::New( HIGH ) );

    target->Set(String::NewSymbol("numPins"),
                FunctionTemplate::New(Num_Pins)->GetFunction());
    target->Set(String::NewSymbol("pinMode"),
                FunctionTemplate::New(Pin_Mode)->GetFunction());
    target->Set(String::NewSymbol("digitalWrite"),
                FunctionTemplate::New(Digital_Write)->GetFunction());
    target->Set(String::NewSymbol("wiringPiSetup"),
                FunctionTemplate::New(Wiring_Pi_Setup)->GetFunction());
    target->Set(String::NewSymbol("delayMicroseconds"),
                FunctionTemplate::New(Delay_Microseconds)->GetFunction());
    target->Set(String::NewSymbol("digitalRead"),
                FunctionTemplate::New(Digital_Read)->GetFunction());
}

NODE_MODULE(wiringpi, init)
