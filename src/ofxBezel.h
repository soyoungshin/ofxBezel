#pragma once

#include "ofShader.h"
#include "ofImage.h"
#include "ofTexture.h"
#include "ofFbo.h"
#include "ofAppRunner.h"

class ofxBezel {
	public:
		ofxBezel() {};
		void setup(float rSpacer, float cSpacer);
		void	draw(ofFbo* fbo);
		float	getDisplayHelper();
		void	setDisplayHelper(bool display);
		float	getColumnSpacer();
		void	setColumnSpacer(float val);
		float	getRowSpacer();
		void	setRowSpacer(float val);

	private:
		ofShader shader;
		ofImage	bezelHelper;
		bool	drawBezelHelper;

		float	columnSpacer;
		float	rowSpacer;
};