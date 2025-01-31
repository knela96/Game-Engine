#include "Application.h"
#include "MeshObject.h"
#include "ModuleGUI.h"
#include "C_Normals.h"
#include "C_Transform.h"
#include "C_Camera.h"
#include "Gizmo.h"
#include "Animator.h"

MeshObject::MeshObject(vector<Vertex> vertices, vector<uint> indices, GameObject* gameObject): gameobject(gameObject)
{
	this->vertices = vertices;
	this->indices = indices;

	SetupBuffers();
}

MeshObject::~MeshObject()
{
}


bool MeshObject::SetupBuffers() {
	bool ret = true;

	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// load data into indices buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// vertex normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	// vertex texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);
	// vertex colours
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colors));
	glEnableVertexAttribArray(3);
	//vertex joints WTF
	glVertexAttribPointer(4, 4,GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Joints)); //if want more bones ad a bigger number in the second parameter (now 4)
	glEnableVertexAttribArray(4);
	//vertex weights WTF
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Weights)); //if want more bones ad a bgger number in the second parameter (now 4)
	glEnableVertexAttribArray(5);

	glBindVertexArray(0);
	App->importer->shader->stop();



	return ret;
}

void MeshObject::Draw()
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	if (!gameobject->active || !App->importer->shader)
		return;

	mat4x4 model = mat4x4();
	model = gameobject->transform->globalMatrix * model;

	App->importer->shader->setBool("render", true);
	/*if (App->renderer3D->texture_active && gameobject->getComponent(Material)->isActive()) {
		if(!gameobject->debug_tex){
			for (unsigned int i = 0; i < gameobject->textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // active texture unit
				string number;
				aiTextureType type = gameobject->textures[i]->type;
				if (type == aiTextureType_DIFFUSE)
					number = std::to_string(diffuseNr++);
				else if (type == aiTextureType_SPECULAR)
					number = std::to_string(specularNr++);
				else if (type == aiTextureType_NORMALS)
					number = std::to_string(normalNr++);
				else if (type == aiTextureType_HEIGHT)
					number = std::to_string(heightNr++);

				//set the sampler to the correct texture unit
				App->importer->shader->setInt((gameobject->getType(type) + number).c_str(), i);

				glBindTexture(GL_TEXTURE_2D, gameobject->textures[i]->id);
			}
			//If mesh has no textures, don't draw any texture
			if (gameobject->textures.size() > 0) {
				App->importer->shader->use(0);
				App->importer->shader->setBool("render", true);
			}
			else {
				App->importer->shader->use(1);
				App->importer->shader->setBool("render", false);
			}
		}
		else {
			glActiveTexture(GL_TEXTURE0);
			//App->importer->shader->setInt("Diffuse_Map1", 1);
			glBindTexture(GL_TEXTURE_2D, App->importer->checkImage_id);
			App->importer->shader->setBool("render", true);
			App->importer->shader->use(0);
		}
	}
	else {
		App->importer->shader->use(1);
		App->importer->shader->setBool("render", false);
	}*/

	glPushMatrix();
	glMultMatrixf(gameobject->transform->globalMatrix.M);//Aplies transform to all rendering objects Lines,Box etc.

	glBindVertexArray(VAO);
	App->importer->shader->setMat4("model", model);
	App->importer->shader->setMat4("view", App->camera->camera->ViewMatrix4x4());
	App->importer->shader->setMat4("projection", App->camera->camera->ProjectionMatrix4x4());
	
	if (!App->renderer3D->texture_active) {
		App->importer->shader->setFloat("near", 1);
		App->importer->shader->setFloat("far", 1000);
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	App->importer->shader->stop();

	glBindTexture(GL_TEXTURE_2D, 0);
	/*if(gameobject->getComponent(Normals)->isActive())
		DebugNormals();*/	

	glBindVertexArray(0);
	glPopMatrix();

	if (gameobject->boundary_box) {
		Gizmo::DrawBox(gameobject->aabb, Color(0.f, 1.f, 0.f, 1.f));
		Gizmo::DrawBox(gameobject->obb, Color(0.f, 0.f, 1.f, 1.f));
	}
}

const vec3 MeshObject::getNormal(vec3 p1, vec3 p2, vec3 p3) const
{
	vec3 output;

	//Calculate vectors to create the normal
	vec3 calU = vec3(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	vec3 calV = vec3(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);

	//Normal Vector
	output.x = calU.y * calV.z - calU.z * calV.y;
	output.y = calU.z * calV.x - calU.x * calV.z;
	output.z = calU.x * calV.y - calU.y * calV.x;

	//Return normal normalized
	return normalize(output);
}

void MeshObject::CleanUp() {
	LOGC("Cleaned MeshObject Buffer");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glBindVertexArray(0);
}

void MeshObject::DebugNormals() const
{
	if (gameobject->vertex_normals) {
		//NORMAL VERTEX
		for (int i = 0; i < vertices.size(); i++)
		{
			vec3 vertex = vec3(vertices[i].Position.x, vertices[i].Position.y, vertices[i].Position.z);
			vec3 normal = vec3(vertices[i].Normal.x, vertices[i].Normal.y, vertices[i].Normal.z);

			glDisable(GL_LIGHTING);
			glBegin(GL_LINES);
			glColor3f(gameobject->normals->vertex_color.r, gameobject->normals->vertex_color.g, gameobject->normals->vertex_color.b);
			glVertex3f(vertex.x, vertex.y, vertex.z);
			glVertex3f((vertex.x + normal.x * gameobject->normals->vertex_lenght), (vertex.y + normal.y * gameobject->normals->vertex_lenght), (vertex.z + normal.z * gameobject->normals->vertex_lenght));
			glEnd();
			glEnable(GL_LIGHTING);
		}
	}

	if (gameobject->face_normals) {
		//NORMAL FACES
		for (int i = 0; i < indices.size(); i += 3)
		{
			vec3 p1 = vec3(vertices[indices[i]].Position.x, vertices[indices[i]].Position.y, vertices[indices[i]].Position.z);
			vec3 p2 = vec3(vertices[indices[i + 1]].Position.x, vertices[indices[i + 1]].Position.y, vertices[indices[i + 1]].Position.z);
			vec3 p3 = vec3(vertices[indices[i + 2]].Position.x, vertices[indices[i + 2]].Position.y, vertices[indices[i + 2]].Position.z);

			const vec3 normal = getNormal(p1, p2, p3);

			vec3 face_center = vec3(
				(p1.x + p2.x + p3.x) / 3,
				(p1.y + p2.y + p3.y) / 3,
				(p1.z + p2.z + p3.z) / 3
			);

			glDisable(GL_LIGHTING);
			glBegin(GL_LINES);
			glColor3f(gameobject->normals->face_color.r, gameobject->normals->face_color.g, gameobject->normals->face_color.b);
			glVertex3f(face_center.x, face_center.y, face_center.z);
			glVertex3f((face_center.x + normal.x * gameobject->normals->face_lenght), (face_center.y + normal.y * gameobject->normals->face_lenght), (face_center.z + normal.z * gameobject->normals->face_lenght));
			glEnd();
			glEnable(GL_LIGHTING);
		}
	}
}
