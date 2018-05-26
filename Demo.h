#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>
using namespace glm;
class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2;
	GLuint VBOplane, VAOplane, EBOplane, textureEdge;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	float angle = 0;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildKolamRenang();
	void BuildPlane();
	void BuildPlane2();
	void DrawKolamRenang();
	void DrawPlane();
	void DrawPlane2();
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
	//skybox
	GLuint VBObox, VAObox, EBObox, texturebox;
	void BuildSkyBox();
	void DrawSkyBox();
	//pagar
	GLuint VBOpagar, VAOpagar, EBOpagar, texturepagar;
	void Buildpagar();
	void Drawpagar();
	//pelampung
	GLuint VBOpelampung, VAOpelampung, EBOpelampung, texturepelampung;
	void BuildPelampung();
	void DrawPelampung();
	//kursi
	GLuint VBOkursi, VAOkursi[9], EBOkursi, texturekursi;
	void BuildKursi(float x, float y, float z, int c);
	void DrawKursi(int c);
	//meja
	GLuint VBOmeja, VAOmeja[7], EBOmeja, texturemeja;
	void BuildMeja(float x, float y, float z, int c);
	void DrawMeja(int c);

	float stopwatch = 0,rotation,forward,side;
};