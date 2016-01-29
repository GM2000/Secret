
#include "Secret.h"
#include "Camera.h"
#include "Shader.h"

namespace camera
{
	std::mutex CameraLock;

	double Speed = 0.01;

	float XRot;
	float YRot;

	location Loc(0.0, 0.0, 0.0);

	bool HasChange = false;

	void refreshUniform()
	{
		if (CameraLock.try_lock())
		{
			glUniformMatrix4fv(NormalShader::LocRotate, 1, GL_TRUE, glm::value_ptr(glm::rotate_slow(glm::mat4(), camera::XRot, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate_slow(glm::mat4(), camera::YRot, glm::vec3(0.0f, 1.0f, 0.0f))));
			glUniformMatrix4fv(NormalShader::LocTranslate, 1, GL_TRUE, glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(Loc.x(), Loc.y(), Loc.z()))));

			CameraLock.unlock();
		}
	}
}