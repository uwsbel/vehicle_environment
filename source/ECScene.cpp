/*
Author: Charles Ricchio

Contains the definitions for ECScene
*/

#include "ECScene.h"
#include <thread>

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
					(double) l_pvertices[l_pindices[i+1]].y,			// Index I+1.y
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

	ECBody& ECScene::loadHeightMap(std::string FilePath, chrono::ChVector<>& Scale) {
		Ogre::TexturePtr l_tex = Ogre::TextureManager::getSingleton().load(FilePath, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		if (l_tex->getFormat() != Ogre::PF_L16 && l_tex->getFormat() != Ogre::PF_L8) {
			Ogre::TextureManager::getSingleton().remove((Ogre::ResourcePtr)l_tex);
			l_tex.setNull();
			l_tex = Ogre::TextureManager::getSingleton().load(FilePath, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, -1, 1.0f, false, Ogre::PF_L8);
		}

		Ogre::HardwarePixelBufferSharedPtr l_pixels = l_tex->getBuffer();
		size_t l_byte_size = l_pixels->getSizeInBytes();
		Ogre::PixelFormat l_format = l_tex->getFormat();

		assert(l_format == Ogre::PF_L16 || l_format == Ogre::PF_L8); // Garuntee grayscale

		size_t l_vertex_count = l_pixels->getHeight() * l_pixels->getWidth();
		std::vector<Ogre::Real> l_vertex_heights;
		Ogre::PixelBox l_temp_pixel_buffer(l_tex->getWidth(), l_tex->getHeight(), l_tex->getDepth(), l_format);
		void* l_pPixels = nullptr;
		bool catfish = l_tex->isLoaded();

		
		l_pPixels = new unsigned char[l_byte_size];


		//l_pixels->lock(l_temp_pixel_buffer, Ogre::HardwareBuffer::HBL_NORMAL);

		//Ogre::PixelBox const &pixel_box = l_pixels->getCurrentLock();
		//l_pixels->blitToMemory(pixel_box);
		//l_pixels->unlock();
		//l_pPixels = pixel_box.data;

		

		memcpy(l_pPixels, l_pixels->lock(Ogre::HardwareBuffer::HBL_NORMAL), l_byte_size);

		double l_height_w = l_format == Ogre::PF_L16 ? (double)USHRT_MAX : (double)UCHAR_MAX;

		for (unsigned int i = 0; i < l_vertex_count; i++) { // Fill vector with normalized heights
			if (l_format == Ogre::PF_L8) {
				l_vertex_heights.push_back( (Ogre::Real) ( ( (double)( (unsigned char*)l_pPixels )[i] ) / l_height_w ) );
			}
			else {
				l_vertex_heights.push_back( (Ogre::Real) ( ( (double)( (unsigned short*)l_pPixels )[i] ) / l_height_w ) );
			}
		}

		delete[] l_pPixels;

		std::vector<Ogre::Vector3> l_vertices;
		l_vertices.resize(l_vertex_count);

		typedef struct {
			unsigned int a;
			unsigned int b;
			unsigned int c;
		} triangle_index_set;

		std::vector<triangle_index_set> l_indices;
		unsigned int l_square_width = l_pixels->getWidth() - 1;
		unsigned int l_square_height = l_pixels->getHeight() - 1;
		unsigned int l_square_count = l_square_width * l_square_height;
		l_indices.resize(l_square_count * 2);

		std::vector<Ogre::Vector3> l_triangle_normals;
		l_triangle_normals.resize(l_square_count * 2);

		std::vector<Ogre::Vector3> l_vertex_normals;
		l_vertex_normals.resize(l_vertex_count);

		for (unsigned int i = 0; i < l_vertex_count; i++) { // Fill vertices

			unsigned int l_w = (i % l_pixels->getWidth());
			unsigned int l_h = (i / l_pixels->getWidth());

			Ogre::Real l_wa = (Ogre::Real)l_w - (Ogre::Real)(l_pixels->getWidth()) / 2.0;
			Ogre::Real l_ha = (Ogre::Real)l_h - (Ogre::Real)(l_pixels->getHeight()) / 2.0;

			l_vertices[i] = Ogre::Vector3(l_wa, std::abs(l_vertex_heights[i]), l_ha);
		}

		for (unsigned int i = 0; i < l_square_count * 2; i += 2) { // Fill indices
			unsigned int l_triangle_width = l_square_width * 2;
			unsigned int l_iteration_y_position = i / l_triangle_width;
			unsigned int l_triangle_to_pixel = (i + (2 * l_iteration_y_position)) / 2;

			l_indices[i + 0].a = l_triangle_to_pixel;
			l_indices[i + 0].b = l_triangle_to_pixel + l_pixels->getWidth();
			l_indices[i + 0].c = l_triangle_to_pixel + 1;
			l_indices[i + 1].a = l_triangle_to_pixel + 1;
			l_indices[i + 1].b = l_triangle_to_pixel + l_pixels->getWidth();
			l_indices[i + 1].c = l_triangle_to_pixel + l_pixels->getWidth() + 1;
		}

		for (unsigned int i = 0; i < l_triangle_normals.size(); i++) { // Calculate normals of all triangles
			Ogre::Vector3 _t1(l_vertices[l_indices[i].a]);
			Ogre::Vector3 _t2(l_vertices[l_indices[i].b]);
			Ogre::Vector3 _t3(l_vertices[l_indices[i].c]);
			Ogre::Vector3 _ret = (_t1 - _t2).crossProduct(_t1 - _t3);
			_ret.normalise();
			l_triangle_normals[i] = _ret;
		}

		//!!!!
		//	This algorithm takes ungodly long single-threaded in larger heightmaps.
		//!!!!
		{ // Calculate normals of all vertices
			typedef struct __thread_set_t {
				size_t _start;
				size_t _end;
				std::thread _thread;
			} __thread_set;

			size_t _thread_count = std::thread::hardware_concurrency();

			std::function<Ogre::Vector3(unsigned int i)> _find_vertex_normal = [&](unsigned int i) {
				Ogre::Vector3 _ret(0, 0, 0);

				bool is_not_top = !(i < l_pixels->getWidth());
				bool is_not_left = !((i % l_pixels->getWidth()) == 0);
				bool is_not_right = !(((i + 1) % l_pixels->getWidth()) == 0);
				bool is_not_bottom = !(i > (l_vertex_count - l_pixels->getWidth()));

				unsigned int iter_x_pos = i % l_pixels->getWidth();
				unsigned int iter_y_pos = i / l_pixels->getHeight();

				if (i == 1) {
					_ret += l_triangle_normals[0];
					_ret += l_triangle_normals[1];
					_ret += l_triangle_normals[2];
					return _ret;
				}

				//		____
				//	   /| / | 
				//	  / |/	|
				//	  | /| / 
				//	  |/_|/
				//

				unsigned int lower_right = i + (iter_y_pos * (l_pixels->getWidth() - 2)) + iter_x_pos;
				unsigned int lower_middle = lower_right - 1;
				unsigned int lower_left = lower_middle - 1;

				unsigned int upper_right = lower_right - ((l_pixels->getWidth() * 2) - 3);
				unsigned int upper_middle = upper_right - 1;
				unsigned int upper_left = upper_middle - 1;

				// Upper-left slice
				if (is_not_top && is_not_left) {
					_ret += l_triangle_normals[upper_left];
				}

				// Upper-middle slice && Upper-right slice
				else if (is_not_top && is_not_right) {
					_ret += l_triangle_normals[upper_middle];
					_ret += l_triangle_normals[upper_right];
				}

				// Lower-left slice && Lower-middle slice
				else if (is_not_left && is_not_bottom) {
					_ret += l_triangle_normals[lower_left];
					_ret += l_triangle_normals[lower_middle];
				}

				// Lower-right slice
				else if (is_not_right && is_not_bottom) {
					_ret += l_triangle_normals[lower_right];
				}

				_ret.normalise();

				return _ret;
			};

			std::function<void(size_t, size_t)> _worker_thread = [&](size_t start, size_t end) {
				Ogre::Vector3 _ret(0, 0, 0);
				for (unsigned int i = start; i < end; i++) {
					/*for (unsigned int j = 0; j < l_indices.size(); j++) {
						if (l_indices[j].a == i || l_indices[j].b == i || l_indices[j].c == i) {
							_ret += l_triangle_normals[j];
						}
					}*/
					_ret = _find_vertex_normal(i);
					_ret.normalise();
					l_vertex_normals[i] = _ret;
				}
			};

			std::vector<__thread_set*> threads;

			for (unsigned int i = 0; i < _thread_count; i++) {
				__thread_set* pthread = new __thread_set;

				if (i == 0) {
					pthread->_start = 0;
					pthread->_end = l_vertex_count / _thread_count;
				}
				else {
					pthread->_start = threads[i - 1]->_end + 1;
					pthread->_end = (l_vertex_count / _thread_count) * (i + 1);
				}

				if (i == _thread_count) {
					pthread->_end = l_vertex_count;
				}

				pthread->_thread = std::thread(_worker_thread, pthread->_start, pthread->_end);
				threads.push_back(pthread);
			}

			for (unsigned int i = 0; i < threads.size(); i++) {
				threads[i]->_thread.join();
				delete threads[i];
				threads[i] = nullptr;
			}

		}

		/*for (unsigned int i = 0; i < l_vertex_normals.size(); i++) {
			Ogre::Vector3 _ret(0, 0, 0);
			for (unsigned int j = 0; j < l_indices.size(); j++) {
				if (l_indices[j].a == i || l_indices[j].b == i || l_indices[j].c == i) {
					_ret = _ret + l_triangle_normals[j];
				}
			}
			_ret.normalise();
			l_vertex_normals[i] = _ret;
		}*/

		Ogre::ManualObject* terrain_object = m_pSceneManager->createManualObject("");

		terrain_object->begin("lambert1", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		for (unsigned int i = 0; i < l_vertex_count; i++) {
			Ogre::Real _x = (Ogre::Real)(i % l_tex->getWidth());
			Ogre::Real _y = (Ogre::Real)(i / l_tex->getWidth());

			terrain_object->position(l_vertices[i]);
			terrain_object->normal(l_vertex_normals[i]);
			terrain_object->colour(Ogre::ColourValue(0.5, 0.5, 0.5));
			terrain_object->textureCoord(_x/(Ogre::Real)l_tex->getWidth(), _y/(Ogre::Real)l_tex->getHeight());
		}

		for (unsigned int i = 0; i < l_indices.size(); i++) {
			terrain_object->index(l_indices[i].a);
			terrain_object->index(l_indices[i].b);
			terrain_object->index(l_indices[i].c);
		}

		terrain_object->end();

		//terrain_object->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState("white.png");
		//terrain_object->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->setLightingEnabled(true);

		ECBody& _ret = createBody();

		_ret.setMesh(terrain_object, Scale);

		chrono::geometry::ChTriangleMeshConnected l_triangle_mesh;

		for (unsigned int i = 0; i < l_indices.size(); i++) {
			l_triangle_mesh.addTriangle(
				chrono::ChVector<>(									// Vertex 0
				(double)l_vertices[l_indices[i].a].x,					// Index a.x
				(double)l_vertices[l_indices[i].a].y,					// Index a.y
				(double)l_vertices[l_indices[i].a].z					// Index a.z
				) * Scale,
				chrono::ChVector<>(									// Vertex 1
				(double)l_vertices[l_indices[i].b].x,					// Index b.x
				(double)l_vertices[l_indices[i].b].y,					// Index b.y
				(double)l_vertices[l_indices[i].b].z					// Index b.z
				) * Scale,
				chrono::ChVector<>(									// Vertex 2
				(double)l_vertices[l_indices[i].c].x,					// Index c.x
				(double)l_vertices[l_indices[i].c].y,					// Index c.y
				(double)l_vertices[l_indices[i].c].z					// Index c.z
				) * Scale
				);
		}

		_ret->GetCollisionModel()->ClearModel();
		_ret->GetCollisionModel()->AddTriangleMesh(l_triangle_mesh, true, false, chrono::ChVector<>(), chrono::QUNIT);
		_ret->GetCollisionModel()->BuildModel();
		_ret->SetCollide(true);
		_ret->SetBodyFixed(true);

		return _ret;
	}

}