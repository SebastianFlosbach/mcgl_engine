#pragma once

#include "IShader.h"


namespace rendering {
namespace shader {


class ShaderCollection {
public:
	ShaderCollection() = default;
	~ShaderCollection() = default;

	void addShader( IShader&& shader );
	const IShader& getShader( MCGLShaderType type );
	void removeShader();

private:


};


}
}
