#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 4);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());

	for (auto& triangle : this->triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		this->location_list.push_back(avg);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	
	this->mesh_list.clear();

	for (int x = -450; x <= 450; x += 900) {

		for (int y = -600; y <= 600; y += 600) {

			ofMesh mesh;

			ofColor mesh_color = ofColor(255);
			ofColor frame_color = ofColor(0);

			int radius = 230;
			for (int i = 0; i < this->location_list.size(); i++) {

				glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;

				vector<glm::vec3> vertices;
				vertices.push_back(this->triangle_list[i].getVertex(0));
				vertices.push_back(this->triangle_list[i].getVertex(1));
				vertices.push_back(this->triangle_list[i].getVertex(2));

				for (auto& vertex : vertices) {

					auto tmp_radius = ofMap(ofNoise(glm::vec4(vertex * 0.005 + glm::vec3(x, y, 0), ofGetFrameNum() * 0.005)), 0, 1, radius - 66, radius + 65);
					vertex = glm::normalize(vertex) * tmp_radius + glm::vec3(x, y, 0);
				}

				mesh.addVertices(vertices);
				mesh.addTriangle(mesh.getNumVertices() - 1, mesh.getNumVertices() - 2, mesh.getNumVertices() - 3);
			}

			this->mesh_list.push_back(mesh);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto& mesh : this->mesh_list) {

		ofSetColor(255);
		mesh.drawFaces();

		ofSetColor(39);
		mesh.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}