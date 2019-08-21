#pragma once

template<typename T>
class SingleInstance {
public:
	SingleInstance() {};
	virtual ~SingleInstance() {};

	static T* GetInstance() {
		static T* Instance = new T();
		return Instance;
	}
};