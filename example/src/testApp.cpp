#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	fbo.allocate(ofGetWidth(), ofGetHeight());
	// amount of pixels to lop off of video between screens, 
	// and number screens in each column/row
	bezel.setup(30.0f, 30.0f, 3, 2);
	player.loadMovie("fingers.mov");
	player.play();
}

//--------------------------------------------------------------
void testApp::update(){
	player.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	fbo.begin();
	player.draw(0, 0, ofGetWidth(), ofGetHeight());
	fbo.end();
	bezel.draw(&fbo);

	// draw some debug info
	ofEnableAlphaBlending();
	ofSetColor(0,0,0,128);
	ofRect(0,0,400,90);
	ofDisableAlphaBlending();

	ofSetHexColor(0xffffff);
	stringstream toDraw;
	toDraw <<	"press up/down arrows to adjust column spacing" << endl <<
				"press left/right arrow to adjust row spacing" << endl << 
				endl <<
				"column spacing: " << bezel.getColumnSpacer() << " pixels" << endl <<
				"row spacing   : " << bezel.getRowSpacer() << " pixels" << endl;  
    ofDrawBitmapString(toDraw.str(), 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	// adjust bezel amount
	switch(key) {
		case OF_KEY_UP:
			bezel.setColumnSpacer(bezel.getColumnSpacer() + 1);
			break;
		case OF_KEY_DOWN:
			bezel.setColumnSpacer(bezel.getColumnSpacer() - 1);
			break;
		case OF_KEY_LEFT:
			bezel.setRowSpacer(bezel.getRowSpacer() + 1);
			break;
		case OF_KEY_RIGHT:
			bezel.setRowSpacer(bezel.getRowSpacer() - 1);
			break;
		case OF_KEY_RETURN:
			bezel.setDisplayHelper(!bezel.getDisplayHelper());
		default:
			break;
	}	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}