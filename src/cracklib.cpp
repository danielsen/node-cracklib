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
#include <nan.h>
#include <node.h>
#include <crack.h>
#include <string.h>
#include <stdlib.h>

using namespace v8;
using namespace std;

/*!
 * \brief   Checks a password against the default cracklib dictionary
 * \param   password Password string to check
 * \return  Cracklib check result
 * 
 * The return value will be a dictionary object with a single member
 * named "message". If "message" is NULL the password is acceptable, in
 * all other cases "message" will contain the reason the password was rejected.
 */
void fascistCheck (const Nan::FunctionCallbackInfo<v8::Value>& info) {

  if (info.Length() < 1) {
    Nan::ThrowError(Nan::Error("fascistCheck(password)"));
  }

  v8::String::Utf8Value spass(info[0]->ToString());

  const char *passwd  = *spass; 
  const char *dict    = GetDefaultCracklibDict();
  char *msg           = (char*)FascistCheck(passwd, dict);

  v8::Local<v8::Object> ret = Nan::New<v8::Object>();

  if (!msg) {
    Nan::Set(ret, Nan::New("message").ToLocalChecked(), Nan::Null());
  } else {
    Nan::Set(ret, Nan::New("message").ToLocalChecked(), 
      Nan::New(msg).ToLocalChecked());
  }
  info.GetReturnValue().Set(ret);
}

/*!
 * \brief   Checks a password / user combination against the default cracklib
 *          dictionary.
 * \param   password  Password string to check
 * \return  Cracklib check result
 * 
 * The return value will be a dictionary object with a single member
 * named "message". If "message" is NULL the password is acceptable, in
 * all other cases "message" will contain the reason the password was rejected.
 */
void fascistCheckUser (const Nan::FunctionCallbackInfo<v8::Value>& info) {
  
  if (info.Length() < 2) {
    Nan::ThrowError(Nan::Error("fascistCheckUser(<password>, <user>)"));
  }

  v8::String::Utf8Value spass(info[0]->ToString());
  v8::String::Utf8Value suser(info[1]->ToString());

  const char *passwd  = *spass;
  const char *user    = *suser;
  const char *dict    = GetDefaultCracklibDict();
  char *msg           = (char*)FascistCheckUser(passwd, dict, user, NULL);

  v8::Local<v8::Object> ret = Nan::New<v8::Object>();

  if (!msg) {
    Nan::Set(ret, Nan::New("message").ToLocalChecked(), Nan::Null());
  } else {
    Nan::Set(ret, Nan::New("message").ToLocalChecked(), 
      Nan::New(msg).ToLocalChecked());
  }
  info.GetReturnValue().Set(ret);
}
    
void InitAll(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("fascistCheck").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(fascistCheck)->GetFunction());
  exports->Set(Nan::New("fascistCheckUser").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(fascistCheckUser)->GetFunction());
}

NODE_MODULE(cracklib, InitAll)
