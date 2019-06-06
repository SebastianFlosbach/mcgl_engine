#pragma once


namespace mesh {


class IMesh {
public:
	virtual ~IMesh() = default;

	virtual void draw() = 0;
};


}
