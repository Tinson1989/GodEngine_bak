#pragma once
#include "Vector.hpp"

//线性变换，mvp矩阵
namespace GodEngine {
	template<typename T, size_t RowSize, size_t ColSize>
	constexpr size_t count(T(&)[RowSize][ColSize]) { return RowSize * ColSize; }

	template<typename T, int ROWS, int COLS>
	struct Matrix {
		union {
			T data[ROWS][COLS];
		};

		T* operator[](int rowIndex) {
			return data[rowIndex];
		}

		const T* operator[] (int rowIndex) const {
			return data[rowIndex];
		}

		operator T* () {
			return &data[0][0];
		}

		operator const T* () const {
			return reinterpret_cast<const T*>(&data[0][0]);
		}


		Matrix& operator=(const T* _data) {
			memcpy(data, _data, ROWS * COLS * sizeof(T));
			return *this;
		}

		bool operator==(const Matrix& m) {
			for (int r = 0; r < ROWS; r++) {
				for (int c = 0; c < COLS; c++) {
					if (data[r][c] != m[r][c]) {
						return false;
					}
				}
			}
			return true;
		}

		template<int _ROWS, int _COLS>
		bool operator!=(const Matrix<T, _ROWS, _COLS>& m) {
			if ((_ROWS != ROWS) || (_COLS != COLS)) {
				return true;
			}

			for (int r = 0; r < ROWS; r++) {
				for (int c = 0; c < COLS; c++) {
					if (data[r][c] != m[r][c]) {
						return true;
					}
				}
			}

			return false;
		}
	};

	typedef Matrix<float, 4, 4> Matrix4x4f;
	typedef Matrix<float, 3, 3> Matrix3x3f;

	//转置矩阵
	template<typename T, int ROWS, int COLS>
	inline void transpose(Matrix<T, COLS, ROWS>& result, const Matrix<T, ROWS, COLS>& m) {
		for(int r = 0; r < ROWS; r++) {
			for(int c = 0; c < COLS; c++) {
				result[c][r] = m[r][c];
			}
		}
	}

	//原地做转换矩阵
	template<typename T, int ROWS, int COLS>
	inline void transposeInPlace(Matrix<T, ROWS, COLS>& m) {
		Matrix<T, ROWS, COLS> result;
		for(int r = 0; r < ROWS; r++) {
			for(int c = 0; c < COLS; c++) {
				result[c][r] = m[r][c];
			}
		}
		m = result;
	}

	//矩阵相加
	template<typename T, int ROWS, int COLS>
	inline void matrixAdd(Matrix<T, ROWS, COLS>& result, const Matrix<T, ROWS, COLS>& m1, const Matrix<T, ROWS, COLS>& m2) {
		for(int r = 0; r < ROWS; r++) {
			for(int c = 0; c < COLS; c++) {
				result[r][c] = m1[r][c] + m2[r][2];
			}
		}
	}

	//矩阵相减
	template<typename T, int ROWS, int COLS>
	inline void matrixSub(Matrix<T, ROWS, COLS>& result, const Matrix<T, ROWS, COLS>& m1, const Matrix<T, ROWS, COLS>& m2) {
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				result[r][c] = m1[r][c] - m2[r][2];
			}
		}
	}

	template<typename T, int Da, int Db, int Dc>
	inline void matrixMultiBy(Matrix<T, Da, Dc>& result, const Matrix<T, Da, Db>& m1, const Matrix<T, Db, Dc>& m2) {
		Matrix<T, Da, Dc> tmp;
		for(int a = 0; a < Da; a++) {
			for(int c = 0; c < Dc; c++) {
				T sum = 0;
				for(int b = 0; b < Db; b++) {
					sum += m1[a][b] * m2[b][c];
				}
				tmp[a][c] = sum;
			}

			for(int a = 0; a < Da; a++) {
				for(int c = 0; c < Dc; c++) {
					result[a][c] = tmp[a][c];
				}
			}
		}
	}

	//矩阵相乘
	template<typename T, int Da, int Db, int Dc>
	Matrix<float, Da, Dc> operator*(const Matrix<T, Da, Db>& m1, const Matrix<T, Db, Dc>& m2) {
		Matrix<float, Da, Dc> tmp;
		matrixMultiBy(tmp, m1, m2);
		return tmp;
	}

	//交换某一列？？几何意义是啥
	template<typename T, int d>
	inline  void matrixSwapCols(Matrix<T, d, d> m, int col1, int col2) {
		for(int row = 0; row < d; row++) {
			T t = m[row][col1];
			m[row][col1] = m[row][col2];
			m[row][col2] = t;
		}
	}

	//交换某一行
	template<typename T, int d>
	inline void matrixSwapRow(Matrix<T, d, d> m, int row1, int row2) {
		for (int col = 0; col < d; col++) {
			T t = m[row1][col];
			m[row1][col] = m[row2][col];
			m[row2][col] = t;
		}
	}

	//逆矩阵
	template<typename T, int d>
	inline float inverse(Matrix<T, d, d>& out, const Matrix<T, d, d>& in) {
		Matrix<T, d, d> m = in;
		float fDet = 1.0f;
		int f = 1;
		int is[d];
		int js[d];
		int k, i, j, l;
		int dd = d;
		for(k = 0; k < d; k++) {
			float fMax = 0.0;
			for(i = k; i< d; i++) {
				for(j = k; j < d; j++) {
					const float f = abs(m[i][j]);
					if(f > fMax) {
						fMax = f;
						is[k] = i;
						js[k] = j;
					}
				}
			}

			if(abs(fMax) < 0.00000001f) {
				return 0;
			}
			if(is[k] != k) {
				f = -f;
				for(l = 0; l < d; l++) {
					T temp = m[k][l];
					m[k][l] = m[is[k]][l];
					m[is[k]][l] = temp;
				}
			}

			fDet *= m[k][k];
			m[k][k] = 1.0f / m[k][k];

			for(j = 0; j < d; j++) {
				if(j != k) {
					m[k][j] *= m[k][k];
				}
			}
			for(i = 0; i < d; i++) {
				if(i != k) {
					for(j = 0; j < d; j++) {
						if(j != k) {
							m[i][j] = m[i][j] - m[i][k] * m[k][j];
						}
					}
				}
			}
			for( i = 0; i < d; i++) {
				if(i != k) {
					m[i][k] *= -m[k][k];
				}
			}
		}

		for(k = d - 1; k>= 0; k--) {
			if(js[k] != k) {
				for(l = 0; l < d; l++) {
					T temp = m[k][l];
					m[k][l] = m[js[k]][l];
					m[js[k]][l] = temp;
				}
			}
			if(is[k] != k) {
				for(l = 0; l < d; l++) {
					T temp = m[l][k];
					m[l][k] = m[l][is[k]];
					m[l][is[k]] = temp;
				}
			}
		}

		out = m;
		return fDet * f;
	}

	inline Vector3f transformPoint(const Matrix4x4f& matrix, Vector3f& point) {
		Vector4f hSpace = Vector4f(point, 1);
		Vector4f temp = Vector4f(0);

		for(int r = 0; r < 4; r++) {
			for(int c = 0; c < 4; c++) {
				temp[r] = hSpace[c] * matrix[r][c];
			}
		}
		return Vector3f(temp.x, temp.y, temp.z);
	}

	inline Vector3f transformVector(const Matrix4x4f& matrix, Vector3f& point) {
		Vector4f hSpace = Vector4f(point, 1);
		Vector4f temp = Vector4f(0);

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				temp[r] = hSpace[c] * matrix[r][c];
			}
		}
		return Vector3f(temp.x, temp.y, temp.z);
	}

	inline Vector3f transformVector(const Matrix3x3f& matrix, Vector3f& vector) {
		Vector3f temp = Vector3f(0);

		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				temp[r] = vector[c] * matrix[r][c];
			}
		}
		return temp;
	}

	//构建旋转矩阵
	inline void buildMatrixRotationX(Matrix4x4f& matrix, const float radio) {
		float c = cosf(radio), s = sinf(radio);
		Matrix4x4f tmp = { {{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, c   , -s,   0.0f},
				{0.0f, s   , c,    0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		matrix = tmp;
	}

	//构建旋转矩阵
	inline void buildMatrixRotationY(Matrix4x4f& matrix, const float radio) {
		float c = cosf(radio), s = sinf(radio);
		Matrix4x4f tmp = { {{
				{	 c,	0.0f,    s, 0.0f },
				{ 0.0f,	1.0f, 0.0f, 0.0f },
				{	-s, 0.0f,    c, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			} } };
		matrix = tmp;
	}

	//构建旋转矩阵
	inline void buildMatrixRotationZ(Matrix4x4f& matrix, const float radio) {
		float c = cosf(radio), s = sinf(radio);
		Matrix4x4f tmp = { {{
				{ c,	-s,  0.0f, 0.0f },
				{ s,	c,    0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			}} };
		matrix = tmp;
	}


	//
	inline void buildMatrixYawPitchRoll(Matrix4x4f& matrix, const float yaw, const float pitch, const float roll) {
		float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;

		cYaw = cosf(yaw);
		cPitch = cosf(pitch);
		cRoll = cosf(roll);

		sYaw = sinf(yaw);
		sPitch = sinf(pitch);
		sRoll = sinf(roll);

		Matrix4x4f tmp = { {{
				{cRoll * cYaw + sRoll * sPitch * sYaw, (-sRoll * cYaw) + (cRoll * sPitch * sYaw), cPitch * sYaw, 0.0f},
				{sRoll * cPitch                      , (cRoll * cPitch),                          -sPitch,       0.0f},
				{cRoll * -sYaw + sRoll * sPitch * cYaw, (sRoll * sYaw) + (cRoll * sPitch * cYaw), cPitch * cYaw, 0.0f},
				{0.0f,                                  0.0f,                                     0.0f,          1.0f}
			}} };
		matrix = tmp;
	}

	//左手坐标系
	inline void buildMatrixViewLookatLH(Matrix4x4f& matrix, const Vector3f& position, const Vector3f& lookAt, const Vector3f& up) {
		Vector3f xAxis, yAxis, zAxis;
		float tmp1, tmp2, tmp3;
		vectorSub(zAxis, lookAt, position);
		normalize(zAxis);

		cross(xAxis, up, zAxis);
		normalize(xAxis);

		cross(yAxis, zAxis, xAxis);

		tmp1 = -dot(xAxis, position);
		tmp2 = -dot(yAxis, position);
		tmp3 = -dot(zAxis, position);

		Matrix4x4f tmp = { {{
				{ xAxis.x, xAxis.y, xAxis.z, tmp1},
				{ yAxis.x, yAxis.y, yAxis.z, tmp2},
				{ zAxis.x, zAxis.y, zAxis.z, tmp3},
				{ 0,       0,       0,       1.0f}
			}} };
		matrix = tmp;
	}

	//右手坐标系
	inline void buildMatrixViewLookatRH(Matrix4x4f& matrix, const Vector3f& position, const Vector3f& lookAt, const Vector3f& up) {
		Vector3f xAxis, yAxis, zAxis;
		float tmp1, tmp2, tmp3;
		//这里好像和Learn-OpenGL的有点像
		vectorSub(zAxis, position, lookAt);
		normalize(zAxis);

		cross(xAxis, up, zAxis);
		normalize(xAxis);

		cross(yAxis, zAxis, xAxis);

		tmp1 = -dot(xAxis, position);
		tmp2 = -dot(yAxis, position);
		tmp3 = -dot(zAxis, position);

		Matrix4x4f tmp = { {{
				{ xAxis.x, xAxis.y, xAxis.z, tmp1},
				{ yAxis.x, yAxis.y, yAxis.z, tmp2},
				{ zAxis.x, zAxis.y, zAxis.z, tmp3},
				{ 0,       0,       0,       1.0f}
			}} };
		matrix = tmp;
	}


	inline void buildMatrixPerspectiveFovLH(Matrix4x4f& matrix, const float fov, const float aspect, const float zn, const float zf) {
		auto yScale = 1.0f / tanf(fov * 0.5f);
		auto xScale = yScale / aspect;

		Matrix4x4f tmp = { {{
				{ xScale,	 0.0f,			  0.0f,					  0.0f},
				{	0.0f,  yScale,			  0.0f,					  0.0f},
				{	0.0f,    0.0f,	zf / (zf - zn), (-zn * zf) / (zf - zn)},
				{	0.0f,    0.0f,			  1.0f,					  0.0f}
			}} };
		matrix = tmp;
	}

	inline void buildMatrixPerspectiveFovRH(Matrix4x4f& matrix, const float fov, const float aspect, const float zn, const float zf) {
		auto yScale = 1.0f / tanf(fov * 0.5f);
		auto xScale = yScale / aspect;

		Matrix4x4f tmp = { {{
				{ xScale,	 0.0f,			  0.0f,					  0.0f},
				{	0.0f,  yScale,			  0.0f,					  0.0f},
				{	0.0f,    0.0f,	zf / (zn - zf),  (zn * zf) / (zn - zf)},
				{	0.0f,    0.0f,			 -1.0f,					  0.0f}
			}} };
		matrix = tmp;
	}

	//正交矩阵(左手坐标系)
	inline void buildMatrixOrthoLH(Matrix4x4f& matrix, const float width, const float height, const float zn, const float zf) {
		Matrix4x4f tmp = { {{
				{ 2 / width, 0.0f, 0.0f, 0.0f},
				{ 0.0f, 2 / height, 0.0f, 0.0f},
				{ 0.0f, 0.0f, 1.0f / (zf - zn), - zn / (zf - zn)},
				{ 0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		matrix = tmp;
	}

	//正交矩阵(右手坐标系)
	inline void buildMatrixOrthoRH(Matrix4x4f& matrix, const float width, const float height, const float zn, const float zf) {
		Matrix4x4f tmp = { {{
				{ 2 / width, 0.0f, 0.0f, 0.0f},
				{ 0.0f, 2 / height, 0.0f, 0.0f},
				{ 0.0f, 0.0f, 1.0f / (zn - zf), zn / (zn - zf)},
				{ 0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		matrix = tmp;
	}

	//平移矩阵
	inline void buildMatrixTranslation(Matrix4x4f& matrix, const float x, const float y, const float z) {
		Matrix4x4f tmp = { {{
				{ 1.0f, 0.0f, 0.0f, x},
				{ 0.0f, 1.0f, 0.0f, y},
				{ 0.0f, 0.0f, 1.0f, z},
				{ 0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		matrix = tmp;
	}

	inline Matrix4x4f buildMatrixTranslation(const float x, const float y, const float z) {
		Matrix4x4f tmp = { {{
				{ 1.0f, 0.0f, 0.0f, x},
				{ 0.0f, 1.0f, 0.0f, y},
				{ 0.0f, 0.0f, 1.0f, z},
				{ 0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		return tmp;
	}

	//缩放矩阵
	inline void buildMatrixScale(Matrix4x4f& matrix, const float x, const float y, const float z) {
		Matrix4x4f tmp = { {{
				{ x, 0.0f, 0.0f, 0.0},
				{ 0.0f, y, 0.0f, 0.0},
				{ 0.0f, 0.0f, z, 0.0},
				{ 0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		matrix = tmp;
	}

	//旋转矩阵，需要了解一下几何意义
	inline void buildMatrixRotationAxis(Matrix4x4f& matrix, const Vector3f& axis, const float radio) {
		float c = cosf(radio), s = sinf(radio), oneMinusC = 1.0f - c;

		Matrix4x4f tmp = { {{
				{ c + axis.x * axis.x * oneMinusC, axis.x * axis.y * oneMinusC - axis.z * s, axis.x * axis.z * oneMinusC + axis.y * s, 0.0f },
				{axis.x * axis.y * oneMinusC + axis.z * s, c + axis.y * axis.y * oneMinusC, axis.y * axis.z * oneMinusC - axis.x *s, 0.0f},
				{axis.x * axis.z * oneMinusC - axis.y * s, axis.y * axis.z * oneMinusC + axis.x * s, c + axis.z * axis.z * oneMinusC, 1.0f},
				{ 0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		matrix = tmp;
	}

	//绕着任意轴旋转
	//https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	inline void matrixRotationQuaternion(Matrix4x4f& matrix, Quaternion q) {
		Matrix4x4f tmp = { {{
				{1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z, 2.0f * q.x * q.y - 2.0f * q.w * q.z, 2.0f * q.x * q.z + 2.0f * q.w * q.y, 0.0f},
				{2.0f * q.x * q.y + 2.0f * q.w * q.z, 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z, 2.0f * q.y * q.z - 2.0f * q.y * q.z - 2.0f * q.w * q.x, 0.0f},
				{2.0f * q.x * q.z - 2.0f * q.w * q.z, 2.0f * q.y * q.z + 2.0f * q.w * q.x, 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		matrix = tmp;
	}

	inline Matrix4x4f matrixRotationQuaternion(Quaternion q) {
		Matrix4x4f tmp;
		matrixRotationQuaternion(tmp, q);
		return tmp;
	}

	//构建单位矩阵
	inline void buildMatrixIdentity(Matrix4x4f& matrix) {
		Matrix4x4f tmp = { {{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		matrix = tmp;
	}

	inline Matrix4x4f buildMatrisIndentity() {
		Matrix4x4f tmp = { {{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}
			}} };
		return tmp;
	}
}
