#include "Application.h"

Application* Application::instance = nullptr;

Application* Application::getInstance() {
	if (!instance) {
		instance = new Application();
	}
	return instance;
}

void Application::pushObject()
{
	if (this->selectedObjectIndex == 0)
		return;

	GLint x = (GLint)this->mouseX;
	GLint y = (GLint)this->mouseY;
	int newy = this->height - y;
	GLfloat depth;

	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	glm::vec3 screenX = glm::vec3(x, newy, depth);
	glm::mat4 view = this->mainScene->camera->getCamera();
	glm::vec4 viewPort = glm::vec4(0, 0, this->width, this->height);
	glm::vec3 pos = glm::unProject(screenX, view, this->mainScene->camera->getProjectionMatrix(), viewPort);
	Object* o = new Object(*this->mainScene->objects[this->mainScene->objectIndex(this->selectedObjectIndex)]);
	o->setPos(pos);
	//this->mainScene->objects.push_back(new Object(*this->mainScene->objects[this->mainScene->objectIndex(this->selectedObjectIndex)]));
	this->mainScene->objects.push_back(o);
}



GLFWwindow* Application::DrawWindow() {
	GLFWwindow* window;
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/* //inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	CallbackHandler::SetCallbacks(window);
	return window;
}


