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

/* Forward declarations */
Handle<Value> Async (const Arguments& args);
void asyncWork (uv_work_t* req);
void asyncAfter (uv_work_t* req);

struct Baton {
  Persistent<Function> callback;

  const char *msg;
  char *password;
};

/* `checkPassword(password, callback)` is the Javascript access point.
 * @password String
 * @callback Function
 * 
 * The callback return value will be a dictionary object with a single member
 * named "message". If "message" is NULL the password is acceptable, in
 * all other cases "message" will contain the reason the password was rejected.
 */
Handle<Value> checkPassword (const Arguments& args) {

  HandleScope scope;

  if (!args[1]->IsFunction()) {
    return ThrowException(Exception::TypeError(
        String::New("checkPassword(<password>, <callback>)")));
  }

  if (args.Length() < 2) {
    return ThrowException(Exception::TypeError(
        String::New("checkPassword(<password>, <callback>)")));
  }

  Local<Function> callback = Local<Function>::Cast(args[1]);

  Baton* baton = new Baton();
  baton->callback = Persistent<Function>::New(callback);

  uv_work_t *req = new uv_work_t();
  req->data = baton;

  v8::String::Utf8Value passwd(args[0]->ToString());
  baton->password = strdup(*passwd);

  int status = uv_queue_work(uv_default_loop(), req, asyncWork,
      (uv_after_work_cb)asyncAfter);

  assert(status == 0);
  return Undefined();
}

void asyncWork (uv_work_t* req) {
  Baton* baton = static_cast<Baton*>(req->data);

  const char *dict = GetDefaultCracklibDict();
  char *msg = (char *) FascistCheck(baton->password, dict);
  baton->msg = msg;
}

void asyncAfter(uv_work_t* req) {
  HandleScope scope;
  Baton* baton = static_cast<Baton*>(req->data);

  const unsigned argc = 1;
  Local<Object> ret = Object::New();

  if (!baton->msg) {
    ret->Set(String::NewSymbol("message"), Null());
  } else {
    ret->Set(String::NewSymbol("message"), String::NewSymbol(baton->msg));
  }
    

  Local<Value> argv[argc] = { ret };

  TryCatch try_catch;
  baton->callback->Call(Context::GetCurrent()->Global(), argc, argv);
  if (try_catch.HasCaught()) {
    node::FatalException(try_catch);
  }

  baton->callback.Dispose();
  delete baton;
  delete req;
}

void RegisterModule(Handle<Object> target) {
  target->Set(String::NewSymbol("checkPassword"),
    FunctionTemplate::New(checkPassword)->GetFunction());
}

NODE_MODULE(cracklib, RegisterModule)
