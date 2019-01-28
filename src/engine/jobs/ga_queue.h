#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** implementing the locking version
*/

#include <mutex>
#include <atomic>

struct ga_queue_node_pointer_t
{
	struct ga_queue_node_t* _ptr;
	uint32_t _count;
};

struct ga_queue_node_t
{
	void *_data;
	std::atomic<ga_queue_node_pointer_t> _next;
	ga_queue_node_t()
	{
		_data = NULL;
	}
	ga_queue_node_t(void *data, ga_queue_node_t* nextPtr) : _data(data)
	{
		ga_queue_node_pointer_t n;
		n._ptr = nextPtr;
		_next = n;
	}
};

class ga_queue
{
public:
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;

private:
	std::atomic<ga_queue_node_pointer_t> _head;
	std::atomic<ga_queue_node_pointer_t> _tail;
	std::atomic<int> _count;
	bool CAS(std::atomic<ga_queue_node_pointer_t>* variable, ga_queue_node_pointer_t* current_value, ga_queue_node_t* node, uint32_t count);
};



