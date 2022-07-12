用于存放图形API的接口


1. Vertex buffer view。渲染模型的顶点数据缓冲。一般而言这些数据包括顶点的模型空间坐标、uv坐标、法向量等。
2. Index buffer view。渲染模型的顶点索引缓冲。主要的作用是复用顶点数据，减少带宽消耗。
3. Constant buffer view。某一次渲染调用过程中的 “常量缓冲”，一般包含例如 MVP矩阵、光照信息、摄像机信息、或者一些全局信息等。
4. Shader。用来实现渲染中的各种效果。
5. Render Target View。渲染目标。一般用来输出主摄像机的额渲染输出，也可以用来实现离屏渲染之类的技术。
6. Texture和SamplerState。渲染用到的贴图和对应的采样器。
7. DepthStencilState。深度模板测试管线状态，可以改变本次渲染的测度测试行为和模板测试行为。
8. BlendState。混合状态，可以改变像素混合的行为。