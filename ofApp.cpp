#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();

	this->icoSphere.setRadius(300);
	this->icoSphere.setResolution(3);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();

	ofRotateY(ofGetFrameNum() / 4.f);

	ofColor sphere_color;
	sphere_color.setHsb((ofGetFrameNum() / 4) % 255, 255, 255);

	vector<ofMeshFace> triangles = icoSphere.getMesh().getUniqueFaces();

	for (int i = 0; i < triangles.size(); i++) {

		ofVec3f avg = (triangles[i].getVertex(0) + triangles[i].getVertex(1) + triangles[i].getVertex(2)) / 3;
		float noise_value = ofMap(ofNoise(avg.x * 0.005, avg.y * 0.005, avg.z * 0.005, ofGetFrameNum() * 0.005), 0, 1, 0, 1.5);
		if (noise_value < 0.8) { noise_value = 0.8; }

		ofMesh mesh;

		ofVec3f point1 = triangles[i].getVertex(0) * noise_value;
		ofVec3f point2 = triangles[i].getVertex(1) * noise_value;
		ofVec3f point3 = triangles[i].getVertex(2) * noise_value;

		mesh.addVertex(point1);
		mesh.addVertex(point2);
		mesh.addVertex(point3);

		ofSetColor(sphere_color);
		mesh.draw();

		ofSetColor(255);
		mesh.drawWireframe();

		ofLine(ofVec3f(), avg * noise_value);

	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}