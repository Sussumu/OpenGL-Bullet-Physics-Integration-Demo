#include "Sphere.h"

Sphere::Sphere(ShaderProgram* shaderProgram, float radius, float precision, glm::vec3 position, float mass, bool enablePhysics)
{
	m_radius = radius;
	m_sectors = m_rings = m_precision = precision;

	m_shaderProgram = shaderProgram;
	m_position = position;

	m_mass = mass;
	hasPhysics = enablePhysics;
	shape = new btSphereShape(1);
	*motionState = btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(btScalar(position.x), btScalar(position.y), btScalar(position.z))));
	shape->calculateLocalInertia(mass, m_inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(m_mass, motionState, shape, m_inertia);
	rigidBody = new btRigidBody(rigidBodyCI);
}

Sphere::~Sphere()
{
}

void Sphere::setup()
{
#pragma region Vertices
	struct VertexData
	{
		GLdouble position[4];
		GLfloat color[3];
		GLfloat normal[3];
		GLfloat tcoords[2];
	};
	int level = 0;
	int polyCountXPitch = m_rings + 1;
	std::vector<VertexData> vertices;
	std::vector<GLushort> indices;

	for (GLuint p1 = 0; p1 < m_sectors - 1; ++p1)
	{
		for (GLuint p2 = 0; p2 < m_rings - 1; ++p2)
		{
			GLuint curr = level + p2;
			indices.push_back(curr + polyCountXPitch);
			indices.push_back(curr);
			indices.push_back(curr + 1);
			indices.push_back(curr + polyCountXPitch);
			indices.push_back(curr + 1);
			indices.push_back(curr + 1 + polyCountXPitch);
		}

		indices.push_back(level + m_rings - 1 + polyCountXPitch);
		indices.push_back(level + m_rings - 1);
		indices.push_back(level + m_rings);

		indices.push_back(level + m_rings - 1 + polyCountXPitch);
		indices.push_back(level + m_rings);
		indices.push_back(level + m_rings + polyCountXPitch);

		level += polyCountXPitch;
	}

	const GLuint polyCountSq = polyCountXPitch * m_sectors;           //top point
	const GLuint polyCountSq1 = polyCountSq + 1;                      //bottom point
	const GLuint polyCountSqM1 = (m_sectors - 1) * polyCountXPitch;   //last rows first index

	for (GLuint p2 = 0; p2 < m_rings - 1; ++p2)
	{
		indices.push_back(polyCountSq);
		indices.push_back(p2 + 1);
		indices.push_back(p2);

		indices.push_back(polyCountSqM1 + p2);
		indices.push_back(polyCountSqM1 + p2 + 1);
		indices.push_back(polyCountSq1);
	}

	indices.push_back(polyCountSq);
	indices.push_back(m_rings);
	indices.push_back(m_rings - 1);

	indices.push_back(polyCountSqM1 + m_rings - 1);
	indices.push_back(polyCountSqM1);
	indices.push_back(polyCountSq1);

	const GLdouble angleX = 2 * glm::pi<float>() / m_rings;
	const GLdouble angleY = glm::pi<float>() / m_sectors;

	GLuint i = 0;
	GLdouble axz;
	GLdouble ay = 0;

	vertices.resize(polyCountXPitch * m_sectors + 2);
	for (GLuint y = 0; y < m_sectors; ++y)
	{
		ay += angleY;
		const GLdouble sinay = std::sin(ay);
		axz = 0;

		for (GLuint xz = 0; xz < m_rings; ++xz)
		{
			const glm::vec3 pos((m_radius * std::cos(axz) * sinay), m_radius * std::cos(ay), m_radius * std::sin(axz) * sinay);
			glm::vec3 normal = pos;
			normal = glm::normalize(normal);

			GLuint tu = 0.5f;
			if (y == 0)
			{
				if (normal.y != -1.0f && normal.y != 1.0f)
					tu = std::acos(glm::clamp<GLdouble>(normal.x / sinay, -1.0f, 1.0f)) * 0.5 * (1.0f / glm::pi<float>());
				if (normal.z < 0.0f)
					tu = 1 - tu;
			}
			else
				tu = vertices[i - polyCountXPitch].tcoords[0];

			VertexData v;
			v.color[0] = 1;
			v.color[1] = 1;
			v.color[2] = 1;
			v.position[0] = pos.x;
			v.position[1] = pos.y;
			v.position[2] = pos.z;
			v.position[3] = 1.0f;
			v.normal[0] = normal.x;
			v.normal[1] = normal.y;
			v.normal[2] = normal.z;
			v.tcoords[0] = tu;
			v.tcoords[1] = ay * (1.0f / glm::pi<float>());
			vertices.at(i) = v;

			++i;
			axz += angleX;
		}

		vertices.at(i) = vertices.at(i - m_rings);
		vertices.at(i).tcoords[0] = 1.0f;
		++i;

		VertexData v;
		v.color[0] = 1;
		v.color[1] = 1;
		v.color[2] = 1;
		v.position[0] = 0;
		v.position[1] = m_radius;
		v.position[2] = 0;
		v.position[3] = 1.0f;
		v.normal[0] = 0;
		v.normal[1] = 1;
		v.normal[2] = 0;
		v.tcoords[0] = 0.5f;
		v.tcoords[1] = 0.0f;
		vertices.at(i) = v;
		++i;
		v.position[1] = -m_radius;
		v.normal[1] = -1.0f;
		v.tcoords[1] = 1.0f;
		vertices.at(i) = v;
	}

#pragma endregion

#pragma region Draw
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct VertexData) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_DOUBLE, GL_FALSE, sizeof(struct VertexData), (const GLvoid*)offsetof(struct VertexData, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct VertexData), (const GLvoid*)offsetof(struct VertexData, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(struct VertexData), (const GLvoid*)offsetof(struct VertexData, normal));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(struct VertexData), (const GLvoid*)offsetof(struct VertexData, tcoords));

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#pragma endregion
}

void Sphere::updatePhysics()
{
	btTransform transform;
	rigidBody->getMotionState()->getWorldTransform(transform);

	m_position.x = transform.getOrigin().getX();
	m_position.y = transform.getOrigin().getY();
	m_position.z = transform.getOrigin().getZ();

	transform.getBasis().getEulerYPR(yaw, pitch, roll);
}

void Sphere::update()
{
	m_shaderProgram->use();

#pragma region Rendering
	GLint modelLoc = glGetUniformLocation(m_shaderProgram->programID, "model");
	GLint viewLoc = glGetUniformLocation(m_shaderProgram->programID, "view");
	GLint projLoc = glGetUniformLocation(m_shaderProgram->programID, "projection");
	GLint objectColorLoc = glGetUniformLocation(m_shaderProgram->programID, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(m_shaderProgram->programID, "lightColor");

	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f);

	glBindVertexArray(m_VAO);
	glm::mat4 model;
	model = glm::translate(model, m_position);
	model = glm::rotate(model, yaw, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, pitch, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, roll, glm::vec3(1.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	m_shaderProgram->unuse();
#pragma endregion
}

void Sphere::clean()
{
	delete shape;
	delete rigidBody->getMotionState();
	delete rigidBody;
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

btRigidBody* Sphere::getRigidBody()
{
	return rigidBody;
}
