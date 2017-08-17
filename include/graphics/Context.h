#pragma once

// Forward declare GLFW's window handling pointer type
struct GLFWwindow;

class Context {
private:
	GLFWwindow *handle;
	

public:
	
	bool getKey(int key);
	bool getMouseButton(int button);
	void getMousePosition(double &x_out, double &y_out);
	double getTime();

	int getJoystickPresent(int joy);
	void setTime(double time);
	
	bool init(size_t w = 800, size_t h = 600, const char *title = "gfx");
	bool step();
	bool exit();
		
};
