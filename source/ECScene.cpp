/*
Author: Charles Ricchio

Contains the definitions for ECScene
*/

#include "ECScene.h"

namespace EnvironmentCore {




	void getMeshInformation(const Ogre::Mesh* const mesh,
		size_t &vertex_count,
		Ogre::Vector3* &vertices,
		size_t &index_count,
		unsigned long* &indices,
		const Ogre::Vector3 &position,
		const Ogre::Quaternion &orient,
		const Ogre::Vector3 &scale)
	{
		bool added_shared = false;
		size_t current_offset = 0;
		size_t shared_offset = 0;
		size_t next_offset = 0;
		size_t index_offset = 0;

		vertex_count = index_count = 0;

		// Calculate how many vertices and indices we're going to need
		for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i) {
			Ogre::SubMesh* submesh = mesh->getSubMesh(i);
			// We only need to add the shared vertices once
			if (submesh->useSharedVertices) {
				if (!added_shared) {
					vertex_count += mesh->sharedVertexData->vertexCount;
					added_shared = true;
				}
			}
			else {
				vertex_count += submesh->vertexData->vertexCount;
			}
			// Add the indices
			index_count += submesh->indexData->indexCount;
		}

		// Allocate space for the vertices and indices
		vertices = new Ogre::Vector3[vertex_count];
		indices = new unsigned long[index_count];

		added_shared = false;

		// Run through the submeshes again, adding the data into the arrays
		for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i) {
			Ogre::SubMesh* submesh = mesh->getSubMesh(i);

			Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

			if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared)) {
				if (submesh->useSharedVertices) {
					added_shared = true;
					shared_offset = current_offset;
				}

				const Ogre::VertexElement* posElem =
					vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

				Ogre::HardwareVertexBufferSharedPtr vbuf =
					vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

				unsigned char* vertex =
					static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

				// There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
				//  as second argument. So make it float, to avoid trouble when Ogre::Real will
				//  be comiled/typedefed as double:
				//Ogre::Real* pReal;
				float* pReal;

				for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize()) {
					posElem->baseVertexPointerToElement(vertex, &pReal);
					Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
					vertices[current_offset + j] = (orient * (pt * scale)) + position;
				}

				vbuf->unlock();
				next_offset += vertex_data->vertexCount;
			}

			Ogre::IndexData* index_data = submesh->indexData;
			size_t numTris = index_data->indexCount / 3;
			Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;

			bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

			unsigned long* pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
			unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);

			size_t offset = (submesh->useSharedVertices) ? shared_offset : current_offset;

			if (use32bitindexes) {
				for (size_t k = 0; k < numTris * 3; ++k) {
					indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
				}
			}
			else {
				for (size_t k = 0; k < numTris * 3; ++k) {
					indices[index_offset++] = static_cast<unsigned long>(pShort[k]) +
						static_cast<unsigned long>(offset);
				}
			}

			ibuf->unlock();
			current_offset = next_offset;
		}
	}




	unsigned int ECScene::m_LightCount = 0;

	ECScene::ECScene(Ogre::SceneManager* SceneManager, chrono::ChSystem* System) {
		m_pSceneManager = SceneManager;
		m_pChSystem = System;
		m_LowerLimit = 0;
	}

	ECScene::~ECScene() {
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			if (m_ECBodies[i]) {
				delete m_ECBodies[i];
			}
		}
	}


	void ECScene::setAmbientLight(Ogre::ColourValue Color) {
		m_pSceneManager->setAmbientLight(Color);
	}

	void ECScene::setAmbientLight(float r, float g, float b) {
		m_pSceneManager->setAmbientLight(Ogre::ColourValue(r, g, b));
	}

	ECLight& ECScene::createLight() {
		Ogre::Light* _ret = m_pSceneManager->createLight("Light" + std::to_string(m_LightCount));
		return *_ret;
	}

	ECLight& ECScene::createLight(std::string Name) {
		Ogre::Light* _ret = m_pSceneManager->createLight(Name);
		return *_ret;
	}

	void ECScene::removeLight(ECLight& Light) {
		m_pSceneManager->getRootSceneNode()->removeAndDestroyChild(Light.getName());
	}

	void ECScene::removeLight(std::string Name) {
		m_pSceneManager->getRootSceneNode()->removeAndDestroyChild(Name);
	}


	ECBody& ECScene::createBody(std::string Name) {
		ECBody* _ret = new ECBody(m_pSceneManager, m_pChSystem);
		_ret->name = Name;
		m_ECBodies.push_back(_ret);
		return *_ret;
	}

	ECBody& ECScene::getBody(std::string Name) {
		ECBody* _ret = nullptr;
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			if (m_ECBodies[i]) {
				if (Name == m_ECBodies[i]->name) {
					_ret = m_ECBodies[i];
				}
			}
		}
		return *_ret;
	}

	void ECScene::removeBody(ECBody& Body) {
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			if (m_ECBodies[i]) {
				if (&Body == m_ECBodies[i]) {
					delete m_ECBodies[i];
					m_ECBodies[i] = m_ECBodies.back();
					m_ECBodies.pop_back();
				}
			}
		}
	}

	void ECScene::removeBody(std::string Name) {
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			if (m_ECBodies[i]) {
				if (Name == m_ECBodies[i]->name) {
					delete m_ECBodies[i];
					m_ECBodies[i] = m_ECBodies.back();
					m_ECBodies.pop_back();
				}
			}
		}
	}

	void ECScene::update() {
		for (unsigned int i = 0; i < m_ECBodies.size(); i++) {
			m_ECBodies[i]->update();
			if (m_ECBodies[i]->getChBody()->GetPos().y < m_LowerLimit && m_ECBodies[i]->deletable == true && m_LowerLimit < 0) {
				removeBody(*m_ECBodies[i]);
			}
		}
	}


	ECBody& ECScene::spawnBox(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		chrono::ChVector<>& size,
		chrono::ChQuaternion<>& rotation,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChBoxShape> _box(new chrono::ChBoxShape);
		_box->GetBoxGeometry().Size = size;

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_box);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddBox(size.x, size.y, size.z);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnCapsule(std::string Name) {

		ECBody& _ret = createBody(Name);

		return _ret;
	}

	ECBody& ECScene::spawnCone(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		chrono::ChVector<>& size,
		chrono::ChQuaternion<>& rotation,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChConeShape> _cone(new chrono::ChConeShape);
		_cone->GetConeGeometry().rad = size;

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_cone);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddCone(size.x, size.z, size.y);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnCylinder(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		chrono::ChVector<>& size,
		chrono::ChQuaternion<>& rotation,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChCylinderShape> _cylinder(new chrono::ChCylinderShape);
		_cylinder->GetCylinderGeometry().rad = size.x;
		_cylinder->GetCylinderGeometry().p1 = chrono::ChVector<>(0, size.y, 0);
		_cylinder->GetCylinderGeometry().p2 = chrono::ChVector<>(0, 0, 0);

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_cylinder);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddCylinder(size.x, size.z, size.y);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnEllipsoid(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		chrono::ChVector<>& size,
		chrono::ChQuaternion<>& rotation,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChEllipsoidShape> _ellipsoid(new chrono::ChEllipsoidShape);
		_ellipsoid->GetEllipsoidGeometry().rad = size;

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_ellipsoid);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddEllipsoid(size.x, size.y, size.z);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnSphere(std::string Name,
		double mass,
		chrono::ChVector<>& position,
		double radius,
		bool fixed) {

		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChSphereShape> _sphere(new chrono::ChSphereShape);
		_sphere->GetSphereGeometry().rad = radius;

		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_sphere);

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddSphere(radius);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();

		return _ret;
	}

	ECBody& ECScene::spawnMesh(std::string Name, double mass, chrono::ChVector<>& position, chrono::ChVector<>& size, chrono::ChQuaternion<>& rotation, std::string FileName, bool fixed) {
		ECBody& _ret = createBody(Name);

		chrono::ChSharedPtr<chrono::ChTriangleMeshShape> _mesh(new chrono::ChTriangleMeshShape);
		_mesh->SetName(FileName);
		_mesh->SetScale(size);

		_ret->SetRot(rotation);
		_ret->SetPos(position);
		_ret->SetMass(mass);
		_ret->GetAssets().push_back(_mesh);

		Ogre::Entity* l_pEntity = m_pSceneManager->createEntity(FileName);
		Ogre::MeshPtr l_pMesh = l_pEntity->getMesh();

		size_t l_vertex_count, l_index_count;
		Ogre::Vector3* l_pvertices;
		unsigned long* l_pindices;
		chrono::geometry::ChTriangleMeshConnected l_triangle_mesh;

		getMeshInformation(l_pMesh.getPointer(), l_vertex_count, l_pvertices, l_index_count, l_pindices, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY, Ogre::Vector3::UNIT_SCALE);

		for (unsigned int i = 0; i < l_index_count; i+=3) {
			l_triangle_mesh.addTriangle(
				chrono::ChVector<>(									// Vertex 0
					(double) l_pvertices[l_pindices[i]].x,				// Index I.x
					(double) l_pvertices[l_pindices[i]].y,				// Index I.y
					(double) l_pvertices[l_pindices[i]].z				// Index I.z
					) * size,
				chrono::ChVector<>(									// Vertex 1
					(double) l_pvertices[l_pindices[i+1]].x,			// Index I+1.x
					(double )l_pvertices[l_pindices[i+1]].y,			// Index I+1.y
					(double) l_pvertices[l_pindices[i+1]].z				// Index I+1.z
					) * size,
				chrono::ChVector<>(									// Vertex 2
					(double) l_pvertices[l_pindices[i+2]].x,			// Index I+2.x
					(double) l_pvertices[l_pindices[i+2]].y,			// Index I+2.y
					(double) l_pvertices[l_pindices[i+2]].z				// Index I+2.z
					) * size
				);
		}

		m_pSceneManager->destroyEntity(l_pEntity);
		delete[] l_pvertices;
		delete[] l_pindices;


		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddTriangleMesh(l_triangle_mesh, true, false, chrono::ChVector<>(), chrono::QUNIT);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(fixed);

		_ret.refresh();
		
		return _ret;
	}


	void ECScene::setLowerLimit(double limit) {
		m_LowerLimit = limit;
	}

	double ECScene::getLowerLimit() {
		return m_LowerLimit;
	}

	void ECScene::setSkyBox(std::string Path) {
		m_pSceneManager->setSkyBox(true, Path);
	}

	void ECScene::disableSkyBox() {
		m_pSceneManager->setSkyBoxEnabled(false);
	}

}