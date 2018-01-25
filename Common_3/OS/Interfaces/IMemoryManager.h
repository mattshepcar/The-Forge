/*
 * Copyright (c) 2018 Confetti Interactive Inc.
 * 
 * This file is part of The-Forge
 * (see https://github.com/ConfettiFX/The-Forge).
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*/

#pragma once

#include <new>

void* m_allocator(size_t size);
void* m_allocator(size_t count, size_t size);
void* m_reallocator(void* ptr, size_t size);
void m_deallocator(void* ptr);

#define conf_malloc(size)		m_allocator(size)
#define conf_calloc(count,size) m_allocator(count,size)
#define conf_realloc(ptr,size)	m_reallocator(ptr,size)
#define conf_free(ptr)			m_deallocator(ptr)

#define	malloc(size)		static_assert(false, "Please use conf_malloc");
#define	calloc(count,size)	static_assert(false, "Please use conf_calloc");
#define	realloc(ptr,size)	static_assert(false, "Please use conf_realloc");
#define	free(ptr)			static_assert(false, "Please use conf_free");
#define	new					static_assert(false, "Please use conf_placement_new");
#define	delete				static_assert(false, "Please use conf_free with explicit destructor call");

#pragma push_macro("new")
#undef new

template<typename T, typename... Args>
static T* conf_placement_new(void* ptr, Args... args)
{
	return new(ptr) T(args...);
}

#pragma pop_macro("new")
