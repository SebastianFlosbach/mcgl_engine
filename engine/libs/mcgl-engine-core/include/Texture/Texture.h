#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <string>

namespace texture {

	struct Texture {
	public:
		Texture( const char* path );
		Texture( const std::string& path );

		Texture( const Texture& other ) = delete;
		Texture& operator=( const Texture& other ) = delete;

		Texture( Texture&& other ) noexcept {
			*this = std::move( other );
		}

		Texture& operator=( Texture&& other ) noexcept {
			this->hTexture_ = other.hTexture_;

			// Cleanup to avoid texture being reused or deleted
			other.hTexture_ = 0;

			return *this;
		}

		~Texture() {
			glDeleteTextures( 1, &hTexture_ );
		}

		
		void bind() const {
			// TODO: Add support for multiple texture units
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, hTexture_ );
		}

		unsigned int get() const {
			return hTexture_;
		}

		int width() const {
			return width_;
		}

		int height() const {
			return height_;
		}

	private:
		unsigned int hTexture_;

		int width_;
		int height_;
	};


}