#pragma once

#include <memory>


namespace mesh {


class IMesh {
public:
	virtual ~IMesh() = default;

	virtual void draw() = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
};

typedef std::unique_ptr<IMesh> IMesh_ptr;


}
