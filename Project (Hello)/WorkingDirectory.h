#pragma once
#include <string>


class WorkingDirectory {
public:
	static const std::string& get() {
		return path;
	}

private:
	/* Path to Game Resources */
	static std::string path;
};