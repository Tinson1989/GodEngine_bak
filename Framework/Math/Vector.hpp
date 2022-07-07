#pragma once

#include <cstdint>
#include <iostream>

//主要实现：加减，点乘，叉乘，缩放，归一化
namespace GodEngine {
	template<typename T, size_t SizeOfArray>
	constexpr  size_t count(T(&)[SizeOfArray]) { return SizeOfArray; }

	template<typename T>
	struct Vector2Type {
		union {
			T data[2];
			struct { T x, y; };
			struct { T r, g; };
			struct { T u, v; };
		};

		//构造函数
		Vector2Type<T>(){}
		Vector2Type<T>(const T& _v) : x(_v), y(_v) {};
		Vector2Type<T>(const T& _x, const T& _y) : x(_x), y(_y) {};

		operator T* () { return data; };
		operator const T* () const { return static_cast<const T*>(data); };
	};

	typedef Vector2Type<float> Vector2f;

	template<typename T>
	struct Vector3Type {
		union {
			T data[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		//构造函数
		Vector3Type<T>() {}
		Vector3Type<T>(const T& _v) : x(_v), y(_v), z(_v) {};
		Vector3Type<T>(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {};

		operator T* () { return data; };
		operator const T* () const { return static_cast<const T*>(data); };
	};

	typedef Vector3Type<float> Vector3f;


	template<typename T>
	struct Vector4Type {
		union {
			T data[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		//构造函数
		Vector4Type<T>() {}
		Vector4Type<T>(const T& _v) : x(_v), y(_v), z(_v), w(_v) {};
		Vector4Type<T>(const T& _x, const T& _y, const T& _z, const T& _w) : x(_x), y(_y), z(_z), w(_w) {};
		//用vector3初始化
		Vector4Type<T>(const Vector3Type<T>& v3) : x(v3.x), y(v3.y), z(v3.z), w(1.0) {};
		Vector4Type<T>(const Vector3Type<T>& v3, const T& _w) :x(v3.x), y(v3.y), z(v3.z), w(_w) {};

		operator T* () { return data; };
		operator const T* () const { return static_cast<const T*>(data); };
		Vector4Type& operator=(const T* f) {
			memcpy(data, f, sizeof(T) * 4);
			return *this;
		}
	};

	typedef Vector4Type<float> Vector4f;
	typedef Vector4Type<float> Quaternion;//定义四元数
	typedef Vector4Type<uint8_t> R8G8B8A8Unorm;
	typedef Vector4Type<uint8_t> Vector4i;
	typedef Vector4Type<float> Color;//定义颜色值，范围可以是0-1，或者0-255

	//输出整个vector
	template<template<typename> class TT, typename T>
	std::ostream& operator<< (std::ostream& out, TT<T> vector) {
		out << "( ";
		for(uint32_t i = 0; i < count(vector.data); i++) {
			out << vector.data[i] << ((i == count(vector.data) - 1) ? ' ' : ',');
		}
		out << ")";
		return out;
	}

	//向量相加
	template<template<typename> class TT, typename T>
	void vectorAdd(TT<T>& result, const TT<T>& vec1, const TT<T>& vec2) {
		size_t size = count(result.data);
		for(size_t i = 0; i < size; i++) {
			result[i] = vec1[i] + vec2[i];
		}
	}

	//向量相减
	template<template<typename> class TT, typename T>
	void vectorSub(TT<T>& result, const TT<T>& vec1, const TT<T>& vec2) {
		size_t size = count(result.data);
		for (size_t i = 0; i < size; i++) {
			result[i] = vec1[i] - vec2[i];
		}
	}

	//叉乘
	template<template<typename> class TT, typename T>
	void cross(TT<T>& result, const TT<T>& vec1, const TT<T>& vec2) {
		result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
		result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	}

	//点乘
	template<template<typename> class TT, typename T>
	inline T dot(const TT<T>& vec1, const TT<T>& vec2) {
		size_t size = count(vec1.data);
		T result = 0;
		for(size_t i = 0; i < size; i++) {
			result += vec1[i] * vec2[i];
		}
		return result;
	}

	//归一化
	template<template<typename> class TT, typename T>
	inline void normalize(TT<T>& result) {
		T length;
		size_t size = count(result.data);
		length = dot(result, result);
		length = 1.0f / sqrt(length);
		for(size_t i = 0; i< size; i++) {
			result[i] = result[i] * length;
		}
	}
}
