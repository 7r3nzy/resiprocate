#ifndef PROTONTHREADBASE_HXX
#define PROTONTHREADBASE_HXX

#include <sstream>
#include <string>

#include "ThreadIf.hxx"
#include "TimeLimitFifo.hxx"

#include <proton/function.hpp>
#include <proton/messaging_handler.hpp>
#include <proton/receiver.hpp>
#include <proton/transport.hpp>
#include <proton/work_queue.hpp>

#include "cajun/json/elements.h"

namespace resip {

class ProtonThreadBase : public resip::ThreadIf, proton::messaging_handler
{
public:
   ProtonThreadBase(const std::string &u,
      std::chrono::duration<long int> maximumAge,
      std::chrono::duration<long int> retryDelay);
   ~ProtonThreadBase();

   void on_container_start(proton::container &c);
   void on_connection_open(proton::connection &conn);
   void on_receiver_open(proton::receiver &);
   void on_receiver_close(proton::receiver &);
   void on_transport_error(proton::transport &t);
   void on_message(proton::delivery &d, proton::message &m);

   virtual void thread();
   virtual void shutdown();

protected:
   resip::TimeLimitFifo<json::Object>& getFifo() { return mFifo; };

private:
   std::chrono::duration<long int> mMaximumAge;
   std::chrono::duration<long int> mRetryDelay;
   std::string mUrl;
   proton::receiver mReceiver;
   proton::work_queue* mWorkQueue;
   resip::TimeLimitFifo<json::Object> mFifo;

   void doShutdown();
};

} // namespace

#endif

/* ====================================================================
 *
 * Copyright 2016-2022 Daniel Pocock https://danielpocock.com
 * Copyright 2022 Software Freedom Institute SA https://softwarefreedom.institute
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. Neither the name of the author(s) nor the names of any contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR(S) OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * ====================================================================
 *
 *
 */
