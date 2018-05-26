#include "Demo.h"

Demo::Demo() {

}
Demo::~Demo() {
}
void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildKolamRenang();

	BuildPlane();
	BuildPlane2(); //pinggiran kolam
	BuildPelampung();
	BuildKursi(0,0,-10,0);
	BuildMeja(0,0,-9.5,0);
	BuildKursi(10,0,-10,1);
	BuildMeja(10,0,-9.5,1);
	BuildKursi(-5,0,-10,2);
	BuildMeja(-5,0,-9.5,2);
	BuildKursi(1.5,0,-15,3);
	BuildMeja(2,0,-14.5,3);
	BuildKursi(2.8, 0, -15, 4);
	BuildMeja(-3, 0, -14.5, 4);
	BuildKursi(-2.2, 0, -15, 7);
	BuildKursi(-3.5, 0, -15, 8);
	BuildKursi(5, 0, -10, 5);
	BuildMeja(5, 0, -9.5, 5);
	BuildKursi(-10, 0, -10, 6);
	BuildMeja(-10, 0, -9.5, 6);
	BuildSkyBox();
	Buildpagar();
	InitCamera();
}
void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	



}
void Demo::Update(double deltaTime) {
	stopwatch += deltaTime;
	if (stopwatch > 20000){
		side = 0;
	}
	if (stopwatch > 23000) {
		side = -CAMERA_SPEED / 4;
		forward = CAMERA_SPEED / 4;
		rotation = 0;
	}
	if (stopwatch > 28000) {
		side = 0;
		rotation = 0.004f;

	}
	if (stopwatch > 33000) {
		rotation = 0;
		forward = -CAMERA_SPEED / 4;
		
	}
	if (stopwatch > 38000) {
		forward = 0;
		rotation = 0.004f;
	}

	if (stopwatch > 42000) {
		rotation = 0;
	}
	if (stopwatch > 44000) {
		forward = CAMERA_SPEED / 6;
	}
	if (stopwatch > 46000) {
		forward = 0;
		rotation = -0.002f;
	}
	if (stopwatch > 49000) {
		rotation = 0.0f;
		forward = -CAMERA_SPEED / 4;
	}
	if (stopwatch > 52000 && stopwatch <55000) {
		posCamY += 0.05;
	}
	if (stopwatch > 56000) {
		side = -CAMERA_SPEED;
		rotation = 0.008f;
	}
	angle += (float) ((deltaTime * 1.5f) / 10000);
	//cinematic camera movement
	StrafeCamera(side);
	MoveCamera(forward);
	RotateCamera(rotation);
	
}
void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.52f, 0.80f, 0.92f, 1.0f);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 200.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// set lighting attributes
	GLint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, posCamX, posCamY, posCamZ);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.direction"), 0.0f, -1.0f, -1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.diffuse"), 0.8f, 0.8f, 0.7f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.specular"), 0.2f, 0.2f, 0.2f);
	DrawKolamRenang();
	DrawPlane();
	DrawPlane2();
	DrawPelampung();
	DrawKursi(0);
	DrawMeja(0);
	DrawKursi(1);
	DrawMeja(1);
	DrawKursi(2);
	DrawMeja(2);
	DrawKursi(3);
	DrawMeja(3);
	DrawKursi(4);
	DrawMeja(4);
	DrawKursi(5);
	DrawMeja(5);
	DrawKursi(6);
	DrawMeja(6);
	DrawKursi(7);
	DrawKursi(8);
	DrawSkyBox();
	Drawpagar();
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}
//pool
void Demo::BuildKolamRenang() { //kolam renang
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Texture/pool.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-7.5, -0.5, 3.5, 0, 0, 0.0f, 0.0f, 1.0f,  // 0
		7.5, -0.5, 3.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
		7.5,  0.5, 3.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 2
		-7.5,  0.5, 3.5, 0, 1, 0.0f, 0.0f, 1.0f, // 3

		// right
		7.5,  0.5,  3.5, 0, 0, 1.0f, 0.0f, 0.0f, // 4
		7.5,  0.5, -3.5, 1, 0, 1.0f, 0.0f, 0.0f, // 5
		7.5, -0.5, -3.5, 1, 1, 1.0f, 0.0f, 0.0f, // 6
		7.5, -0.5,  3.5, 0, 1, 1.0f, 0.0f, 0.0f, // 7

		// back
		-7.5, -0.5, -3.5, 0, 0, 0.0f, 0.0f, -1.0f, // 8 
		7.5,  -0.5, -3.5, 1, 0, 0.0f, 0.0f, -1.0f, // 9
		7.5,   0.5, -3.5, 1, 1, 0.0f, 0.0f, -1.0f, // 10
		-7.5,  0.5, -3.5, 0, 1, 0.0f, 0.0f, -1.0f, // 11

		// left
		-7.5, -0.5, -3.5, 0, 0, -1.0f, 0.0f, 1.0f, // 12
		-7.5, -0.5,  3.5, 1, 0, -1.0f, 0.0f, 1.0f, // 13
		-7.5,  0.5,  3.5, 1, 1, -1.0f, 0.0f, 1.0f, // 14
		-7.5,  0.5, -3.5, 0, 1, -1.0f, 0.0f, 1.0f, // 15

		// upper
		7.5, 0.5,  3.5, 0, 0,   0.0f, 1.0f, 0.0f, // 16
		-7.5, 0.5,  3.5, 1, 0,  0.0f, 1.0f, 0.0f, // 17
		-7.5, 0.5, -3.5, 1, 1,  0.0f, 1.0f, 0.0f, // 18
		7.5, 0.5, -3.5, 0, 1,   0.0f, 1.0f, 0.0f, // 19

		// bottom
		-7.5, -0.5, -3.5, 0, 0, 0.0f, -1.0f, 0.0f, // 20
		7.5, -0.5, -3.5, 1, 0,  0.0f, -1.0f, 0.0f, // 21
		7.5, -0.5,  3.5, 1, 1,  0.0f, -1.0f, 0.0f, // 22
		-7.5, -0.5,  3.5, 0, 1, 0.0f, -1.0f, 0.0f, // 23
	};
	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
		if (i % 8 == 0) { //x
			vertices[i] *= 2;
		}
		else if (i % 8 == 1) { //y
			vertices[i] -= 0.9;
		}
		else if (i % 8 == 2) { //z
			vertices[i] *= 2;
		}
		else if (i % 8 == 3) { //texX
		//	vertices[i] *= 4;
		}
		else if (i % 8 == 4) { //texY
		//	vertices[i] *= 4;
		}

	}

	unsigned int indices[] = {
		//8,  9,  10, 8,  10, 11,  // back
		//20, 22, 21, 20, 23, 22,   // bottom
		//4,  5,  6,  4,  6,  7,   // right
		//12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		//0,  1,  2,  0,  2,  3   // front
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawKolamRenang(){
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "shininess"), 5);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::BuildPlane(){
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("Texture/plain.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -50.0,  0,  0,  0.0f, 1.0f, 0.0f,
		50.0, -0.5, -50.0, 50,  0, 0.0f, 1.0f, 0.0f,
		50.0, -0.5,  50.0, 50, 50, 0.0f, 1.0f, 0.0f,
		-50.0, -0.5,  50.0,  0, 50, 0.0f, 1.0f, 0.0f,


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawPlane(){
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::InitCamera(){
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 16.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.009f;
	fovy = 45.0f;
	rotation = 0.004f;
	side = -CAMERA_SPEED / 2;
	forward = 0;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Demo::MoveCamera(float speed){
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}
void Demo::StrafeCamera(float speed){
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}
void Demo::RotateCamera(float speed){
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}
void Demo::BuildPlane2(){ //tepianKolam
	// Load and create a texture 
	glGenTextures(1, &textureEdge);
	glBindTexture(GL_TEXTURE_2D, textureEdge);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("Texture/tepian kolam.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// front
		-7.5, -0.5, 3.5, 0, 0, 0.0f, 0.0f, 1.0f,  // 0
		7.5, -0.5, 3.5, 1, 0, 0.0f, 0.0f, 1.0f,  // 1
		7.5,  0.5, 3.5, 1, 1, 0.0f, 0.0f, 1.0f,  // 2
		-7.5,  0.5, 3.5, 0, 1, 0.0f, 0.0f, 1.0f, // 3

		// right
		7.5,  0.5,  3.5, 0, 0, 1.0f, 0.0f, 0.0f, // 4
		7.5,  0.5, -3.5, 1, 0, 1.0f, 0.0f, 0.0f, // 5
		7.5, -0.5, -3.5, 1, 1, 1.0f, 0.0f, 0.0f, // 6
		7.5, -0.5,  3.5, 0, 1, 1.0f, 0.0f, 0.0f, // 7

		// back
		-7.5, -0.5, -3.5, 0, 0, 0.0f, 0.0f, -1.0f, // 8 
		7.5,  -0.5, -3.5, 1, 0, 0.0f, 0.0f, -1.0f, // 9
		7.5,   0.5, -3.5, 1, 1, 0.0f, 0.0f, -1.0f, // 10
		-7.5,  0.5, -3.5, 0, 1, 0.0f, 0.0f, -1.0f, // 11

		// left
		-7.5, -0.5, -3.5, 0, 0, -1.0f, 0.0f, 1.0f, // 12
		-7.5, -0.5,  3.5, 1, 0, -1.0f, 0.0f, 1.0f, // 13
		-7.5,  0.5,  3.5, 1, 1, -1.0f, 0.0f, 1.0f, // 14
		-7.5,  0.5, -3.5, 0, 1, -1.0f, 0.0f, 1.0f, // 15

		// upper
		7.5, 0.5,  3.5, 0, 0,   0.0f, 1.0f, 0.0f, // 16
		-7.5, 0.5,  3.5, 1, 0,  0.0f, 1.0f, 0.0f, // 17
		-7.5, 0.5, -3.5, 1, 1,  0.0f, 1.0f, 0.0f, // 18
		7.5, 0.5, -3.5, 0, 1,   0.0f, 1.0f, 0.0f, // 19

		// bottom
		-7.5, -0.5, -3.5, 0, 0, 0.0f, -1.0f, 0.0f, // 20
		7.5, -0.5, -3.5, 1, 0,  0.0f, -1.0f, 0.0f, // 21
		7.5, -0.5,  3.5, 1, 1,  0.0f, -1.0f, 0.0f, // 22
		-7.5, -0.5,  3.5, 0, 1, 0.0f, -1.0f, 0.0f, // 23

	};
	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
		if (i % 8 == 0) { //x
			vertices[i] *= 2.1;
		}
		else if (i % 8 == 1) { //y
			vertices[i] -= 0.91;
		}
		else if (i % 8 == 2) { //z
			vertices[i] *= 2.2;
		}

	}

	unsigned int indices[] = {
		8,  9,  10, 8,  10, 11,  // back
		20, 22, 21, 20, 23, 22,   // bottom
		4,  5,  6,  4,  6,  7,   // right
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		0,  1,  2,  0,  2,  3   // front
	};

	glGenVertexArrays(1, &VAOplane);
	glGenBuffers(1, &VBOplane);
	glGenBuffers(1, &EBOplane);

	glBindVertexArray(VAOplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBOplane);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOplane);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawPlane2(){
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureEdge);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAOplane); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::BuildPelampung() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texturepelampung);
	glBindTexture(GL_TEXTURE_2D, texturepelampung);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Texture/Ban.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		//outer
		//lurus dpn
		4.0, 0.0, 0.0, 0.5,0, 0.0f, 0.0f, 1.0f,  //0
		6.0, 0.0, 0.0,  0.5,1, 0.0f, 0.0f, 1.0f, //1
		4.0, 2.0, 0.0,  1,0, 0.0f, 0.0f, 1.0f, //2
		6.0, 2.0, 0.0,  1,1, 0.0f, 0.0f, 1.0f, //3
		//serong
		6.0, 0.0, 0.0, 0.5,0,  1.0f, 0.0f, 1.0f, //4
		8.0, 0.0, 2.0,  0.5,1, 1.0f, 0.0f, 1.0f,//5
		6.0, 2.0, 0.0,  1,0, 1.0f, 0.0f, 1.0f,//6
		8.0, 2.0, 2.0,  1,1, 1.0f, 0.0f, 1.0f,//7
		//serong
		4.0, 0.0, 0.0, 0.5,0,  1.0f, 0.0f, 1.0f,//8
		2.0, 0.0, 2.0,  0.5,1, 1.0f, 0.0f, 1.0f,//9
		4.0, 2.0, 0.0,  1,0, 1.0f, 0.0f, 1.0f,//10
		2.0, 2.0, 2.0,  1,1, 1.0f, 0.0f, 1.0f,//11
		//lurus samping
		2.0, 0.0, 2.0, 0.5,0,  1.0f, 0.0f, 0.0f,//12
		2.0, 0.0, 4.0,  0.5,1, 1.0f, 0.0f, 0.0f,//13
		2.0, 2.0, 2.0,  1,0, 1.0f, 0.0f, 0.0f,//14
		2.0, 2.0, 4.0,  1,1, 1.0f, 0.0f, 0.0f,//15
		//lurus samping
		8.0, 0.0, 2.0, 0.5,0,  1.0f, 0.0f, 0.0f,//16
		8.0, 0.0, 4.0,  0.5,1, 1.0f, 0.0f, 0.0f,//17
		8.0, 2.0, 2.0,  1,0, 1.0f, 0.0f, 0.0f,//18
		8.0, 2.0, 4.0,  1,1, 1.0f, 0.0f, 0.0f,//19
		//lurus depan
		4.0, 0.0, 6.0, 0.5,0,  0.0f, 0.0f, 1.0f,//20
		6.0, 0.0, 6.0,  0.5,1, 0.0f, 0.0f, 1.0f,//21
		4.0, 2.0, 6.0,  1,0, 0.0f, 0.0f, 1.0f,//22
		6.0, 2.0, 6.0,  1,1, 0.0f, 0.0f, 1.0f,//23
		//serong
		6.0, 0.0, 6.0, 0.5,0,  1.0f, 0.0f, 1.0f,//24
		8.0, 0.0, 4.0,  0.5,1, 1.0f, 0.0f, 1.0f,//25
		6.0, 2.0, 6.0,  1,0, 1.0f, 0.0f, 1.0f,//26
		8.0, 2.0, 4.0,  1,1, 1.0f, 0.0f, 1.0f,//27
		//serong
		4.0, 0.0, 6.0, 0.5,0,  1.0f, 0.0f, 1.0f,//28
		2.0, 0.0, 4.0,  0.5,1, 1.0f, 0.0f, 1.0f,//29
		4.0, 2.0, 6.0,  1,0, 1.0f, 0.0f, 1.0f,//30
		2.0, 2.0, 4.0,  1,1, 1.0f, 0.0f, 1.0f,//31

		//inside
		//lurus dpn
		4.0, 0.0, 1.5, 0.5,0,  0.0f, 0.0f, 0.0f,//32
		6.0, 0.0, 1.5,  0.5,1, 0.0f, 0.0f, 0.0f,//33
		4.0, 2.0, 1.5,  1,0, 0.0f, 0.0f, 0.0f,//34
		6.0, 2.0, 1.5,  1,1, 0.0f, 0.0f, 0.0f,//35
		//lurus depan
		4.0, 0.0, 4.5, 0.5,0,  0.0f, 0.0f, 0.0f,//36
		6.0, 0.0, 4.5,  0.5,1, 0.0f, 0.0f, 0.0f,//37
		4.0, 2.0, 4.5,  1,0, 0.0f, 0.0f, 0.0f,//38
		6.0, 2.0, 4.5,  1,1, 0.0f, 0.0f, 0.0f,//39
		//lurus samping
		3.5, 0.0, 2.0, 0.5,0,  0.0f, 0.0f, 0.0f,//40
		3.5, 0.0, 4.0,  0.5,1, 0.0f, 0.0f, 0.0f,//41
		3.5, 2.0, 2.0,  1,0, 0.0f, 0.0f, 0.0f,//42
		3.5, 2.0, 4.0,  1,1, 0.0f, 0.0f, 0.0f,//43
		//lurus samping
		6.5, 0.0, 2.0, 0.5,0,  0.0f, 0.0f, 0.0f,//44
		6.5, 0.0, 4.0,  0.5,1, 0.0f, 0.0f, 0.0f,//45
		6.5, 2.0, 2.0,  1,0, 0.0f, 0.0f, 0.0f,//46
		6.5, 2.0, 4.0,  1,1, 0.0f, 0.0f, 0.0f,//47
		//serong
		4.0, 0.0, 1.5, 0.5,0,  0.0f, 0.0f, 0.0f,//48
		3.5, 0.0, 2.0,  0.5,1, 0.0f, 0.0f, 0.0f,//49
		4.0, 2.0, 1.5,  1,0, 0.0f, 0.0f, 0.0f,//50
		3.5, 2.0, 2.0,  1,1, 0.0f, 0.0f, 0.0f,//51
		//serong
		6.0, 0.0, 1.5, 0.5,0,  0.0f, 0.0f, 0.0f,//52
		6.5, 0.0, 2.0,  0.5,1, 0.0f, 0.0f, 0.0f,//53
		6.0, 2.0, 1.5,  1,0, 0.0f, 0.0f, 0.0f,//54
		6.5, 2.0, 2.0,  1,1, 0.0f, 0.0f, 0.0f,//55
		//serong
		4.0, 0.0, 4.5, 0.5,0,  0.0f, 0.0f, 0.0f,//56
		3.5, 0.0, 4.0,  0.5,1, 0.0f, 0.0f, 0.0f,//57
		4.0, 2.0, 4.5,  1,0, 0.0f, 0.0f, 0.0f,//58
		3.5, 2.0, 4.0,  1,1, 0.0f, 0.0f, 0.0f,//59
		//serong
		6.0, 0.0, 4.5, 0.5,0,  0.0f, 0.0f, 0.0f,//60
		6.5, 0.0, 4.0,  0.5,1, 0.0f, 0.0f, 0.0f,//61
		6.0, 2.0, 4.5,  1,0, 0.0f, 0.0f, 0.0f,//62
		6.5, 2.0, 4.0,  1,1, 0.0f, 0.0f, 0.0f,//63	
		
		//up
		//lurus dpn
		4.0, 2.0, 0.0, 0,0,  0.0f, 1.0f, 0.0f,//64
		6.0, 2.0, 0.0,  0,1, 0.0f, 1.0f, 0.0f,//65
		4.0, 2.0, 1.5,  0.5,0, 0.0f, 1.0f, 0.0f,//66
		6.0, 2.0, 1.5,  0.5,1, 0.0f, 1.0f, 0.0f,//67
		//lurus dpn
		4.0, 2.0, 4.5, 0,0,  0.0f, 1.0f, 0.0f,//68
		6.0, 2.0, 4.5,  0,1, 0.0f, 1.0f, 0.0f,//69
		4.0, 2.0, 6.0,  0.5,0, 0.0f, 1.0f, 0.0f,//70
		6.0, 2.0, 6.0,  0.5,1, 0.0f, 1.0f, 0.0f,//71
		//lurus samping
		2.0, 2.0, 2.0, 0,0,  0.0f, 1.0f, 0.0f,//72
		2.0, 2.0, 4.0,  0,1, 0.0f, 1.0f, 0.0f,//73
		3.5, 2.0, 2.0,  0.5,0, 0.0f, 1.0f, 0.0f,//74
		3.5, 2.0, 4.0, 0.5,1, 0.0f, 1.0f, 0.0f,//75
		//lurus samping
		6.5, 2.0, 2.0, 0,0,  0.0f, 1.0f, 0.0f,//76
		6.5, 2.0, 4.0,  0,1, 0.0f, 1.0f, 0.0f,//77
		8.0, 2.0, 2.0, 0.5,0, 0.0f, 1.0f, 0.0f,//78
		8.0, 2.0, 4.0, 0.5,1, 0.0f, 1.0f, 0.0f,//79
		//serong
		6.0, 2.0, 0.0, 0, 0, 0.0f, 1.0f, 0.0f,//80
		8.0, 2.0, 2.0, 0, 1, 0.0f, 1.0f, 0.0f,//81
		6.0, 2.0, 1.5, 0.5, 0, 0.0f, 1.0f, 0.0f,//82
		6.5, 2.0, 2.0, 0.5, 1, 0.0f, 1.0f, 0.0f,//83
		//serong
		6.0, 2.0, 6.0, 0, 0, 0.0f, 1.0f, 0.0f,//84
		8.0, 2.0, 4.0, 0, 1, 0.0f, 1.0f, 0.0f,//85
		6.0, 2.0, 4.5, 0.5, 0, 0.0f, 1.0f, 0.0f,//86
		6.5, 2.0, 4.0, 0.5, 1, 0.0f, 1.0f, 0.0f,//87
		//serong
		4.0, 2.0, 0.0, 0, 0, 0.0f, 1.0f, 0.0f,//88
		2.0, 2.0, 2.0, 0, 1, 0.0f, 1.0f, 0.0f,//89
		4.0, 2.0, 1.5, 0.5, 0, 0.0f, 1.0f, 0.0f,//90
		3.5, 2.0, 2.0, 0.5, 1, 0.0f, 1.0f, 0.0f,//91
		//serong
		4.0, 2.0, 6.0, 0, 0, 0.0f, 1.0f, 0.0f,//92
		2.0, 2.0, 4.0, 0, 1, 0.0f, 1.0f, 0.0f,//93
		4.0, 2.0, 4.5, 0.5, 0, 0.0f, 1.0f, 0.0f,//94
		3.5, 2.0, 4.0, 0.5, 1, 0.0f, 1.0f, 0.0f,//95
							 
		//bot
	};
	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
		if (i % 8 == 0) { //x
			vertices[i] /= 4;
		}
		else if (i % 8 == 1) { //y
			vertices[i] /= 5;
			vertices[i] -= 0.55;
		}
		else if (i % 8 == 2) { //z
			vertices[i] /= 4;
		}
		else if (i % 8 == 3) { //texX
			//vertices[i] *= 4;
		}
		else if (i % 8 == 4) { //texY
			//vertices[i] *= 4;
		}

	}
	
	unsigned int indices[] = {
		//outer
		0,  1,  2,  1,  2,  3,
		4,  5,  6,  5,  6,  7,
		8,  9,  10,  9,  10,  11,
		12,  13,  14,  13,  14,  15,
		16,  17,  18,  17,  18,  19,
		20,  21,  22,  21,  22,  23,
		24,  25,  26,  25,  26,  27,
		28,  29,  30,  29,  30,  31,
		//inside
		32,  33,  34,  33,  34,  35,
		36,  37,  38,  37,  38,  39,
		40,  41,  42,  41,  42,  43,
		44,  45,  46,  45,  46,  47,
		48,  49,  50,  49,  50,  51,
		52,  53,  54,  53,  54,  55,
		56,  57,  58,  57,  58,  59,
		60,  61,  62,  61,  62,  63,
		//up
		64,  65,  66,  65,  66,  67,
		68,  69,  70,  69,  70,  71,
		72,  73,  74,  73,  74,  75,
		76,  77,  78,  77,  78,  79,
		80,  81,  82,  81,  82,  83,
		84,  85,  86,  85,  86,  87,
		88,  89,  90,  89,  90,  91,
		92,  93,  94,  93,  94,  95,
		//bot
	};

	glGenVertexArrays(1, &VAOpelampung);
	glGenBuffers(1, &VBOpelampung);
	glGenBuffers(1, &EBOpelampung);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOpelampung);

	glBindBuffer(GL_ARRAY_BUFFER, VBOpelampung);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOpelampung);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawPelampung() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturepelampung);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 2);

	glBindVertexArray(VAOpelampung); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(3, 0, 0));
	
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 200, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

}
void Demo::BuildKursi(float x, float y, float z, int c) {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texturekursi);
	glBindTexture(GL_TEXTURE_2D, texturekursi);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Texture/woods.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-2.0, -0.2, 2.0, 0, 0,  0.0f, 0.0f, 1.0f, // 0
		2.0, -0.2, 2.0, 1, 0,   0.0f, 0.0f, 1.0f,// 1
		2.0, 0.2, 2.0, 1, 1,    0.0f, 0.0f, 1.0f,// 2
		-2.0, 0.2, 2.0, 0, 1,   0.0f, 0.0f, 1.0f,// 3

		// right
		2.0, -0.2, -2.0, 0, 0,  1.0f, 0.0f, 0.6f,// 4
		2.0, 0.2, -2.0, 1, 0,  1.0f, 0.0f, 0.6f,// 5
		2.0, 0.2, 2.0, 1, 1,  1.0f, 0.0f, 0.6f,// 6
		2.0, -0.2, 2.0, 0, 1,  1.0f, 0.0f, 0.6f,// 7

		// back
		-2.0, -0.2, -2.0, 0, 0, 0.0f, 0.0f, -1.0f,// 8 
		-2.0, 0.2, -2.0, 1, 0, 0.0f, 0.0f, -1.0f,// 9
		2.0, 0.2, -2.0, 1, 1, 0.0f, 0.0f, -1.0f,// 10
		2.0, -0.2, -2.0, 0, 1, 0.0f, 0.0f, -1.0f,// 11

		// left
		-2.0, -0.2, -2.0, 0, 0, -1.0f, 0.0f, 0.6f,// 12
		-2.0, -0.2, 2.0, 1, 0, -1.0f, 0.0f, 0.6f,// 13
		-2.0, 0.2, 2.0, 1, 1, -1.0f, 0.0f, 0.6f,// 14
		-2.0, 0.2, -2.0, 0, 1, -1.0f, 0.0f, 0.6f,// 15

		// upper
		2.0, 0.2, 2.0, 0, 0,   0.0f, 1.0f, 0.0f,// 16
		-2.0, 0.2, 2.0, 1, 0,  0.0f, 1.0f, 0.0f,// 17
		-2.0, 0.2, -2.0, 1, 1,  0.0f, 1.0f, 0.0f,// 18
		2.0, 0.2, -2.0, 0, 1,   0.0f, 1.0f, 0.0f,// 19

		// bottom
		2.0, -0.2, 2.0, 0, 0, 0.0f, -1.0f, 0.0f,// 20
		-2.0, -0.2, 2.0, 1, 0,  0.0f, -1.0f, 0.0f,// 21
		-2.0, -0.2, -2.0, 1, 1,  0.0f, -1.0f, 0.0f,// 22
		2.0, -0.2, -2.0, 0, 1, 0.0f, -1.0f, 0.0f,// 23

		//table front leg
		//front
		2.0, -0.2, 1.6, 0, 0, 0.0f, 0.0f, 1.0f,//24
		1.4, -0.2, 1.6, 1, 0, 0.0f, 0.0f, 1.0f,//25
		1.4, -3.0, 1.6, 1, 1, 0.0f, 0.0f, 1.0f,//26
		2.0, -3.0, 1.6, 0 ,1, 0.0f, 0.0f, 1.0f,//27

		//back
		2.0, -0.2, 1.2, 0, 0, 0.0f, 0.0f, -1.0f,//28
		1.4, -0.2, 1.2, 1, 0, 0.0f, 0.0f, -1.0f,//29
		1.4, -3.0, 1.2, 1, 1, 0.0f, 0.0f, -1.0f,//30
		2.0, -3.0, 1.2, 0, 1, 0.0f, 0.0f, -1.0f,//31

		//right
		2.0, -0.2, 1.6, 0, 0, 1.0f, 0.0f, 0.6f,//32
		2.0, -0.2, 1.2, 1, 0, 1.0f, 0.0f, 0.6f,//33
		2.0, -3.0, 1.2, 1, 1, 1.0f, 0.0f, 0.6f,//34
		2.0, -3.0, 1.6, 0, 1, 1.0f, 0.0f, 0.6f,//35

		//left
		1.4, -0.2, 1.6, 0, 0, -1.0f, 0.0f, 0.6f,//36
		1.4, -0.2, 1.2, 1, 0, -1.0f, 0.0f, 0.6f,//37
		1.4, -3.0, 1.2, 1, 1, -1.0f, 0.0f, 0.6f,//38
		1.4, -3.0, 1.6, 0, 1, -1.0f, 0.0f, 0.6f,//39

		//back leg back
		//front
		2.0, -0.2, -1.2, 0, 0, 0.0f, 0.0f, 1.0f,//40
		1.4, -0.2, -1.2, 1, 0, 0.0f, 0.0f, 1.0f,//41
		1.4, -3.0, -1.2, 1, 1, 0.0f, 0.0f, 1.0f,//42
		2.0, -3.0, -1.2, 0, 1, 0.0f, 0.0f, 1.0f,//43

		//back
		2.0, -0.2, -1.6, 0, 0, 0.0f, 0.0f, -1.0f,//44
		1.4, -0.2, -1.6, 1, 0, 0.0f, 0.0f, -1.0f,//45
		1.4, -3.0, -1.6, 1, 1, 0.0f, 0.0f, -1.0f,//46
		2.0, -3.0, -1.6, 0 ,1, 0.0f, 0.0f, -1.0f,//47

		//right
		2.0, -0.2, -1.6, 0, 0, 1.0f, 0.0f, 0.6f,//48
		2.0, -0.2, -1.2, 1, 0, 1.0f, 0.0f, 0.6f,//49
		2.0, -3.0, -1.2, 1, 1, 1.0f, 0.0f, 0.6f,//50
		2.0, -3.0, -1.6, 0, 1, 1.0f, 0.0f, 0.6f,//51

		//left
		1.4, -0.2, -1.6, 0, 0, -1.0f, 0.0f, 0.6f,//52
		1.4, -0.2, -1.2, 1, 0, -1.0f, 0.0f, 0.6f,//53
		1.4, -3.0, -1.2, 1, 1, -1.0f, 0.0f, 0.6f,//54
		1.4, -3.0, -1.6, 0, 1, -1.0f, 0.0f, 0.6f,//55

		//leg left front
		-2.0, -0.2, 1.6, 0, 0, 0.0f, 0.0f, 1.0f,//56
		-1.4, -0.2, 1.6, 1, 0, 0.0f, 0.0f, 1.0f,//57
		-1.4, -3.0, 1.6, 1, 1, 0.0f, 0.0f, 1.0f,//58
		-2.0, -3.0, 1.6, 0, 1, 0.0f, 0.0f, 1.0f,//59

		//back
		-2.0, -0.2, 1.2, 0, 0, 0.0f, 0.0f, -1.0f,//60
		-1.4, -0.2, 1.2, 1, 0, 0.0f, 0.0f, -1.0f,//61
		-1.4, -3.0, 1.2, 1, 1, 0.0f, 0.0f, -1.0f,//62
		-2.0, -3.0, 1.2, 0, 1, 0.0f, 0.0f, -1.0f,//63

		//right
		-2.0, -0.2, 1.6, 0, 0, 1.0f, 0.0f, 0.6f,//64
		-2.0, -0.2, 1.2, 1, 0, 1.0f, 0.0f, 0.6f,//65
		-2.0, -3.0, 1.2, 1, 1, 1.0f, 0.0f, 0.6f,//66
		-2.0, -3.0, 1.6, 0, 1, 1.0f, 0.0f, 0.6f,//67

		//left
		-1.4, -0.2, 1.6, 0, 0, -1.0f, 0.0f, 0.6f,//68
		-1.4, -0.2, 1.2, 1, 0, -1.0f, 0.0f, 0.6f,//69
		-1.4, -3.0, 1.2, 1, 1, -1.0f, 0.0f, 0.6f,//70
		-1.4, -3.0, 1.6, 0, 1, -1.0f, 0.0f, 0.6f,//71

		//left leg back front
		//front
		-2.0, -0.2, -1.2, 0, 0, 0.0f, 0.0f, 1.0f,//72
		-1.4, -0.2, -1.2, 1, 0, 0.0f, 0.0f, 1.0f,//73
		-1.4, -3.0, -1.2, 1, 1, 0.0f, 0.0f, 1.0f,//74
		-2.0, -3.0, -1.2, 0, 1, 0.0f, 0.0f, 1.0f,//75

		//back
		-2.0, -0.2, -1.6, 0, 0, 0.0f, 0.0f, -1.0f,//76
		-1.4, -0.2, -1.6, 1, 0, 0.0f, 0.0f, -1.0f,//77
		-1.4, -3.0, -1.6, 1, 1, 0.0f, 0.0f, -1.0f,//78
		-2.0, -3.0, -1.6, 0, 1, 0.0f, 0.0f, -1.0f,//79

		//right
		-2.0, -0.2, -1.6, 0, 0, 1.0f, 0.0f, 0.6f,//80
		-2.0, -0.2, -1.2, 1, 0, 1.0f, 0.0f, 0.6f,//81
		-2.0, -3.0, -1.2, 1, 1, 1.0f, 0.0f, 0.6f,//82
		-2.0, -3.0, -1.6, 0, 1, 1.0f, 0.0f, 0.6f,//83

		//left
		-1.4, -0.2, -1.6, 0, 0, -1.0f, 0.0f, 0.6f,//84
		-1.4, -0.2, -1.2, 1, 0, -1.0f, 0.0f, 0.6f,//85
		-1.4, -3.0, -1.2, 1, 1, -1.0f, 0.0f, 0.6f,//86
		-1.4, -3.0, -1.6, 0, 1, -1.0f, 0.0f, 0.6f,//87

		//chair back
		//front
		-2.0, 0.2, -1.5, 0.5, 0, 0.0f, 0.0f, 1.0f,//88
		2.0, 0.2, -1.5, 1, 0, 0.0f, 0.0f, 1.0f,//89
		2.0, 4.0, -1.5, 1, 1, 0.0f, 0.0f, 1.0f,//90
		-2.0, 4.0, -1.5, 0.5, 1, 0.0f, 0.0f, 1.0f,//91

		//back
		-2.0, 0.2, -2.0, 0, 0, 0.0f, 0.0f, -1.0f,//92
		2.0, 0.2, -2.0, 0.5, 0, 0.0f, 0.0f, -1.0f,//93
		2.0, 4.0, -2.0, 0.5, 1, 0.0f, 0.0f, -1.0f,//94
		-2.0, 4.0, -2.0, 0, 1, 0.0f, 0.0f, -1.0f,//95

		//left
		-2.0, 0.2, -2.0, 0, 0, -1.0f, 0.0f, 0.6f,//96
		-2.0, 4.0, -2.0, 1, 0, -1.0f, 0.0f, 0.6f,//97
		-2.0, 4.0, -1.5, 1, 1, -1.0f, 0.0f, 0.6f,//98
		-2.0, 0.2, -1.5, 0, 1, -1.0f, 0.0f, 0.6f,//99

		//right
		2.0, 0.2, -2.0, 0, 0, 1.0f, 0.0f, 0.6f,//100
		2.0, 4.0, -2.0, 1, 0, 1.0f, 0.0f, 0.6f,//101
		2.0, 4.0, -1.5, 1, 1, 1.0f, 0.0f, 0.6f,//102
		2.0, 0.2, -1.5, 0, 1, 1.0f, 0.0f, 0.6f,//103

		//upper
		-2.0, 4.0, -2.0, 0, 0, 0.0f, 1.0f, 0.0f,//104
		2.0, 4.0, -2.0, 1, 0, 0.0f, 1.0f, 0.0f,//105
		2.0, 4.0, -1.5, 1, 1, 0.0f, 1.0f, 0.0f,//106
		-2.0, 4.0, -1.5, 0, 1, 0.0f, 1.0f, 0.0f,//107
	};
	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
		if (i % 8 == 0) { //x
			vertices[i] /= 5;
			vertices[i] += x;
		}
		else if (i % 8 == 1) { //y
			vertices[i] /= 5;
			vertices[i] += y;
		}
		else if (i % 8 == 2) { //z
			vertices[i] /= 5;
			vertices[i] += z;
		}
		else if (i % 8 == 3) { //texX
			//vertices[i] *= 4;
		}
		else if (i % 8 == 4) { //texY
			//vertices[i] *= 4;
		}
	}

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom

		24, 26, 25, 24, 27, 26, //table front leg , front
		28, 30, 29, 28, 31, 30, //back
		32, 34, 33, 32, 35, 34, //right
		36, 38, 37, 36, 39, 38, //left

		40, 42, 41, 40, 43, 42, //back leg back, front
		44, 46, 45, 44, 47, 46, //back
		48, 50, 49, 48, 51, 50, //right
		52, 54, 53, 52, 55, 54, //left

		56, 58, 57, 56, 59, 58, //leg left front
		60, 62, 61, 60, 63, 62, //back
		64, 66, 65, 64, 67, 66, //right
		68, 70, 69, 68, 71, 70, //left

		72, 74, 73, 72, 75, 74, //left leg back front
		76, 78, 77, 76, 79, 78, //back
		80, 82, 81, 80, 83, 82, //right
		84, 86, 85, 84, 87, 86, //left

		88, 90, 89, 88, 91, 90, //chair back, front
		92, 94, 93, 92, 95, 94, //back
		96, 98, 97, 96, 99, 98, //
		100, 102, 101, 100, 103, 102, //
		104, 106, 105, 104, 107, 106
	};

	glGenVertexArrays(1, &(VAOkursi[c]));
	glGenBuffers(1, &VBOkursi);
	glGenBuffers(1, &EBOkursi);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOkursi[c]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOkursi);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOkursi);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawKursi(int c) {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturekursi);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 3);

	glBindVertexArray(VAOkursi[c]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	//model = rotate(model, 1.5f, vec3(0, 1, 0));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 162, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

}
void Demo::BuildMeja(float x, float y, float z, int c) {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texturemeja);
	glBindTexture(GL_TEXTURE_2D, texturemeja);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Texture/mejapayung.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//tiang
		0.1, -3, -0.1, 0, 0, 1.0f, 0.0f, 1.0f, // 0
		0.1, -3, 0.1, 0.4, 0,  1.0f, 0.0f, 1.0f, // 1
		-0.1, -3, 0.1, 0.4, 0.5,  1.0f, 0.0f, 1.0f, // 2
		-0.1, -3, -0.1, 0, 0.5,  1.0f, 0.0f, 1.0f,// 3
		0.1, 7.8, -0.1, 0, 0,  1.0f, 0.0f, 1.0f,// 4
		0.1, 7.8, 0.1, 0.4, 0,  1.0f, 0.0f, 1.0f,// 5
		-0.1, 7.8, 0.1, 0.4, 0.5,  1.0f, 0.0f, 1.0f,// 6
		-0.1, 7.8, -0.1, 0, 0.5,  1.0f, 0.0f, 1.0f,// 7
		//payung
		0, 8, 0, 0.5, 0, 0.0f, 1.0f, 0.0f,// 8 
		-2, 7, 4, 1, 0, 0.0f, 1.0f, 0.0f,// 9
		2, 7, 4, 1, 1, 0.0f, 1.0f, 0.0f,// 10
		4, 7, 2, 0.6, 1, 0.0f, 1.0f, 0.0f,// 11
		4, 7, -2.0, 1, 0, 0.0f, 1.0f, 0.0f,// 12
		2.0, 7, -4, 1, 1, 0.0f, 1.0f, 0.0f,// 13
		-2.0, 7, -4.0, 1, 0, 0.0f, 1.0f, 0.0f,// 14
		-4.0, 7, -2.0, 1, 1, 0.0f, 1.0f, 0.0f,// 15
		-4.0, 7, 2.0, 1, 0,   0.0f, 1.0f, 0.0f,// 16
		//meja
		-1.0, 1.3, 2.0,  0.49, 0,  0.0f, 1.0f, 0.0f,// 17
		1.0, 1.3, 2.0,   0.0, 0.0,  0.0f, 1.0f, 0.0f,// 18
		2, 1.3, 1.0,     0.49, 0.5,   0.0f, 1.0f, 0.0f,// 19
		2.0, 1.3, -1.0,  0.49, 1, 0.0f, 1.0f, 0.0f,// 20
		1.0, 1.3, -2.0,  0.49, 1.0,  0.0f, 1.0f, 0.0f,// 21
		-1.0, 1.3, -2.0, 0.0, 1.0,  0.0f, 1.0f, 0.0f,// 22
		-2.0, 1.3, -1.0, 0, 0.5, 0.0f, 1.0f, 0.0f,// 23
		-2.0, 1.3, 1,    0, 0, 0.0f, 1.0f, 0.0f,//24
		-1, 1.1, 2,      0.49, 0, 0.0f, 1.0f, 0.0f,//25
		1, 1.1, 2,       0.49, 1, 0.0f, 1.0f, 0.0f,//26
		2.0, 1.1, 1,     0 ,0.5, 0.0f, 1.0f, 0.0f,//27
		2.0, 1.1, -1,    0, 0, 0.0f, 1.0f, 0.0f,//28
		1, 1.1, -2,      0.49, 0, 0.0f, 1.0f, 0.0f,//29
		-1, 1.1, -2,     0.49, 0.5, 0.0f, 1.0f, 0.0f,//30
		-2.0, 1.1, -1,   0, 0.5, 0.0f, 1.0f, 0.0f,//31
		-2.0, 1.1, 1,    0, 0, 0.0f, 1.0f, 0.0f,//32
		//extra
		-2, 7, 4, 1, 1, 0.0f, 1.0f, 0.0f,// 33
		2, 7, 4, 1, 0, 0.0f, 1.0f, 0.0f,// 34
		2, 1.3, 1.0,     0.49, 0,   0.0f, 1.0f, 0.0f,// 35
		2.0, 1.3, -1.0,  0.49, 1, 0.0f, 1.0f, 0.0f,// 36
		2.0, 1.3, -1.0,  0.49, 1, 0.0f, 1.0f, 0.0f,// 37
		1.0, 1.3, -2.0,  0.49, 0.0,  0.0f, 1.0f, 0.0f,// 38
		2.0, 7, -4, 1, 0, 0.0f, 1.0f, 0.0f,// 39


	};
	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
		if (i % 8 == 0) { //x
			vertices[i] /= 3;
			vertices[i] += x;
		}
		else if (i % 8 == 1) { //y
			vertices[i] /= 3;
			vertices[i] += y;
		}
		else if (i % 8 == 2) { //z
			vertices[i] /= 3;
			vertices[i] += z;
		}
		else if (i % 8 == 3) { //texX
			//vertices[i] *= 4;
		}
		else if (i % 8 == 4) { //texY
			//vertices[i] *= 4;
		}
	}

	unsigned int indices[] = {
		0,1,2,0,2,3, //bottom
		5,1,2,5,2,6, //front
		4,0,3,4,3,7, //back
		6,2,3,6,3,7, //left
		5,1,0,5,0,4, //right
		4,5,6,4,6,7, //top
		//payungnya
		8,9,10,8,11,34,
		8,12,11, 8,12,13,
		8,13,14,8,14,15,
		8,15,16,8,16,33,
		
		//mejanya
		17,23,24,17,22,23,
		18,22,17,18,21,22,
		18,36,35,18,37,38,
		25,31,32,25,30,31,
		26,30,25,26,29,30,
		27,28,26,28,29,26,
		
		//itunya meja
		17,18,26,17,26,25,
		18,19,27,18,27,26,
		19,20,28,19,28,27,
		20,21,29,20,29,28,
		21,22,30,21,30,29,
		22,23,31,22,31,30,
		23,24,32,23,32,31,
		24,17,25,24,25,32
	};

	glGenVertexArrays(1, &(VAOmeja[c]));
	glGenBuffers(1, &VBOmeja);
	glGenBuffers(1, &EBOmeja);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOmeja[c]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOmeja);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOmeja);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawMeja(int x) {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturemeja);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 3);

	glBindVertexArray(VAOmeja[x]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 162, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

}
void Demo::BuildSkyBox() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texturebox);
	glBindTexture(GL_TEXTURE_2D, texturebox);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Texture/skybox2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// back
		-3.5, -3.5, 3.5, 4.0f / 4, 1.0f / 3,  0.0f, 0.0f, 1.0f,  // 0
		3.5, -3.5, 3.5, 3.0f / 4, 1.0f / 3,   0.0f, 0.0f, 1.0f,// 1
		3.5,  3.5, 3.5, 3.0f / 4, 2.0f / 3,   0.0f, 0.0f, 1.0f,// 2
		-3.5,  3.5, 3.5, 4.0f / 4, 2.0f / 3,  0.0f, 0.0f, 1.0f,// 3

		// right
		3.5,  3.5,  3.5, 3.0f / 4, 2.0f / 3,  0.0f, 1.0f, 0.0f,// 4
		3.5,  3.5, -3.5, 2.0f / 4, 2.0f / 3,  0.0f, 1.0f, 0.0f,// 5
		3.5, -3.5, -3.5, 2.0f / 4, 1.0f / 3,  0.0f, 1.0f, 0.0f,// 6
		3.5, -3.5,  3.5, 3.0f / 4, 1.0f / 3,  0.0f, 1.0f, 0.0f,// 7

		// front
		-3.5, -3.5, -3.5, 1.0f / 4, 1.0f / 3, 0.0f, 0.0f, 1.0f,// 8 
		3.5,  -3.5, -3.5, 2.0f / 4, 1.0f / 3, 0.0f, 0.0f, 1.0f,// 9
		3.5,   3.5, -3.5, 2.0f / 4, 2.0f / 3, 0.0f, 0.0f, 1.0f,// 10
		-3.5,  3.5, -3.5, 1.0f / 4, 2.0f / 3, 0.0f, 0.0f, 1.0f,// 11

		// left
		-3.5, -3.5, -3.5, 1.0f / 4, 1.0f / 3, 0.0f, 1.0f, 0.0f,// 12
		-3.5, -3.5,  3.5, 0, 1.0f / 3, 0.0f, 1.0f, 0.0f,// 13
		-3.5,  3.5,  3.5, 0, 2.0f / 3, 0.0f, 1.0f, 0.0f,// 14
		-3.5,  3.5, -3.5, 1.0f / 4, 2.0f / 3, 0.0f, 1.0f, 0.0f,// 15

		// upper
		3.5, 3.5,  3.5, 2.0f / 4, 3.0f / 3,   0.0f, 1.0f, 0.0f,// 16
		-3.5, 3.5,  3.5, 1.0f / 4, 3.0f / 3,  0.0f, 1.0f, 0.0f,// 17
		-3.5, 3.5, -3.5, 1.0f / 4, 2.0f / 3,  0.0f, 1.0f, 0.0f,// 18
		3.5, 3.5, -3.5, 2.0f / 4, 2.0f / 3,   0.0f, 1.0f, 0.0f,// 19

		// bottom
		-3.5, -3.5, -3.5, 0, 0, 0.0f, 0.0f, 0.0f,// 20
		3.5, -3.5, -3.5, 1, 0,  0.0f, 0.0f, 0.0f,// 21
		3.5, -3.5,  3.5, 1, 1,  0.0f, 0.0f, 0.0f,// 22
		-3.5, -3.5,  3.5, 0, 1, 0.0f, 0.0f, 0.0f,// 23
	};

	unsigned int indices[] = {
		8,  9,  10, 8,  10, 11,  // back
		20, 22, 21, 20, 23, 22,   // bottom
		4,  5,  6,  4,  6,  7,   // right
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		0,  1,  2,  0,  2,  3   // front
	};

	glGenVertexArrays(1, &VAObox);
	glGenBuffers(1, &VBObox);
	glGenBuffers(1, &EBObox);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAObox);

	glBindBuffer(GL_ARRAY_BUFFER, VBObox);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBObox);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawSkyBox(){
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturebox);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "shininess"), 20);

	glBindVertexArray(VAObox); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
							
	glm::mat4 model;
	model = glm::scale(model, vec3(25.0f, 25.0f, 25.0f));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::Buildpagar() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texturepagar);
	glBindTexture(GL_TEXTURE_2D, texturepagar);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Texture/pagar.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// back
		-3.5, -3.5, 3.5, 0, 0,  0.0f, 0.0f, 1.0f,  // 0
		3.5, -3.5, 3.5, 1, 0,   0.0f, 0.0f, 1.0f,// 1
		3.5,  3.5, 3.5, 1, 1,   0.0f, 0.0f, 1.0f,// 2
		-3.5,  3.5, 3.5, 0, 1,  0.0f, 0.0f, 1.0f,// 3

		// right
		3.5,  3.5,  3.5, 0, 0,  0.0f, 1.0f, 0.0f,// 4
		3.5,  3.5, -3.5, 1, 0,  0.0f, 1.0f, 0.0f,// 5
		3.5, -3.5, -3.5, 1, 1,  0.0f, 1.0f, 0.0f,// 6
		3.5, -3.5,  3.5, 0, 1,  0.0f, 1.0f, 0.0f,// 7

		// front
		-3.5, -3.5, -3.5, 0, 0, 0.0f, 0.0f, 1.0f,// 8 
		3.5,  -3.5, -3.5, 1, 0, 0.0f, 0.0f, 1.0f,// 9
		3.5,   3.5, -3.5, 1, 1, 0.0f, 0.0f, 1.0f,// 10
		-3.5,  3.5, -3.5, 0, 1, 0.0f, 0.0f, 1.0f,// 11

		// left
		-3.5, -3.5, -3.5, 0, 0 , 0.0f, 1.0f, 0.0f,// 12
		-3.5, -3.5,  3.5, 1, 0, 0.0f, 1.0f, 0.0f,// 13
		-3.5,  3.5,  3.5, 1, 1, 0.0f, 1.0f, 0.0f,// 14
		-3.5,  3.5, -3.5, 0, 1, 0.0f, 1.0f, 0.0f,// 15

		// bottom
		-3.5, -3.5, -3.5, 0, 0, 0.0f, 0.0f, 0.0f,// 20
		3.5, -3.5, -3.5, 1, 0,  0.0f, 0.0f, 0.0f,// 21
		3.5, -3.5,  3.5, 1, 1,  0.0f, 0.0f, 0.0f,// 22
		-3.5, -3.5,  3.5, 0, 1, 0.0f, 0.0f, 0.0f,// 23
	};

	unsigned int indices[] = {
		8,  9,  10, 8,  10, 11,  // back
		4,  5,  6,  4,  6,  7,   // right
		12, 14, 13, 12, 15, 14,  // left
		0,  1,  2,  0,  2,  3   // front
	};

	glGenVertexArrays(1, &VAOpagar);
	glGenBuffers(1, &VBOpagar);
	glGenBuffers(1, &EBOpagar);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOpagar);

	glBindBuffer(GL_ARRAY_BUFFER, VBOpagar);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOpagar);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::Drawpagar() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturepagar);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAOpagar); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::scale(model, vec3(20.0f, 2.0f, 20.0f));
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Swimming Pool", 1366, 768, true, true);
}
