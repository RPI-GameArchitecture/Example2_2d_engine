/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"


bool operator==(const ga_queue_node_pointer_t a, const ga_queue_node_pointer_t b)
{
	return ((a._ptr == b._ptr) && (a._count == b._count));
}

// implementing the lock-free version

ga_queue::ga_queue(int node_count)
{
	ga_queue_node_t* node = new ga_queue_node_t(NULL,NULL);
	ga_queue_node_pointer_t p;
	p._ptr = node;
	p._count = 0;

	_head = p;
	_tail = p;
	_count = 0;
}

ga_queue::~ga_queue()
{

}

bool ga_queue::CAS(std::atomic<ga_queue_node_pointer_t>* variable, ga_queue_node_pointer_t* current_value, ga_queue_node_t* node, uint32_t count)
{
	ga_queue_node_pointer_t new_value;
	new_value._ptr = node;
	new_value._count = count;
	return std::atomic_compare_exchange_weak(variable, current_value, new_value);
}

void ga_queue::push(void* data)
{
	ga_queue_node_t* node = new ga_queue_node_t (data, NULL);
	ga_queue_node_pointer_t tail;
	for (;;)
	{
		tail = _tail.load();
		ga_queue_node_pointer_t next = tail._ptr->_next;
		
		if (tail==_tail.load())	// are tail and next consistent?
		{
			if (next._ptr == NULL)	// was tail pointing to the last node?
			{
				if (CAS(&tail._ptr->_next, &next, node, next._count+1))
				{
					break;
				}
			}
			else
			{
				CAS(&_tail, &tail, next._ptr, tail._count + 1);
			}
		}
	}
	CAS(&_tail, &tail, node, tail._count + 1);
	_count++;
}


bool ga_queue::pop(void** data)
{
	ga_queue_node_pointer_t head = _head.load();
	ga_queue_node_pointer_t tail = _tail.load();
	for (;;)
	{
		head = _head.load();
		tail = _tail.load();
		ga_queue_node_pointer_t next = head._ptr->_next;
		if (head == _head.load())
		{
			if (head._ptr == tail._ptr)		// is queue empty or tail falling behind?
			{
				if (next._ptr == NULL)		// is queue empty?
				{
					return false;			// queue is empty, couldn't pop
				}
				CAS(&_tail, &tail, next._ptr, tail._count + 1);
			}
			else
			{
				//read value before CAS, otherwise another dequeue might free the next node
				*data = next._ptr->_data;
				if (CAS(&_head, &head, next._ptr, head._count + 1))
				{
					break;
				}
			}
		}
	}
	free(head._ptr);
	return true;
}

int ga_queue::get_count() const
{

	return _count;
}



/*
// implementing the dual-lock version
// how to use lock guard: std::lock_guard<std::mutex> lock(g_i_mutex);


ga_queue::ga_queue(int node_count)
{
	// TODO:
	// Initialize the queue.

	ga_queue_node_t *node = new ga_queue_node_t();
	node->_next = NULL;
	_head = node;
	_tail = node;
	_count = 0;

}

ga_queue::~ga_queue()
{
	// TODO:
	// Free any resources held by the queue.

	void* data;
	while (pop(&data))
	{
		;
	}
	
}

void ga_queue::push(void* data)
{
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	
	ga_queue_node_t *node = new ga_queue_node_t();
	node->data = data;
	node->_next = NULL;

	{
		std::lock_guard<std::mutex> lock(_tail_mutex);
		_tail->_next = node;
		_tail = node;
		_count++;
	}
}

bool ga_queue::pop(void** data)
{
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.

	{
		std::lock_guard<std::mutex> lock(_head_mutex);
		ga_queue_node_t *node = _head;
		ga_queue_node_t *new_head = _head->_next;
		if (new_head == NULL)	// is queue empty?
		{
			return false;
		}
		else
		{
			*data = new_head->data;
			_head = new_head;
			free(node);
			_count--;
		}
	}
	return true;
}

int ga_queue::get_count() const
{
	// TODO:
	// Get the number of elements currently in the queue.
	return _count;
}
*/
