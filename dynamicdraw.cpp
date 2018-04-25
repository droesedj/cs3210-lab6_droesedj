/**
 *	LAB WEEK 6: DRAWING EVENTS
 *	CS3210
 *	@author Dennis Droese
 *	@date April 18, 2018
 *  @file dynamicdraw.h
 */

#include "dynamicdraw.h"
#include "math.h"

/// Helper methods
int getDistance(int x0, int y0, int x1, int y1);

//=================================================

dynamicdraw::dynamicdraw() {
	color = GraphicsContext::WHITE;
	theImage = new image();
	drawingMode = DRAWMODE_POINT;
	state = STATE_NEWTRI;
	isDragging = false;
	x0 = 0;
	x1 = 0;
	y0 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

dynamicdraw::~dynamicdraw() {
	delete theImage;
}

void dynamicdraw::paint(GraphicsContext* gc) {
	// refresh the image.
	theImage->draw(gc);
}

void dynamicdraw::mouseButtonDown(GraphicsContext* gc, unsigned int button,
		int x, int y) {
	if (drawingMode == DRAWMODE_LINE) {
		x0 = x;
		y0 = y;
		x1 = x;
		y1 = y;
		gc->setMode(GraphicsContext::MODE_XOR);
		gc->drawLine(x0, y0, x1, y1);
		isDragging = true;

	} else if (drawingMode == DRAWMODE_POINT) {
		point* myPoint = new point(x, y, 0, color);
		myPoint->draw(gc);
		theImage->add(myPoint);

	} else if (drawingMode == DRAWMODE_CIRCLE) {
		x0 = x;
		y0 = y;
		x1 = x;
		y1 = y;
		gc->setMode(GraphicsContext::MODE_XOR);
		gc->drawCircle(x0, y0, 1);
		isDragging = true;

	} else if (drawingMode == DRAWMODE_TRI) {
		if (state == STATE_NEWTRI) {
			// drawing the first line
			x0 = x;
			y0 = y;
			x1 = x;
			y1 = y;
			gc->setMode(GraphicsContext::MODE_XOR);
			gc->drawLine(x0, y0, x1, y1);
			isDragging = true;

		} else if (state == STATE_ENDTRI) {
			// drawing the third point connected to the previous two.
			x2 = x;
			y2 = y;
			gc->drawLine(x0, y0, x2, y2);
			gc->drawLine(x1, y1, x2, y2);
			isDragging = true;
		}
	}
}

void dynamicdraw::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x,
		int y) {
	if (drawingMode == DRAWMODE_LINE) {
		if (isDragging) {
			gc->drawLine(x0, y0, x1, y1);
			x1 = x;
			y1 = y;
			gc->setMode(GraphicsContext::MODE_NORMAL);

			line* myLine = new line(x0, y0, 0, x1, y1, 0, color);
			myLine->draw(gc);
			// Add the line to the image and draw it.
			theImage->add(myLine);
			isDragging = false;
		}
	} else if (drawingMode == DRAWMODE_POINT) {
		if (isDragging) {
			// nothing to do here, may as well make sure it's not dragging.
			isDragging = false;
		}
	} else if (drawingMode == DRAWMODE_CIRCLE) {
		if (isDragging) {
			gc->drawCircle(x0, y0, getDistance(x0, y0, x1, y1));
			x1 = x;
			y1 = y;
			gc->setMode(GraphicsContext::MODE_NORMAL);

			circle* myCircle = new circle(x0, y0, 0,
					getDistance(x0, y0, x1, y1), color);
			myCircle->draw(gc);
			theImage->add(myCircle);
			isDragging = false;
		}
	} else if (drawingMode == DRAWMODE_TRI) {
		if (isDragging) {
			if (state == STATE_NEWTRI) {
				gc->drawLine(x0, y0, x1, y1);
				x1 = x;
				y1 = y;
				// Draw the first line of the tri. do not add to image yet.
				gc->drawLine(x0, y0, x1, y1);
				isDragging = false;
				state = STATE_ENDTRI;
			} else if (state == STATE_ENDTRI) {
				gc->drawLine(x0, y0, x2, y2);
				gc->drawLine(x1, y1, x2, y2);
				gc->setMode(GraphicsContext::MODE_NORMAL);

				triangle* myTri = new triangle(x0, y0, 0, x1, y1, 0, x, y, 0,
						color);
				myTri->draw(gc);
				theImage->add(myTri);
				isDragging = false;
				state = STATE_NEWTRI;
			}
		}
	}
}

void dynamicdraw::mouseMove(GraphicsContext* gc, int x, int y) {
	if (drawingMode == DRAWMODE_LINE) {
		if (isDragging) {
			gc->drawLine(x0, y0, x1, y1);
			x1 = x;
			y1 = y;
			gc->drawLine(x0, y0, x1, y1);
		}
	} else if (drawingMode == DRAWMODE_CIRCLE) {
		if (isDragging) {
			gc->drawCircle(x0, y0, getDistance(x0, y0, x1, y1));
			x1 = x;
			y1 = y;
			gc->drawCircle(x0, y0, getDistance(x0, y0, x1, y1));
		}
	} else if (drawingMode == DRAWMODE_TRI) {
		if (isDragging) {
			if (state == STATE_NEWTRI) {
				gc->drawLine(x0, y0, x1, y1);
				x1 = x;
				y1 = y;
				gc->drawLine(x0, y0, x1, y1);
			} else if (state == STATE_ENDTRI) {
				gc->drawLine(x0, y0, x2, y2);
				gc->drawLine(x1, y1, x2, y2);
				x2 = x;
				y2 = y;
				gc->drawLine(x0, y0, x2, y2);
				gc->drawLine(x1, y1, x2, y2);
			}
		}
	}
}

void dynamicdraw::keyUp(GraphicsContext* gc, unsigned int keycode) {
	if (!isDragging && state != STATE_ENDTRI) {
		// not allowed to change tools while dragging or completing a triangle.
		if (keycode == 'p') {
			drawingMode = DRAWMODE_POINT;
			return;
		} else if (keycode == 'l') {
			drawingMode = DRAWMODE_LINE;
			return;
		} else if (keycode == 'c') {
			drawingMode = DRAWMODE_CIRCLE;
			return;
		} else if (keycode == 't') {
			drawingMode = DRAWMODE_TRI;
			return;
		}
		// Color selection
		if (keycode == '1') {
			color = GraphicsContext::RED;
		} else if (keycode == '2') {
			color = GraphicsContext::YELLOW;
		} else if (keycode == '3') {
			color = GraphicsContext::GREEN;
		} else if (keycode == '4') {
			color = GraphicsContext::BLUE;
		} else if (keycode == '5') {
			color = GraphicsContext::CYAN;
		} else if (keycode == '6') {
			color = GraphicsContext::MAGENTA;
		} else if (keycode == '7') {
			color = GraphicsContext::WHITE;
		} else if (keycode == '8') {
			color = GraphicsContext::GRAY;
		} else if (keycode == '9') {
			color = GraphicsContext::BLACK;
		}

		gc->setColor(color);
	}
}

/// "Helper" methods

/**
 * Gets the distance between two 2D points.
 * @param x0 first x-coordinate
 * @param y0 first y-coordinate
 * @param x1 second x-coordinate
 * @param y1 second y-coordinate
 * @return distance in pixels.
 */
int getDistance(int x0, int y0, int x1, int y1) {
	int x;
	int y;
	if (x0 > x1) {
		x = x0 - x1;
	} else {
		x = x1 - x0;
	}
	if (y0 > y1) {
		y = y0 - y1;
	} else {
		y = y1 - y0;
	}
	return (sqrt((x * x) + (y * y)));
}
