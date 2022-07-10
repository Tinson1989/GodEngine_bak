#pragma once
#include "Math/Matrix.hpp"

namespace GodEngine{
    class IRenderResource {
	    
    };

    struct ConstantBuffer {
        Matrix4x4f  world;          //世界矩阵
    	Matrix4x4f  view;           //视窗矩阵
        Matrix4x4f  projection;     //投影矩阵
        Vector4f    debugColor;     //调试的颜色
        Vector4f    pbrParameter;   //pbr参数
        Vector4f    camPos;         //摄像机位置
    };

    //光照信息，目前光照有：环境光，平行光，点光，聚光，面光
    struct ConstantBufferLighting {
        Vector4f directionDir;      //平行光方向
        Vector4f directionColor;    //平行光颜色
        Vector4f pointLightDir[4];  //点光源方向，看来是四个
        Vector4f pointLightColor[4];//点光源颜色
    };

    //动画矩阵？？？
    struct ConstantBufferAnimation {
        Matrix4x4f boneMatrix[32];
    };
}
