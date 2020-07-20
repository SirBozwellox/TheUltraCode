#include "main.h"

int stateSize = 64;

graph::graph() {
	addState(state("*", (renderx / 2) - 100, 380));
}

char graph::getNextLetter() {
	for (int i = 1; i < 40; i++) {
		if (!stateList[i].active) {
			return i + 64;
		}
	}
	return '\0';
}

void graph::drawBulbGlow() {
	for (int i = 0; i < 40; i++) {
		if (stateList[i].active) {
			stateList[i].drawGlow();
		}
	}
}

void graph::draw() {
	float x1;
	float x2;
	float y1;
	float y2;
	float dist;
	float midx;
	float midy;
	float rot;
	float tileAmount;

	if (currentState == 0 && finishCounter == -1) {
		if (inputIndex >= 0 && stepCounter <= stepCounterReset * 0.4) {
			if (inputString[inputIndex] == 'a' || inputString[inputIndex] == 'r') {
				stateList[0].lit = true;
			}
		}
	}
				
	for (int i = 0; i < 100; i++) {
		if (edgeList[i].fromState != -1 || edgeList[i].toState != -1) {
			drawEdgeShadow(edgeList[i].fromState, edgeList[i].toState, edgeList[i].type);
		}
	}
	for (int i = 0; i < 40; i++) {
		if (stateList[i].active) {
			stateList[i].drawBack(stateList[i].lit);
		}
	}
	drawStartingEdge(firstEdgeActive);
	for (int i = 0; i < 100; i++) {
		if (edgeList[i].fromState != -1 || edgeList[i].toState != -1) {
			drawEdgeReal(edgeList[i].fromState, edgeList[i].toState, edgeList[i].type);
		}
	}
	
	for (int i = 0; i < 40; i++) {
		if (stateList[i].active) {
			if (!edgeExists('0', i)) {
				if (!(placeEdge == i && placeEdgeType == '0')) {
					placeimagerotatetile(wireRed2, stateList[i].x, stateList[i].y, 128, 128, 1, 1, 0.1, -0.05, stateList[i].rot0, TRUE);
				}
			}
			if (!edgeExists('1', i)) {
				if (!(placeEdge == i && placeEdgeType == '1')) {
					placeimagerotatetile(wireGreen2, stateList[i].x, stateList[i].y, 128, 128, 1, 1, 0.1, -0.05, stateList[i].rot1, TRUE);
				}
			}
			if (i == currentState && finishCounter == -1) {
				if (i > 0) {
					stateList[i].draw(TRUE);
				}
				else {
					if (inputIndex >= 0 && stepCounter <= stepCounterReset * 0.4) {
						stateList[i].draw(TRUE);
					}
					else {
						stateList[i].draw(FALSE);
					}
				}
			}
			else {
				stateList[i].draw(FALSE);
			}
		}
	}
}

void graph::addState(state newState) {
	bool found = FALSE;
	for (int i = 0; i < 40; i++) {
		if (!stateList[i].active && !found) {
			found = TRUE;
			stateList[i] = newState;
			stateList[i].active = TRUE;
		}
	}
}

void graph::addEdge(edge newEdge) {
	if (edgeExists(newEdge.type, newEdge.fromState)) {
		removeState(findEdge(newEdge.type, newEdge.fromState));
	}
	bool found = FALSE;
	for (int i = 0; i < 100; i++) {
		if (edgeList[i].fromState == -1 && edgeList[i].toState == -1 && !found) {
			found = TRUE;
			edgeList[i] = newEdge;
		}
	}
}

void graph::removeState(int i) {
	for (int x = 0; x < 100; x++) {
		if (edgeList[x].fromState == i || edgeList[x].toState == i) {
			removeEdge(x);
		}
	}
	stateList[i] = state();
}

void graph::removeEdge(int i) {
	edgeList[i].fromState = -1;
	edgeList[i].toState = -1;
	edgeList[i].type = '\0';
}

bool graph::edgeExists(char inType, int inFromState) {
	bool ret = FALSE;
	for (int i = 0; i < 100; i++) {
		if (edgeList[i].fromState == inFromState && edgeList[i].type == inType) {
			ret = TRUE;
		}
	}
	return ret;
}

bool graph::edgeExists(char inType, int inFromState, int inToState) {
	bool ret = FALSE;
	for (int i = 0; i < 100; i++) {
		if (edgeList[i].fromState == inFromState && edgeList[i].toState == inToState && edgeList[i].type == inType) {
			ret = TRUE;
		}
	}
	return ret;
}

bool graph::edgeExists(int inFromState, int inToState) {
	bool ret = FALSE;
	for (int i = 0; i < 100; i++) {
		if (edgeList[i].fromState == inFromState && edgeList[i].toState == inToState) {
			ret = TRUE;
		}
	}
	return ret;
}

int graph::findEdge(char inType, int inFromState) {
	int ret = -1;
	for (int i = 0; i < 100; i++) {
		if (edgeList[i].fromState == inFromState && edgeList[i].type == inType) {
			ret = i;
		}
	}
	return ret;
}

void graph::drawEdgeShadow(int fromState, int toState, char type) {
	float x1 = stateList[fromState].x;
	float y1 = stateList[fromState].y;
	float x2 = stateList[toState].x;
	float y2 = stateList[toState].y;
	float offset = 4;
	if (fromState == toState) {
		if (type == '0') {
			glColor4f(0.0, 0.0, 0.0, 0.6);
			placeimagerotatecentre(wireRedLoop1, stateList[fromState].x + offset, stateList[fromState].y + offset, 256, 256, stateList[fromState].rot0, TRUE);
		}
		else {
			glColor4f(0.0, 0.0, 0.0, 0.6);
			placeimagerotatecentre(wireRedLoop1, stateList[fromState].x + offset, stateList[fromState].y + offset, 256, 256, stateList[fromState].rot1, TRUE);
		}
	}
	else {
		float dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		float midx = (x1 + x2) / 2;
		float midy = (y1 + y2) / 2;
		float rot = 0.0f;
		if (y1 - y2 != 0) {
			rot = -atan((x1 - x2) / (y1 - y2)) + (pi / 2);
		}
		else {
			if (x1 < x2) {
				rot = 0.0f;
			}
			else {
				rot = pi;
			}
		}
		if (y1 > y2) {
			rot -= pi;
		}
		float tileAmount = dist / 64.0;
		glColor4f(0.0, 0.0, 0.0, 0.6);
		placeimagerotatetile(wireRedGreen1, midx + offset, midy + offset, dist, 64, tileAmount / 2, 1, 0.0, 0.2, rot, TRUE);
	}
}

void graph::drawEdge(int fromState, int toState, char type) {
	float x1 = stateList[fromState].x;
	float y1 = stateList[fromState].y;
	float x2 = stateList[toState].x;
	float y2 = stateList[toState].y;
	if (fromState == toState) {
		if (type == '0') {
			glColor4f(1.0, 1.0, 1.0, 1.0);
			placeimagerotatecentre(wireRedLoop1, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot0, TRUE);
		}
		else {
			glColor4f(1.0, 1.0, 1.0, 1.0);
			placeimagerotatecentre(wireGreenLoop1, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot1, TRUE);
		}
	}
	else {
		float dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		float midx = (x1 + x2) / 2;
		float midy = (y1 + y2) / 2;
		float rot = 0.0f;
		if (y1 - y2 != 0) {
			rot = -atan((x1 - x2) / (y1 - y2)) + (pi / 2);
		}
		else {
			if (x1 < x2) {
				rot = 0.0f;
			}
			else {
				rot = pi;
			}
		}
		if (y1 > y2) {
			rot -= pi;
		}
		float tileAmount = dist / 64.0;
		glColor4f(1.0, 1.0, 1.0, 1.0);
		if (type == '1') {
			stateList[fromState].rot1 = rot + (pi / 2);
			if (edgeExists('0', fromState, toState)) {
				placeimagerotatetile(wireRedGreen1, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.2, rot, TRUE);
			}
			else {
				placeimagerotatetile(wireGreen1, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
			}
		}
		else {
			stateList[fromState].rot0 = rot + (pi / 2);
			if (edgeExists('1', fromState, toState)) {
				placeimagerotatetile(wireRedGreen1, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.2, rot, TRUE);
			}
			else {
				placeimagerotatetile(wireRed1, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
			}
		}
	}
	stateList[toState].draw(FALSE);
}

float shadeOffset = -0.2;

void graph::drawEdgeReal(int fromState, int toState, char type) {
	float x1 = stateList[fromState].x;
	float y1 = stateList[fromState].y;
	float x2 = stateList[toState].x;
	float y2 = stateList[toState].y;
	if (fromState == toState) {
		if (type == '0') {
			glColor4f(1.0, 1.0, 1.0, 1.0);
			placeimagerotatecentre(wireRedLoop1, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot0, TRUE);
			float tempRot = stateList[fromState].rot0 + 0.8 - pi;
			float sideRot = stateList[fromState].rot0 + 0.8 - (pi * 0.5);
			if (tempRot < -pi) {
				tempRot += 2 * pi;
			}
			if (tempRot > pi) {
				tempRot -= 2 * pi;
			}
			if (sideRot < -pi) {
				sideRot += 2 * pi;
			}
			if (sideRot > pi) {
				sideRot -= 2 * pi;
			}
			float shade = abs(tempRot / pi);
			glColor4f(1.0, 1.0, 1.0, shade + shadeOffset);
			placeimagerotatecentre(wireLoopShadeBottom, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot0, TRUE);
			glColor4f(1.0, 1.0, 1.0, 1.0 - shade + shadeOffset);
			placeimagerotatecentre(wireLoopShadeTop, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot0, TRUE);
			shade = abs(sideRot / pi);
			glColor4f(1.0, 1.0, 1.0, shade + shadeOffset);
			placeimagerotatecentre(wireLoopShadeLeft, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot0, TRUE);
			glColor4f(1.0, 1.0, 1.0, 1.0 - shade + shadeOffset);
			placeimagerotatecentre(wireLoopShadeRight, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot0, TRUE);
		}
		else {
			glColor4f(1.0, 1.0, 1.0, 1.0);
			placeimagerotatecentre(wireGreenLoop1, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot1, TRUE);
			float tempRot = stateList[fromState].rot1 + 0.8 - pi;
			float sideRot = stateList[fromState].rot1 + 0.8 - (pi * 0.5);
			if (tempRot > pi) {
				tempRot -= 2 * pi;
			}
			if (tempRot < -pi) {
				tempRot += 2 * pi;
			}
			if (sideRot < -pi) {
				sideRot += 2 * pi;
			}
			if (sideRot > pi) {
				sideRot -= 2 * pi;
			}
//			printf("%f, %f\n", tempRot, 0.0f);
			float shade = abs(tempRot / pi);
			glColor4f(1.0, 1.0, 1.0, shade + shadeOffset);
			placeimagerotatecentre(wireLoopShadeBottom, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot1, TRUE);
			glColor4f(1.0, 1.0, 1.0, 1.0 - shade + shadeOffset);
			placeimagerotatecentre(wireLoopShadeTop, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot1, TRUE);
			shade = abs(sideRot / pi);
			glColor4f(1.0, 1.0, 1.0, shade + shadeOffset);
			placeimagerotatecentre(wireLoopShadeLeft, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot1, TRUE);
			glColor4f(1.0, 1.0, 1.0, 1.0 - shade + shadeOffset);
			placeimagerotatecentre(wireLoopShadeRight, stateList[fromState].x, stateList[fromState].y, 256, 256, stateList[fromState].rot1, TRUE);
		}
	}
	else {
		float dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		float midx = (x1 + x2) / 2;
		float midy = (y1 + y2) / 2;
		float rot = 0.0f;
		if (y1 - y2 != 0) {
			rot = -atan((x1 - x2) / (y1 - y2)) + (pi / 2);
		}
		else {
			if (x1 < x2) {
				rot = 0.0f;
			}
			else {
				rot = pi;
			}
		}
		if (y1 > y2) {
			rot -= pi;
		}
		float tileAmount = dist / 64.0;
		glColor4f(1.0, 1.0, 1.0, 1.0);
		if (type == '1') {
			stateList[fromState].rot1 = rot + (pi / 2);
			if (edgeExists('0', fromState, toState)) {
				placeimagerotatetile(wireRedGreen1, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.2, rot, TRUE);
			}
			else {
				placeimagerotatetile(wireGreen1, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
			}
		}
		else {
			stateList[fromState].rot0 = rot + (pi / 2);
			if (edgeExists('1', fromState, toState)) {
				placeimagerotatetile(wireRedGreen1, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.2, rot, TRUE);
			}
			else {
				placeimagerotatetile(wireRed1, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
			}
		}
		float tempRot = rot + 0.8 - pi;
		if (tempRot < -pi) {
			tempRot += 2 * pi;
		}
		float shade = abs(tempRot / pi);
		glColor4f(1.0, 1.0, 1.0, shade + shadeOffset);
		placeimagerotatetile(wireShadeBottom, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
		glColor4f(1.0, 1.0, 1.0, 1.0 - shade + shadeOffset);
		placeimagerotatetile(wireShadeTop, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
	stateList[toState].draw(FALSE);
}

void graph::drawStartingEdge(bool active) {
	float x1 = 142;
	float y1 = 380;
	float x2 = stateList[0].x;
	float y2 = stateList[0].y;
	float dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	float midx = (x1 + x2) / 2;
	float midy = (y1 + y2) / 2;
	float rot = 0.0f;
	float dx = (x2 - x1);
	float dy = (y2 - y1);
	float distance = ((float)stepCounter - (float)(stepCounterReset * 0.4)) / ((float)stepCounterReset * 0.6);

	float glowAlpha = ((float)stepCounter - ((float)stepCounterReset * 0.4)) / ((float)stepCounterReset * 0.6);
	glowAlpha = sin(glowAlpha * pi);

	if (y1 - y2 != 0) {
		rot = -atan((x1 - x2) / (y1 - y2)) + (pi / 2);
	}
	else {
		if (x1 < x2) {
			rot = 0.0f;
		}
		else {
			rot = pi;
		}
	}
	if (y1 > y2) {
		rot -= pi;
	}
	float tileAmount = dist / 64.0;
	glColor4f(1.0, 1.0, 1.0, 1.0);
	placeimagerotatetile(wireBlack1, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.0, rot, TRUE);
	if (active && stepCounter > stepCounterReset * 0.4 && inputIndex >= -1) {
		glColor4f(1.0, 1.0, 1.0, 0.4);
		placeimagerotatetile(wireGlow1, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.0, rot, TRUE);
		glColor4f(1.0, 1.0, 1.0, glowAlpha);
		placeimagerotatetile(glow1, x2 - (dx * distance), y2 - (dy * distance), 64, 128, 1.0, 1.0, 0.0, -0.1, rot, TRUE);
	}
	float tempRot = rot + 0.8 - pi;
	if (tempRot < -pi) {
		tempRot += 2 * pi;
	}
	float shade = abs(tempRot / pi);
	glColor4f(1.0, 1.0, 1.0, shade + shadeOffset - 0.4);
	placeimagerotatetile(wireShadeBottom, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.0, rot, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0 - shade + shadeOffset - 0.3);
	placeimagerotatetile(wireShadeTop, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.0, rot, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

void graph::drawEdgeGlow(int fromState, int toState, char type, float distance) {
	float x1 = stateList[fromState].x;
	float y1 = stateList[fromState].y;
	float x2 = stateList[toState].x;
	float y2 = stateList[toState].y;
	float glowAlpha = ((float)stepCounter - ((float)stepCounterReset * 0.4)) / ((float)stepCounterReset * 0.6);
	glowAlpha = sin(glowAlpha * pi);
	if (fromState == toState) {
		glColor4f(1.0, 1.0, 1.0, 0.3);
		if (type == '1') {
			placeimagerotatecentre(wireGlow2, x1, y1, 256, 256, stateList[fromState].rot1, TRUE);
			glColor4f(1.0, 1.0, 1.0, glowAlpha);
			y2 = -32;
			x2 = 0;
			zrotate(x2, y2, stateList[fromState].rot1);
			x1 += x2;
			y1 += y2;
			placeimagerotatecentre(glow2, x1, y1, 64, 128, (distance * -pi * 2.0) + stateList[fromState].rot1 + pi, TRUE);
		}
		else {
			placeimagerotatecentre(wireGlow2, x1, y1, 256, 256, stateList[fromState].rot0, TRUE);
			glColor4f(1.0, 1.0, 1.0, glowAlpha);
			y2 = -32;
			x2 = 0;
			zrotate(x2, y2, stateList[fromState].rot0);
			x1 += x2;
			y1 += y2;
			placeimagerotatecentre(glow2, x1, y1, 64, 128, (distance * -pi * 2.0) + stateList[fromState].rot0 + pi, TRUE);
		}
	}
	else {
		float dx = (x2 - x1);
		float dy = (y2 - y1);
		float dist = sqrt(pow(dx, 2) + pow(dy, 2));
		float midx = (x1 + x2) / 2;
		float midy = (y1 + y2) / 2;
		float rot = 0.0f;
		if (y1 - y2 != 0) {
			rot = -atan((x1 - x2) / (y1 - y2)) + (pi / 2);
		}
		else {
			if (x1 < x2) {
				rot = 0.0f;
			}
			else {
				rot = pi;
			}
		}
		if (y1 > y2) {
			rot -= pi;
		}
		float tileAmount = dist / 64.0;
		glColor4f(1.0, 1.0, 1.0, 0.3);
		placeimagerotatetile(wireGlow1, midx, midy, dist, 64, tileAmount / 2, 1, 0.0, 0.2, rot, TRUE);
		glColor4f(1.0, 1.0, 1.0, glowAlpha);
		placeimagerotatecentre(glow1, x2 - (dx * distance), y2 - (dy * distance), 64, 128, rot, TRUE);
	}
	stateList[fromState].draw(FALSE);
	stateList[toState].draw(FALSE);
}

void graph::drawEdgeSpark(int fromState, int toState, int type) {
	float x1 = stateList[fromState].x;
	float y1 = stateList[fromState].y;
	float x2 = stateList[toState].x;
	float y2 = stateList[toState].y;
	glColor4f(1.0, 1.0, 1.0, 0.5);
	if (fromState == toState) {
	}
	else {
		float dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		float midx = (x1 + x2) / 2;
		float midy = (y1 + y2) / 2;
		float rot = 0.0f;
		if (y1 - y2 != 0) {
			rot = -atan((x1 - x2) / (y1 - y2)) + (pi / 2);
		}
		else {
			if (x1 < x2) {
				rot = 0.0f;
			}
			else {
				rot = pi;
			}
		}
		if (y1 > y2) {
			rot -= pi;
		}
		float tileAmount = dist / 64.0;
		int image = spark2a;
		if (type == 1) {
			image = spark2b;
		}
		else if (type == 2) {
			image = spark2c;
		}
		else if (type == 3) {
			image = spark2d;
		}
		placeimagerotatetile(image, midx, midy, dist, 64, tileAmount / 2, 1.0, 0.0, 0.15, rot, TRUE);
	}
	glColor4f(1.0, 1.0, 1.0, 1.0);
	stateList[fromState].draw(FALSE);
	stateList[toState].draw(FALSE);
}

int graph::getStateNum() {
	int count = 0;
	for (int i = 0; i < 100; i++) {
		if (stateList[i].active) {
			count += 1;
		}
	}
	return count;
}

state::state() {
	strcpy_s(name, 20, "\0");
	x = 0;
	y = 0;
	active = FALSE;
	rot0 = pi * 1.5;
	rot1 = pi * 0.5;
	final = FALSE;
}

state::state(char inName[20], float inx, float iny) {
	strcpy_s(name, 20, inName);
	x = inx;
	y = iny;
	active = TRUE;
	rot0 = pi * 1.5;
	rot1 = pi * 0.5;
	final = FALSE;
}

void state::drawShadow() {
	glColor4f(0.0, 0.0, 0.0, 0.6);
	placeimageeasy(state1, x + 4 - (stateSize), y + 4 - (stateSize), stateSize * 2, stateSize * 2, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

void state::drawGlow() {
	if (lit) {
		glColor4f(1.0, 1.0, 1.0, 0.5);
		if (strcmp(name, "*") == 0) {
			glColor4f(0.0, 0.9, 1.0, 0.5);
		}
		if (final) {
			glColor4f(0.0, 1.0, 0.2, 0.5);
		}
		placeimageeasy(glow3, x + 4 - (stateSize * 2), y + 4 - (stateSize * 2), stateSize * 4, stateSize * 4, TRUE);
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
}

void state::drawBack(bool enabled) {
	glColor4f(1.0, 1.0, 1.0, 1.0);
	if (enabled) {
		placeimageeasy(stateBackOn, x - (stateSize), y - (stateSize), stateSize * 2, stateSize * 2, TRUE);
	}
	else {
		placeimageeasy(stateBack, x - (stateSize), y - (stateSize), stateSize * 2, stateSize * 2, TRUE);
	}
}

void state::draw(bool enabled) {
	glColor4f(1.0, 1.0, 1.0, 1.0);
	if (strcmp(name, "*") == 0) {
		glColor4f(0.0, 0.9, 1.0, 1.0);
	}
	if (final) {
		glColor4f(0.0, 1.0, 0.2, 1.0);
	}
	if (enabled) {
		placeimageeasy(state1on, x - (stateSize), y - (stateSize), stateSize * 2, stateSize * 2, TRUE);
	}
	else {
		placeimageeasy(state1, x - (stateSize), y - (stateSize), stateSize * 2, stateSize * 2, TRUE);
	}
	glColor3f(0.0, 0.0, 0.0);
	drawtext_centre(name, x - 2, y, stateSize / 2, stateSize / 2);
	glColor3f(1.0, 1.0, 1.0);
}

bool state::mouseOver() {
	float dist = sqrt(pow(x - mousex, 2) + pow(y - mousey, 2));
	if (dist < stateSize / 2) {
		return true;
	}
	else {
		return false;
	}
}

float state::getMouseDist() {
	float dist = sqrt(pow(x - mousex, 2) + pow(y - mousey, 2));
	return dist;
}

float state::getMouseAngle() {
	float midx = (x + mousex) / 2;
	float midy = (y + mousey) / 2;
	float rot = 0.0f;
	if (y - mousey != 0) {
		rot = -atan((x - mousex) / (y - mousey)) + (pi / 2);
	}
	else {
		if (x < mousex) {
			rot = 0.0f;
		}
		else {
			rot = pi;
		}
	}
	if (y > mousey) {
		rot -= pi;
	}
	rot += pi / 2;
	if (rot < 0.0) {
		rot += 2*pi;
	}
	return rot;
}

edge::edge() {
	type = '\0';
	fromState = -1;
	toState = -1;
}

edge::edge(char inType, int inFromState, int inToState) {
	type = inType;
	fromState = inFromState;
	toState = inToState;
}