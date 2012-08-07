#include "ofxBezel.h"

void ofxBezel::setup(float rSpacer, float cSpacer, int numRows, int numColumns) {
	if(numRows < 0) numRows = 1;
	if(numColumns < 0) numColumns = 1;

	stringstream fragmentShader;

	fragmentShader << 
		"#version 130\n \
		#extension GL_ARB_texture_rectangle : enable\n \
		\
		uniform sampler2DRect tex0;\
		\
		uniform float columnSpacer;\
		uniform float rowSpacer;\
		\
		uniform float texWidth;\
		uniform float texHeight;\
		void main()\
		{\
		vec2 st	= gl_TexCoord[0].st;\
		\
		float texWidthChunk = texWidth / " << numColumns << ";\
		\
		float texHeightChunk = texHeight / " << numRows << ";\
		\
		float horzScalar = 1 - columnSpacer * " << numColumns - 1 << " / texWidth; \
		int column = int(st[0] / texWidthChunk); \
		st[0] = st[0] * horzScalar + column * columnSpacer; \
		\
		int row = int(st[1] / texHeightChunk); \
		float vertScalar = 1 - rowSpacer * " << numRows - 1 << " / texHeight;\
		st[1] = st[1] * vertScalar + row * rowSpacer;\
		\
		gl_FragColor = texture(tex0 , st);\
		}";

	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader.str());
	shader.linkProgram();

	bezelHelper.loadImage("bezelHelper.png");
	drawBezelHelper = false;

	// the number of pixels to lop off between each pair of displays
	columnSpacer = cSpacer;
	rowSpacer = rSpacer;
}

void ofxBezel::draw(ofFbo* fbo) {
	shader.begin();

	shader.setUniform1f("columnSpacer", columnSpacer);
	shader.setUniform1f("rowSpacer", rowSpacer);
	shader.setUniform1f("texWidth", fbo->getWidth());
	shader.setUniform1f("texHeight", fbo->getHeight());

	if(drawBezelHelper) {
		bezelHelper.draw(0, 0, ofGetWidth(), ofGetHeight());
	} else {
		fbo->draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	shader.end();
}

float ofxBezel::getDisplayHelper() {
	return drawBezelHelper;
}

void ofxBezel::setDisplayHelper(bool display) {
	drawBezelHelper = display;
}

float ofxBezel::getColumnSpacer() {
	return columnSpacer;
}

void ofxBezel::setColumnSpacer(float val) {
	if(val >= 0 && val < ofGetWidth()) {
		columnSpacer = val;
	}
}

float ofxBezel::getRowSpacer() {
	return rowSpacer;
}

void ofxBezel::setRowSpacer(float val) {
	if(val >= 0 && val < ofGetHeight()) {
		rowSpacer = val;
	}
}
