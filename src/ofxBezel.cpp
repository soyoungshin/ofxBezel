#include "ofxBezel.h"

void ofxBezel::setup(float cSpacer, float rSpacer) {
	//shader.load(vertShaderPath, fragShaderPath);
	string fragmentShader = 
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
		float halfTexWidth = texWidth / 2;\
		float thirdTexHeight = texHeight / 3;\
		\
		float horzScalar = 1 - columnSpacer / texWidth;\
		if(st[0] < halfTexWidth) {\
			st[0] = st[0] * horzScalar;\
		} else {\
			st[0] = st[0] * horzScalar + columnSpacer;\
		}\
		\
		float vertScalar = 1 - rowSpacer * 2 / texHeight;\
		\
		if(st[1] < thirdTexHeight) {\
			st[1] = st[1] * vertScalar;\
		} else if(st[1] < thirdTexHeight * 2) {\
			st[1] = st[1] * vertScalar + rowSpacer;\
		} else {\
			st[1] = st[1] * vertScalar + rowSpacer * 2;\
		}\
		\
		gl_FragColor = texture(tex0 , st);\
		}";

	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
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
