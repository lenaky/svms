#include <iostream>
#include <thread>

#include "zmq.hpp"

volatile bool g_ventilator = true;
volatile bool g_worker_a = true;
volatile bool g_worker_b = true;
volatile bool g_sink = true;

void ventilator_thread()
{
    std::cout << "ventilator" << std::endl;
}

void worker_thread(bool* run)
{
    std::cout << "worker" << std::endl;
}

void sink_thread()
{
    std::cout << "sink" << std::endl;
}


int main(void)
{
    zmq::context_t zmq_context(1);

    zmq::socket_t ventilator_push_bind_socket(zmq_context, ZMQ_PUSH);
    zmq::socket_t ventilator_push_connect_socket(zmq_context, ZMQ_PUSH);

    zmq::socket_t worker_pull_connect_socket(zmq_context, ZMQ_PULL);
    zmq::socket_t worker_push_connect_socket(zmq_context, ZMQ_PUSH);
    zmq::socket_t worker_subscribe_connect_socket(zmq_context, ZMQ_SUB);

    zmq::socket_t sink_pull_bind_socket(zmq_context, ZMQ_PULL);
    zmq::socket_t sink_publish_bind_socket(zmq_context, ZMQ_PUB);

    std::thread ventilator_thread(ventilator_thread);
    std::thread worker_thread_a(worker_thread, (bool*)&g_worker_a);
    std::thread worker_thread_b(worker_thread, (bool*)&g_worker_b);


    ventilator_thread.join();
    worker_thread_a.join();
    worker_thread_b.join();

    return 0;
}