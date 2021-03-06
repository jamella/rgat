/*
Copyright 2016 Nia Catlin

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
This class holds (and provides dubiously mutex guarded access to) OpenGl vertex and colour data
*/
#pragma once
#include <stdafx.h>
#include "mathStructs.h"

class GRAPH_DISPLAY_DATA {
public:
	GRAPH_DISPLAY_DATA(bool preview = false);
	~GRAPH_DISPLAY_DATA();

	vector <float>* acquire_pos();
	vector <float>* acquire_col();

	float *readonly_col() { if (!vcolarray.empty()) return &vcolarray.at(0); return 0; }
	float *readonly_pos() { if (!vposarray.empty()) return &vposarray.at(0); return 0; }

	void release_pos();
	void release_col();
	void clear();
	void reset();
	unsigned int col_size() { return colSize; }
	unsigned int pos_size() { return posSize; }
	unsigned int col_sizec() { return vcolarray.size(); }
	//this is actually quite slow? or at least is a significant % of reported cpu time
	unsigned int col_buf_capacity_floats() { return vcolarraySize; }
	unsigned int get_numVerts() { return numVerts; }
	void set_numVerts(unsigned int num);
	unsigned int get_renderedEdges() { return edgesRendered; }
	void inc_edgesRendered() { ++edgesRendered; }

	bool get_coord(unsigned int index, FCOORD* result);

	bool isPreview() { return preview; }

private:
	HANDLE posmutex;
	HANDLE colmutex;
	unsigned int numVerts = 0;

	vector<GLfloat> vposarray;
	vector<GLfloat> vcolarray;

	unsigned int colSize = 0;
	unsigned int posSize = 0;
	unsigned int vcolarraySize = 0;

	//not used for nodes
	unsigned int edgesRendered = 0;
	bool preview = false;
};