/*
 * Copyright (C) <2015>  <Dan Nielsen dnielsen@reachmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <v8.h>
#include <node.h>
#include <crack.h>
#include <string.h>
#include <stdlib.h>

using namespace v8;
using namespace std;

/* `checkPassword(password, callback)` is the Javascript access point.
 * @password String
 * @callback Function
 * 
 * The callback return value will be a dictionary object with a single member
 * named "message". If "message" is NULL the password is acceptable, in
 * all other cases "message" will contain the reason the password was rejected.
 */
Handle<Value> fascistCheck (const Arguments& args) {

  HandleScope scope;

  if (args.Length() < 1) {
    return ThrowException(Exception::TypeError(
        String::New("fascistCheck(<password>)")));
  }

  v8::String::Utf8Value spass(args[0]->ToString());
  const char *passwd = *spass; 

  const char *dict = GetDefaultCracklibDict();
  char *msg = (char *) FascistCheck(passwd, dict);

  Local<Object> ret = Object::New();
  
  if (!msg) {
    ret->Set(String::NewSymbol("message"), Null());
  } else {
    ret->Set(String::NewSymbol("message"), String::NewSymbol(msg));
  }
  return scope.Close(ret);
}

Handle<Value> fascistCheckUser (const Arguments& args) {
  
  HandleScope scope;

  if (args.Length() < 2) {
    return ThrowException(Exception::TypeError(
        String::New("fascistCheckUser(<password>, <user>)")));
  }

  v8::String::Utf8Value spass(args[0]->ToString());
  v8::String::Utf8Value suser(args[1]->ToString());
  const char *passwd = *spass;
  const char *user = *suser;

  const char *dict = GetDefaultCracklibDict();
  char *msg = (char *) FascistCheckUser(passwd, dict, user, NULL);

  Local<Object> ret = Object::New();

  if (!msg) {
    ret->Set(String::NewSymbol("message"), Null());
  } else {
    ret->Set(String::NewSymbol("message"), String::NewSymbol(msg));
  }
  return scope.Close(ret);
}
    
void RegisterModule(Handle<Object> target) {
  target->Set(String::NewSymbol("fascistCheck"),
    FunctionTemplate::New(fascistCheck)->GetFunction());
  target->Set(String::NewSymbol("fascistCheckUser"),
    FunctionTemplate::New(fascistCheckUser)->GetFunction());
}

NODE_MODULE(cracklib, RegisterModule)
