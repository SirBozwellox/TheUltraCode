#include "main.h"

button::button()
{
	active = FALSE;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	normalTex = blank;
	hoverTex = blank;
	clickTex = blank;
	hover = false;
	click = false;
}

button::button(char* inname, int inx, int iny, int inwidth, int inheight, int innormalTex, int inhoverTex, int inclickTex)
{
	strcpy_s(name, 40, inname);
	active = TRUE;
	x = inx;
	y = iny;
	width = inwidth;
	height = inheight;
	normalTex = innormalTex;
	hoverTex = inhoverTex;
	clickTex = inclickTex;
	hover = FALSE;
	click = FALSE;
}

void button::man()
{
	hover = FALSE;
	click = FALSE;
	if (mousex >= x && mousex <= x + width)
	{
		if (mousey >= y && mousey <= y + width)
		{
			hover = TRUE;
			if (leftclick_flag)
			{
				click = TRUE;
			}
		}
	}
}

void button::draw()
{
	if (hover == TRUE)
	{
		if (click == TRUE)
		{
			placeimageeasy(clickTex, x, y, width, height, TRUE);
		}
		else
		{
			placeimageeasy(hoverTex, x, y, width, height, TRUE);
		}
	}
	else
	{
		if (click == TRUE)
		{
			placeimageeasy(clickTex, x, y, width, height, TRUE);
		}
		else {
			placeimageeasy(normalTex, x, y, width, height, TRUE);
		}
	}
}

bool button::compare(button inButton)
{
	bool retval = TRUE;
	if (x != inButton.x) { retval == FALSE; }
	if (y != inButton.y) { retval == FALSE; }
	if (width != inButton.width) { retval == FALSE; }
	if (height != inButton.height) { retval == FALSE; }
	return retval;
}

bool button::mouseOver()
{
	bool retval = FALSE;
	if (mousex >= x && mousex <= x + width && mousex >= 0 && mousex <= renderx)
	{
		if (mousey >= y && mousey <= y + height && mousey >= 0 && mousey <= rendery)
		{
			retval = TRUE;
		}
	}
	return retval;
}

slider::slider()
{
	active = FALSE;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	front = blank;
	back = blank;
	click = FALSE;
	position = 0.0;
	orientation = 0;
}

slider::slider(char* inname, int inx, int iny, int inwidth, int inheight, int inback, int infront, int inorientation)
{
	strcpy_s(name, 40, inname);
	active = TRUE;
	click = FALSE;
	x = inx;
	y = iny;
	width = inwidth;
	height = inheight;
	front = infront;
	back = inback;
	position = 0.5;
	orientation = inorientation;
}

void slider::draw() {
	if (orientation == 0) {
		placeimagerotatecentre(back, x + (width / 2), y + (height / 2), width, height, 0.0, TRUE);
		glColor4f(0.0, 0.0, 0.0, 0.5);
		placeimagerotatecentre(front, x + (width / 2) - (height / 2) + (position * width) + 4, y + (height / 2) + 4, width, height, 0.0, TRUE);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		placeimagerotatecentre(front, x + (width / 2) - (height / 2) + (position * width), y + (height / 2), width, height, 0.0, TRUE);
	}
	else {
		placeimagerotatecentre(back, x + (height / 2), y + (width / 2), width, height, pi * 0.5, TRUE);
		glColor4f(0.0, 0.0, 0.0, 0.5);
		placeimagerotatecentre(front, x + (height / 2) + 4, y + (width / 2) - (height / 2) + ((1.0 - position) * width) + 4, width, height, pi * 0.5, TRUE);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		placeimagerotatecentre(front, x + (height / 2), y + (width / 2) - (height / 2) + ((1.0 - position) * width), width, height, pi * 0.5, TRUE);
	}
}

bool slider::mouseOver() {
	bool retval = FALSE;
	if (orientation == 0) {
		if (mousex > x - (height / 2) && mousex < x + width + (height / 2)) {
			if (mousey > y && mousey < y + height) {
				retval = TRUE;
			}
		}
	}
	else {
		if (mousey > y - (height / 2) && mousey < y + width + (height / 2)) {
			if (mousex > x && mousex < x + height) {
				retval = TRUE;
			}
		}
	}
	return retval;
}

void slider::setPosition(float inpos) {
	position = inpos;
	if (position < 0.0) {
		position = 0.0;
	}
	if (position > 1.0) {
		position = 1.0;
	}
}

void slider::calcPosition() {
	if (orientation == 0) {
		float xval = mousex - x;
		float p = xval / width;
		setPosition(p);
	}
	else {
		float yval = mousey - y;
		float p = 1.0 - (yval / width);
		setPosition(p);
	}
}

textButton::textButton()
{
	active = FALSE;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	normalTex = blank;
	hoverTex = blank;
	clickTex = blank;
	hover = false;
	click = false;
}

textButton::textButton(char* inname, char* intext, int insize, int inx, int iny, int inwidth, int inheight, int innormalTex, int inhoverTex, int inclickTex)
{
	strcpy_s(name, 40, inname);
	strcpy_s(text, 40, intext);
	fontsize = insize;
	active = TRUE;
	x = inx;
	y = iny;
	width = inwidth;
	height = inheight;
	normalTex = innormalTex;
	hoverTex = inhoverTex;
	clickTex = inclickTex;
	hover = FALSE;
	click = FALSE;
}

void textButton::man()
{
	hover = FALSE;
	click = FALSE;
	if (mousex >= x && mousex <= x + width)
	{
		if (mousey >= y && mousey <= y + width)
		{
			hover = TRUE;
			if (leftclick_flag)
			{
				click = TRUE;
			}
		}
	}
}

void textButton::draw()
{
	if (hover == TRUE)
	{
		if (click == TRUE)
		{
			placeimageeasy(clickTex, x, y, width, height, TRUE);
		}
		else
		{
			placeimageeasy(hoverTex, x, y, width, height, TRUE);
		}
	}
	else
	{
		placeimageeasy(normalTex, x, y, width, height, TRUE);
	}
	drawtext(text, x, y, fontsize, fontsize);
}

bool textButton::mouseOver()
{
	bool retval = FALSE;
	if (mousex >= x && mousex <= x + width)
	{
		if (mousey >= y && mousey <= y + width)
		{
			retval = TRUE;
		}
	}
	return retval;
}

toggle::toggle()
{
	active = FALSE;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	normalTex = blank;
	enabledTex = blank;
	enabled = false;
}

toggle::toggle(char* inname, int inx, int iny, int inwidth, int inheight, int innormalTex, int inenabledTex)
{
	strcpy_s(name, 40, inname);
	active = TRUE;
	x = inx;
	y = iny;
	width = inwidth;
	height = inheight;
	normalTex = innormalTex;
	enabledTex = inenabledTex;
	enabled = FALSE;
}

void toggle::man()
{
	if (mousex >= x && mousex <= x + width)
	{
		if (mousey >= y && mousey <= y + width)
		{
			if (leftclick)
			{
				enabled = !enabled;
			}
		}
	}
}

void toggle::draw()
{
	if (enabled == TRUE)
	{
		placeimageeasy(enabledTex, x, y, width, height, TRUE);
	}
	else
	{
		placeimageeasy(normalTex, x, y, width, height, TRUE);
	}
}

bool toggle::compare(toggle inTog)
{
	bool retval = TRUE;
	if (x != inTog.x) { retval = FALSE; }
	if (y != inTog.y) { retval = FALSE; }
	if (width != inTog.width) { retval = FALSE; }
	if (height != inTog.height) { retval = FALSE; }
	return retval;
}

bool toggle::mouseOver()
{
	bool retval = FALSE;
	if (mousex >= x && mousex <= x + width)
	{
		if (mousey >= y && mousey <= y + width)
		{
			retval = TRUE;
		}
	}
	return retval;
}