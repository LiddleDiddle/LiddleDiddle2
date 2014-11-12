#include "Camera2D.h"

namespace Bengine
{

	Camera2D::Camera2D(void) : 
		_position(0.0f,0.0f), 
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(1),
		_screenWidth(500),
		_screenHeight(500)
	{
	}


	Camera2D::~Camera2D(void)
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho( 0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight );
	}

	void Camera2D::update() {

		if (_needsMatrixUpdate) {

			//Camera Translation
            glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
            _cameraMatrix = glm::translate(_orthoMatrix, translate);

            //Camera Scale
            glm::vec3 scale(_scale, _scale, 0.0f);
            _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}

	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords){
		//Invert y direction
		screenCoords.y = _screenHeight - screenCoords.y;
		
		//make 0 the center
		screenCoords -= glm::vec2(_screenWidth/2, _screenHeight/2);
		//scale the coordinates
		screenCoords /= _scale;
		//translate with the camera position
		screenCoords += _position;
		return screenCoords;
	}

	glm::vec2 Camera2D::getScreenDimensions()
	{
		return glm::vec2(_screenWidth,_screenHeight);
	}

}