#include "drawHandler.hpp"


glm::mat4 drawHandler::getProjection()
{
	return ProjectionMatrix;
}

glm::mat4 drawHandler::getView()
{
	return ViewMatrix;
}