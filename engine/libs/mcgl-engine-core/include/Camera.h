#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

class Camera {
public:
	Camera( glm::vec3 position, glm::vec3 direction ) : pos_( position ), direction_( glm::normalize( direction ) ) {
		yaw_ = asin( direction_.z );
		pitch_ = asin( direction_.y );
	}

	Camera( float cx = 0.0f, float cy = 0.0f, float cz = 0.0f, float dx = 1.0f, float dy = 0.0f, float dz = 0.0f ) : Camera( glm::vec3( cx, cy, cz ), glm::vec3( dx, dy, dz ) ) {
	}

	void setPosition( glm::vec3 position ) {
		pos_ = position;
	}

	void setPosition( float x, float y, float z ) {
		setPosition( glm::vec3( x, y, z ) );
	}

	void move( glm::vec3 diff ) {
		pos_ += diff.z * direction_ + diff.x * glm::normalize( glm::cross( direction_, up_ ) );
	}

	void move( float dx, float dy, float dz ) {
		move( glm::vec3( dx, dy, dz ) );
	}

	const glm::vec3& getPosition() const {
		return pos_;
	}

	void setDirection( glm::vec3 direction ) {
		direction_ = glm::normalize( direction );
	}

	void setDirection( float x, float y, float z ) {
		setDirection( glm::vec3( x, y, z ) );
	}

	void rotate( float dPitch, float dYaw, float dRoll = 0.0f ) {
		pitch_ += dPitch;
		yaw_ += dYaw;
		roll_ += dRoll;

		if ( pitch_ > glm::radians( 89.0f ) )
			pitch_ = glm::radians( 89.0f );
		if ( pitch_ < glm::radians( -89.0f ) )
			pitch_ = glm::radians( -89.0f );

		direction_.x = cos( pitch_ ) * cos(yaw_ );
		direction_.y = sin( pitch_ );
		direction_.z = cos( pitch_ ) * sin( yaw_ );
		direction_ = glm::normalize( direction_ );
	}

	void rotateD( float dPitch, float dYawn, float dRoll = 0.0f ) {
		rotate( glm::radians( dPitch ), glm::radians( dYawn ), glm::radians( dRoll ) );
	}

	const glm::mat4 getView() const {
		return glm::lookAt( pos_, pos_ + direction_, up_ );
	}

private:
	glm::vec3 pos_;
	glm::vec3 direction_;
	float pitch_;
	float yaw_;
	float roll_ = 0;

	static const glm::vec3 up_;
};