/* -*- c++ -*- */
/*
 * Copyright 2011 Free Software Foundation, Inc.
 * 
 * This file is part of gr-eventstream
 * 
 * gr-eventstream is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * gr-eventstream is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gr-eventstream; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <qa_es_common.h>
#include <cppunit/TestAssert.h>

#include <stdio.h>
#include <es/es.h>

// Test event generation, queue insertion, handler binding, general non gr-runtime operation
void 
qa_es_common::t1()
{
    printf("t1\n");
    es_queue_sptr q = es_make_queue();
    pmt_t arb = es_make_arbiter();

    pmt_t evt1 = event_create( es::event_type_1, 1, 4 );
    pmt_t evt2 = event_create( es::event_type_1, 100, 10 );
    pmt_t evt3 = event_create( "custom_evt", 200, 10 );
    event_print (evt1 );
    std::cout << "event time = " <<  event_time( evt1 ) << "\n";
    printf("event type = %s\n", event_type( evt2 ).c_str());
    printf("event type = %s\n", event_type( evt3 ).c_str());

    q->register_event_type( event_type( evt1 ) );
    q->register_event_type( event_type( evt2 ) );
    q->register_event_type( event_type( evt3 ) );

    es_handler_sptr h1( es_make_handler_print(es_handler_print::TYPE_F32) );
    es_handler_sptr h2( es_make_handler_print(es_handler_print::TYPE_C32) );

    q->bind_handler( event_type(evt1), h1 );
    q->bind_handler( event_type(evt3), h2 );

    q->add_event(evt1);
    q->add_event(evt2);
    q->add_event(evt3);

    q->print_queue();

}



